/* @file sample_imgproc_fisheye2perspective.cpp
 * @brief Test the fisheye to perspective transformation.
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */

#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include "transform/inc/transform/transform_headers.hpp"
//#include "ts.hpp"

namespace
{

/** @brief Test the fisheye to perspective transformation.
*/
void test(int argc, char *argv[])
{
	//// Sample0
	//{
	//	cv::Mat m0 = cv::imread("..\\..\\data\\B.jpg");
	//	//cv::Mat m0 = cv::imread("..\\..\\data\\14135931-2016-01-11-165358.jpg");
	//	cv::Mat polar, fisheye;
	//	bool direction = false;
	//	cv::imshow("m0", m0);
	//	cv::waitKey(1);
	//	cv::resize(m0, m0, cv::Size(1630, 1630));
	//	CmnIP::transform::FishEye2Polar::fish2polar(m0, polar, direction);
	//	CmnIP::transform::FishEye2Polar::polar2fisheye(polar, fisheye, direction);
	//	cv::imwrite("polar0B.png", polar);
	//	cv::imwrite("fisheye0B.png", fisheye);
	//	return;
	//}

	// Cam1
	{
		cv::Rect r(210, 190, 1840 - 210, 1840 - 210);
		cv::Mat m0 = cv::imread("..\\..\\data\\test7.png");
		//cv::Mat m0 = cv::imread("..\\..\\data\\14135931-2016-01-11-165358.jpg");
		cv::Mat polar, fisheye;
		bool direction = false;
		CmnIP::transform::FishEye2Polar::fish2polar(m0(r), polar, direction);
		CmnIP::transform::FishEye2Polar::polar2fisheye(polar, fisheye, direction);
		cv::imwrite("polar1.png", polar);
		cv::imwrite("fisheye1.png", fisheye);
	}
	// Cam2
	{
		cv::Rect r(210, 190, 1840 - 210, 1840 - 210);
		cv::Mat m0 = cv::imread("..\\..\\data\\test8.png");
		cv::Mat polar, fisheye;
		bool direction = true;
		CmnIP::transform::FishEye2Polar::fish2polar(m0(r), polar, direction);
		CmnIP::transform::FishEye2Polar::polar2fisheye(polar, fisheye, direction);
		cv::imwrite("polar2.png", polar);
		cv::imwrite("fisheye2.png", fisheye);
	}
}

}	// namespace

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	//check_mapping();
	//return 0;
	std::cout << "Test fish eye -> polar" << std::endl;

	test(argc, argv);
	return 0;
}

#endif