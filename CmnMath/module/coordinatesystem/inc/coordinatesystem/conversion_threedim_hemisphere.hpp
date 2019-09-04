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

#ifndef CMNMATH_COORDINATESYSTEM_CONVERSIONTHREEDIMHEMISPHERE_HPP__
#define CMNMATH_COORDINATESYSTEM_CONVERSIONTHREEDIMHEMISPHERE_HPP__


#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace coordinatesystem
{


/** @brief Class to transform over a sphere object
*/
template <typename _Ty2, typename _Ty3>
class conversion_threedim_hemisphere
{
public:

	/** @brief Calculate the point position on the world with the radius 1 and
	no camera distortions.

	@param[in] s source.
	@param[in] c center.
	@param[in] o output.
	*/
	static void camera2world(const _Ty2 &s, const _Ty2 &c,
		_Ty3 &o) {
		float x = s.x;
		float y = s.y;

		// Calculate the position of the points on the emisphere
		float _x = x / c.x, _y = y / c.y;
		o.x = (_x * 2.0f) /
			(1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f));
		o.y = (_y * 2.0f) /
			(1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f));
		o.z = (-1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f)) /
			(1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f));
	}

};


} // namespace coordinatesystem
} // namespace CmnMath



#endif /* CMNMATH_COORDINATESYSTEM_CONVERSIONTHREEDIMHEMISPHERE_HPP__ */
