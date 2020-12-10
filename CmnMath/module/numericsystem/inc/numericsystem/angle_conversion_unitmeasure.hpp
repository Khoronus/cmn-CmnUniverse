/**
* @file angle_conversion_unitmeasure.hpp
* @brief Header to class to convert angle reference system.
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

#ifndef CMNMATH_NUMERICSYSTEM_ANGLECONVERSIONUNITMEASURE_HPP__
#define CMNMATH_NUMERICSYSTEM_ANGLECONVERSIONUNITMEASURE_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "cmnmathcore/inc/cmnmathcore/constants.hpp"

namespace CmnMath
{
namespace numericsystem
{


//##############################
// Angle Conversion
//##############################

/** This class provides the conversion of angles
*	@author Dr. Moro Alessandro
*	@ingroup Conversion
*/
template <typename _Ty>
class AngleConversionUnitMeasure
{
public:
	/** Convert the grad in rad */
	static _Ty ToRad(_Ty grad)		{ return static_cast<_Ty>((core::kPI / 180.0f) * grad); }
	/** Convert the rad in grad */
	static _Ty ToGrad(_Ty rad)		{ return static_cast<_Ty>((180.0f * rad) / core::kPI); }
};

}	// namespace numericsystem
}	// namespace CmnMath

#endif // CMNMATH_NUMERICSYSTEM_ANGLECONVERSIONUNITMEASURE_HPP__
