/**
* @file norm.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_NORM_HPP__
#define CMNMATH_ALGEBRALINEAR_NORM_HPP__

#include <memory>
#include <cmath>

namespace CmnMath
{
namespace algebralinear
{

/** @brief Class to calculate the norm of a vector.

    Class to calculate the norm of a vector.
*/
class Norm
{
public:

	template <typename _Ty3>
	static _Ty3 calculate(const _Ty3 &p)
	{
		float module = std::sqrt(std::pow(p.x, 2.0f) + std::pow(p.y, 2.0f) +
			std::pow(p.z, 2.0f));
		return _Ty3(p.x / module, p.y / module, p.z / module);
	}

};



} // namespace algebralinear
} // namespace CmnMath

#endif /* CMNMATH_ALGEBRALINEAR_NORM_HPP__ */
