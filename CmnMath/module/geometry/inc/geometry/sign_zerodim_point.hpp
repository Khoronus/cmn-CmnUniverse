/* @file sign.hpp
 * @brief Classes to determine the sign of function or geometric elements.
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
 * @author Moro Alessandro
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */

#ifndef CMNMATH_GEOMETRY_SIGNZERODIMPOINT_HPP__
#define CMNMATH_GEOMETRY_SIGNZERODIMPOINT_HPP__

#include <iostream>
#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to determine the sign of 2D geometric elements.

	Class to determine the sign of 2D gemoetric elements.
	@note It expect element with x, y members
*/
template <typename _Ty>
class Sign2D
{
public:

	/** @brief It return if a point is left or right side of two other points.

		It return if a point is left or right side of two other points. The sign
		should be positive if right side, negative otherwise.
		@param[in] p1 The point to test.
		@param[in] p2 The first vertex.
		@param[in] p3 The second vertex.
		@return It returns a negative or positive value if the point is left or
		        right side.
	*/
	static CMN_32F sign(const _Ty &p1, const _Ty &p2, const _Ty &p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

};


}   // namespace geometry
}	// namespace CmnMath


#endif /* CMNMATH_GEOMETRY_SIGNZERODIMPOINT_HPP__ */
