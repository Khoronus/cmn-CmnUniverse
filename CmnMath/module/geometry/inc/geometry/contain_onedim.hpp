/**
 * @file Contains.cpp
 * @brief Program to detect if a geometric figure contains another.
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
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * @author  Alessandro Moro <antigorite@hotmail.com>
 * @bug No known bugs.
 * @version 0.1
 * 
 */


#ifndef CMNMATH_GEOMETRY_CONTAINONEDIM_HPP__
#define CMNMATH_GEOMETRY_CONTAINONEDIM_HPP__

#include <cmath>
#include "sign_zerodim_point.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to verify if points are inside a geometric figure.
*/
class Inside
{
 public:

	/** @brief How to check if a point is inside an ellipsoid?

		How to check if a point is inside an ellipsoid?
		@param[in] a Horizontal axe (x)
		@param[in] b Vertical axe (y)
		@param[in] c Depth axe (z)
		@return Return 1 if the point is inside the ellipse. Return 2 if on the
		        border. Return 0 if it is outside.

		@note: The standard equation of an ellipsoid centered at the origin 
		       and aligned with the axes is

			(x/a)2 + (y/b)2 + (z/c)2 = 1

		       (The ellipsoid passes through points (a, 0, 0), (0, b, 0) and 
			   (0, 0, c).) Just plug in values for (x, y, z) for your point 
			   and if it's less than 1, the point is inside the ellipsoid.
	*/
	static CMN_32S ellipsoid(CMN_32F a, CMN_32F b, CMN_32F c,
	CMN_32F x, CMN_32F y, CMN_32F z)
	{
		CMN_64F d = (std::pow(x/a,2) + std::pow(y/b,2) + std::pow(z/c,2));
		if (d < 1) return 1;
		if (d == 1) return 2;
		return 0;
	}

	/** @brief Test if a point is inside a triangle.

		Test if a point is inside a triangle. It is a solution for 2D points.
		@param[in] pt Point to test.
		@param[in] v1 Vertex of the triangle.
		@param[in] v2 Vertex of the triangle.
		@param[in] v3 Vertex of the triangle.
		@return Return TRUE in case the point is inside the triangle.
		@link: http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle
	*/
	template <typename _Ty>
	static bool triangle2d(const _Ty &pt, const _Ty &v1, const _Ty &v2,
		const _Ty &v3)
	{
		CMN_BOOL b1, b2, b3;

		b1 = Sign2D<_Ty>::sign(pt, v1, v2) < 0.0f;
		b2 = Sign2D<_Ty>::sign(pt, v2, v3) < 0.0f;
		b3 = Sign2D<_Ty>::sign(pt, v3, v1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}
};


}	// namespace geometry
}	// namespace CmnMath

#endif