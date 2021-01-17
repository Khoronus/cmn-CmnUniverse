/**
* @file information.hpp
* @brief Measure the quantity of information in a source.
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

#ifndef CMNIP_MEASURE_INFORMATION_HPP__
#define CMNIP_MEASURE_INFORMATION_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"

#include "cmnipcore/inc/cmnipcore/math_function.hpp"
#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief Class to measure the quantity of information inside a source.

    Class to measure the quantity of information inside a source.
*/
class Information
{
public:

	/** @brief It calculates the entropy of the histogram of intensity of a source
	image.

	It calculates the entropy of the histogram of intensity of a source image.
	*/
	static double entropy(const cv::Mat &src)
	{
		cv::Mat frame = src.clone();
		// Transform the matrix with float values into a
#if CV_MAJOR_VERSION == 3
		if (frame.channels() == 3) {
			cvtColor(frame, frame, CV_BGR2GRAY);
		}
#elif CV_MAJOR_VERSION == 4
		if (frame.channels() == 3) {
			cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
		}
#endif
		int numBins = 256, nPixels;
		float range[] = { 0, 255 };
		double imgEntropy = 0, prob;
		const float* histRange = { range };
		cv::Mat histValues;

		//calculating the histogram
		cv::calcHist(&frame, 1, 0, cv::Mat(), histValues, 1, &numBins, 
			&histRange, true, true);

		nPixels = cv::sum(histValues)[0];

		for (int i = 1; i < numBins; i++)
		{
			prob = histValues.at<float>(i) / nPixels;
			if (prob < FLT_EPSILON)
				continue;
			//imgEntropy += prob*(log(prob) / log(2));
			imgEntropy -= prob * CMNIP_LOG2F(prob);
		}
		return imgEntropy;
	}

	static double entropy_v2(const cv::Mat &src)
	{
		cv::Mat frame = src.clone();
#if CV_MAJOR_VERSION == 3
		if (frame.channels() == 3) {
			cvtColor(frame, frame, CV_BGR2GRAY);
		}
#elif CV_MAJOR_VERSION == 4
		if (frame.channels() == 3) {
			cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
		}
#endif
		// Establish the number of bins
		int histSize = 256;
		// Set the ranges ( for B,G,R) )
		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true; bool accumulate = false;
		cv::Mat hist;
		// Compute the histograms:
		cv::calcHist(&frame, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange,
			uniform, accumulate);
		hist /= frame.total();

		cv::Mat logP;
		cv::log(hist, logP);

		return -1 * cv::sum(hist.mul(logP)).val[0];
	}

};



} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_INFORMATION_HPP__
