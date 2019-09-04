/**
* @file squareroot.hpp
* @brief Simple square root calculation
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

#ifndef CMNMATH_ALGEBRALINEAR_SATURATION_HPP__
#define CMNMATH_ALGEBRALINEAR_SATURATION_HPP__

namespace CmnMath
{
namespace algebralinear
{

/** @brief It performs the clamp of an input source
*/
class Saturation
{
public:

	/** @brief Clamp the input value between the minimum and maximum range.

		Clamp the input value between the minimum and maximum range.
		@param[in] value Value to clamp.
		@param[in] vmin Minimum value. value is >= vmin
		@param[in] vmax Maximum value. value is <= vmax
		@return Return the clamped value.
		@note The template it is a 
	*/
	template <typename _Ty>
	static _Ty clamp(_Ty value, const _Ty vmin, const _Ty vmax)
	{
		if (value < vmin)
			value = vmin;
		if (value > vmax)
			value = vmax;
		return value;
	}
};

} // namespace algebralinear
} // namespace CmnMath

#endif