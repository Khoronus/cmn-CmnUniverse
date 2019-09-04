/**
* @file sample_test_pca.cpp
* @brief Container for training/testing images
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "cmnipworld/inc/cmnipworld/cmnipworld_headers.hpp"


class Flow
{
public:

	void detect(cv::Mat &src)
	{
		// Dense
		cv::Mat gray;
		if (src.channels() == 1) {
			gray = src.clone();
		}
		else {
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(src, gray, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
#endif
		}
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
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);
#endif
			CmnIP::draw::OpticalFlowDrawer::flow2rgb(flow, cflow);
			if (!cflow.empty()) cv::imshow("flow_rgb", cflow);
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);
#endif
			CmnIP::draw::OpticalFlowDrawer::drawOptFlowMap(flow, cflow, 10);
			if (!cflow.empty()) cv::imshow("flow_lines", cflow);
		}
		std::swap(prevgray, gray);
	}


	/** maxdiv Value which the flow is divided
	maxobserv Size of the feature window
	*/
	void feature(float maxdiv, float maxobserv)
	{
		float divval = maxdiv;
		float maxval = maxobserv;
		cv::Mat m(maxval * 2 + 1, maxval * 2 + 1, CV_32FC1, cv::Scalar::all(0));
		for (int y = 0; y < flow.rows; y++)
		{
			for (int x = 0; x < flow.cols; x++)
			{
				const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
				//if (std::abs(fxy.x) < 2 && std::abs(fxy.y) < 2) continue;
				float vx = fxy.x / divval;
				float vy = fxy.y / divval;
				if (vx < -1) vx = -1;
				if (vx > 1) vx = 1;
				if (vy < -1) vy = -1;
				if (vy > 1) vy = 1;
				vx = vx * maxval + maxval;
				vy = vy * maxval + maxval;
				m.at<float>(vy, vx) += 1;
			}
		}
		double minVal, maxVal;
		cv::minMaxIdx(m, &minVal, &maxVal);
		m /= maxVal;
		//m *= 255;
		//std::cout << m << std::endl;
		cv::imshow("Feature", m);
		//std::cout << minVal << " " << maxVal << std::endl;
	}


	/** @brief Spatial non blurred time features
	*/
	void feature2()
	{
		if (flow.empty()) return;
		std::vector<cv::Mat> mm;
		for (int i = 0; i < 4; i++) {
			mm.push_back(cv::Mat(flow.size(), CV_32F, cv::Scalar::all(0)));
		}
		for (int y = 0; y < flow.rows; y++)
		{
			for (int x = 0; x < flow.cols; x++)
			{
				const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
				float vx = fxy.x;
				float vy = fxy.y;
				if (vx < -1) mm[0].at<float>(y, x) = vx;
				if (vx > 1) mm[1].at<float>(y, x) = vx;
				if (vy < -1) mm[2].at<float>(y, x) = vy;
				if (vy > 1) mm[3].at<float>(y, x) = vy;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			double minVal, maxVal;
			cv::minMaxIdx(mm[i], &minVal, &maxVal);
			mm[i] /= maxVal;
			//m *= 255;
			//std::cout << m << std::endl;
			char buf[256];
			sprintf(buf, "Feature%i", i);
			if (!mm[i].empty()) cv::imshow(buf, mm[i]);
			//std::cout << minVal << " " << maxVal << std::endl;
		}
	}



private:

	cv::Mat prevgray, flow, cflow;
};



int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	// Estimate the flow of the image
	Flow flow;

	cv::Mat img;
	while (true)
	{
		cap >> img;
		if (img.empty()) break;
		flow.detect(img);
		flow.feature(10, 30);
		flow.feature2();
		cv::imshow("video capture", img);
		if (cv::waitKey(1) == 27) break;
	}
	return 0;
}
