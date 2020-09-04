/**
* @file generator_zerodim_point.hpp
* @brief Header of the classes and functions that generates 3D structures.
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

#ifndef CMNMATH_GEOMETRY_GENERATORZERODIM_LOXODROME_HPP__
#define CMNMATH_GEOMETRY_GENERATORZERODIM_LOXODROME_HPP__

#include <vector>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to generate the vertexes of a N dimensional structures with 
           points.

    Class to generate the vertexes of a N dimensional structures with points.
*/
template <typename _Ty>
class GeneratorZeroDimLoxodrome
{
public:

	/** @brief Function to create a set of points which represents a Rhumb line.

	Function to create a set of points which represents a Rhumb line (loxodrome).
	@param[in] a Latitude interval [0.01, 1] Usually 1.
	@param[in] r Radius of the Rhub line. Usually 1.
	@param[in] k Longitude interval [0.01, 1] Usually 0.09.
	@param[in] lambda0 Crossing longitude where passing the equator. Usually 0.
	@param[in] minlambda Min interval value for the longitude. A -float_max is
	                     recommended to preserve the default value. 0 to start
	                     from the equator.
	@param[in] maxlambda Max interval value for the longitude. A +float_max is
	                     recommended to preserve the default value. 0 to stop
	                     to the equator.
	@param[in] num_points Number of points desired (i.e. 20). It follows the
	                      angular interval not distance!
	@param[out] points Vertexes.

	@link http://en.wikipedia.org/wiki/Rhumb_line
	@link http://stackoverflow.com/questions/3738384/stable-cotangent
	@link http://en.wikipedia.org/wiki/Gudermannian_function
	@link http://mathematica.stackexchange.com/questions/26295/how-can-i-plot-a-loxodrome
	*/
	static void loxodrome(CMN_32F a, CMN_32F r, CMN_32F k, CMN_32F lambda0,
		CMN_32F minlambda, CMN_32F maxlambda, CMN_32S num_points,
		std::vector<_Ty> &points)
	{
		// check no error condition
		if (num_points <= 1 || k == 0) return;

		CMN_32F v0 = 2.0f * a * core::kPIf / k;
		CMN_32F maxval = (std::min)(v0, maxlambda);
		CMN_32F minval = (std::max)(-maxval, minlambda);
		CMN_32F singleinterval = (maxval - minval) / num_points;
		for (CMN_32F lambda = minval; lambda <= maxval; lambda += singleinterval)
		{
			CMN_32F beta = lambda - lambda0;
			CMN_32F m = beta;//std::tan(CmnMath::core::kPI / 2 - beta);
			CMN_32F ch = std::cosh(k * m);
			CMN_32F c = std::cos(lambda);
			CMN_32F s = std::sin(lambda);
			CMN_32F th = std::tanh(k * m);
			CMN_32F x = r * c / ch;
			CMN_32F y = r * s / ch;
			CMN_32F z = r * th;
			points.push_back(_Ty(x, y, z));
		}
	}


	/** @brief This function prune the points generated wih the loxodrome based
	           on the distance between the points in the spiral.

	     This function prune the points generated wih the loxodrome based
	     on the distance between the points in the spiral.
		 It preserves the equidistance between the points.
		 @param[in] points The set to prune.
		 @param[in] points_desired The total number of points desired.
		 @param[out] points_out The container where the new points are insert.
	*/
	static void prune_loxodrome(std::vector<_Ty> &points, CMN_32S points_desired,
		std::vector<_Ty> &points_out) {
		// sum the distance to estimate the equidistance between the points
		CMN_32F d = 0;
		CMN_32S n = points.size();
		for (CMN_32S i = 0; i < n - 1; ++i)
		{
			d += CmnMath::geometry::DistanceZeroDimPoint::point_point_3d<cv::Point3f, CMN_32F>(
				points[i], points[i + 1]);
		}
		CMN_32F dbin = d / (points_desired - 1);
		CMN_32F dexpected = 0;
		CMN_32F dlastmem = -1;
		d = 0;
		for (CMN_32S i = 0; i < n - 1; ++i)
		{
			d += CmnMath::geometry::DistanceZeroDimPoint::point_point_3d<cv::Point3f, CMN_32F>(
				points[i], points[i + 1]);
			if (d >= dexpected) {// && d > dlastmem + 0.9) {
				dexpected += dbin;
				dlastmem = d;
				points_out.push_back(points[i]);
			}
		}
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_GENERATORZERODIM_LOXODROME_HPP__ */
