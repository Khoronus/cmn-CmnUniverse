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

#ifndef CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXY_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXY_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with one dimension geometrical
           structures.

	Class to perform interpolations with one dimension geometrical
	structures.
*/
template <typename _Ty>
class IntersectionOneDimLineXY
{
public:

	// Finds the intersection of two lines, or returns false.
	// The lines are defined by (o1, p1) and (o2, p2).
	static CMN_BOOL line_line(const _Ty& o1, const _Ty& p1,
		const _Ty& o2, const _Ty& p2,
		_Ty& r)
	{
		_Ty x = o2 - o1;
		_Ty d1 = p1 - o1;
		_Ty d2 = p2 - o2;

		CMN_32F cross = d1.x*d2.y - d1.y*d2.x;
		if (std::abs(cross) < /*EPS*/1e-8)
			return false;

		CMN_64F t1 = (x.x * d2.y - x.y * d2.x) / cross;
		r = o1 + d1 * t1;
		return true;
	}


	/** @brief Computes the intersection between two segments.

	Computes the intersection between two segments.

	@param[in] x1 Starting point of Segment 1
	@param[in] y1 Starting point of Segment 1
	@param[in] x2 Ending point of Segment 1
	@param[in] y2 Ending point of Segment 1
	@param[in] x3 Starting point of Segment 2
	@param[in] y3 Starting point of Segment 2
	@param[in] x4 Ending point of Segment 2
	@param[in] y4 Ending point of Segment 2
	@param[out] r Intersection points of the segments.
	@return Return TRUE in case the intersection point has been found.
	*/
	static CMN_BOOL segment_segment(CMN_32S x1, CMN_32S y1, CMN_32S x2, CMN_32S y2,
		CMN_32S x3, CMN_32S y3, CMN_32S x4, CMN_32S y4,
		_Ty &r)
	{
		CMN_32S d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
		if (d == 0) return false;

		CMN_32S xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
		CMN_32S yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

		r =_Ty(xi, yi);
		if (xi < (std::min)(x1, x2) || xi >(std::max)(x1, x2)) return false;
		if (xi < (std::min)(x3, x4) || xi >(std::max)(x3, x4)) return false;
		return true;
	}


	/** @brief Computes the intersection between two segments.

	Computes the intersection between two segments.

	@param[in] x1 Starting point of Segment 1
	@param[in] y1 Starting point of Segment 1
	@param[in] x2 Ending point of Segment 1
	@param[in] y2 Ending point of Segment 1
	@param[in] x3 Starting point of Segment 2
	@param[in] y3 Starting point of Segment 2
	@param[in] x4 Ending point of Segment 2
	@param[in] y4 Ending point of Segment 2
	@param[out] x_out Intersection points of the segments.
	@param[out] y_out Intersection points of the segments.
	@return Return TRUE in case the intersection point has been found.
	*/
	template <typename _Ty2>
	static CMN_BOOL segment_segment(_Ty2 x1, _Ty2 y1, _Ty2 x2, _Ty2 y2,
		_Ty2 x3, _Ty2 y3, _Ty x4, _Ty2 y4,
		_Ty2 &x_out, _Ty2 &y_out)
	{
		_Ty2 d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
		if (d == 0) return false;

		_Ty2 xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
		_Ty2 yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

		x_out = xi;
		y_out = yi;
		if (xi < (std::min)(x1, x2) || xi >(std::max)(x1, x2)) return false;
		if (xi < (std::min)(x3, x4) || xi >(std::max)(x3, x4)) return false;
		if (yi < (std::min)(y1, y2) || yi >(std::max)(y1, y2)) return false;
		if (yi < (std::min)(y3, y4) || yi >(std::max)(y3, y4)) return false;
		return true;
	}


	/** @brief Computes the intersection between two segments.

	Computes the intersection between two segments.

	@param[in] x1 Starting point of Segment 1
	@param[in] y1 Starting point of Segment 1
	@param[in] x2 Ending point of Segment 1
	@param[in] y2 Ending point of Segment 1
	@param[in] x3 Starting point of Segment 2
	@param[in] y3 Starting point of Segment 2
	@param[in] x4 Ending point of Segment 2
	@param[in] y4 Ending point of Segment 2
	@param[out] x_out Intersection points of the segments.
	@param[out] y_out Intersection points of the segments.
	@return Return TRUE in case the intersection point has been found.
	*/
	template <typename _Ty>
	static CMN_BOOL segment_segment(_Ty x1, _Ty y1, _Ty x2, _Ty y2,
		_Ty x3, _Ty y3, _Ty x4, _Ty y4,
		_Ty &x_out, _Ty &y_out)
	{
		_Ty d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
		if (d == 0) return false;

		_Ty xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
		_Ty yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

		x_out = xi;
		y_out = yi;
		if (xi < (std::min)(x1, x2) || xi >(std::max)(x1, x2)) return false;
		if (xi < (std::min)(x3, x4) || xi >(std::max)(x3, x4)) return false;
		if (yi < (std::min)(y1, y2) || yi >(std::max)(y1, y2)) return false;
		if (yi < (std::min)(y3, y4) || yi >(std::max)(y3, y4)) return false;
		return true;
	}

};

} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXY_HPP__ */
