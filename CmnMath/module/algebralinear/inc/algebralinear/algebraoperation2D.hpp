/**
* @file algebraoperation2D.hpp
* @brief Algebra operation
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

#ifndef CMNMATH_ALGEBRALINEAR_ALGEBRAOPERATION2D_HPP__
#define CMNMATH_ALGEBRALINEAR_ALGEBRAOPERATION2D_HPP__

namespace CmnMath
{
namespace algebralinear
{

/** @brief Class to perform algebra operation
*/
template <typename _Ty2, typename REAL>
class AlgebraOperation2D
{
public:

	/** @brief It performs the perp product of two vectors

		@link http://mathworld.wolfram.com/PerpDotProduct.html
	*/
	static REAL perp(const _Ty2 &u, const _Ty2 &v) {
		return ((u).x * (v).y - (u).y * (v).x);
	}
};

} // namespace algebralinear
} // namespace CmnMath

#endif // CMNMATH_ALGEBRALINEAR_ALGEBRAOPERATION2D_HPP__