/**
* @file CoordinateSystemConversion2D.hpp
* @brief Header related to the conversion of coordinate system in 2D.
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

#ifndef CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION2D_HPP__
#define CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION2D_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace coordinatesystem
{


/** @brief Class to perform a coordinate conversion in 2D space.
*/
template <typename _Ty>
class CoordinateSystemConversion2D
{
public:

	static void polar2cartesian(_Ty r, _Ty theta, _Ty &x, _Ty &y) {
		x = r * std::cos(theta);
		y = r * std::sin(theta);
	}

	static void cartesian2polar(_Ty x, _Ty y, _Ty &r, _Ty &theta) {
		r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		//if (x != 0) {
		//	theta = std::atan(y / x);
		//} else {
		//	theta = std::numeric_limits<_Ty>::max();
		//}
		theta = 2.0f * std::atan(y / (x + r));
	}

	static void logpolar2cartesian(_Ty p, _Ty theta, _Ty &x, _Ty &y) {
		x = std::pow(CmnMath::core::kE, p) * std::cos(theta);
		y = std::pow(CmnMath::core::kE, p) * std::sin(theta);
	}

	static void cartesian2logpolar(_Ty x, _Ty y, _Ty &p, _Ty &theta) {
		p = std::log(std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
		if (x != 0) {
			theta = std::atan(y / x);
		} else {
			theta = std::numeric_limits<_Ty>::max();
		}
	}

};


} // namespace coordinatesystem
} // namespace CmnMath


#endif // CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION2D_HPP__
