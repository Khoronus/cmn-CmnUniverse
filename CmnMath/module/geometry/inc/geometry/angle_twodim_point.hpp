/**
* @file angle_twodim_point.hpp
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

#ifndef CMNMATH_GEOMETRY_ANGLETWODIMPOINT_HPP__
#define CMNMATH_GEOMETRY_ANGLETWODIMPOINT_HPP__

#include "algebralinear/inc/algebralinear/matrix3.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Estimates the angle between two points.

    Estimates the angle between two points with center origin.
*/
template <typename _Ty3>
class AngleTwoDimPoint
{
public:

	/** @brief It calculates the rotation matrix which represents the angle 
	           between two vectors.
			   The vectors are defined by two points which has 0 as origin.

		@param[in] v1 First point.
		@param[in] v1 Second point.
		@return It returns the matrix which represents the rotation matrix.
	*/
	static CmnMath::algebralinear::Matrix3 rotation_between_vectors_to_matrix(
		_Ty3& v1,
		_Ty3& v2)
	{

		CmnMath::algebralinear::Vector3f axis = v1.cross(v2);
		axis.normalize();

		_Ty3 m1c = axis.cross(v1);
		_Ty3 m2c = axis.cross(v2);

		// construct 2 matrices
		CmnMath::algebralinear::Matrix3 m1(v1.x, v1.y, v1.z,
			axis.x, axis.y, axis.z, m1c.x, m1c.y, m1c.z);
		CmnMath::algebralinear::Matrix3 m2(v1.x, v1.y, v1.z,
			axis.x, axis.y, axis.z, m1c.x, m1c.y, m1c.z);
		// calculate the difference between m1 and m2
		m1.transpose();
		CmnMath::algebralinear::Matrix3 matrix = m2 * m1;

		return matrix;
	}


	/** @brief It calculates the angle between two vectors centered
	*          to the origin.

		@param[in] a First point.
		@param[in] b Second point.
		@return It returns the angle for all the components.

		@note Please consider also CmnMath::algebralinear::Vector3f::angle
		      which calculates the angle between two vectors!
	*/
	static _Ty3 vectors2angles(
		const _Ty3& a,
		const _Ty3& b) {

		// calculate the angle with the two points
		CmnMath::algebralinear::Vector3f v(b.x - a.x, b.y - a.y, b.z - a.z);
		v.normalize();
		_Ty3 angle(std::asin(v.x), std::asin(v.y), std::asin(v.z));
		return angle;
	}
};

} // namespace geometry
} // namespace CmnMath

#endif // CMNMATH_GEOMETRY_AREATWODIMTRIANGLE_HPP__
