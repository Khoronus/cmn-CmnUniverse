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
* @version 0.2.0.0
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

	/** @brief Similar to Moller Trumbore ray-triangle intersection, but not check back-culling
		@link https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
	*/
	static int RayTriangle(
		_Ty3 &p, _Ty3 &d,
		_Ty3 &v0, _Ty3 &v1, _Ty3 &v2, 
		REAL epsilon, bool test_backculling,
		REAL&t) {

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


	/** @brief Similar to Moller Trumbore ray-triangle intersection, but not check back-culling
		@link https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
	*/
	static int RayTriangle(
		_Ty3 &p, _Ty3 &d,
		std::vector<_Ty3> &vv, 
		REAL epsilon, 
		bool test_backculling, 
		REAL &t) {

		float a, f, u, v;
		_Ty3 e1 = vv[1] - vv[0];
		_Ty3 e2 = vv[2] - vv[0];
		_Ty3 h = d.cross(e2);
		a = e1.dot(h);

		// if the determinant is negative the triangle is backfacing
		// if the determinant is close to 0, the ray misses the triangle
		if (test_backculling && a < epsilon) return false;

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

	/** @brief Similar to Moller Trumbore ray-triangle intersection, but not check back-culling
		@link https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
	*/
	static int RayTriangle(
		const _Ty3 &p, const _Ty3 &d,
		const std::vector<_Ty3> &vv, 
		REAL epsilon, bool test_backculling,
		REAL &t) {

		float a, f, u, v;
		_Ty3 e1 = vv[1] - vv[0];
		_Ty3 e2 = vv[2] - vv[0];
		_Ty3 h = d.cross(e2);
		a = e1.dot(h);

		// if the determinant is negative the triangle is backfacing
		// if the determinant is close to 0, the ray misses the triangle
		if (test_backculling && a < epsilon) return false;

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

	/** @brief MOLLER_TRUMBORE ray-triangle intersection

		@link: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

		@previous_name rayTriangleIntersect
	*/
	bool rayTriangleIntersectMoller(
		const _Ty3 &orig, const _Ty3 &dir,
		const _Ty3 &v0, const _Ty3 &v1, const _Ty3 &v2,
		REAL epsilon, REAL &t, REAL &u, REAL &v)
	{
//#ifdef MOLLER_TRUMBORE 
		_Ty3 v0v1 = v1 - v0;
		_Ty3 v0v2 = v2 - v0;
		_Ty3 pvec = dir.cross(v0v2);
		float det = v0v1.dot(pvec);
//#ifdef CULLING 
		// if the determinant is negative the triangle is backfacing
		// if the determinant is close to 0, the ray misses the triangle
		if (det < epsilon) return false;
//#else 
		// ray and triangle are parallel if det is close to 0
//		if (fabs(det) < epsilon) return false;
//#endif 
		REAL invDet = 1 / det;

		_Ty3 tvec = orig - v0;
		u = tvec.dot(pvec) * invDet;
		if (u < 0 || u > 1) return false;

		_Ty3 qvec = tvec.cross(v0v1);
		v = dir.dot(qvec) * invDet;
		if (v < 0 || u + v > 1) return false;

		t = v0v2.dot(qvec) * invDet;

		return true;
//#else 

//#error "intersection_twodim_trianglexyz::rayTriangleIntersect: body missing"
//		return false;
//#endif 
	}


};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLEXYZ_HPP__ */
