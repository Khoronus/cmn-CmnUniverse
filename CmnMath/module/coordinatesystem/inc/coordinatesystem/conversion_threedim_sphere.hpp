/**
* @file conversion_threedim_sphere.hpp
* @brief Performs transformation over sphere
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
* @author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_COORDINATESYSTEM_CONVERSIONTHREEDIMSPHERE_HPP__
#define CMNMATH_COORDINATESYSTEM_CONVERSIONTHREEDIMSPHERE_HPP__


#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace coordinatesystem
{


/** @brief Class to transform over a sphere object
*/
template <typename _Ty1, typename _Ty2>
class conversion_threedim_sphere
{
public:

	/** @brief Finding UV on a sphere

		Finding UV on a sphere.

		@link http://en.wikipedia.org/wiki/UV_mapping
		@remark UV [0,1]
	*/
	static void sphere2uvf(_Ty1 &xyz, _Ty2 &uv)
	{
		uv.x = 0.5f + (std::atan2f(xyz.z, xyz.x) / (2 * CmnMath::core::kPIf));
		uv.y = 0.5f - (std::asinf(xyz.y) / CmnMath::core::kPIf);
	}

	/** @brief Finding UV on a sphere

		Finding UV on a sphere.

		@link http://en.wikipedia.org/wiki/UV_mapping
		@remark UV [0,1]
	*/
	static void sphere2uv(_Ty1 &xyz, _Ty2 &uv)
	{
		uv.x = 0.5 + (std::atan2(xyz.z, xyz.x) / (2 * CmnMath::core::kPI));
		uv.y = 0.5 - (std::asin(xyz.y) / CmnMath::core::kPI);
	}

	///** @brief NO GOOD!!! Finding UV on a sphere

	//	Finding UV on a sphere. The range is corrected to match the position
	//	with the function "uv2sphere_ypolef".

	//	@link http://en.wikipedia.org/wiki/UV_mapping
	//	@remark UV [0,1]
	//*/
	//static void sphere2uv_ypolef(_Ty1 &xyz, _Ty2 &uv)
	//{
	//	uv.x = 1.0 + (std::atan2f(xyz.z, xyz.x) / (2 * CmnMath::core::kPI));
	//	if (uv.x > 1.0) uv.x -= 1.0;
	//	uv.y = 0.5 - (std::asinf(xyz.y) / CmnMath::core::kPI);
	//}


	/** @brief This function is almost same in the conversion3d::spherical2cartesian
	*/
	static void uv2sphere(_Ty2 &uv, CmnMath::CMN_64F radius, _Ty1 &xyz)
	{
		CmnMath::CMN_64F theta = uv.x * CmnMath::core::kPI * 2.;
		CmnMath::CMN_64F phi = uv.y * CmnMath::core::kPI;

		xyz.x = std::cos(theta) * std::sin(phi) * radius;
		xyz.y = std::sin(theta) * std::sin(phi) * radius;
		xyz.z = std::cos(phi) * radius;
	}

	/** @brief This function is almost same in the conversion3d::spherical2cartesian
	*/
	static void uv2spheref(_Ty2 &uv, CmnMath::CMN_32F radius, _Ty1 &xyz)
	{
		// it subtracts PI because in the sphere2uv conversion the solution 
		// starts from PI (0.5+)
		// 0.5 represents PI in a 2PI solution
		CmnMath::CMN_32F theta = uv.x * CmnMath::core::kPIf * 2. - CmnMath::core::kPIf;
		CmnMath::CMN_32F phi = uv.y * CmnMath::core::kPIf;

		xyz.x = std::cosf(theta) * std::sinf(phi) * radius;
		xyz.y = std::sinf(theta) * std::sinf(phi) * radius;
		xyz.z = std::cosf(phi) * radius;
	}


	/** @brief Converts a uv map in a sphere coordinate. Y pole

		Converts a uv map in a sphere coordinate. Y pole.
		This function coordinates match with sphere2uvf.
	*/
	static void uv2sphere_ypolef(_Ty2 &uv, CmnMath::CMN_32F radius, _Ty1 &xyz)
	{
		// it subtracts PI because in the sphere2uv conversion the solution 
		// starts from PI (0.5+)
		// 0.5 represents PI in a 2PI solution
		CmnMath::CMN_32F theta = uv.x * CmnMath::core::kPIf * 2. - CmnMath::core::kPIf;
		CmnMath::CMN_32F phi = uv.y * CmnMath::core::kPIf;

		xyz.x = std::cosf(theta) * std::sinf(phi) * radius;
		xyz.z = std::sinf(theta) * std::sinf(phi) * radius;
		xyz.y = std::cosf(phi) * radius;
	}

};


} // namespace coordinatesystem
} // namespace CmnMath



#endif /* CMNMATH_COORDINATESYSTEM_CONVERSION2D_HPP__ */
