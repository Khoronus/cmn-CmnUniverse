/**
* @file arithmetic.hpp
* @brief Arithmetic operation
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
* @original author Geometric Tools LLC
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_ARITHMETIC_ARITHMETIC_HPP_
#define CMNMATH_ARITHMETIC_ARITHMETIC_HPP_

#include <cmath>
#include <type_traits>

#include "IEEEBinary16.hpp"
#include "BSNumber.hpp"
#include "BSRational.hpp"
#include "UIntegerAP32.hpp"
#include "UIntegerFP32.hpp"

namespace CmnMath
{
namespace arithmetic
{

class Arithmetic
{
public:
    // The tag-dispatch pattern is used for template-parameter-controlled
    // instantiation of mathematical functions.  See GteFunctions.h for
    // examples of how to use this type-trait system.

    enum Type
    {
        IS_INVALID,             // not an arithmetic type
        IS_FLOATING_POINT,      // 'float' or 'double' or 'long double'
        IS_FP16,                // IEEEBinary16
        IS_BINARY_SCIENTIFIC    // BSNumber or BSRational
    };

    typedef std::integral_constant<Type, IS_INVALID> IsInvalidType;
    typedef std::integral_constant<Type, IS_FLOATING_POINT> IsFPType;
    typedef std::integral_constant<Type, IS_FP16> IsFP16Type;
    typedef std::integral_constant<Type, IS_BINARY_SCIENTIFIC> IsBSType;

    template <typename T> struct WhichType : IsInvalidType{};
    template <typename U> struct WhichType<BSNumber<U>> : IsBSType{};
    template <typename U> struct WhichType<BSRational<U>> : IsBSType{};
};

template<> struct Arithmetic::WhichType<float> : IsFPType{};
template<> struct Arithmetic::WhichType<double> : IsFPType{};
template<> struct Arithmetic::WhichType<long double> : IsFPType{};
template<> struct Arithmetic::WhichType<IEEEBinary16> : IsFP16Type{};


} // namespace arithmetic
} // namespace CmnMath

#endif // CMNMATH_ARITHMETIC_ARITHMETIC_HPP_