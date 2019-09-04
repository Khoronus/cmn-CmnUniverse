/**
* @file intersection_twodim_trianglexyz.hpp
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

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLEXYZ_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLEXYZ_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{
/** @brief It estimates the intersection points with a triangle figure in a 3D
space.

It estimates the intersection points with a triangle figure in a 3D space.
@link http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
*/
template <typename _Ty3, typename REAL>
class IntersectionTwoDimTriangleXYZ
{
public:

	static int RayTriangle(
		_Ty3 &p, _Ty3 &d,
		_Ty3 &v0, _Ty3 &v1, _Ty3 &v2, REAL epsilon, REAL&t) {

		float a, f, u, v;
		_Ty3 e1 = v1 - v0;
		_Ty3 e2 = v2 - v0;
		_Ty3 h = d.cross(e2);
		a = e1.dot(h);

		if (a > -epsilon && a < epsilon)
			return(false);

		f = 1 / a;
		_Ty3 s = p - v0;
		u = f * s.dot(h);

		if (u < 0.0 || u > 1.0)
			return(false);

		_Ty3 q = s.cross(e1);
		v = f * d.dot(q);

		if (v < 0.0 || u + v > 1.0)
			return(false);

		// at this stage we can compute t to find out where
		// the intersection point is on the line
		t = f * e2.dot(q);

		if (t > epsilon) // ray intersection
			return(true);

		else // this means that there is a line intersection
			// but not a ray intersection
			return (false);
	}


	static int RayTriangle(
		_Ty3 &p, _Ty3 &d,
		std::vector<_Ty3> &vv, REAL epsilon, REAL&t) {

		float a, f, u, v;
		_Ty3 e1 = vv[1] - vv[0];
		_Ty3 e2 = vv[2] - vv[0];
		_Ty3 h = d.cross(e2);
		a = e1.dot(h);

		if (a > -epsilon && a < epsilon)
			return(false);

		f = 1 / a;
		_Ty3 s = p - vv[0];
		u = f * s.dot(h);

		if (u < 0.0 || u > 1.0)
			return(false);

		_Ty3 q = s.cross(e1);
		v = f * d.dot(q);

		if (v < 0.0 || u + v > 1.0)
			return(false);

		// at this stage we can compute t to find out where
		// the intersection point is on the line
		t = f * e2.dot(q);

		if (t > epsilon) // ray intersection
			return(true);

		else // this means that there is a line intersection
			// but not a ray intersection
			return (false);
	}

	static int RayTriangle(
		const _Ty3 &p, const _Ty3 &d,
		const std::vector<_Ty3> &vv, REAL epsilon, REAL&t) {

		float a, f, u, v;
		_Ty3 e1 = vv[1] - vv[0];
		_Ty3 e2 = vv[2] - vv[0];
		_Ty3 h = d.cross(e2);
		a = e1.dot(h);

		if (a > -epsilon && a < epsilon)
			return(false);

		f = 1 / a;
		_Ty3 s = p - vv[0];
		u = f * s.dot(h);

		if (u < 0.0 || u > 1.0)
			return(false);

		_Ty3 q = s.cross(e1);
		v = f * d.dot(q);

		if (v < 0.0 || u + v > 1.0)
			return(false);

		// at this stage we can compute t to find out where
		// the intersection point is on the line
		t = f * e2.dot(q);

		if (t > epsilon) // ray intersection
			return(true);

		else // this means that there is a line intersection
			// but not a ray intersection
			return (false);
	}



};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLEXYZ_HPP__ */
