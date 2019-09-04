/**
* @file algorithm.hpp
* @brief Virtual class to manage algorithms
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR/AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#include "histogram/inc/histogram/equalizeimage.hpp"


namespace CmnIP
{
namespace histogram
{

//-----------------------------------------------------------------------------
void EqualizeImage::color(const cv::Mat &src, int channel, float value,
	cv::Mat &out, bool copy)
{
	std::vector<cv::Mat> src_channels;
	cv::split(src, src_channels); //split the image into channels
	src_channels[channel] *= value;
	cv::merge(src_channels, out); //merge 3 channels including the 
}
//-----------------------------------------------------------------------------
void EqualizeImage::color(const cv::Mat &img, const cv::Mat &ref, int channel,
	cv::Mat &out, bool copy)
{
	cv::Mat src = img;// .clone();
	if (copy) src = img.clone();
	std::vector<cv::Mat> src_channels, ref_channels;
	cv::Mat src_y = src;
	cv::Mat ref_y = ref;
	cv::split(src_y, src_channels); //split the image into channels
	cv::split(ref_y, ref_channels); //split the image into channels
	cv::Scalar r_mean = cv::mean(ref_channels[channel]);
	cv::Scalar s_mean = cv::mean(src_channels[channel]);
	src_channels[channel] *= ((float)r_mean[0] / (float)s_mean[0]);
	std::cout << r_mean << " " << s_mean << std::endl;
	cv::merge(src_channels, src_y); //merge 3 channels including the 
		                            //modified 1st channel into one image
	out = src;
}
//-----------------------------------------------------------------------------
void EqualizeImage::color(const cv::Mat &img, const cv::Mat &ref, int channel,
	float alpha, cv::Mat &out, bool copy)
{
	cv::Mat src = img;// .clone();
	if (copy) src = img.clone();
	std::vector<cv::Mat> src_channels, ref_channels;
	cv::Mat src_y = src;
	cv::Mat ref_y = ref;
	cv::split(src_y, src_channels); //split the image into channels
	cv::split(ref_y, ref_channels); //split the image into channels
	cv::Scalar r_mean = cv::mean(ref_channels[channel]);
	cv::Scalar s_mean = cv::mean(src_channels[channel]);
	src_channels[channel] = (src_channels[channel] * alpha) + 
		(src_channels[channel] * ((float)r_mean[0] / (float)s_mean[0])) * (1 - alpha);
	//std::cout << r_mean << " " << s_mean << std::endl;
	cv::merge(src_channels, src_y); //merge 3 channels including the 
	//modified 1st channel into one image
	out = src;
}
//-----------------------------------------------------------------------------
void EqualizeImage::color(const cv::Mat &img, const cv::Mat &ref, const cv::Mat &mprob,
	const cv::Mat &mprobneg, int channel,
	cv::Mat &out, bool copy)
{
	cv::Mat src = img;// .clone();
	if (copy) src = img.clone();
	std::vector<cv::Mat> src_channels, ref_channels;
	cv::Mat src_y = src;
	cv::Mat ref_y = ref;
	cv::split(src_y, src_channels); //split the image into channels
	cv::split(ref_y, ref_channels); //split the image into channels
	cv::Scalar r_mean = cv::mean(ref_channels[channel]);
	cv::Scalar s_mean = cv::mean(src_channels[channel]);
	cv::Mat tmp = src_channels[channel] * ((float)r_mean[0] / (float)s_mean[0]);
	cv::Mat channelfloat, channelfloatadj;
	src_channels[channel].convertTo(channelfloat, CV_32F);
	tmp.convertTo(channelfloatadj, CV_32F);

	cv::Mat result(channelfloat.size(), CV_32F);
	for (int y = 0; y < result.rows; y++)
	{
		for (int x = 0; x < result.cols; x++)
		{
			//std::cout << x << " " << y << " " << channelfloat.at<float>(y, x) << " " << mprob.at<float>(y, x) << " " <<
				//channelfloatadj.at<float>(y, x) << " " << mprobneg.at<float>(y, x) << std::endl;

			result.at<float>(y, x) = channelfloat.at<float>(y, x) * mprob.at<float>(y, x) +
				channelfloatadj.at<float>(y, x) * mprobneg.at<float>(y, x);

			//std::cout << x << " " << y << " " << result.at<float>(y, x) << std::endl;

		}
	}
	result.convertTo(src_channels[channel], CV_8U);
	std::cout << r_mean << " " << s_mean << std::endl;
	cv::merge(src_channels, src_y); //merge 3 channels including the 
	//modified 1st channel into one image
	out = src;
}
//-----------------------------------------------------------------------------
void EqualizeImage::adjust_intensity(const cv::Mat &img, const cv::Mat &ref, cv::Mat &out,
	bool copy)
{
	cv::Mat src = img;// .clone();
	if (copy) src = img.clone();
	std::vector<cv::Mat> src_channels, ref_channels;
	cv::Mat src_y, ref_y;

	cv::cvtColor(src, src_y, cv::COLOR_BGR2YCrCb); //change the color image 
		                                        // from BGR to YCrCb format
	cv::split(src_y, src_channels); //split the image into channels
	cv::cvtColor(ref, ref_y, cv::COLOR_BGR2YCrCb); //change the color image
		                                        // from BGR to YCrCb format
	cv::split(ref_y, ref_channels); //split the image into channels
	cv::Scalar r_mean = cv::mean(ref_channels[0]);
	cv::Scalar s_mean = cv::mean(src_channels[0]);
	src_channels[0] *= ((float)r_mean[0] / (float)s_mean[0]);
	std::cout << r_mean << " " << s_mean << std::endl;
	cv::merge(src_channels, src_y); //merge 3 channels including the 
		                            // modified 1st channel into one image
	cvtColor(src_y, src, cv::COLOR_YCrCb2BGR); //change the color image from 
		                                    //YCrCb to BGR format (to display 
		                                    //image properly)
	out = src;
}
//-----------------------------------------------------------------------------
int EqualizeImage::equalize_intensity(const cv::Mat &img, cv::Mat &out)
{
	if (img.empty()) //if unsuccessful, exit the program
	{
		std::cout << "Image cannot be loaded..!!" << std::endl;
		return 0;
	}

	std::vector<cv::Mat> channels;
	cv::Mat img_hist_equalized;

	cv::cvtColor(img, img_hist_equalized, cv::COLOR_BGR2YCrCb); //change 
		// the color image from BGR to YCrCb format

	cv::split(img_hist_equalized, channels); //split the image into 
		// channels

	cv::equalizeHist(channels[0], channels[0]); //equalize histogram on 
		// the 1st channel (Y)

	cv::merge(channels, img_hist_equalized); //merge 3 channels including 
		// the modified 1st channel into one image

	cv::cvtColor(img_hist_equalized, img_hist_equalized, 
		cv::COLOR_YCrCb2BGR); //change the color image from YCrCb to BGR 
		                        //format (to display image properly)
	out = img_hist_equalized;
	return 1;
}
//-----------------------------------------------------------------------------
int EqualizeImage::change_contrast(cv::Mat &img, double alpha, cv::Mat &out)
{
	if (img.empty())
	{
		std::cout << "Image cannot be loaded..!!" << std::endl;
		return 0;
	}
	cv::Mat imgC;
	img.convertTo(imgC, -1, alpha, 0); //increase the contrast (double)

	out = imgC;
	return 1;
}
//-----------------------------------------------------------------------------
void EqualizeImage::rgbclahe(cv::Mat &src, cv::Mat &out) {
	// READ RGB color image and convert it to Lab
	cv::Mat bgr_image = src;
	cv::Mat lab_image;
	cv::cvtColor(bgr_image, lab_image, cv::COLOR_BGR2Lab);

	// Extract the L channel
	std::vector<cv::Mat> lab_planes(3);
	cv::split(lab_image, lab_planes);  // now we have the L image in 
		                                // lab_planes[0]

	// apply the CLAHE algorithm to the L channel
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst);

	// Merge the the color planes back into an Lab image
	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, lab_image);

	// convert back to RGB
	cv::Mat image_clahe;
	cv::cvtColor(lab_image, image_clahe, cv::COLOR_Lab2BGR);

	out = image_clahe;
}

} // namespace histogram
} // namespace CmnIP
