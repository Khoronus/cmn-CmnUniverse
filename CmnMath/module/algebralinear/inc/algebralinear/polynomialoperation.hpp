/**
* @file matrixoperation.hpp
* @brief Class to perform some operations with matrix
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
* @original author Will Perone (will.perone@gmail.com)
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_ALGEBRALINEAR_POLYNOMIALOPERATION_HPP__
#define CMNMATH_ALGEBRALINEAR_POLYNOMIALOPERATION_HPP__

#include <memory>
#include <cmath>

namespace CmnMath
{
namespace algebralinear
{


/** @brief Performs some polynomial operations

    Performs some polynomial operations
*/
template <typename _Ty>
class PolynomialOperation
{
public:

	//! evaluates a degree (arraysize-1) polynomial in the order x^n*array[0] + ... + array[arraysize-1]
	static inline _Ty HornerEval(const CMN_32F x, const _Ty *array, 
		CMN_32U arraysize)
	{
		_Ty p = *array;
		while (--arraysize) p = *++array + p*x;
		return p;
	}

};


} // namespace algebralinear
} // namespace CmnMath

#endif /* CMNMATH_ALGEBRALINEAR_POLYNOMIALOPERATION_HPP__ */
