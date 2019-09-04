/**
* @file trigonometry.hpp
* @brief Classes to manage some simple trigonometry operations
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

#ifndef CMNMATH_TRIGONOMETRY_TRIGONOMETRY_HPP__
#define CMNMATH_TRIGONOMETRY_TRIGONOMETRY_HPP__

#include <cmath>

namespace CmnMath
{
namespace trigonometry
{

/** @brief Class to calculate circumference trigonometry operations.
*/
template <typename _Ty>
class Circumference
{
public:

	/** @brief Length of the arc of circumference is l = theta * r
	           check if the r is not zero.

		Length of the arc of circumference is l = theta * r check if the r is 
		not zero.
		@param[in] length Length measured.
		@param[in] radius Radius in rad.
		@return Return the angle.
	*/
	static _Ty angle_from_length(_Ty length, _Ty radius) {
		return length / radius;
	}

	/** @brief Return the angle covered by the point to reach the expected 
	           position.

		Return the angle covered by the point to reach the expected position.
		@param[in] angle Angle measured.
		@param[in] radius Radius in rad.
		@return Return the length.
	*/
	static _Ty length_from_angle(_Ty angle, _Ty radius) {
		return angle * radius;
	}

	/** @brief Calculate the position of a point on a circumference given
	           the theta angle.

		Calculate the position of a point on a circumference given
	    the theta angle.
		@param[in] theta Angle measured.
		@param[in] radius Radius in rad.
		@param[out] x x coordinate.
		@param[out] y y coordinate.
	*/
	static void coordinate(_Ty theta, _Ty radius, _Ty &x, _Ty &y) {
		x = std::cos(theta) * radius;
		y = std::sin(theta) * radius;
	}
};


} // namespace trigonometry
} // namespace CmnMath

#endif /* CMNMATH_TRIGONOMETRY_TRIGONOMETRY_HPP__ */
