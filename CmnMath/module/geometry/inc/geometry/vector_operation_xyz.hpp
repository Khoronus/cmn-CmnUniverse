/**
* @file vector_operation_xyz.hpp
* @brief Class to perform vector operation over a class which support xyz vars.
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

#ifndef CMNMATH_GEOMETRY_VECTOROPERATIONXYZ_HPP__
#define CMNMATH_GEOMETRY_VECTOROPERATIONXYZ_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to perform elementary operations on a vector.
*/
template <typename _Ty>
class VectorOperationXYZ
{
public:

	template <typename _Ty2>
	static _Ty2 dot_product(const _Ty &a, const _Ty &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	/** @brief Cross product
	*/
	static _Ty cross(const _Ty &a, const _Ty &b)
	{
		return _Ty(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}
	/** @brief Normalize a vector with origin on 0.
	*/
	static _Ty unit(const _Ty &a)
	{
		CMN_64F v = std::sqrt(dot_product<CMN_64F>(a, a));
		if (v == 0) return a;
		return _Ty(a.x / v, a.y / v, a.z / v);
	}
	/** @brief Normalize a vector with origin on 0.
	*/
	static _Ty unitf(const _Ty &a)
	{
		CMN_32F v = std::sqrtf(dot_product<CMN_32F>(a, a));
		if (v == 0) return a;
		return _Ty(a.x / v, a.y / v, a.z / v);
	}

	/** @brief Calculate the euclidean distance.

		Calculate the euclidean distance.
		@param[in] a First point.
		@param[in] b First point.
		@return Return the distance.
	*/
	template <typename _Ty2>
	static _Ty2 magnitude_3d(const _Ty &a)
	{
		return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2) +
			std::pow(a.z, 2));
	}
	/** @brief Calculate the euclidean distance.

	Calculate the euclidean distance.
	@param[in] a First point.
	@param[in] b First point.
	@return Return the distance.
	*/
	template <typename _Ty2>
	static _Ty2 magnitude_3df(const _Ty &a)
	{
		return std::sqrtf(std::powf(a.x, 2) + std::powf(a.y, 2) +
			std::powf(a.z, 2));
	}


};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_VECTOROPERATIONXYZ_HPP__ */
