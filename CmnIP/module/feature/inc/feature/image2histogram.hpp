/**
* @file histogram.cpp
* @brief Example of the drawing organized images.
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


#ifndef CMNIP_FEATURE_IMAGE2HISTOGRAM_HPP__
#define CMNIP_FEATURE_IMAGE2HISTOGRAM_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


namespace CmnIP
{
namespace feature
{


/** @brief Perform a dense histogram estimation over an input image.
*/
class Image2Histogram
{
public:

	/** @brief Generate an histogram data over a grayscale image.
	*/
	static int grayscale(const cv::Mat &src, cv::Mat &dst, const int histSize,
		const int histMinRange, const int histMaxRange, bool uniform, bool accumulate)
	{
		if (!src.data) { return 0; }

		/// Set the ranges ( for B,G,R) )
		float range[] = { static_cast<float>(histMinRange), 
		  static_cast<float>(histMaxRange) };
		const float* histRange = { range };

		cv::Mat gray;
		if (src.channels() == 1) {
			gray = src;
		} else {
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(src, gray, CV_BGR2GRAY);
#elif CV_MAJOR_VERSION == 4
			cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
#endif
		}

		/// Compute the histograms:
		cv::calcHist(&gray, 1, 0, cv::Mat(), dst, 1, &histSize, &histRange, uniform,
			accumulate);
		cv::normalize(dst, dst, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	}


	/** @brief Generate a 2 channel histogram in a hsv color space (hs)
	*/
	static void hs_on_hsv(const cv::Mat &src, cv::MatND &hist) {
		cv::Mat hsv;
		/// Convert to HSV
		cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

		/// Using 50 bins for hue and 60 for saturation
		int h_bins = 50; int s_bins = 60;
		//int h_bins = 180; int s_bins = 256;
		int histSize[] = { h_bins, s_bins };

		// hue varies from 0 to 179, saturation from 0 to 255
		float h_ranges[] = { 0, 180 };
		float s_ranges[] = { 0, 256 };

		const float* ranges[] = { h_ranges, s_ranges };

		// Use the o-th and 1-st channels
		int channels[] = { 0, 1 };

		/// Calculate the histograms for the HSV images
		cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 2, histSize, ranges,
			true, false);
		cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	}
};


}	// namespace feature
}	// namespace CmnIP

#endif /* CMNIP_FEATURE_IMAGE2HISTOGRAM_HPP__ */

