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

#ifndef CMNMATH_TRIGONOMETRY_COSINELAW_HPP__
#define CMNMATH_TRIGONOMETRY_COSINELAW_HPP__

#include <cmath>

namespace CmnMath
{
namespace trigonometry
{

/** @brief Class to calculate circumference trigonometry operations.
*/
template <typename _Ty>
class CosineLaw
{
public:

	//! retuns the angle to side a given an arbitrary triangle of sides of length a,b,c
	static inline _Ty cosine_law_sss(_Ty a, _Ty b, _Ty c)
	{
		return std::acosf((b*b + c*c - a*a) / (2 * b*c));
	}

	//! returns the length of the side across from angle in an arbitrary triangle
	static inline _Ty cosine_law_sas(_Ty len1, _Ty angle, _Ty len2)
	{
		return std::sqrtf(len1*len1 + len2*len2 - 2 * len1*len2*std::cosf(angle));
	}
};


} // namespace trigonometry
} // namespace CmnMath

#endif /* CMNMATH_TRIGONOMETRY_COSINELAW_HPP__ */
