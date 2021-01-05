/**
* @file image_matching.hpp
* @brief Performs simple template matching between images.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNIP_MEASURE_IMAGEMATCHING_HPP__
#define CMNIP_MEASURE_IMAGEMATCHING_HPP__

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

#include "templatematching.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief Define the Timestamp
*/
typedef int TIMESTAMP;

/** @brief Make a smart function to manage the template for pattern recognition
*/
class TemplateContainer
{
public:

	TemplateContainer() {}

	TemplateContainer(const cv::Mat &src, TIMESTAMP timestamp) {
		src_ = src;
		timestamp_ = timestamp;
	}

	cv::Mat src_;
	TIMESTAMP timestamp_;
};

/** @brief Enum with the possible match condition considered with the system.
*/
enum MATCH_CONDITION
{
	kMatchConditionUnknown = 0,
	kMatchConditionHighLikelihood = 1,
	kMatchConditionLowLikelihood = 2
};


// Function 1: Stable position
// Cross correlation
// Images distant n frames match with likelihood > t.

/** @brief Class to estimate if an image changed compared to a reference.

Class to estimate if an image changed compared to a reference.
*/
class ImageChanged
{
public:

	ImageChanged() {}

	ImageChanged(double likelihood_min, int timestamp_diff) :
		likelihood_min_(likelihood_min), timestamp_diff_(timestamp_diff) {
		int c = 512;// 1000 / 30;
		int sec = 512;// 10;
		img_ts_ = cv::Mat::zeros(sec, c, CV_8UC3);
	}

	/** @brief Set the thresholds
	*/
	void set(double likelihood_min, int timestamp_diff);

	/** @brief Estimate if there is a change with the reference image.
	*/
	bool is_changed(const cv::Mat &src, TIMESTAMP ts, bool show,
		double &likelihood);

private:

	/** @brief Template to match the reference image.
	*/
	TemplateContainer template_;
	/** @brief It defines the minimum likelihood allowed to consider an
	           image similar to the reference image.
	*/
	double likelihood_min_;
	/** @brief It defines the minimum number of frames necessary to compare
	           an image with the reference image.
	*/
	int timestamp_diff_;

	/** @brief Container with the debug image to estimate if the source 
	           changed.
	*/
	cv::Mat img_ts_;


	/** @brief Function to estimate the match between tw
	*/
	MATCH_CONDITION match(TemplateContainer &tc, const cv::Mat &curr,
		TIMESTAMP ts, double likelihood_min,
		int timestamp_diff, double &likelihood_out);

	/** @brief Debug function to visualize if the image match or not
	*/
	void debug_ts_visualizer(cv::Mat &img_ts_, MATCH_CONDITION condition,
		TIMESTAMP ts_);
};


} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_IMAGEMATCHING_HPP__
