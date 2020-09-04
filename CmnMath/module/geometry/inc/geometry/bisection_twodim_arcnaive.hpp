/**
* @file bisection_onedim_line.hpp
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

#ifndef CMNMATH_GEOMETRY_BISECTIONTWODIMARCNAIVE_HPP__
#define CMNMATH_GEOMETRY_BISECTIONTWODIMARCNAIVE_HPP__

#include "algebralinear/inc/algebralinear/norm.hpp"
#include "trigonometry/inc/trigonometry/bisection_angle.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Bisection of an arc in a naive solution.
*/
template <typename _Ty2, typename REAL = float>
class BisectionTwoDimArcnaive
{
public:

	/** @brief Get the arc information. Lenght and and most distant vertexes.
	*/
	static bool get_arc_3pts(std::vector<_Ty2> &pts,
		_Ty2 &p0, _Ty2 &p1, _Ty2 &pbisec) {

		// Get the maximum distance of two points on an arc
		REAL L = 0;
		if (!get_arc_max_distance(pts, L, p0, p1)) return false;
		size_t s = pts.size();

		//cv::Mat out(512, 512, CV_8UC3, cv::Scalar::all(0));

		// Get the average bisec position given the n points
		std::vector<float> angles;
		for (auto it : pts) {
			float a0 = std::atan2(it.y, it.x);
			a0 = (a0 > 0 ? a0 : (2 * CmnMath::core::kPI + a0));
			//std::cout << "a: " << a0 << std::endl;
			angles.push_back(a0);
			//cv::circle(out, cv::Point2f(it.x * 256 + 256, it.y * 256 + 256), 1, cv::Scalar(0, 255, 0), -1);
			//cv::imshow("out", out);
			//cv::waitKey();
		}
		float theta, R;
		CmnMath::statistics::directional::SeriesAnalysis<float>::mean(angles, theta, R);
		//std::cout << "Angles: " << theta << " " << R << std::endl;
		// Get the bisec of the arc between p0 and p1
		float a;
		_Ty2 pa;
		get_bisec_arc_naive(pts, p0, p1, 0.1f, pa, a);
		a = theta;
		pa = cv::Point2f(std::cos(a), std::sin(a));

		//cv::circle(out, cv::Point2f(p0.x * 256 + 256, p0.y * 256 + 256), 3, cv::Scalar(0, 0, 255), 2);
		//cv::circle(out, cv::Point2f(p1.x * 256 + 256, p1.y * 256 + 256), 3, cv::Scalar(255, 0, 255), 2);
		//cv::circle(out, cv::Point2f(pa.x * 256 + 256, pa.y * 256 + 256), 3, cv::Scalar(0, 255, 255), 2);
		//cv::imshow("out", out);
		//cv::waitKey(0);


		// Get the direction of the extremes compared to the temporary bisection
		float signs[2];
		signs[0] = CmnMath::geometry::Sign2D<_Ty2>::sign(p0, _Ty2(0, 0), pa);
		signs[1] = CmnMath::geometry::Sign2D<_Ty2>::sign(p1, _Ty2(0, 0), pa);
		signs[0] = signs[0] < 0 ? -1 : 1;
		signs[1] = signs[1] < 0 ? -1 : 1;

		// Test one side of the collection of points at time to calculate the
		// distance from the bisec.
		// cycle 2 because 2 possible direction (left or right)
		for (int k = 0; k < 2; ++k) {

			float max_distance = 0;

			// Test the points on the p0 direction
			for (size_t i = 0; i < s; ++i) {
				float a0 = std::atan2(pts[i].y, pts[i].x);

				// Get the current point position
				float sign_tmp = CmnMath::geometry::Sign2D<_Ty2>::sign(pts[i],
					_Ty2(0, 0), pa);
				sign_tmp = sign_tmp < 0 ? -1 : 1;

				float d = get_angle_max_distance(pts[i], pa);
				if (sign_tmp == signs[k]) {
					if (d > max_distance) {
						max_distance = d;
						k == 0 ? p0 = pts[i] : p1 = pts[i];
					}
				}
			}
		}

		// Recalculate the output bisec with the final extremes
		get_bisec_arc_naive(pts, p0, p1, 0.1f, pbisec, a);

		//cv::circle(out, cv::Point2f(p0.x * 256 + 256, p0.y * 256 + 256), 3, cv::Scalar(0, 0, 255), 2);
		//cv::circle(out, cv::Point2f(p1.x * 256 + 256, p1.y * 256 + 256), 3, cv::Scalar(255, 0, 255), 2);
		//cv::circle(out, cv::Point2f(pbisec.x * 256 + 256, pbisec.y * 256 + 256), 3, cv::Scalar(0, 255, 255), 2);
		//cv::imshow("out", out);
		//cv::waitKey(0);

		return true;
	}

private:

