/**
* @file barycentric_twodim_trianglexyz.hpp
* @brief Header of all the files related to the statistics
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

#ifndef CMNMATH_GEOMETRY_BARYCENTRICTWODIMTRIANGLEXYZ_HPP__
#define CMNMATH_GEOMETRY_BARYCENTRICTWODIMTRIANGLEXYZ_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to calculate the barycentric coordinate of a triangle.
*/
template <typename _Ty3>
class BarycentricTwoDimTriangleXYZ
{
public:

	// Compute barycentric coordinates (u, v, w) for
	// point p with respect to triangle (a, b, c)
	// link: http://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
	static _Ty3 barycentric(const _Ty3 &a, const _Ty3 &b, const _Ty3 &c, 
				const _Ty3 &p)
	{
		_Ty3 v0 = b - a, v1 = c - a, v2 = p - a;
		float d00 = v0.dot(v0);
		float d01 = v0.dot(v1);
		float d11 = v1.dot(v1);
		float d20 = v2.dot(v0);
		float d21 = v2.dot(v1);
		float denom = d00 * d11 - d01 * d01;
		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
		return _Ty3(u, v, w);
	}

	/** @brief Calculate the Cartesian coordinates of a barycentric point.
	*/
	static _Ty3 cartesian(const _Ty3 &p0, const _Ty3 &p1, const _Ty3 &p2,
		const _Ty3 &barycentric) {
		return barycentric.x * p0 + barycentric.y * p1 + barycentric.z * p2;
	}
};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_BARYCENTRICTWODIMTRIANGLEXYZ_HPP__ */
