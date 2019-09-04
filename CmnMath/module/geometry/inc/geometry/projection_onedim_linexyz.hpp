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

#ifndef CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXYZ_HPP__
#define CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXYZ_HPP__

#include "distance_zerodim_point.hpp"

namespace CmnMath
{
namespace geometry
{

template <typename _Ty>
class ProjectOneDimLineXYZ
{
public:

	/** @brief Calculate the projection of a point over a line.

	    Calculate the projection of a point over a line.
		@param[in] point The point to project.
		@param[in] lineStart Where the line start.
		@param[in] lineEnd Where the line end.
		@return Return the position where the point is located.
		@remark The point is expected to support the x,y,z coordinate.
	*/
	static _Ty point2line(const _Ty &point, const _Ty &lineStart, const _Ty &lineEnd)
	{
		_Ty rhs = point - lineStart;
		_Ty vector2 = lineEnd - lineStart;
		CMN_32F magnitude = VectorOperationXYZ<_Ty>::magnitude_3d<CMN_32F>(vector2);
		_Ty lhs = vector2;
		if (magnitude > 1E-06f)
		{
			lhs = (_Ty)(lhs * (1 / magnitude));
		}
		//CMN_32F num2 = clamp(Vector3.Dot(lhs, rhs), 0f, magnitude);
		//CMN_32F num2 = clamp(lhs.dot(rhs), 0.0f, magnitude);
		CMN_32F num2 = lhs.dot(rhs);
		return (lineStart + ((_Ty)(lhs * num2)));
	}

	
};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXYZ_HPP__ */
