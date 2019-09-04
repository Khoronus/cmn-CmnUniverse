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

#ifndef CMNIP_DRAW_COLORED_RANGE_HPP__
#define CMNIP_DRAW_COLORED_RANGE_HPP__

#include <vector>

#include "transform/inc/transform/transform_headers.hpp"

namespace CmnIP
{
namespace draw
{

/** Class to calculate some colored ranges
*/
class ColoredRange
{
 public:

  /** Return a rgb color in a given interval
  */
  static void blu_to_red_range(float min_distance, 
	float max_distance, float value, std::vector<float> &rgb);
};

} // namespace transform
} // namespace CmnIP

#endif /* CMNIP_TRANSFORM_COLORED_RANGE_HPP__ */