	/** @brief It calculates the maximum distances of points of an arc of
	circumferences.

	It calculates the maximum distances of points of an arc of
	circumferences.

	@param[in] p0 First extreme
	@param[in] p1 Second extreme
	@return It returns the distance
	*/
	static REAL get_angle_max_distance(_Ty2 &p0, _Ty2 &p1) {
		REAL a0 = std::atan2(p0.y, p0.x);
		REAL a1 = std::atan2(p1.y, p1.x);
		REAL a = a1 - a0;
		if (a > CmnMath::core::kPI) a -= CmnMath::core::kPI * 2;
		if (a < -CmnMath::core::kPI) a += CmnMath::core::kPI * 2;
		return std::abs(a);
	}


	/** @brief It gets the maximum distances between points in a arc of
	circumnference.

	@param[in] pts Collection of points on the arc
	@param[out] L max distance
	@param[out] p0 First extreme
	@param[out] p1 Second extreme
	*/
	static bool get_arc_max_distance(std::vector<_Ty2> &pts, REAL &L,
		_Ty2 &p0, _Ty2 &p1) {
		size_t s = pts.size();
		if (s < 2) return false;
		L = 0;
		REAL max_distance = 0;

		for (size_t i = 0; i < s; ++i) {
			float a0 = std::atan2(pts[i].y, pts[i].x);
			for (size_t j = i + 1; j < s; ++j) {
				REAL a1 = std::atan2(pts[j].y, pts[j].x);
				REAL theta, R;
				REAL  a = a1 - a0;
				if (a > CmnMath::core::kPI) a -= CmnMath::core::kPI * 2;
				if (a < -CmnMath::core::kPI) a += CmnMath::core::kPI * 2;
				if (std::abs(a) > max_distance) {
					max_distance = std::abs(a);
					p0 = pts[i]; p1 = pts[j];
				}
			}
		}
		L = max_distance;
	}

	/** @brief It gets the bisec of the arc.

	It gets the bisec of the arc. Since two solution are possible,
	the first result is tested with the collection of points which describe
	the arc. If no point are found, PI is add to the bisec angle.

	@param[in] pts Collection of points
	@param[in] p0 First vertex of arc
	@param[in] p1 Second vertex of arc
	@param[in] angle_test The maximum research angle to verify that the bisec
	is in the right direction.
	@param[out] pa Position of the bisec
	@param[out] a Angle of the bisec (range any)
	*/
	static void get_bisec_arc_naive(std::vector<_Ty2> &pts,
		_Ty2 &p0, _Ty2 &p1, REAL value_test,
		_Ty2 &pa, REAL &a) {

		size_t s = pts.size();
		// Get the temporary data
		REAL a0 = std::atan2(p0.y, p0.x);
		REAL a1 = std::atan2(p1.y, p1.x);
		a0 = (a0 > 0 ? a0 : (2 * CmnMath::core::kPI + a0));
		a1 = (a1 > 0 ? a1 : (2 * CmnMath::core::kPI + a1));
		a = CmnMath::trigonometry::BisectionAngle<REAL>::bisectAngle0_2PI(a0,
			a1);
		pa = _Ty2(std::cos(a), std::sin(a));

		// test if the middle point is in the right direction
		// NAIVE. Implement a better algebrical solution
		bool found = false;
		for (size_t i = 0; i < s; ++i) {
			float d =
				CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<_Ty2>(
				pts[i], pa);
			if (d < value_test) {
				std::cout << "pts[i] " << pts[i] << " " << pa << " " << value_test << std::endl;
				found = true;
				break;
			}
		}
		if (!found) {
			a += CmnMath::core::kPI;
			a = (a > 0 ? a : (2 * CmnMath::core::kPI + a));
			pa = _Ty2(std::cos(a), std::sin(a));
		}
	}
};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_BISECTIONONEDIMLINE_HPP__ */
