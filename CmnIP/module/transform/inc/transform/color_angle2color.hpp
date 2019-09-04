/* @file color_normalization.hpp
 * @brief Class to perform the color normalization of a source of data.
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

#ifndef CMNIP_TRANSFORM_COLORANGLE2COLOR_HPP__
#define CMNIP_TRANSFORM_COLORANGLE2COLOR_HPP__


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


namespace CmnIP
{
namespace transform
{

/** Class used to convert an angle in color
*/
class ConversionAngleToColor
{
public:
	/** Convert an angle and magnitude in a rgb color
	*/
	static void convert_angle(float angle, float min_angle, float max_angle,
		float magnitude, float min_magnitude, float max_magnitude,
		std::vector<float> &rgb)
	{
		// normalize angle
		float aA = max_angle - min_angle;
		float a = (angle - min_angle) / aA < 1.0f ? (angle - min_angle) / aA : 1.f;//std::min( (angle - min_angle) / aA, 1.0f );
		// normalize magnitude
		float mM = max_magnitude - min_magnitude;
		float m = (magnitude - min_magnitude) / mM < 1.f ? (magnitude - min_magnitude) / mM : 1.f;//std::min( (magnitude - min_magnitude) / mM, 1.0f );
		// convert the angle to color
		ColorConversion::HSVToRGB(a, m, 255.0f, &rgb[0], &rgb[1], &rgb[2]);
	}
	/** Convert two vertex position in a rgb color
	*/
	static void convert_point(float xs, float ys, float xe, float ye,
		float min_magnitude, float max_magnitude,
		std::vector<float> &rgb)
	{
		// container size is unexpected
		if (static_cast<int>(rgb.size()) != 3)
		{
			rgb.clear();
			for (int i = 0; i < 3; i++)
				rgb.push_back(0);
		}
		// orientation
		float angle = std::atan2(ye - ys, xe - xs);
		float magnitude = std::sqrt(std::pow(xe - xs, 2.0f) +
			std::pow(ye - ys, 2.0f));
		convert_angle(angle, -3.14159265f, 3.14159265f, magnitude, min_magnitude,
			max_magnitude, rgb);
	}
};


} // namespace transform
} // namespace CmnIP

#endif /* CMNIP_TRANSFORM_COLORANGLE2COLOR_HPP__ */
