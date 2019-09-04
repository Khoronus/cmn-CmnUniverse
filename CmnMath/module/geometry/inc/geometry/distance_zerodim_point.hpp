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

#ifndef CMNMATH_GEOMETRY_DISTANCEZERODIMPOINT_HPP__
#define CMNMATH_GEOMETRY_DISTANCEZERODIMPOINT_HPP__

#include <cmath>

namespace CmnMath
{
namespace geometry
{

/** @brief Estimates the distance between zero dimensional structures.

Estimates the distance between geometrical structures.
@note It is a template class. It is supposed that the object has x,y,z
as public element.
*/
class DistanceZeroDimPoint
{
public:

	/** @brief Calculate the euclidean distance.

  	    Calculate the euclidean distance.
		@param[in] a First point (by default first = x, second = y).
		@param[in] a Second point (by default first = x, second = y).
		@return Return the distance between the points
		*/
	template <typename _Ty>
	static _Ty point_point_2d(const std::pair<_Ty, _Ty> &a,
		const std::pair<_Ty, _Ty> &b) {
		return std::sqrt(std::pow(a.first - b.first, 2) +
			std::pow(a.second - b.second, 2));
	}

	/** @brief Calculate the euclidean distance.

	Calculate the euclidean distance.
	@param[in] a First point.
	@param[in] b First point.
	@return Return the distance.
	*/
	template <typename _Ty>
	static CMN_32F point_point_2d(const _Ty &a, const _Ty &b)
	{
		return std::sqrt(std::pow(a.x - b.x, 2) +
			std::pow(a.y - b.y, 2));
	}

	/** @brief Calculate the euclidean distance.

	Calculate the euclidean distance.
	@param[in] a First point.
	@param[in] b First point.
	@return Return the distance.
	*/
	template <typename _Ty, typename _Ty2>
	static _Ty2 point_point_3d(const _Ty &a, const _Ty &b)
	{
		//return std::pow( std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + 
		//	std::pow(a.z - b.z, 2), 1.0f / 3.0f );
		return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) +
			std::pow(a.z - b.z, 2));
	}

	/** @brief Calculate the index of the most distant points.

	Calculate the index of the most distant points.
	@param[in] v_points Set of points to analyze.
	@param[in] idx_first Index of one of the two most distant points.
	@param[in] idx_second Index of the other of the two most distant
	points.
	@return Return 1 in case of success. 0 otherwise.
	*/
	template <typename _Ty>
	static CMN_32S points_2_most_distant(const std::vector<_Ty> &v_points,
		CMN_32S &idx_first, CMN_32S &idx_second)
	{
		// Calculate the extremes
		CMN_32S s = v_points.size();
		if (s <= 1) return 0;
		idx_first = idx_second = -1;
		CMN_32F dist = 0;
		for (CMN_32S i = 0; i < s; ++i)
		{
			for (CMN_32S j = i + 1; j < s; ++j)
			{
				CMN_32F d = point_point_2d(v_points[i],
					v_points[j]);
				if (dist < d) {
					dist = d;
					idx_first = i; idx_second = j;
				}
			}
		}
		return 1;
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_DISTANCEZERODIMPOINT_HPP__ */
