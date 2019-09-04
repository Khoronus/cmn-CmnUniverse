/* @file sample_math_interpolation.hpp
* @brief Perform a sample interpolation of 2D points.
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
* @author Various
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>

#include "numericanalysis/inc/numericanalysis/numericanalysis_headers.hpp"

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace
{

void func_interpolate(cv::Mat &m, std::vector< cv::Point3f > &v_points) {

	// Fitting
	if (true)
	{
		// Linear
		CmnMath::CMN_64L s = v_points.size();
		for (CmnMath::CMN_32U i = 0; i < s - 1; ++i)
		{
			CmnMath::CMN_64L j = i + 1;
			for (CmnMath::CMN_64F k = 0; k < 100; k += 1.0)
			{
				CmnMath::CMN_64F x = CmnMath::numericalanalysis::InterpolateLinear::estimate<CmnMath::CMN_64F>(v_points[i].x, v_points[j].x, k / 100.0);
				CmnMath::CMN_64F y = CmnMath::numericalanalysis::InterpolateLinear::estimate<CmnMath::CMN_64F>(v_points[i].y, v_points[j].y, k / 100.0);
				cv::rectangle(m, cv::Point2d(x - 1, y - 1),
					cv::Point2d(x + 1, y + 1), cv::Scalar(70, 100, 220), -1);
			}
		}


		// Cosine
		for (CmnMath::CMN_64L i = 0; i < s - 1; ++i)
		{
			CmnMath::CMN_64L j = i + 1;
			for (CmnMath::CMN_64F k = 0; k < 100; k += 1.0)
			{
				CmnMath::CMN_64F x = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::CosineInterpolate(v_points[i].x, v_points[j].x, k / 100.0);
				CmnMath::CMN_64F y = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::CosineInterpolate(v_points[i].y, v_points[j].y, k / 100.0);
				cv::rectangle(m, cv::Point2d(x - 1, y - 1),
					cv::Point2d(x + 1, y + 1), cv::Scalar(70, 255, 220), -1);
			}
		}


		// Cubic
		for (CmnMath::CMN_32U i = 0; i < s - 3; i++)
		{
			CmnMath::CMN_32U j1 = i + 1;
			CmnMath::CMN_32U j2 = i + 2;
			CmnMath::CMN_32U j3 = i + 3;
			for (CmnMath::CMN_64F k = 0; k < 100; k += 1.0)
			{
				CmnMath::CMN_64F x = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::CubicInterpolate(v_points[i].x, v_points[j1].x, v_points[j2].x, v_points[j2].x, k / 100.0);
				CmnMath::CMN_64F y = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::CubicInterpolate(v_points[i].y, v_points[j1].y, v_points[j2].y, v_points[j3].y, k / 100.0);
				cv::rectangle(m, cv::Point2d(x - 1, y - 1),
					cv::Point2d(x + 1, y + 1), cv::Scalar(70, 255, 0), -1);
			}
		}


		// Hermite
		for (CmnMath::CMN_32U i = 0; i < s - 3; i++)
		{
			CmnMath::CMN_32U j1 = i + 1;
			CmnMath::CMN_32U j2 = i + 2;
			CmnMath::CMN_32U j3 = i + 3;
			for (CmnMath::CMN_64F k = 0; k < 100; k += 1.0)
			{
				CmnMath::CMN_64F x = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::HermiteInterpolate(v_points[i].x, v_points[j1].x, v_points[j2].x, v_points[j2].x, k / 100.0, 0, 0);
				CmnMath::CMN_64F y = CmnMath::numericalanalysis::Interpolate<CmnMath::CMN_64F>::HermiteInterpolate(v_points[i].y, v_points[j1].y, v_points[j2].y, v_points[j3].y, k / 100.0, 0, 0);
				cv::rectangle(m, cv::Point2d(x - 1, y - 1),
					cv::Point2d(x + 1, y + 1), cv::Scalar(255, 55, 55), -1);
			}
		}
	}

	// Show the original points position
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v_points.begin(); it != v_points.end(); it++)
#else
	for (std::vector< cv::Point3f >::const_iterator it = v_points.begin(); it != v_points.end(); it++)
#endif
	{
		cv::rectangle(m, cv::Point2f(it->x - 2, it->y - 2),
			cv::Point2f(it->x + 2, it->y + 2), cv::Scalar(0, 0, 255), -1);
	}
}


/** @brief Example to fit a sphere.
*/
void sphere_fit()
{
	std::vector<cv::Point3f> points;
	cv::Point3f center;
	float radius;
	//points.push_back(cv::Point3f(1, 2, 3));
	//points.push_back(cv::Point3f(4, 5, 6));
	//points.push_back(cv::Point3f(7, 8, 9));
	//points.push_back(cv::Point3f(10, 11, 12));
	points.push_back(cv::Point3f(0, 0, 1));
	points.push_back(cv::Point3f(1, 0, 0));
	points.push_back(cv::Point3f(0, 1, 0));
	points.push_back(cv::Point3f(0, 0, -1));

	CmnMath::numericalanalysis::SphereFit<cv::Point3f>::points2sphere(points, center, radius);
	std::cout << "Center: " << center << " radius: " << radius << std::endl;
}



/** @brief Function to test the interpolation performances.
*/
void test()
{
	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));

	std::vector< cv::Point3f > v_points;

	//v_points.push_back(cv::Point3f(70, 380, 0));
	//v_points.push_back(cv::Point3f(100, 250, 0));
	//v_points.push_back(cv::Point3f(150, 200, 0));
	//v_points.push_back(cv::Point3f(250, 400, 0));
	//v_points.push_back(cv::Point3f(300, 100, 0));
	//v_points.push_back(cv::Point3f(350, 350, 0));
	//v_points.push_back(cv::Point3f(400, 300, 0));
	//v_points.push_back(cv::Point3f(460, 200, 0));
	//v_points.push_back(cv::Point3f(490, 270, 0));
	//v_points.push_back(cv::Point3f(146, 391, 0));
	//v_points.push_back(cv::Point3f(133, 332, 0));
	//v_points.push_back(cv::Point3f(129, 310, 0));
	//v_points.push_back(cv::Point3f(124, 287, 0));
	//v_points.push_back(cv::Point3f(123, 234, 0));
	//v_points.push_back(cv::Point3f(125, 204, 0));
	//v_points.push_back(cv::Point3f(133, 166, 0));
	//v_points.push_back(cv::Point3f(260, 9, 0));

	v_points.push_back(cv::Point3f(399, 993, 0));
	v_points.push_back(cv::Point3f(383, 931, 0));
	v_points.push_back(cv::Point3f(375, 861, 0));
	v_points.push_back(cv::Point3f(367, 701, 0));
	v_points.push_back(cv::Point3f(495, 651, 0));
	v_points.push_back(cv::Point3f(375, 613, 0));
	v_points.push_back(cv::Point3f(395, 491, 0));
	v_points.push_back(cv::Point3f(768, 0, 0));

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v_points.begin(); it != v_points.end(); it++)
#else
	for (std::vector< cv::Point3f >::iterator it = v_points.begin(); it != v_points.end(); it++)
#endif
	{
		*it = *it * (1.0 / 3.0);
	}

	func_interpolate(m, v_points);

	cv::imshow("test", m);
	cv::waitKey(0);

	sphere_fit();
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test fitting" << std::endl;
	test();
	return 0;
}

#else

int main(int argc, char *argv[])
{
	std::cout << "Test fitting" << std::endl;
	return 0;
}

#endif /* USE_OPENCV */
