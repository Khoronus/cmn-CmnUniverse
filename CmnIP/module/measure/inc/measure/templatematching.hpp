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

#ifndef CMNIP_MEASURE_TEMPLATEMATCHING_HPP__
#define CMNIP_MEASURE_TEMPLATEMATCHING_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief Class to perform the template matching.

Class to perform the template matching.
*/
class TemplateMatching
{
public:

	/** @brief Perform the template matching.

	Perform the template matching and extract a region with a degined offset.
	@param[in] image The source image.
	@param[in] model Template to find inside the image. The size MUST be
	smaller than the source image.
	@param[in] match_method Matching method used. For more information search
	in the OpenCV documentation (matchTemplate)
	@param[in] show If TRUE it displays the match result.
	@param[out] region_out Rectangle which contains the extracted region.
	@param[out] likelihood Probability of the correlation.
	@return Return 1 in case of success. 0 otherwise.
	*/
	static int region(const cv::Mat image, const cv::Mat &model, int match_method,
		bool show, cv::Rect &region_out, double &likelihood)
	{
		// check that the image data is not empty
		if (image.empty()) return 0;
		if (model.empty()) return 0;
		if (model.cols > image.cols || model.rows > image.rows) return 0;
		// Check that the image and model size are compatible.
		//if (image.size() < model.size()) return 0;
		// Capture the first frame to get the image dimension
		cv::Mat result;

		/// Create the result matrix
		int result_cols = image.cols - model.cols + 1;
		int result_rows = image.rows - model.rows + 1;

		result.create(result_cols, result_rows, CV_32FC1);

		// Do the Matching and Normalize
		cv::matchTemplate(image, model, result, match_method);
		//cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

		// Localizing the best match with minMaxLoc
		double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
		cv::Point matchLoc;
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

		//std::cout << "MinMax: " << minVal << " " << maxVal << std::endl;
		likelihood = maxVal;

		// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all 
		// the other methods, the higher the better
#if CV_MAJOR_VERSION == 3
		if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		} else {
			matchLoc = maxLoc;
		}
#elif CV_MAJOR_VERSION == 4
		if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		} else {
			matchLoc = maxLoc;
		}
#endif

		// Expected lips region position
		region_out = cv::Rect(matchLoc, cv::Point(matchLoc.x + model.cols,
			matchLoc.y + model.rows));

		// Show me what you got
		if (show)
		{
			cv::Mat img_display = image.clone();
			// Track region
			cv::rectangle(img_display, matchLoc, cv::Point(matchLoc.x + model.cols,
				matchLoc.y + model.rows), cv::Scalar::all(0), 2, 8, 0);
			// Track region
			cv::rectangle(result, matchLoc - cv::Point(model.cols / 2, model.rows / 2),
				cv::Point(matchLoc.x + model.cols / 2, matchLoc.y + model.rows / 2),
				cv::Scalar(0, 0, 255), 3, 8, 0);

			cv::imshow("template_display", img_display);
			cv::imshow("template_result_window", result);
		}

		return 1;
	}

};


} // namespace measure
} // namespace CmnIP

#endif /* CMNIP_MEASURE_TEMPLATEMATCHING_HPP__ */
