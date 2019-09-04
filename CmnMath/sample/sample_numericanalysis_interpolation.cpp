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
	// Linear interpolation
	std::vector< cv::Point2f > v_points2f, v_out2f;
	for (size_t i = 0; i < v_points.size(); i++)
		v_points2f.push_back(cv::Point2f(v_points[i].x, v_points[i].y));
	CmnMath::numericalanalysis::InterpolateLinear::estimate<cv::Point2f>(v_points2f, v_out2f);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v_out2f.begin(); it != v_out2f.end(); it++)
#else
	for (std::vector< cv::Point2f >::const_iterator it = v_out2f.begin(); it != v_out2f.end(); it++)
#endif
	{
		cv::rectangle(m, cv::Point(it->x - 1, it->y - 1),
			cv::Point(it->x + 1, it->y + 1), cv::Scalar(30, 80, 200), -1);
	}

	// Linear interpolation
	if (true)
	{
		// Interpolations
		std::vector < cv::Point3f > v_pt = v_points;
		for (CmnMath::CMN_32S i = 0; i < 3; i++)
			CmnMath::numericalanalysis::Chaikin<cv::Point3f>::IncreaseLod(v_pt);

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_pt.begin(); it != v_pt.end(); ++it)
#else
		for (std::vector < cv::Point3f >::const_iterator it = v_pt.begin(); it != v_pt.end(); ++it)
#endif
		{
			cv::rectangle(m, cv::Point(it->x - 1, it->y - 1),
				cv::Point(it->x + 1, it->y + 1), cv::Scalar(0, 255), -1);
		}
		std::vector< cv::Point3f > v_out;
		CmnMath::numericalanalysis::clamped_bSpline<cv::Point3f>::estimate(v_points, 10, v_out);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_out.begin(); it != v_out.end(); ++it)
#else
		for (std::vector< cv::Point3f >::const_iterator it = v_out.begin(); it != v_out.end(); ++it)
#endif
		{
			cv::rectangle(m, cv::Point(it->x - 1, it->y - 1),
				cv::Point(it->x + 1, it->y + 1), cv::Scalar(255), -1);
		}
		CmnMath::numericalanalysis::nurbsCurve <cv::Point3f>::estimate(v_points, 100, v_out);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_out.begin(); it != v_out.end(); ++it)
#else
		for (std::vector< cv::Point3f >::const_iterator it = v_out.begin(); it != v_out.end(); ++it)
#endif
		{
			cv::rectangle(m, cv::Point2f(it->x - 1, it->y - 1),
				cv::Point2f(it->x + 1, it->y + 1), cv::Scalar(0, 255, 255), -1);
		}
		CmnMath::numericalanalysis::BezierCurves<cv::Point3f>::estimate(v_points, 100, v_out);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_out.begin(); it != v_out.end(); ++it)
#else
		for (std::vector< cv::Point3f >::const_iterator it = v_out.begin(); it != v_out.end(); ++it)
#endif
		{
			cv::rectangle(m, cv::Point2f(it->x - 1, it->y - 1),
				cv::Point2f(it->x + 1, it->y + 1), cv::Scalar(170, 200, 120), -1);
		}
	}

	// Show the original points position
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v_points.begin(); it != v_points.end(); ++it)
#else
	for (std::vector< cv::Point3f >::const_iterator it = v_points.begin(); it != v_points.end(); ++it)
#endif
	{
		cv::rectangle(m, cv::Point2f(it->x - 2, it->y - 2),
			cv::Point2f(it->x + 2, it->y + 2), cv::Scalar(0, 0, 255), -1);
	}
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
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test interpolation" << std::endl;
	test();
	return 0;
}

#else

int main(int argc, char *argv[])
{
	std::cout << "Test interpolation" << std::endl;
	return 0;
}

#endif /* USE_OPENCV */