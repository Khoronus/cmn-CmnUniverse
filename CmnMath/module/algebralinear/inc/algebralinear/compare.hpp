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

#ifndef CMNMATH_ALGEBRALINEAR_COMPARE_HPP__
#define CMNMATH_ALGEBRALINEAR_COMPARE_HPP__

#include <cfloat>
#include <memory>
#include <cmath>

namespace CmnMath
{
namespace algebralinear
{


/** @brief It performs the numeric comparison
*/
template <typename _Ty>
class CompareNumbers
{
public:

	// tests for floating point fuzzy equalities
	static inline bool equal(const _Ty f1, const _Ty f2, const _Ty epsilon = FLT_EPSILON)
	{
		return f1 >= f2 - epsilon && f1 <= f2 + epsilon;
	}

	static inline bool lessthan(const _Ty f1, const _Ty f2, const _Ty epsilon = FLT_EPSILON)
	{   return f1 + epsilon < f2;  }

	static inline bool lessthanorequalto(const _Ty f1, const _Ty f2, const _Ty epsilon = FLT_EPSILON)
	{
		return f1 + epsilon <= f2;
	}

	static inline bool greaterthan(const _Ty f1, const _Ty f2, const _Ty epsilon = FLT_EPSILON)
	{
		return f1 - epsilon > f2;
	}

	static inline bool greaterthanorequalto(const _Ty f1, const _Ty f2, const _Ty epsilon = FLT_EPSILON)
	{
		return f1 - epsilon >= f2;
	}

	// TEMPLATE FUNCTION min
	static const _Ty& (minval)(const _Ty& _Left, const _Ty& _Right)
	{	// return smaller of _Left and _Right
		return (_Right <= _Left ? _Right : _Left);
	}

	// TEMPLATE FUNCTION min
	static const _Ty& (maxval)(const _Ty& _Left, const _Ty& _Right)
	{	// return greater of _Left and _Right
		return (_Right >= _Left ? _Right : _Left);
	}
};


} // namespace algebralinear
} // namespace CmnMath

#endif /* CMNMATH_ALGEBRALINEAR_COMPARE_HPP__ */
