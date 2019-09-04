/**
* @file constants.hpp
* @brief Header of constants values
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

#ifndef CMNMATH_CMNMATHCORE_VALID_HPP__
#define CMNMATH_CMNMATHCORE_VALID_HPP__

#include <limits>
#include "assert.hpp"
#include "define.hpp"

namespace CmnMath
{
namespace core
{

#ifdef CMNMATH_USE_VALID_NUMBER

class ValidNumber
{
public:

	//! returns if a CMN_32F is valid
	static inline bool is_valid(const CMN_32F f)
	{
		// assert on the freed memory values :
		// these *are* valid floats, but the chance of
		// getting one on purpose is very slim
		Assert(FLOAT_AS_INT(f) != 0xCDCDCDCD, "Probably incorrect CMN_32F: 0xCDCDCDCD");
		Assert(FLOAT_AS_INT(f) != 0xDDDDDDDD, "Probably incorrect CMN_32F: 0xDDDDDDDD");

		// this works because NAN always returns false on compares 
		return (f >= -FLT_MAX && f <= FLT_MAX);
		//return (f >= std::numeric_limits<CMN_32F>::min() && 
		//	f <= std::numeric_limits<CMN_32F>::max());
	}
};

#endif /* CMNMATH_USE_VALID_NUMBER */


} // namespace core
} // namespace CmnMath

#endif /* CMNMATH_CMNMATHCORE_CONSTANTS_HPP__ */
