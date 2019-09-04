/**
* @file intersection_twodim_plane.hpp
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

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTHREEDIMSPHERE_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTHREEDIMSPHERE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with three dimension geometrical
           structures.

	Class to perform interpolations with three dimension geometrical
	structures.
	@link: http://sci.tuomastonteri.fi/programming/sse/example3
	@link: http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
*/
template <typename _Ty>
class IntersectionThreeDimSphere
{
public:

	/** @brief Ray direction and origin
	           Sphere position and radius
			   Hit point
			   Distance Normal
	*/
	static CMN_BOOL rayf(const _Ty& raydir, const _Ty& rayorig, const _Ty& pos,
		const CMN_32F &rad, _Ty& hitpoint, CMN_32F &distance, _Ty& normal)
	{
		CMN_32F a = sum(mul(raydir, raydir));
		_Ty tmp2 = (rayorig - pos) * 2;
		_Ty tmp = mul(raydir, tmp2);
		CMN_32F b = sum(tmp);
		CMN_32F c0 = sum(mul(pos, pos));
		CMN_32F c1 = sum(mul(rayorig, rayorig));
		CMN_32F c2 = sum(mul(rayorig, pos));
		CMN_32F c3 = rad * rad;
		CMN_32F c = c0 + c1 - 2.0f * c2 - c3;
		CMN_32F D = b*b + (-4.0f)*a*c;

		// If ray can not intersect then stop
		if (D < 0) return false;
		D = sqrtf(D);

		// Ray can intersect the sphere, solve the closer hitpoint
		CMN_32F t = (-0.5f)*(b + D) / a;
		if (t > 0.0f)
		{
			distance = sqrtf(a)*t;
			hitpoint = rayorig + t*raydir;
			normal = (hitpoint - pos) * (1.0 / rad);
		}
		else
		{
			return false;
		}
		return true;
	}


	/** @brief Ray direction and origin
	Sphere position and radius
	Hit point
	Distance Normal
	*/
	static CMN_BOOL rayf(const _Ty& raydir, const _Ty& rayorig, const _Ty& pos,
		const CMN_32F &rad, std::vector<_Ty>& hitpoint, 
		std::vector<CMN_32F> &distance, std::vector<_Ty>& normal)
	{
		CMN_32F a = sum(mul(raydir, raydir));
		_Ty tmp2 = (rayorig - pos) * 2;
		_Ty tmp = mul(raydir, tmp2);
		CMN_32F b = sum(tmp);
		CMN_32F c0 = sum(mul(pos, pos));
		CMN_32F c1 = sum(mul(rayorig, rayorig));
		CMN_32F c2 = sum(mul(rayorig, pos));
		CMN_32F c3 = rad * rad;
		CMN_32F c = c0 + c1 - 2.0f * c2 - c3;
		CMN_32F D = b*b + (-4.0f)*a*c;

		// If ray can not intersect then stop
		if (D < 0) return false;
		D = sqrtf(D);

		// clean the container
		distance.clear();
		hitpoint.clear();
		normal.clear();

		// Ray can intersect the sphere, solve the closer hitpoint
		CMN_32F t = (-0.5f)*(b + D) / a;
		if (t > 0.0f)
		{
			distance.push_back(sqrtf(a)*t);
			hitpoint.push_back(rayorig + t*raydir);
			normal.push_back((hitpoint[0] - pos) * (1.0 / rad));
		}
		t = (-0.5f)*(b - D) / a;
		if (t > 0.0f)
		{
			distance.push_back(sqrtf(a)*t);
			hitpoint.push_back(rayorig + t*raydir);
			normal.push_back((hitpoint[1] - pos) * (1.0 / rad));
		}
		if (distance.size() == 0) return false;
		return true;
	}


private:

	static _Ty mul(const _Ty &a, const _Ty &b)
	{
		_Ty c(a.x * b.x, a.y * b.y, a.z * b.z);
		return c;
	}

	static CMN_32F sum(const _Ty &a)
	{
		return (a.x + a.y + a.z);
	}

};




} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTHREEDIMSPHERE_HPP__ */
