/**
* @file image_matching.cpp
* @brief Body of the classes and structures defined in the hpp file.
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
* @original author cforster
* @modified by Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include "measure/inc/measure/imagematching.hpp"

namespace CmnIP {
namespace measure {

//-----------------------------------------------------------------------------
void ImageChanged::set(double likelihood_min, int timestamp_diff) {
	likelihood_min_ = likelihood_min;
	timestamp_diff_ = timestamp_diff;
}
//-----------------------------------------------------------------------------
bool ImageChanged::is_changed(const cv::Mat &src, TIMESTAMP ts, bool show, 
	double &likelihood) {
	//double likelihood = 0;

	// Empty template
	if (template_.src_.empty()) {
		template_ = TemplateContainer(src.clone(), ts);
	}
	if (show && !template_.src_.empty()) cv::imshow("template", template_.src_);
	// Match
	MATCH_CONDITION r = match(template_, src, ts, likelihood_min_,
		timestamp_diff_, likelihood);
	if (show)
	{
		debug_ts_visualizer(img_ts_, r, ts);
		cv::imshow("img_ts", img_ts_);
	}
	// Check condition
	if (r == MATCH_CONDITION::kMatchConditionLowLikelihood) {
		template_ = TemplateContainer(src.clone(), ts);
	}
	else if (r == MATCH_CONDITION::kMatchConditionHighLikelihood) {
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------
MATCH_CONDITION ImageChanged::match(TemplateContainer &tc, const cv::Mat &curr,
	TIMESTAMP ts, double likelihood_min,
	int timestamp_diff, double &likelihood_out)
{
	if (ts - tc.timestamp_ < timestamp_diff) {
		return kMatchConditionUnknown;
	}
	cv::Rect region_out;
	TemplateMatching::region(tc.src_, curr, 5, false,
		region_out,
		likelihood_out);
	if (likelihood_out >= likelihood_min) {
		return kMatchConditionHighLikelihood;
	}
	return kMatchConditionLowLikelihood;
}
//-----------------------------------------------------------------------------
void ImageChanged::debug_ts_visualizer(cv::Mat &img_ts_, 
	MATCH_CONDITION condition, TIMESTAMP ts_)
{
	int y = ts_ / img_ts_.cols;
	int x = ts_ % img_ts_.cols;
	if (x >= 0 && y >= 0 && x < img_ts_.cols && y < img_ts_.rows)
	{
		if (condition == MATCH_CONDITION::kMatchConditionLowLikelihood) {

			img_ts_.at<cv::Vec3b>(y, x)[0] = 0;
			img_ts_.at<cv::Vec3b>(y, x)[1] = 0;
			img_ts_.at<cv::Vec3b>(y, x)[2] = 255;
		}
		if (condition == MATCH_CONDITION::kMatchConditionHighLikelihood) {
			img_ts_.at<cv::Vec3b>(y, x)[0] = 0;
			img_ts_.at<cv::Vec3b>(y, x)[1] = 255;
			img_ts_.at<cv::Vec3b>(y, x)[2] = 0;
		}
	}
}

} // namespace measure
} // namespace CmnIP


