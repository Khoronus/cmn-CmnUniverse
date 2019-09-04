/**
* @file subset_zerodim_point.hpp
* @brief Header of all the files for subset extraction.
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

#ifndef CMNMATH_GEOMETRY_SUBSETZERODIMPOINT_HPP__
#define CMNMATH_GEOMETRY_SUBSETZERODIMPOINT_HPP__

#include "distance_zerodim_point.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Estimate a subset from a set of points.

    Estimate simple subset from a set of points. Elementary algorithms are
	implemented at this level.
*/
class SubsetZeroDimPoint
{
public:

	/** @brief Calculate the equidistant points from the first.

	*/
	template <typename _Ty>
	static void equidistant(const std::vector<_Ty>& src, CMN_32S num_points,
		std::vector<_Ty>& out) {
		// sum the distance to estimate the equidistance between the points
		CMN_32F d = 0;
		size_t n = src.size();
		for (size_t i = 0; i < n - 1; ++i)
		{
			d += DistanceZeroDimPoint::point_point_3d<_Ty, CMN_32F>(
				src[i], src[i + 1]);
		}
		CMN_32F dbin = d / (num_points - 1);
		CMN_32F dexpected = 0;
		CMN_32F dlastmem = -1;
		d = 0;
		for (size_t i = 0; i < n - 1; ++i)
		{
			d += DistanceZeroDimPoint::point_point_3d<_Ty, CMN_32F>(
				src[i], src[i + 1]);
			if (d >= dexpected) {
				dexpected += dbin;
				dlastmem = d;
				out.push_back(src[i]);
			}
		}

	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_SUBSETZERODIMPOINT_HPP__ */
