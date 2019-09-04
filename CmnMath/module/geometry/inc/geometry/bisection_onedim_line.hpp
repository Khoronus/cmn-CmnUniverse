/**
* @file bisection_onedim_line.hpp
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

#ifndef CMNMATH_GEOMETRY_BISECTIONONEDIMLINE_HPP__
#define CMNMATH_GEOMETRY_BISECTIONONEDIMLINE_HPP__

#include "algebralinear/inc/algebralinear/norm.hpp"
#include "distance_zerodim_point.hpp"
#include "projection_onedim_linexyz.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Estimates the distance between geometrical structures in a 3D space.

    Estimates the distance between geometrical structures in a 3D space.
*/
class BisectionOneDimLine
{
public:

	/** @brief It calculates the bisection between two lines.

	It calculates the bisection between two lines.
	The solution is where the points at the same distance of the lines
	are located.

	@param[in] v0 origin of one line
	@param[in] v1 direction of one line
	@param[in] u0 origin of one line
	@param[in] u1 direction of one line
	@param[out] p0 one point of the plane
	@param[out] dir_line1 one direction of the plane
	@param[out] dir_line2 opposite direction of the plane
	@param[out] dir_plane second direction of the plane

	A point on the plane is defined as follow
	solution 1 = p0 + r * dir_line1 + s * dir_plane
	solution 2 = p0 + r * dir_line2 + s * dir_plane

	where r and s are any two real values.
	*/
	template <typename _Ty3>
	static void bisection_twolines(
		_Ty3 &v0, _Ty3 &v1,
		_Ty3 &u0, _Ty3 &u1,
		_Ty3 &p0, _Ty3 &dir_line1, _Ty3 &dir_line2,
		_Ty3 &dir_plane)
	{
		// Point on the first line to find the bisection plane
		_Ty3 p = v0;
		_Ty3 vn1 = algebralinear::norm<_Ty3>(v1);
		_Ty3 un1 = algebralinear::norm<_Ty3>(u1);
		// direction solution 1
		dir_line1 = vn1 + un1;
		dir_line2 = vn1 - un1;
		// Crossproduct of the direction, to get the bisection plane direction
		dir_line2 = v1.cross(u1);
	}

	//template <typename _Ty3>
	//static _Ty3 norm(const _Ty3 &p)
	//{
	//	float module = std::sqrt(std::pow(p.x, 2.0f) + std::pow(p.y, 2.0f) +
	//		std::pow(p.z, 2.0f));
	//	return p * (1.0f / module);
	//}
};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_BISECTIONONEDIMLINE_HPP__ */
