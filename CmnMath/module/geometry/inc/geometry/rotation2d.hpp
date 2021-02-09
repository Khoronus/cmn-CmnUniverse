/**
* @file rotation2.hpp
* @brief Header of all the files related to 2D rotation
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

#ifndef CMNMATH_GEOMETRY_ROTATION2D_HPP__
#define CMNMATH_GEOMETRY_ROTATION2D_HPP__

#include <cmath>

namespace CmnMath
{
namespace geometry
{

/** @brief Class to calculate circumference trigonometry operations.
*/
template <typename _Ty>
class Rotation2D
{
public:

	/** @brief Rotation of a 2D point around another point.
	*/
	static void point(const _Ty &in, CMN_64F angle, 
	                  const _Ty &center, _Ty &out) {
		_Ty aux = in - center;
		CMN_64F c = std::cos(angle);
		CMN_64F s = std::sin(angle);
		out.x = aux.x * c - aux.y * s + center.x;
		out.y = aux.x * s + aux.y * c + center.y;
	}

	/** @brief Rotation of a 2D point around another point.
	*/
	static void pointf(const _Ty &in, CMN_32F angle, 
	                   const _Ty &center, _Ty &out) {
		_Ty aux = in - center;
		CMN_32F c = std::cos(angle);
		CMN_32F s = std::sin(angle);
		out.x = aux.x * c - aux.y * s + center.x;
		out.y = aux.x * s + aux.y * c + center.y;
	}

};

} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_ROTATION2D_HPP__ */
