/**
* @file chart_radar.cpp
* @brief Body of the chart visualization radar type.
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

#include "draw/inc/draw/opticalflowdrawer.hpp"

namespace CmnIP
{
namespace draw
{


//-----------------------------------------------------------------------------
void OpticalFlowDrawer::drawOptFlowMoving(const cv::Mat& flow,
	cv::Mat& cflowmap, int step, double thr)
{
	cv::Scalar color;
	for (int y = 0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step)
		{
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		if (std::sqrt(std::pow(fxy.x, 2) + std::pow(fxy.y, 2)) < thr)
		{
			color = cv::Scalar::all(255);
		}
		else {
			color = cv::Scalar(0, 0, 255);
		}
		circle(cflowmap, cv::Point(x, y), 1, color, -1);
		}
}
//-----------------------------------------------------------------------------
void OpticalFlowDrawer::OptFlowMoving(const cv::Mat& flow, int step, double thr,
	cv::Mat& cflowmap)
{
	cv::Scalar color;
	for (int y = 0; y < flow.rows; y += step)
		for (int x = 0; x < flow.cols; x += step)
		{
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		if (std::sqrt(std::pow(fxy.x, 2) + std::pow(fxy.y, 2)) < thr)
		{
			color = cv::Scalar::all(0);
		}
		else {
			color = cv::Scalar::all(255);
		}
		circle(cflowmap, cv::Point(x, y), 1, color, -1);
		}
}
//-----------------------------------------------------------------------------
void OpticalFlowDrawer::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
	int step, double, const cv::Scalar& color)
{
	for (int y = 0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step)
		{
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		line(cflowmap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x),
			cvRound(y + fxy.y)), color);
		circle(cflowmap, cv::Point(x, y), 2, color, -1);
		}
}
//-----------------------------------------------------------------------------
void OpticalFlowDrawer::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
	int step)
{
	cv::Scalar color(1, 1, 1);
	std::vector<float> rgb;
	for (int i = 0; i < 3; i++)
		rgb.push_back(0);
	for (int y = 0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step)
		{
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		CmnIP::transform::ConversionAngleToColor::convert_point(
			static_cast<float>(x), static_cast<float>(y), 
			fxy.x + static_cast<float>(x), 
			fxy.y + static_cast<float>(y), 0.0f, 10.0f, rgb);
		color = cv::Scalar(rgb[0], rgb[1], rgb[2]);
		line(cflowmap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x),
			cvRound(y + fxy.y)), color);
		circle(cflowmap, cv::Point(x, y), 1, color, -1);
		}
}
//-----------------------------------------------------------------------------
bool OpticalFlowDrawer::scenario_changed(const cv::Mat& flow, int step,
	float threshold)
{
	float sum = 0;
	int num_total = 0;
	for (int y = 0; y < flow.rows; y += step)
		for (int x = 0; x < flow.cols; x += step)
		{
		++num_total;
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		sum += std::sqrt(cv::pow(fxy.x, 2.0f) +
			cv::pow(fxy.y, 2.0f));
		}
	if (num_total > 0)
	{
		sum /= num_total;
		//std::cout << "sum: " << sum << std::endl;
		if (sum > threshold) return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
	void OpticalFlowDrawer::flow2rgb(cv::Mat &flow, cv::Mat &rgb) {
	std::vector<cv::Mat> flow_split;
	cv::split(flow, flow_split);
	cv::Mat mag, ang;
	cv::cartToPolar(flow_split[0], flow_split[1], mag, ang);
	float thr = 1.0;
	for (auto y = 0; y < mag.rows; y++)
	{
		for (auto x = 0; x < mag.cols; x++)
		{
			if (mag.at<float>(y, x) < thr) {
				mag.at<float>(y, x) = ang.at<float>(y, x) = 0;
			}
		}
	}
	//std::cout << "size: " << flow_split.size() << std::endl;
	//std::cout << flow(cv::Rect(5,5,5,5)) << std::endl;
	//std::cout << flow_split[0](cv::Rect(5,5,5,5)) << std::endl;
	//std::cout << flow_split[1](cv::Rect(5,5,5,5)) << std::endl;
	//std::cout << ang << std::endl;
	cv::Mat hsv(flow.size(), CV_32FC3, cv::Scalar::all(0));
	std::vector<cv::Mat> hsv_split;
	cv::split(hsv, hsv_split);
	hsv_split[0] = (ang / (CV_PI * 2)) * 255;
	cv::normalize(mag, hsv_split[2], 0, 255, cv::NORM_MINMAX);
	//std::cout << hsv_split[0](cv::Rect(5,5,5,5)) << std::endl;
	//std::cout << hsv_split[1](cv::Rect(5,5,5,5)) << std::endl;
	//std::cout << hsv_split[2](cv::Rect(5,5,5,5)) << std::endl;
	cv::merge(hsv_split, hsv);
	//cv::cvtColor(hsv, hsv, CV_HSV2BGR);
	hsv.convertTo(rgb, CV_8UC3);
}
//-----------------------------------------------------------------------------
	void OpticalFlowDrawer::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
	int colormode)
{
	cv::Scalar color(1, 1, 1);
	std::vector<float> rgb;
	for (int i = 0; i < 3; i++)
		rgb.push_back(0);
	for (int y = 0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step)
		{
		const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
		if (colormode == 0) {
			CmnIP::transform::ConversionAngleToColor::convert_point(
				static_cast<float>(x), static_cast<float>(y),
				fxy.x + static_cast<float>(x),
				fxy.y + static_cast<float>(y), 0.0f, 10.0f, rgb);
			color = cv::Scalar(rgb[0], rgb[1], rgb[2]);
			line(cflowmap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x),
				cvRound(y + fxy.y)), color);
			circle(cflowmap, cv::Point(x, y), 1, color, -1);
		}
		else {
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			float d = std::sqrt(std::pow(fxy.x, 2) + std::pow(fxy.y, 2));
			color = cv::Scalar(255 - 255 * (d / 3), 0, 255 * (d / 3));
			line(cflowmap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x),
				cvRound(y + fxy.y)), color);
			circle(cflowmap, cv::Point(x, y), 1, color, -1);
		}
		}
}



} // namespace drawing
} // namespace CmnIP
