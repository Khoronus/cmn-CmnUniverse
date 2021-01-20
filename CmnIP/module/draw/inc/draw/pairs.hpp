/**
* @file pairs.hpp
* @brief Header of the pairs visualization.
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
* @version 1.0.0.0
*
*/

#ifndef CMNIP_DRAW_PAIRS_HPP__
#define CMNIP_DRAW_PAIRS_HPP__

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "transform/inc/transform/transform_headers.hpp"

namespace CmnIP
{
namespace draw
{

/** @brief Draw pairs
*/
class Pairs
{
public:

	/** @brief Draw a set of lines over an input matrix.

		Draw a set of lines over an input matrix. If the number of elements
		differ, it draw the minimum number of pairs.
		@param[in] v1 A vertex of the line.
		@param[in] v2 A vertex of the line.
		@param[in] color The color to give to the lines. If nullptr, set a 
		                 random color.
		@param[in] thickness The thickness of the lines.
		@param[inout] inout The matrix where the lines will be draw.
		@return Return 1 in case of success, 0 otherwise.
		*/
	template <typename _Ty>
	static int line(const std::vector<_Ty> &v1,
		const std::vector<_Ty> &v2,
		const cv::Scalar *color, int thickness,
		cv::Mat &inout) {
		if (inout.empty()) return 0;
		int s = (std::min)(v1.size(), v2.size());
		cv::RNG r;
		cv::Scalar _color;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		if (color != nullptr) _color = *color;
#else
		if (color != 0) _color = *color;
#endif
		for (int i = 0; i < s; i++) {
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			if (color == nullptr) 
#else
			if (color == 0) 
#endif
			{
				_color = cv::Scalar(r.uniform(0, 255),
					r.uniform(0, 255), r.uniform(0, 255));
			}
			cv::line(inout, v1[i], v2[i], _color, thickness);
		}
		return 1;
	}

	/** @brief Draw a set of points over an input matrix.

	Draw a set of points over an input matrix. If the number of elements
	differ, it draw the minimum number of pairs.
	@param[in] v1 A vertex of the line.
	@param[in] v2 A vertex of the line.
	@param[in] maxscale The maximum range the first vector can go. It is
	                    used to determine the blue to red scale.
	@param[in] minradius The minimum radius of the points.
	@param[in] maxradius The maximum radius of the points.
	@param[inout] inout The matrix where the points will be draw.
	@return Return 1 in case of success, 0 otherwise.
	*/
	template <typename _Ty>
	static int points(const std::vector<_Ty> &v1,
		const std::vector<_Ty> &v2,
		float maxscale, int minradius, int maxradius,
		cv::Mat &inout) {
		if (inout.empty()) return 0;
		if (maxscale <= 0) return 0;
		int s = (std::min)(v1.size(), v2.size());
		for (int i = 0; i < s; i++)
		{
			std::vector<float> rgb;
			float value = (float)(v1[i].x) / maxscale;
			float radius = (std::max)(minradius, rand() % maxradius);
			CmnIP::draw::ColoredRange::blu_to_red_range(0, 1, value,
				rgb);
			cv::Scalar color(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255);
			cv::circle(inout, v1[i], radius, color, -1);
			cv::circle(inout, v2[i], radius, color, -1);
		}
		return 1;
	}


	/** @brief Draw a set of points over an input matrix.

	Draw a set of points over an input matrix. If the number of elements
	differ, it draw the minimum number of pairs.
	@param[in] v1 A vertex of the line.
	@param[in] v2 A vertex of the line.
	@param[in] fontFace Type of font used.
	@param[in] fontScale Size of the font.
	@param[in] color Color display (bgr).
	@param[inout] inout The matrix where the points will be draw.
	@return Return 1 in case of success, 0 otherwise.
	*/
	template <typename _Ty>
	static int numbers(const std::vector<_Ty> &v1,
		const std::vector<_Ty> &v2,
		int fontFace, float fontScale, cv::Scalar &color,
		cv::Mat &inout) {
		if (inout.empty()) return 0;
		size_t s = (std::min)(v1.size(), v2.size());
		char buf[1024];
		for (size_t i = 0; i < s; i++)
		{
			sprintf(buf, "%i", i);
			cv::putText(inout, buf, v1[i], fontFace, fontScale, color, 1);
			cv::putText(inout, buf, v2[i], fontFace, fontScale, color, 1);
		}
		return 1;
	}

	/** @brief Draw a set of points over an input matrix.

	Draw a set of points over an input matrix. If the number of elements
	differ, it draw the minimum number of pairs.
	@param[in] v1 A vertex of the line.
	@param[in] v2 A vertex of the line.
	@param[in] w A container with the weight to apply to the size [0,1].
	@param[in] fontFace Type of font used.
	@param[in] fontScale Size of the font.
	@param[in] color Color display (bgr).
	@param[inout] inout The matrix where the points will be draw.
	@return Return 1 in case of success, 0 otherwise.
	*/
	template <typename _Ty>
	static int numbers_weight(const std::vector<_Ty> &v1,
		const std::vector<_Ty> &v2, const std::vector<float> &w,
		int fontFace, float fontScale, const cv::Scalar &color,
		cv::Mat &inout) {
		if (inout.empty()) return 0;
		size_t s = (std::min)(v1.size(), v2.size());
		if (w.size() < s) return 0;
		char buf[1024];
		for (size_t i = 0; i < s; i++)
		{
			sprintf(buf, "%i", i);
			float scale = fontScale * w[i];
			cv::putText(inout, buf, v1[i], fontFace, scale, color, 1);
			cv::putText(inout, buf, v2[i], fontFace, scale, color, 1);
		}
		return 1;
	}


};


} // namespace draw
} // namespace CmnIP

#endif /* CMNIP_DRAW_PAIRS_HPP__ */
