/**
* @file statistics_headers.hpp
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

#ifndef CMNMATH_GEOMETRY_AREATWODIMTRIANGLE_HPP__
#define CMNMATH_GEOMETRY_AREATWODIMTRIANGLE_HPP__

#include "vector_operation_xyz.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Estimates the area of a two dimensional triangle.

    Estimates the area of a two dimensional triangle.
*/
class AreaTwoDimTriangle
{
public:

	/** @brief It calculates the area of a 3D triangle
	@link http://math.stackexchange.com/questions/128991/how-to-calculate-area-of-3d-triangle
	*/
	template <typename _Ty3, typename REAL = float>
	static REAL area_triangle(const _Ty3 &p0, const _Ty3 &p1,
		const _Ty3 &p2) {
		_Ty3 ab = p1 - p0;
		_Ty3 ac = p2 - p0;
		REAL m_ab = VectorOperationXYZ<_Ty3>::magnitude_3d<REAL>(ab);
		REAL m_ac = VectorOperationXYZ<_Ty3>::magnitude_3d<REAL>(ac);
		REAL theta = std::acos(ab.dot(ac) / (m_ab * m_ac));
		return m_ab * m_ac * sin(theta) * 0.5;
	}

};


} // namespace geometry
} // namespace CmnMath

#endif // CMNMATH_GEOMETRY_AREATWODIMTRIANGLE_HPP__
