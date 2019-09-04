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

#ifndef CMNMATH_GEOMETRY_DISTANCEONEDIMLINE_HPP__
#define CMNMATH_GEOMETRY_DISTANCEONEDIMLINE_HPP__

#include "distance_zerodim_point.hpp"
#include "projection_onedim_linexyz.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Estimates the distance between geometrical structures in a 3D space.

    Estimates the distance between geometrical structures in a 3D space.
*/
class DistanceOneDimLine
{
public:

	/** @brief Calculate the euclidean distance.

	Calculate the euclidean distance.
	@param[in] a First point.
	@param[in] b First point.
	@return Return the distance.
	@note _Ty is a container which support x,y,z variable. _Ty2 is usually 
	    CMN_32F or CMN_64F.
	*/
	template <typename _Ty, typename _Ty2>
	static _Ty2 point_line(const _Ty &point, const _Ty &lineStart, const _Ty &lineEnd)
	{
		return VectorOperationXYZ<_Ty>::magnitude_3d<CMN_32F>(
			ProjectOneDimLineXYZ<_Ty>::point2line(point, lineStart, lineEnd) - point);
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_DISTANCE3D_HPP__ */
