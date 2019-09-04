/**
* @file parametric_twodim_circle.hpp
* @brief Header of all the class related to a parametric function for circle.
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

#ifndef CMNMATH_GEOMETRY_PROJECTIONTHREEDIMSPHERE_HPP__
#define CMNMATH_GEOMETRY_PROJECTIONTHREEDIMSPHERE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to performs the projection on a sphere.

	Class to perform the projection on a sphere
*/
template <typename _Ty, typename REAL>
class ProjectionThreeDimSphere
{
public:

	/* @brief It projects a point on a sphere

		It projects a point on a sphere
		@link http://stackoverflow.com/questions/9604132/how-to-project-a-point-on-to-a-sphere

		1. Write the point in a coordinate system centered at the center of the sphere (x0,y0,z0):
		P = (x',y',z') = (x - x0, y - y0, z - z0)
		2. Compute the length of this vector:
		|P| = sqrt(x'^2 + y'^2 + z'^2)

		3. Scale the vector so that it has length equal to the radius of the sphere:
		Q = (radius/|P|)*P


		4. And change back to your original coordinate system to get the projection:
		R = Q + (x0,y0,z0)
		@param[in] i Point to project
		@param[in] c Center of the sphere
		@param[in] r Radius of the sphere
		@param[out] o Projected point
	*/
	static void project_on_sphere(_Ty &i, _Ty &c, REAL r,
		_Ty &o) {

		// 1.
		_Ty p = i - o;
		// 2.
		REAL mp = std::sqrt(std::pow(p.x, 2) + std::pow(p.y, 2) +
			std::pow(p.z, 2));
		// 3. 
		_Ty q = (r / mp) * p;
		// 4.
		o = q + c;
	}
};



} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_PARAMETRICTWODIMCIRCLE_HPP__ */
