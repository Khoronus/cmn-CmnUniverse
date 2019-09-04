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

#ifndef CMNMATH_GEOMETRY_LOCATIONTWODIMPLANE_HPP__
#define CMNMATH_GEOMETRY_LOCATIONTWODIMPLANE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

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
class LocationTwoDimPlane
{
public:

	/** @brief Determine if a point lay on a side or another of a plane.

	@link: http://math.stackexchange.com/questions/214187/point-on-the-left-or-right-side-of-a-plane-in-3d-space

	@param[in] A point of a plane.
	@param[in] B point of a plane.
	@param[in] C point of a plane.
	@param[in] X point used to determine in which side of the plane is placed.
	@return It returns a positive value or negative if the points is on left
	        or right side of the plane.
			Return 0 if unable to estimate the determinant.
	*/
	static int plane_point_side(_Ty &A, _Ty &B, _Ty &C, _Ty &X)
	{
		_Ty B1 = B - A;
		_Ty C1 = C - A;
		_Ty X1 = X - A;
		//cv::Mat B1C1X1(3, 3, CV_64FC1);
		//B1C1X1.at<double>(0, 0) = B1.x;
		//B1C1X1.at<double>(0, 1) = B1.y;
		//B1C1X1.at<double>(0, 2) = B1.z;
		//B1C1X1.at<double>(1, 0) = C1.x;
		//B1C1X1.at<double>(1, 1) = C1.y;
		//B1C1X1.at<double>(1, 2) = C1.z;
		//B1C1X1.at<double>(2, 0) = X1.x;
		//B1C1X1.at<double>(2, 1) = X1.y;
		//B1C1X1.at<double>(2, 2) = X1.z;
		//double det = cv::determinant(B1C1X1);
		std::vector<CMN_32F> a;
		a.push_back(B1.x);
		a.push_back(B1.y);
		a.push_back(B1.z);
		a.push_back(C1.x);
		a.push_back(C1.y);
		a.push_back(C1.z);
		a.push_back(X1.x);
		a.push_back(X1.y);
		a.push_back(X1.z);
		CMN_32F det = algebralinear::MatrixOperation::mat_det33(a);
		if (det < 0) return -1;
		if (det > 0) return 1;
		return 0;
	}
};




} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_LOCATIONTWODIMPLANE_HPP__ */
