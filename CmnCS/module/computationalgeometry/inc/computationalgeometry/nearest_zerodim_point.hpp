/**
* @file nearest_zerodim_point.hpp
* @brief Contains classes to measure the nearest distance.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.0.0
*
*/


#ifndef CMNCS_COMPUTATIONALGEOMETRY_NEARESTZERODIMPOINT_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_NEARESTZERODIMPOINT_HPP__

#include <limits>       // std::numeric_limits
#include <vector>
#include <map>

#include "cmncscore\inc\cmncscore\type.hpp"

namespace CmnCS
{
namespace computationalgeometry
{

/** @brief Invalid index
*/
const int kInvalidNearestIndex = -1;

/** @brief Class to manage N dimension vertex.

	Class to manage N dimension vertex.
*/
class NearestZeroDimPoint
{
public:

	/** @brief Find the nearest point
	*/
	template <typename _Ty>
	static int find_index_nearest(const _Ty &a, std::map<int, _Ty> &m_points)
	{
		float d = std::numeric_limits<float>::max();
		int id = kInvalidNearestIndex;
		for (auto it = m_points.begin(); it != m_points.end(); it++)
		{
			float dist = distance<_Ty>(a, it->second);
			if (dist < d) {
				id = it->first;
				d = dist;
			}
		}
		return id;
	}

	/** @brief Find the nearest point from a source point a and a reference point
			   point b.

		Find the nearest point from a source point a and a reference point point b.
		@param[in] src The source point to test.
		@param[in] ref The reference point to calculate the distance from.
		@param[in] angle_tolerance The maximum tolerance admitted to select the
								   point.
		@param[in] m_points The set of points to test
		@return Return the index of a nearer point. -1 otherwise.

		@example
						b


				p0
						 p1
			p2

		  a

		The nearest is p0
	*/
	template <typename _Ty>
	static int find_index_nearest(_Ty &src, _Ty &ref, float angle_tolerance,
		std::map<int, _Ty> &m_points)
	{
		float d = std::numeric_limits<float>::max();
		int id = kInvalidNearestIndex;
		float angle = std::atan2((float)(ref.y - src.y),
			(float)(ref.x - src.x));
		d = distance<cv::Point2f>(src, ref);
		for (auto it = m_points.begin(); it != m_points.end(); it++)
		{
			float angle_pts = std::atan2((float)(ref.y - it->second.y),
				(float)(ref.x - it->second.x));
			float dist = distance<_Ty>(_Ty(ref.x, ref.y), it->second);
			if (std::abs(angle - angle_pts) < angle_tolerance && dist < d) {
				id = it->first;
				d = dist;
			}
		}
		return id;
	}

private:

	template <typename _Ty>
	static float distance(const _Ty &a, const _Ty &b)
	{
		return std::sqrt(std::pow((float)(a.x - b.x), 2.0f) +
			std::pow((float)(a.y - b.y), 2.0f));
	}

};




} // namespace computationalgeometry
} // namespace CmnCS

#endif // CMNCS_COMPUTATIONALGEOMETRY_NEARESTZERODIMPOINT_HPP__