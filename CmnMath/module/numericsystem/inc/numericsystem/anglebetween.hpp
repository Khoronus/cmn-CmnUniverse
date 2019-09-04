/**
* @file anglebetween.hpp
* @brief Header related to angle analysis.
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

#ifndef CMNMATH_NUMERICSYSTEM_ANGLEBETWEEN_HPP__
#define CMNMATH_NUMERICSYSTEM_ANGLEBETWEEN_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "cmnmathcore/inc/cmnmathcore/constants.hpp"

namespace CmnMath
{
namespace numericsystem
{


/** @brief This class is used to check if an angle is between a range

    This class is used to check if an angle is between a range
*/
template <typename _Ty>
class AngleBetween
{
public:

	/** @brief The angle is between two other angles. The target is in deg.

	    The angle is between two other angles. The target is in deg.
		@param[in] target The angle to check.
		@param[in] angle1 The min angle interval.
		@param[in] angle2 The max angle interval.
		@return Return TRUE in case the angle is in the range. FALSE otherwise.
	*/
	static bool two_angles(_Ty target, _Ty angle1, _Ty angle2)
	{
		// make the angle from angle1 to angle2 to be <= 180 degrees
		_Ty rAngle = std::fmod((std::fmod(angle2 - angle1, 360.0) + 360.0), 360.0);
		if (rAngle >= 180)
			std::swap(angle1, angle2);

		// check if it passes through zero
		if (angle1 <= angle2) {
			return target >= angle1 && target <= angle2;
		}
		else {
			return target >= angle1 || target <= angle2;
		}
	}
};

}	// namespace numericsystem
}	// namespace CmnMath

#endif /* CMNMATH_NUMERICSYSTEM_ANGLECONVERSION_HPP__ */
