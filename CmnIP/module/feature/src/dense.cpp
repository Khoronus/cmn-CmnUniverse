/**
* @file dense.cpp
* @brief Body of the relative header file.
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
* @version 1.0.0.1
*
*/


#include "feature/inc/feature/dense.hpp"

namespace CmnIP
{
namespace feature
{

//-----------------------------------------------------------------------------
void Dense::linear6histo(const cv::Mat &src, bool show, cv::Mat &output)
{
	// Define the histogram range and bin
	int histBin = 8, histMinRange = 0, histMaxRange = 256;
	cv::Mat hist, imagehist(400, 512, CV_8UC3, cv::Scalar::all(0));
	output = cv::Mat(8, 6, CV_32FC1, cv::Scalar::all(0));
	cv::Mat dst;

	// Get 4 gabor directions
	for (int i = 0; i < 4; i++)
	{
		filter::FilterLinear::get_gabor(src, 31, 2, 25,
		180.0f / 4.0f * (float)i, 90, dst);
		//std::cout << dst << std::endl;
		// Calculate the histogram
		cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		//std::cout << dst << std::endl;
		if (show && !src.empty()) cv::imshow("src", src);
		if (show && !dst.empty()) cv::imshow("Result", dst);
		//cv::imwrite("gabor.png", dst);
		Image2Histogram::grayscale(dst, hist, histBin, histMinRange, 
			histMaxRange, true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
		hist.copyTo(output(cv::Rect(i, 0, 1, histBin)));

		if (show) {
			cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
			draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400, 
				histBin, cv::Scalar(0, 0, 255));
			cv::imshow("hist", imagehist);
		}
	}

	// Laplace
	filter::FilterLinear::get_laplace(src, 3, 1, 0, CV_16S,
	cv::Size(3, 3), true, dst);
	// Display the result
	cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	if (show && !dst.empty()) cv::imshow("Result", dst);
	//cv::imwrite("laplace.png", dst);
	// Calculate the histogram
	Image2Histogram::grayscale(dst, hist, histBin, histMinRange, 
		histMaxRange, true, false);
	cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
	hist.copyTo(output(cv::Rect(4, 0, 1, histBin)));
	if (show) { 
		cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
		draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400, 
			histBin, cv::Scalar(0, 255));
		cv::imshow("hist", imagehist);
	}

	// Laplace2
	cv::Mat kernel;
	filter::FilterLinear::create_laplace_filter(kernel);
	filter::FilterLinear::filter2D(src, kernel, dst);
	// Display the result
	cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	if (show && !dst.empty()) cv::imshow("Result", dst);
	//cv::imwrite("laplace2.png", dst);
	// Calculate the histogram
	Image2Histogram::grayscale(dst, hist, histBin, histMinRange, 
		histMaxRange, true, false);
	cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
	hist.copyTo(output(cv::Rect(5, 0, 1, histBin)));
	if (show) { 
		cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
		draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400, 
			histBin, cv::Scalar(255));
		cv::imshow("hist", imagehist);
	}
}
//-----------------------------------------------------------------------------
void Dense::linear10histo(const cv::Mat &src, bool show, cv::Mat &output)
{
	// Define the histogram range and bin
	int histBin = 8, histMinRange = 0, histMaxRange = 256;
	cv::Mat hist, imagehist(400, 512, CV_8UC3, cv::Scalar::all(0));
	output = cv::Mat(8, 10, CV_32FC1, cv::Scalar::all(0));
	cv::Mat dst;

	// Get 4 gabor directions
	for (int i = 0; i < 4; i++)
	{
		filter::FilterLinear::get_gabor(src, 31, 2, 25,
		180.0f / 4.0f * (float)i, 90, dst);
		//std::cout << dst << std::endl;
		// Calculate the histogram
		cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		//std::cout << dst << std::endl;
		if (show && !src.empty()) cv::imshow("src", src);
		if (show && !dst.empty()) cv::imshow("Result", dst);
		//cv::imwrite("gabor.png", dst);
		Image2Histogram::grayscale(dst, hist, histBin, histMinRange, 
			histMaxRange, true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
		hist.copyTo(output(cv::Rect(i, 0, 1, histBin)));

		if (show) {
			cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
			draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400,
				histBin, cv::Scalar(0, 0, 255));
			cv::imshow("hist", imagehist);
		}
	}

	// Laplace
	filter::FilterLinear::get_laplace(src, 3, 1, 0, CV_16S,
	cv::Size(3, 3), true, dst);
	// Display the result
	cv::normalize(dst, dst, 0, 256, cv::NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	if (show && !dst.empty()) cv::imshow("Result", dst);
	//cv::imwrite("laplace.png", dst);
	// Calculate the histogram
	Image2Histogram::grayscale(dst, hist, histBin, histMinRange, 
		histMaxRange, true, false);
	cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX);
	hist.copyTo(output(cv::Rect(4, 0, 1, histBin)));
	if (show) { 
		cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
		draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400, 
			histBin, cv::Scalar(0, 255));
		cv::imshow("hist", imagehist);
	}

	// HSV
	{
		cv::Mat hsv;
		/// Convert to HSV
		cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
		std::vector<cv::Mat> planes;
		cv::split(hsv, planes);
		// hue varies from 0 to 179, saturation from 0 to 255
		float h_ranges[] = { 0, 180 };
		float s_ranges[] = { 0, 256 };
		const float* hranges = { h_ranges };
		const float* sranges = { s_ranges };
		// Use the o-th and 1-st channels
		int channels[] = { 0, 1 };
		/// Calculate the histograms for the HSV images
		cv::calcHist(&planes[0], 1, 0, cv::Mat(), hist, 1, &histBin, &hranges,
			true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
		hist.copyTo(output(cv::Rect(5, 0, 1, histBin)));
		if (show) { 
			cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
			draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400, 
				histBin, cv::Scalar(255));
			cv::imshow("hist", imagehist);
		}
		cv::calcHist(&planes[1], 1, 0, cv::Mat(), hist, 1, &histBin, &sranges,
			true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
		hist.copyTo(output(cv::Rect(6, 0, 1, histBin)));
		if (show) { 
			cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
			draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400,
				histBin, cv::Scalar(255));
			cv::imshow("hist", imagehist);
		}
	}

	// RGB
	{
		std::vector<cv::Mat> planes;
		cv::split(src, planes);
		// hue varies from 0 to 179, saturation from 0 to 255
		float ranges[] = { 0, 256 };
		const float* vranges = { ranges };
		// Use the o-th and 1-st channels
		int channels[] = { 0, 1 };
		/// Calculate the histograms for the HSV images
		for (int i = 0; i < 3; i++)
		{
			cv::calcHist(&planes[i], 1, 0, cv::Mat(), hist, 1, &histBin, &vranges,
				true, false);
			cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
			hist.copyTo(output(cv::Rect(7 + i, 0, 1, histBin)));
			if (show) { 
				cv::normalize(hist, hist, 0, 256, cv::NORM_MINMAX);
				draw::Histogram2Image::onechannel_hist(imagehist, hist, 512, 400,
					histBin, cv::Scalar(255, 255));
				cv::imshow("hist", imagehist);
			}
		}
	}

}



}	// namespace feature
}	// namespace CmnIP

