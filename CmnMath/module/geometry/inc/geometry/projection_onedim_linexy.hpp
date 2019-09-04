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

#ifndef CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXY_HPP__
#define CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXY_HPP__

#include "distance_zerodim_point.hpp"

namespace CmnMath
{
namespace geometry
{

template <typename _Ty>
class ProjectOneDimLineXY
{
public:

	/** @brief Given a point, it calculates the projected point on a line.

	Given a point, it calculates the projected point on a line.

	@param[in] p1x Starting point of Segment 1.
	@param[in] p1y Starting point of Segment 1.
	@param[in] p2x Ending point of Segment 1.
	@param[in] p2y Ending point of Segment 1.
	@param[in] p3x Point to project.
	@param[in] p3y Point to project.
	@param[out] outx Projected point position.
	@param[out] outy Projected point position.
	@return Return TRUE in case the the point is inside the segment.
	*/
	static CMN_BOOL point2Line(_Ty p1x, _Ty p1y, _Ty p2x, _Ty p2y, _Ty p3x, 
		_Ty p3y, _Ty &outx, _Ty &outy) {
		CMN_BOOL isValid = false;

		if (p1x == p2x && p1y == p2y) p1x -= 0.00001;

		_Ty U = ((p3x - p1x) * (p2x - p1x)) + ((p3y - p1y) * (p2y - p1y));

		_Ty Udenom = std::pow(p2x - p1x, 2) + std::pow(p2y - p1y, 2);

		U /= Udenom;

		outx = p1x + (U * (p2x - p1x));
		outy = p1y + (U * (p2y - p1y));

		_Ty minx, maxx, miny, maxy;

		minx = (std::min)(p1x, p2x);
		maxx = (std::max)(p1x, p2x);

		miny = (std::min)(p1y, p2y);
		maxy = (std::max)(p1y, p2y);

		isValid = (outx >= minx && outx <= maxx) &&
			(outy >= miny && outy <= maxy);

		return isValid;
	}

	
};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_PROJECTIONONEDIMLINEXY_HPP__ */
