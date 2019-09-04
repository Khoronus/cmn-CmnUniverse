/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/


#include "filter/inc/filter/filter_headers.hpp"

namespace
{

void hist2image(cv::Mat &image, cv::Mat &hist, int hist_w, int hist_h, 
	int histSize, cv::Scalar &color) {

  // Draw the histograms for B, G and R
  int bin_w = cvRound( (double) hist_w/histSize );

  /// Normalize the result to [ 0, histImage.rows ]
  cv::Mat hist_out;
  cv::normalize(hist, hist_out, 0, image.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  /// Draw for each channel
  for( int i = 1; i < histSize; i++ )
  {
      cv::line( image, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_out.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(hist_out.at<float>(i)) ),
                       color, 2, 8, 0  );
  }
}

int image2histogram(const cv::Mat &src, cv::Mat &dst, const int histSize, 
	const int histMinRange, const int histMaxRange, bool uniform, bool accumulate)
{
  if( !src.data ) { return 0; }

  /// Set the ranges ( for B,G,R) )
  float range[] = { histMinRange, histMaxRange } ;
  const float* histRange = { range };

  cv::Mat gray;
  if (src.channels() == 1) {
	  gray = src;
  } else {
#if CV_MAJOR_VERSION == 3
	  cv::cvtColor(src, gray, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
	  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
#endif
  }

  /// Compute the histograms:
  cv::calcHist( &gray, 1, 0, cv::Mat(), dst, 1, &histSize, &histRange, uniform, 
	  accumulate );
}


/** @brief Function to draw a matrix of floats as colored data
*/
int drawMatrix(const cv::Mat &src, cv::Mat &image)
{
	if (src.empty() || image.empty()) return 0;
	int xbin = image.cols / src.cols;
	int ybin = image.rows / src.rows;

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			int xmin = x * xbin;
			int xmax = (x + 1) * xbin;
			int ymin = y * ybin;
			int ymax = (y + 1) * ybin;
			cv::Rect r(cv::Point(xmin, ymin), cv::Point(xmax, ymax));
			//std::cout << r << std::endl;
			cv::Scalar color(255 - 255 * src.at<float>(y, x), 0, 
				255 * src.at<float>(y, x));
			if (src.at<float>(y, x) == 0) color = cv::Scalar::all(0);
			cv::rectangle(image, r, color, -1);
		}
	}

	return 1;
}

// Convert an image in a histogram
void image2histogram(const cv::Mat &src, cv::Mat &output)
{
	int histBin = 8, histMinRange = 0, histMaxRange = 256;

	cv::Mat hist, imagehist(400, 512, CV_8UC3, cv::Scalar::all(0));

	output = cv::Mat(8, 6, CV_32FC1, cv::Scalar::all(0));

	cv::Mat dst;
	//CmnIP::imgproc::FilterLinear::get_gabor(src, 31, 5, 50, 
	//	180.0f / 8.0f * (float)0, 90, dst);
	for (int i = 0; i < 4; i++)
	{
		CmnIP::filter::FilterLinear::get_gabor(src, 31, 2, 25,
		180.0f / 4.0f * (float)i, 90, dst);
		//std::cout << dst << std::endl;
		// Calculate the histogram
		cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		//std::cout << dst << std::endl;
		cv::imshow("src", src);
		cv::imshow("Result", dst);
		image2histogram(dst, hist, histBin, histMinRange, histMaxRange, true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
		hist.copyTo(output(cv::Rect(i, 0, 1, 8)));
		cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
		hist2image(imagehist, hist, 512, 400, histBin, cv::Scalar(0, 0, 255));
		//std::cout << hist << std::endl;
		cv::imshow("hist", imagehist);
		cv::waitKey();
	}

	// Laplace
	CmnIP::filter::FilterLinear::get_laplace(src, 3, 1, 0, CV_16S,
	cv::Size(3, 3), true, dst);
	// Display the result
	cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	cv::imshow("Result", dst);
	// Calculate the histogram
	image2histogram(dst, hist, histBin, histMinRange, histMaxRange, true, false);
	cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
	hist.copyTo(output(cv::Rect(5, 0, 1, 8)));
	cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
	hist.copyTo(output(cv::Rect(4, 0, 1, 8)));
	cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
	hist2image(imagehist, hist, 512, 400, histBin, cv::Scalar(0, 255));
	//std::cout << hist << std::endl;
	cv::imshow("hist", imagehist);
	cv::waitKey();

	// Laplace2
	cv::Mat kernel;
	CmnIP::filter::FilterLinear::create_laplace_filter(kernel);
	CmnIP::filter::FilterLinear::filter2D(src, kernel, dst);
	// Display the result
	cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	cv::imshow("Result", dst);
	// Calculate the histogram
	image2histogram(dst, hist, histBin, histMinRange, histMaxRange, true, false);
	cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
	hist2image(imagehist, hist, 512, 400, histBin, cv::Scalar(255));
	//std::cout << hist << std::endl;
	cv::imshow("hist", imagehist);
	cv::waitKey();
}

} // namespace anonymous

/**
 * @function main
 */
int main( int argc, char** argv )
{

	cv::Mat src = cv::imread("..\\..\\data\\horses.jpg", 0);
	cv::Mat dst;
	CmnIP::filter::FilterLinear::get_gabor(src, 31, 5, 50,
	180.0f / 8.0f * (float)0, 90, dst);
	cv::imshow("src", src);
	cv::imshow("Result", dst);

	src = dst;

  /// Establish the number of bins
  int histSize = 256;

  /// Set the ranges ( for B,G,R) )
  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  cv::Mat hist;

  /// Compute the histograms:
  cv::calcHist( &src, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, 
	  uniform, accumulate );

  // Draw the histograms for B, G and R
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  cv::Mat hist_out;
  /// Normalize the result to [ 0, histImage.rows ]
  normalize(hist, hist_out, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  /// Draw for each channel
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_out.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(hist_out.at<float>(i)) ),
                       cv::Scalar( 255, 0, 0), 2, 8, 0  );
  }

  /// Display
#if CV_MAJOR_VERSION == 3
  cv::namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
  cv::namedWindow("calcHist Demo", cv::WINDOW_AUTOSIZE);
#endif
  cv::imshow("calcHist Demo", histImage );

  cv::waitKey(0);

  std::cout << "Test the other linear filters" << std::endl;
  {
		cv::Mat src = cv::imread("..\\..\\data\\horses.jpg", 0);
		cv::Mat output;
		image2histogram(src, output);
  }  

  return 0;
}