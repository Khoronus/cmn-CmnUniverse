/* @file color_conversion.hpp
 * @brief Class to convert a color space in another.
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
 * @version 0.2.0.0
 * 
 */

#include "draw/inc/draw/colored_range.hpp"

namespace CmnIP
{
namespace draw
{

//-----------------------------------------------------------------------------
void ColoredRange::blu_to_red_range(float min_distance, 
	float max_distance, float value, std::vector<float> &rgb)
{
	float diff_distance = max_distance - min_distance;
	rgb.clear();

	if (value < min_distance)
	{
		rgb.push_back(0);
		rgb.push_back(0);
		rgb.push_back(0);
	} else if (value > max_distance) {
		rgb.push_back(1.0);
		rgb.push_back(1.0);
		rgb.push_back(1.0);
	} else {
		float max_div = 0.7f;
		float div = (max_div / diff_distance) * (value - min_distance);
		float hsv[3] = {div, 1.0f, 1.0f};
		float c[3];

		transform::ColorConversion::HSVToRGB(hsv, c);
		rgb.push_back(c[0]);
		rgb.push_back(c[1]);
		rgb.push_back(c[2]);
	}
}

} // namespace transform
} // namespace CmnIP

