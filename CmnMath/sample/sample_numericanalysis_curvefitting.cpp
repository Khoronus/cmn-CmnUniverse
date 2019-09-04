/* @file sample_numericanalysis_curvefting.hpp
* @brief Perform a sample 2D curve fitting.
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
#endif

namespace
{

/** @brief Function to test the interpolation performances.
*/
void test()
{
#ifdef USE_OPENCV
	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));

	std::vector< cv::Point3f > v_points;

	v_points.push_back(cv::Point3f(80.8224, 103.98465, 0));
	v_points.push_back(cv::Point3f(82.2746, 105.08662, 0));
	v_points.push_back(cv::Point3f(83.4259, 106.17513, 0));

	CmnMath::numericalanalysis::CCurveFit ccf;
	//ccf.AddPoints(80.8224, 4.98465);
	//ccf.AddPoints(82.2746, 5.08662);
	//ccf.AddPoints(83.4259, 5.17513);

	//for (int i = 0; i < 10; ++i) {
	//	v_points.push_back(cv::Point3f(i * 30 + 10, rand() % m.rows, 0));
	//	//ccf.AddPoints(i * 30 + 10, rand() % m.rows);
	//}

	for (auto &it : v_points) {
		ccf.AddPoints(it.x, it.y);
		cv::circle(m, cv::Point2d(it.x, it.y), 2, cv::Scalar(0, 255, 0), 1);
	}

	double a = ccf.GetATerm();
	double b = ccf.GetBTerm();
	double c = ccf.GetCTerm(); 


	for (double x = 0; x < m.cols; ++x)
	{
		double y = a * std::pow(x, 2) + b * x + c;
		//double y = a * std::pow(x, 2) - b * x + c;
		cv::circle(m, cv::Point2d(x, y), 0, cv::Scalar(0, 0, 255), 1);
	}

	cv::imshow("test", m);
	cv::waitKey(0);
#endif
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test curve fitting" << std::endl;
	test();
	return 0;
}