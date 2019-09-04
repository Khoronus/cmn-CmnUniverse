/**
* @file trigonometry.hpp
* @brief Classes to manage some simple trigonometry operations
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.0.0
*
*/

#ifndef CMNMATH_TRIGONOMETRY_BISECTIONANGLE_HPP__
#define CMNMATH_TRIGONOMETRY_BISECTIONANGLE_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/constants.hpp"

namespace CmnMath
{
namespace trigonometry
{

/** @brief Class to calculate bisection of two angles

    @link: http://stackoverflow.com/questions/11498169/dealing-with-angle-wrap-in-c-code
*/
template <typename _Ty>
class BisectionAngle
{
public:

	/** @brief Bisection of two angles in the range [0, 2PI[
	*/
	static _Ty bisectAngle0_2PI(_Ty a, _Ty b){
		return constrainAngle0_2PI(a + angleDiff(a, b) * 0.5);
	}

	/** @brief Bisection of two angles in the range [-PI, PI]
	*/
	static _Ty bisectAnglePI_PI(_Ty a, _Ty b){
		return constrainAnglePI_PI(a + angleDiff(a, b) * 0.5);
	}

private:

	static _Ty constrainAngle0_2PI(_Ty x){
		x = fmod(x, CmnMath::core::kPI * 2);
		if (x < 0)
			x += CmnMath::core::kPI * 2;
		return x;
	}

	static _Ty constrainAnglePI_PI(_Ty x){
		x = fmod(x + CmnMath::core::kPI, CmnMath::core::kPI * 2);
		if (x < 0)
			x += CmnMath::core::kPI * 2;
		return x - CmnMath::core::kPI;
	}

	static _Ty angleDiff(_Ty a, _Ty b){
		_Ty dif = fmod(b - a + CmnMath::core::kPI, CmnMath::core::kPI * 2);
		if (dif < 0)
			dif += CmnMath::core::kPI * 2;
		return dif - CmnMath::core::kPI;
	}

};


} // namespace trigonometry
} // namespace CmnMath

#endif // CMNMATH_TRIGONOMETRY_BISECTIONANGLE_HPP__
