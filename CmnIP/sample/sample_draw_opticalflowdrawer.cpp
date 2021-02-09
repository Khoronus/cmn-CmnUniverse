/**
* @file sample_drawing_map2d.cpp
* @brief Example of the visualization of the chart radar type.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.0.1
*
*/

#include <iostream>

#include "opencv2/video/video.hpp"

#include "draw/inc/draw/draw_headers.hpp"

namespace
{

/** @brief Test function.
*/
void test()
{
	cv::VideoCapture vc(0);
	if (!vc.isOpened()) {
		std::cout << "Unable to open the video." << std::endl;
		return;
	}

	cv::Mat prevgray, flow, cflow;
	while (true) //Show the image captured in the window and repeat
	{
		cv::Mat frameReference;
		vc >> frameReference;
		if (frameReference.empty()) continue;
		//cv::resize(frameReference, frameReference, cv::Size(32, 32));

		////////////////////////////////// Elaboration ////////////////////////////////////////

		// Dense
		cv::Mat gray;
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(frameReference, gray, CV_BGR2GRAY);
#elif CV_MAJOR_VERSION == 4
		cv::cvtColor(frameReference, gray, cv::COLOR_BGR2GRAY);
#endif
		if (prevgray.empty()) {
			prevgray = gray;
		}
		if (prevgray.data)
		{
			int of_size = 2;
			int d_size = 1;

			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, of_size, 3, 5, 1.2, 0);
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
#elif CV_MAJOR_VERSION == 4
			cv::cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);
#endif
			CmnIP::draw::OpticalFlowDrawer::flow2rgb(flow, cflow);
			if (!cflow.empty()) cv::imshow("flow_rgb", cflow);
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
#elif CV_MAJOR_VERSION == 4
			cv::cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);
#endif
			CmnIP::draw::OpticalFlowDrawer::drawOptFlowMap(flow, cflow, 10);
			if (!cflow.empty()) cv::imshow("flow_lines", cflow);
		}

		std::swap(prevgray, gray);

		char c = cv::waitKey(1);
		if (c == 27) break;
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
	std::cout << "Test optical flow drawer" << std::endl;
	test();
	return 0;
}

#endif
