/**
* @file parametric_twodim_circle.hpp
* @brief Header of all the class related to a parametric function for circle.
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

#ifndef CMNMATH_GEOMETRY_PARAMETRICTWODIMCIRCLE_HPP__
#define CMNMATH_GEOMETRY_PARAMETRICTWODIMCIRCLE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/**
http://demonstrations.wolfram.com/ParametricEquationOfACircleIn3D/
http://stackoverflow.com/questions/13977354/build-circle-from-3-points-in-3d-space-implementation-in-c-or-c
*/
//class ParametricCircle
//{
//public:
//
//	ParametricCircle() { }
//
//	void toParametric(float elevation, float azimuth) {
//		n_.x = std::cos(elevation) * std::sin(azimuth);
//		n_.y = std::sin(azimuth) * std::sin(elevation);
//		n_.z = std::cos(azimuth);
//
//		u_.x = -std::sin(elevation);
//		u_.y = std::cos(elevation);
//		u_.z = 0;
//
//		nxu_.x = std::cos(azimuth) * std::cos(elevation);
//		nxu_.y = std::cos(azimuth) * std::sin(elevation);
//		nxu_.z = -std::sin(azimuth);
//	}
//
//	void estimate(float r, cv::Point3f &C, float t, cv::Point3f &p) {
//		p = r * std::cos(t) * u_ + r * std::sin(t) * nxu_ + C;
//	}
//
//	void toParametric(cv::Point3f &C, cv::Point3f &xyz)
//	{
//		CmnMath::geometry::Plane plane(CmnMath::algebralinear::Vector3f(xyz.x, xyz.y, xyz.z),
//			CmnMath::algebralinear::Vector3f(-xyz.x, -xyz.y, -xyz.z), CmnMath::algebralinear::Vector3f(0, 0, -1));
//		CmnMath::algebralinear::Vector3f v3f = plane.n.normalized();
//		n_ = cv::Point3f(v3f.x, v3f.y, v3f.z);
//		u_ = xyz - C;
//		v_ = n_.cross(u_);
//		//std::cout << n_ << " " << u_ << " " << v_ << std::endl;
//	}
//
//	void estimate2(float r, const cv::Point3f &C, float t, cv::Point3f &p) {
//		p = C + r * std::cos(t) * u_ + r * std::sin(t) * v_;
//	}
//
//private:
//
//	cv::Point3f n_;
//	cv::Point3f u_;
//	cv::Point3f nxu_;
//	cv::Point3f v_;
//};

/** @brief Class to calculate a parametric function of a circle in a 2dim.

    Class to calculate a parametric function of a circle in a 2dim (x,y,z).
	estimate function is specialized for OpenCV cv::Point3f class.
*/
template <typename _Ty>
class ParametricCircle
{
public:

	ParametricCircle() { }

	void toParametric(CMN_32F elevation, CMN_32F azimuth) {
		n_.x = std::cos(elevation) * std::sin(azimuth);
		n_.y = std::sin(azimuth) * std::sin(elevation);
		n_.z = std::cos(azimuth);

		u_.x = -std::sin(elevation);
		u_.y = std::cos(elevation);
		u_.z = 0;

		nxu_.x = std::cos(azimuth) * std::cos(elevation);
		nxu_.y = std::cos(azimuth) * std::sin(elevation);
		nxu_.z = -std::sin(azimuth);
	}

	void estimate(CMN_32F r, _Ty &C, CMN_32F t, _Ty &p) {
		p = r * std::cos(t) * u_ + r * std::sin(t) * nxu_ + C;
	}

	void toParametric(const _Ty &fix_point, _Ty &C, _Ty &xyz)
	{
		CmnMath::geometricprimitive::Plane plane(CmnMath::algebralinear::Vector3f(xyz.x, xyz.y, xyz.z),
			CmnMath::algebralinear::Vector3f(-xyz.x, -xyz.y, -xyz.z),
			CmnMath::algebralinear::Vector3f(fix_point.x, fix_point.y, fix_point.z));
		CmnMath::algebralinear::Vector3f v3f = plane.n.normalized();
		n_ = _Ty(v3f.x, v3f.y, v3f.z);
		u_ = xyz - C;
		v_ = n_.cross(u_);
		//std::cout << n_ << " " << u_ << " " << v_ << std::endl;
	}

	void estimate2(CMN_32F r, const _Ty &C, CMN_32F t, _Ty &p) {
		p = C + r * std::cos(t) * u_ + r * std::sin(t) * v_;
	}

	void get_angle(CMN_32F r, const _Ty &C, const _Ty &p, CMN_32F &t) {
		CMN_32F Ax = (p.x - C.x) / r;
		CMN_32F Ay = (p.y - C.y) / r;
		CMN_32F Az = (p.z - C.z) / r;
		CMN_32F Ux = u_.x;
		CMN_32F Vx = v_.x;
		CMN_32F Uy = u_.y;
		CMN_32F Vy = v_.y;
		CMN_32F Uz = u_.z;
		CMN_32F Vz = v_.z;
		CMN_32F val0 = (Ay * Ux - Ax * Uy) / (Vy * Ux - Vx * Uy);
		CMN_32F val1 = (Az * Ux - Ax * Uz) / (Vz * Ux - Vx * Uz);
		//std::cout << Ux << " " << Uy << " " << Vx << " " << Vy << " " << val0 << " " << val1 << std::endl;
		t = std::asin(val1);
		//t = 0;
	}

	void debug_showparams() {
		std::cout << "n: " << n_ << std::endl;
		std::cout << "u: " << u_ << std::endl;
		std::cout << "nxu: " << nxu_ << std::endl;
		std::cout << "v: " << v_ << std::endl;
	}

private:

	_Ty n_;
	_Ty u_;
	_Ty nxu_;
	_Ty v_;
};



} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_PARAMETRICTWODIMCIRCLE_HPP__ */
