/**
* @file sample_numericsystem_numericsystem.cpp
* @brief Sample dynamic.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "photo/inc/photo/photo_headers.hpp"

namespace
{

/** @brief Perform an affine transformation to rotate an image.
*/
void rotate(cv::Mat& image, double angle, cv::Mat &out)
{
	cv::Point2f src_center(image.cols / 2.0F, image.rows / 2.0F);

	cv::Mat rot_matrix = getRotationMatrix2D(src_center, angle, 1.0);

	cv::Mat rotated_img(cv::Size(image.size().height, image.size().width), image.type());

	cv::warpAffine(image, rotated_img, rot_matrix, image.size());
	out = rotated_img;
}


std::string type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}


void pow_matrix(const cv::Mat &m, float p, cv::Mat &out)
{
	out = cv::Mat(m.size(), CV_32FC2);
	int kw = m.cols;
	int kh = m.rows;
	for (int y = 0; y < kh; y++)
	{
		for (int x = 0; x < kw; x++)
		{
			for (int c = 0; c < 2; c++)
			{
				out.at<cv::Vec2f>(y, x)[c] = std::pow(m.at<cv::Vec2f>(y, x)[c], p);
			}
		}
	}
}

void sum_cols(const cv::Mat &m, cv::Mat &out)
{
	int kw = m.cols;
	int kh = m.rows;
	std::cout << kw << "<>" << kh << std::endl;
	out = cv::Mat(kh, kw, CV_32F);
	std::cout << kw << " " << kh << std::endl;
	for (int y = 0; y < kh; y++)
	{
		for (int x = 0; x < kw; x++)
		{
			float s = 0;
			for (int c = 0; c < 2; c++)
			{
				s += m.at<cv::Vec2f>(y, x)[c];
			}
			out.at<float>(y, x) = s;
		}
	}
}

void newaxis(const cv::Mat &m, cv::Mat &out)
{
	int kw = m.cols;
	int kh = m.rows;
	out = cv::Mat(kw, 1, CV_32FC2);
	for (int y = 0; y < kh; y++)
	{
		for (int x = 0; x < kw; x++)
		{
			out.at<cv::Vec2f>(x, 0)[y] = m.at<float>(y, x);
		}
	}

}

void divide(const cv::Mat &m, const cv::Mat &div, cv::Mat &out)
{
	int kw = m.cols;
	int kh = m.rows;
	out = m.clone();
	for (int y = 0; y < kh; y++)
	{
		for (int x = 0; x < kw; x++)
		{
			for (int c = 0; c < 2; c++)
			{
				out.at<cv::Vec2f>(y, x)[c] = m.at<cv::Vec2f>(y, x)[c] /
					div.at<float>(y, x);
			}
		}
	}
}

void roll(const cv::Mat &src, int w, int h, cv::Mat &out)
{
	out = cv::Mat(src.size(), src.type());
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			int yy = y + h;
			int xx = x + w;
			if (yy >= src.rows) yy = yy - src.rows;
			if (xx >= src.cols) xx = xx - src.cols;
			out.at<float>(y, x) =
				src.at<float>(yy, xx);
		}
	}
}

