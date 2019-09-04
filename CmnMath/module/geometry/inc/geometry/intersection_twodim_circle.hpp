/**
* @file intersection_twodim_ellipse.hpp
* @brief Header of all the files related to the statistics
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTWODIMCIRCLE_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTWODIMCIRCLE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with two dimension geometrical
           structures.

	Class to perform interpolations with two dimension geometrical
	structures.
*/
template <typename _Ty>
class IntersectionTwoDimCircle
{
public:

	/** @brief Function to calculate the intersection point between a line and
	circle.

	Function to calculate the intersection point between a line and circle.
	@param[in] E is the starting point of the ray,
	@param[in] L is the end point of the ray,
	@param[in] C is the center of sphere you're testing against
	@param[in] radius is the radius of that sphere
	@param[in] t Parametric values at intersection points
	@param[in] point Intersection points
	@param[in] normal Normals at intersection points
	@return Return TRUE if there is intersection. FALSE otherwise
	*/
	static CMN_BOOL line_circle(
		const _Ty& E,
		const _Ty& L,
		const _Ty& C,
		float radius, std::vector<CMN_32F> &t,
		std::vector<_Ty> &point,
		std::vector<_Ty> &normal)
	{
		_Ty d = L - E;
		_Ty f = E - C;
		CMN_32F a = d * d;
		CMN_32F b = (f * d) * 2;
		CMN_32F c = f * f - radius * radius;

		CMN_32F disc = b*b - 4 * a*c;

		if (disc < 0.0f) {
			return false;
		}
		CMN_32F sqrtDisc = std::sqrt(disc);
		t[0] = (-b - sqrtDisc) / (2 * a);
		t[1] = (-b + sqrtDisc) / (2 * a);
		CMN_32F invRadius = 1.0f / radius;
		for (int i = 0; i < 2; ++i) {
			_Ty p = d * (CMN_32F)(t[i]);
			point[i] = E + p;
			normal[i] = (point[i] - C) * invRadius;
		}
		return true;
	}

};




} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMCIRCLE_HPP__ */
