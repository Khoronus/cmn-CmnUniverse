/**
* @file intersection_twodim_triangle.hpp
* @brief Performs the intersection over a 2 dimensional triangle
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

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLE_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"
#include "geometry_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief It estimates the intersection points with a triangle figure in a 3D 
           space.

	It estimates the intersection points with a triangle figure in a 3D space.
	@link http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
*/
template <typename REAL>
class IntersectionTwoDimTriangle
{
public:

	static int RayTriangle(REAL *p, REAL *d,
		REAL *v0, REAL *v1, REAL *v2, REAL epsilon, REAL &t) {

		REAL e1[3], e2[3], h[3], s[3], q[3];
		REAL a, f, u, v;
		VectorOperation<REAL*>::vector(v1, v0, e1);
		VectorOperation<REAL*>::vector(v2, v0, e2);

		VectorOperation<REAL*>::cross(d, e2, h);
		a = VectorOperation<REAL*>::dotf(e1, h);

		if (a > -epsilon && a < epsilon)
			return(false);

		f = 1 / a;
		VectorOperation<REAL*>::vector(p, v0, s);
		u = f * (VectorOperation<REAL*>::dotf(s, h));

		if (u < 0.0 || u > 1.0)
			return(false);

		VectorOperation<REAL*>::cross(s, e1, q);
		v = f * VectorOperation<REAL*>::dotf(d, q);

		if (v < 0.0 || u + v > 1.0)
			return(false);

		// at this stage we can compute t to find out where
		// the intersection point is on the line
		t = f * VectorOperation<REAL*>::dotf(e2, q);

		if (t > epsilon) // ray intersection
			return(true);

		else // this means that there is a line intersection
			// but not a ray intersection
			return (false);
	}
};



} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMTRIANGLE_HPP__ */