int sample_dft(cv::Mat &src)
{
	if (false)
	{
		//{
		//	cv::Mat a(3, 3, CV_32F);
		//	a.at<float>(0, 0) = 1;
		//	a.at<float>(0, 1) = 2;
		//	a.at<float>(0, 2) = 3;
		//	a.at<float>(1, 0) = 4;
		//	a.at<float>(1, 1) = 5;
		//	a.at<float>(1, 2) = 6;
		//	a.at<float>(2, 0) = 7;
		//	a.at<float>(2, 1) = 8;
		//	a.at<float>(2, 2) = 9;
		//	std::cout << a << std::endl;
		//	cv::Mat kernel_dft;
		//	cv::dft(a, kernel_dft, DFT_COMPLEX_OUTPUT);
		//	std::cout << kernel_dft << std::endl;
		//	return 0;
		//}

		//cv::Mat a(3, 3, CV_32FC2);
		//a.at<cv::Vec2f>(0, 0)[0] = 1;
		//a.at<cv::Vec2f>(0, 1)[0] = 2;
		//a.at<cv::Vec2f>(0, 2)[0] = 3;
		//a.at<cv::Vec2f>(1, 0)[0] = 4;
		//a.at<cv::Vec2f>(1, 1)[0] = 5;
		//a.at<cv::Vec2f>(1, 2)[0] = 6;
		//a.at<cv::Vec2f>(2, 0)[0] = 7;
		//a.at<cv::Vec2f>(2, 1)[0] = 8;
		//a.at<cv::Vec2f>(2, 2)[0] = 9;

		//a.at<cv::Vec2f>(0, 0)[1] = 10;
		//a.at<cv::Vec2f>(0, 1)[1] = 11;
		//a.at<cv::Vec2f>(0, 2)[1] = 12;
		//a.at<cv::Vec2f>(1, 0)[1] = 13;
		//a.at<cv::Vec2f>(1, 1)[1] = 14;
		//a.at<cv::Vec2f>(1, 2)[1] = 15;
		//a.at<cv::Vec2f>(2, 0)[1] = 16;
		//a.at<cv::Vec2f>(2, 1)[1] = 17;
		//a.at<cv::Vec2f>(2, 2)[1] = 18;

		cv::Mat a(3, 3, CV_32F);
		a.at<float>(0, 0) = 1;
		a.at<float>(0, 1) = 2;
		a.at<float>(0, 2) = 3;
		a.at<float>(1, 0) = 4;
		a.at<float>(1, 1) = 5;
		a.at<float>(1, 2) = 6;
		a.at<float>(2, 0) = 7;
		a.at<float>(2, 1) = 8;
		a.at<float>(2, 2) = 9;
		std::cout << a << std::endl;
		cv::dft(a, a, cv::DFT_COMPLEX_OUTPUT);

		std::cout << a << std::endl;
		cv::Mat a2;
		pow_matrix(a, 2.0f, a2);
		std::cout << a2 << std::endl;
		for (int c = 0; c < a2.channels(); c++)
		{
			for (int y = 0; y < a2.rows; y++)
			{
				for (int x = 0; x < a2.cols; x++)
				{
					std::cout << a2.at<cv::Vec2f>(y, x)[c] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		cv::Mat a3;
		sum_cols(a2, a3);
		std::cout << "sum_cols: " << a3 << std::endl;
		cv::Mat a5;// = a / a3;
		divide(a, a3, a5);
		std::cout << a.cols << " " << a.rows << " " << a.channels() << " -> " <<
			a3.cols << " " << a3.rows << " " << a3.channels() << std::endl;
		std::cout << a5 << std::endl;
		//cv::Mat a4;
		//float noise = std::pow(10, -0.1 * 25);
		//std::cout << "noise: " << noise << std::endl;
		//a3 += noise;
		//newaxis(a3, a4);
		//std::cout << "a4: " << a4 << std::endl;
		//cv::Mat a5;
		//divide(a, a4, a5);
		//std::cout << a5 << std::endl;
		//std::cout << a.cols << " " << a4.cols << " " << a.rows << " " << a4.cols << " " <<
		//	a.channels() << " " << a4.channels() << std::endl;
		return 0;
	}

	cv::Mat I;
	if (src.channels() == 3) {
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src, I, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(src, I, cv::COLOR_BGR2GRAY);
#endif
	} else {
		I = src;
	}
	if (I.empty())
		return -1;

	I.convertTo(I, CV_32F);
	I /= 255;

	cv::Mat padded;                            //expand input image to optimal size
	int m = cv::getOptimalDFTSize(I.rows);
	int n = cv::getOptimalDFTSize(I.cols); // on the border add zero values
	cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	// make some blur operation

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	cv::dft(complexI, complexI, cv::DFT_COMPLEX_OUTPUT);            // this way the result may fit in the source matrix


	// <BLA BLA BLA>
	float noise = std::pow(10, -0.1 * 25);
	std::cout << "noise: " << noise << std::endl;

	//cv::namedWindow("kernel", CV_WINDOW_NORMAL);
	cv::Mat kernel_(65, 65, CV_8U, cv::Scalar::all(0));
#if CV_MAJOR_VERSION == 3
	cv::circle(kernel_, cv::Point(kernel_.cols / 2, kernel_.rows / 2), 7, 
		cv::Scalar::all(255), -1, CV_AA);
#else if CV_MAJOR_VERSION == 4
	cv::circle(kernel_, cv::Point(kernel_.cols / 2, kernel_.rows / 2), 7, 
		cv::Scalar::all(255), -1, cv::LINE_AA);
#endif
	cv::imshow("kernel", kernel_);
	kernel_.convertTo(kernel_, CV_32F);
	kernel_ /= 255.0f;
	cv::Scalar scalar = cv::sum(kernel_);
	std::cout << "sum " << scalar[0] << std::endl;
	//return 0;
	kernel_ /= scalar[0];
	//std::cout << kernel_ << std::endl;
	//return 0;
	cv::Mat mkernel(complexI.size(), kernel_.type(), cv::Scalar::all(0));
	kernel_.copyTo(mkernel(cv::Rect(0, 0, kernel_.cols, kernel_.rows)));
	cv::Mat kernel_dft;
	cv::dft(mkernel, kernel_dft, cv::DFT_COMPLEX_OUTPUT, kernel_.rows);
	std::cout << "kernel : " << kernel_dft.cols << " " <<
		kernel_dft.rows << " " << kernel_dft.channels() << " " <<
		type2str(kernel_dft.type()) << std::endl;


	//std::cout << kernel_dft << std::endl;
	//return 0;
	cv::Mat partColorFourieResult;
	cv::Mat partColorResultComplexChannel;



	//int kw = kernel_dft.cols;
	//int kh = kernel_dft.rows;
	//int kc = kernel_dft.channels();
	//std::cout << kw << " " << kh << " " << kc << " " << type2str(kernel_dft.type()) << std::endl;
	//system("pause");
	//for (int y = 0; y < kh; y++)
	//{
	//	for (int x = 0; x < kw; x++)
	//	{
	//		for (int c = 0; c < 2; c++)
	//		{
	//			kernel_dft.at<cv::Vec2f>(y, x)[c] = std::pow(kernel_dft.at<cv::Vec2f>(y, x)[c], 2);
	//		}
	//	}
	//}

	cv::Mat mpow2;
	pow_matrix(kernel_dft, 2, mpow2);
	cv::Mat msumcols;
	sum_cols(mpow2, msumcols);
	msumcols += noise;
	//cv::Mat mnewaxis;
	//newaxis(msumcols, mnewaxis);
	//std::cout << "-> " << mnewaxis.cols << " " << mnewaxis.rows << " " << mnewaxis.channels() << std::endl;
	cv::Mat mdivide;
	divide(kernel_dft, msumcols, mdivide);
	kernel_dft = mdivide;

	//kernel_dft *= kernel_dft;
	//std::cout << kernel_dft << std::endl;

	std::cout << "Spectrum: " << complexI.cols << " " << complexI.rows << " " << complexI.channels() << " " <<
		kernel_dft.cols << " " << kernel_dft.rows << " " << kernel_dft.channels() << std::endl;

	mulSpectrums(complexI, kernel_dft, partColorFourieResult, 0);
	idft(partColorFourieResult, partColorResultComplexChannel, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
	cv::imshow("resB", partColorResultComplexChannel);

	// Roll the image
	cv::Mat partColorResultComplexChannelclone = partColorResultComplexChannel.clone();
	roll(partColorResultComplexChannelclone, kernel_.cols / 2,
		kernel_.rows / 2, partColorResultComplexChannel);
	//// Roll the image
	//int h = kernel_.rows / 2;
	//int w = kernel_.cols / 2;
	//std::cout << h << " " << w << std::endl;
	//cv::Mat partColorResultComplexChannelclone = partColorResultComplexChannel.clone();
	//for (int y = 0; y < partColorResultComplexChannel.rows; y++)
	//{
	//	for (int x = 0; x < partColorResultComplexChannel.cols; x++)
	//	{
	//		int yy = y + h;
	//		int xx = x + w;
	//		if (yy >= partColorResultComplexChannel.rows) yy = yy - partColorResultComplexChannel.rows;
	//		if (xx >= partColorResultComplexChannel.cols) xx = xx - partColorResultComplexChannel.cols;
	//		partColorResultComplexChannel.at<float>(y, x) =
	//			partColorResultComplexChannelclone.at<float>(yy, xx);
	//	}
	//}

	//cv::normalize(partColorResultComplexChannel, partColorResultComplexChannel, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	cv::imshow("resA", partColorResultComplexChannel);

	// </BLA BLA BLA>





	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	cv::Mat mmagnitude, mangle;
	cv::cartToPolar(planes[0], planes[1], mmagnitude, mangle);
	//cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	cv::Mat magI = mmagnitude;// planes[0];

	magI += cv::Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	// Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
#if CV_MAJOR_VERSION == 3
	cv::normalize(magI, magI, 0, 1, CV_MINMAX); 
#else if CV_MAJOR_VERSION == 4
	cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);
#endif

	cv::imshow("Input Image", I);    // Show the result
	cv::imshow("spectrum magnitude", magI);
#if CV_MAJOR_VERSION == 3
	cv::normalize(mangle, mangle, 0, 1, CV_MINMAX);
#else if CV_MAJOR_VERSION == 4
	cv::normalize(mangle, mangle, 0, 1, cv::NORM_MINMAX);
#endif
	cv::imshow("specturm phase", mangle);
	cv::waitKey(10);

	//calculating the idft
	cv::Mat inverseTransform;
	cv::dft(complexI, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
#if CV_MAJOR_VERSION == 3
	cv::normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
#else if CV_MAJOR_VERSION == 4
	cv::normalize(inverseTransform, inverseTransform, 0, 1, cv::NORM_MINMAX);
#endif
	cv::imshow("Reconstructed", inverseTransform);
	cv::waitKey(0);

	return 0;
}





} // namespace anonymous

// ############################################################################

int main()
{
	std::cout << "Sample Photo Focus" << std::endl;

	//capture.open(filename);
	//cv::Mat frame = cv::imread("../../data/lenablur.jpg");
	cv::Mat frame = cv::imread("../../data/photo.jpg");
	if (frame.empty()) return 0;

	sample_dft(frame);
	return 0;
}




