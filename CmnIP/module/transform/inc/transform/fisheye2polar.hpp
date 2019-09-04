/* @file fisheye2perspective.hpp
 * @brief Class to map the points from a fish-eye to perspective and viceversa.
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
 * @version 0.2.0.0
 * 
 */

#ifndef CMNIP_TRANSFORM_FISHEYE2POLAR_HPP__
#define CMNIP_TRANSFORM_FISHEYE2POLAR_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace transform
{


/** Map the points from fish-eye image to rectangular area
	@example
*/
class FishEye2Polar
{
public:

	// Convert a fish eye image in a polar image
	static void fish2polar(cv::Mat &image, cv::Mat &out, bool direction) {
		cv::Mat m0 = image;
		//cv::resize(m0, m0, cv::Size(512, 512));
		cv::Point center(m0.cols / 2, m0.rows / 2);

		cv::Mat m(1024 * 2, 2048 * 2, CV_8UC3, cv::Scalar::all(0));

		for (float r = 0; r < m0.rows / 2; r += 0.25) {
			for (float theta = -CV_PI; theta < CV_PI; theta += 0.0001) {
				float x, y;
				CmnMath::coordinatesystem::CoordinateSystemConversion2D<float>::polar2cartesian(r, theta, x, y);
				//float r_, theta_;
				//CoordinateSystemConversion2D::cartesian2polar(x, y, r_, theta_);
				//std::cout << r << " " << theta << " " << r_ << " " << theta_ << " " << x << " " << y << std::endl;


				int y0, x1, y1, x0 = ((theta + CV_PI) / (2 * CV_PI)) * m.cols;
				y1 = y + m0.rows / 2;
				x1 = x + m0.cols / 2;
				if (direction) {
					y0 = (r / (m0.rows / 2)) * m.rows;
				}
				else {
					y0 = (m.rows - 1) - (r / (m0.rows / 2)) * m.rows;
					if (x0 < m.cols / 2) {
						x0 += m.cols / 2;
					}
					else {
						x0 -= m.cols / 2;
					}
					x0 = (m.cols - 1) - x0;
				}

				m.at<cv::Vec3b>(y0, x0) = m0.at<cv::Vec3b>(y1, x1);

				//std::cout << r << " " << theta << " " << x0 << " " << y0 << " " << x1 << " " << y1 << std::endl;


				//float v0 = r / (m0.cols / 2);
				//float v1 = (theta) / (CV_PI / 2);
				//int x0 = v0 * m.cols, y0 = v1 * m.rows;
				//if ((x0 >= 0 && y0 >= 0 && x0 < m.cols && y0 < m.rows)) {
				//	m.at<cv::Vec3b>(y0,x0) = m0.at<cv::Vec3b>(y,x);
				//}
			}
		}

		out = m;
	}


	// Covert a polar coordinate image in a fish eye image
	static void polar2fisheye(cv::Mat &image, cv::Mat &out, bool direction) {
		cv::Mat m = image;
		int kCut = 0;
		m = m(cv::Rect(0, kCut, m.cols, m.rows - kCut));

		// Output image size
		cv::Mat m0(1630, 1630, CV_8UC3, cv::Scalar(0, 255));
		for (float r = 0; r < m0.rows / 2; r += 0.5) {
			for (float theta = -CV_PI; theta < CV_PI; theta += 0.001) {
				float x, y;
				CmnMath::coordinatesystem::CoordinateSystemConversion2D<float>::polar2cartesian(r, theta, x, y);
				//float r_, theta_;
				//CoordinateSystemConversion2D::cartesian2polar(x, y, r_, theta_);
				//std::cout << r << " " << theta << " " << r_ << " " << theta_ << " " << x << " " << y << std::endl;


				int y0, x1, y1, x0 = ((theta + CV_PI) / (2 * CV_PI)) * m.cols;
				y1 = y + m0.rows / 2;
				x1 = x + m0.cols / 2;
				if (direction) {
					y0 = (r / (m0.rows / 2)) * m.rows;
				}
				else {
					y0 = (m.rows - 1) - (r / (m0.rows / 2)) * m.rows;
					if (x0 < m.cols / 2) {
						x0 += m.cols / 2;
					}
					else {
						x0 -= m.cols / 2;
					}
					x0 = (m.cols - 1) - x0;
				}

				if (x1 >= 0 && y1 >= 0 && x1 < m0.cols && y1 < m0.rows &&
					x0 >= 0 && y0 >= 0 && x0 < m.cols && y0 < m.rows) {
					m0.at<cv::Vec3b>(y1, x1) = m.at<cv::Vec3b>(y0, x0);
				}
			}
		}
		out = m0;
	}



	// Convert a fish eye image in a polar image
	static int fish2polarMap(cv::Mat &src, bool direction, cv::Mat &mapx, cv::Mat &mapy) {

		if (src.empty()) return 0;
		mapx = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));
		mapy = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));

		cv::Mat m0 = src;
		//cv::resize(m0, m0, cv::Size(512, 512));
		cv::Point center(m0.cols / 2, m0.rows / 2);

		cv::Mat m(1024 * 2, 2048 * 2, CV_8UC3, cv::Scalar::all(0));

		for (float r = 0; r < m0.rows / 2; r += 0.25) {
			for (float theta = -CV_PI; theta < CV_PI; theta += 0.001) {
				float x, y;
				CmnMath::coordinatesystem::CoordinateSystemConversion2D<float>::polar2cartesian(r, theta, x, y);
				//float r_, theta_;
				//CoordinateSystemConversion2D::cartesian2polar(x, y, r_, theta_);
				//std::cout << r << " " << theta << " " << r_ << " " << theta_ << " " << x << " " << y << std::endl;


				int y0, x1, y1, x0 = ((theta + CV_PI) / (2 * CV_PI)) * m.cols;
				y1 = y + m0.rows / 2;
				x1 = x + m0.cols / 2;
				if (direction) {
					y0 = (r / (m0.rows / 2)) * m.rows;
				}
				else {
					y0 = (m.rows - 1) - (r / (m0.rows / 2)) * m.rows;
					if (x0 < m.cols / 2) {
						x0 += m.cols / 2;
					}
					else {
						x0 -= m.cols / 2;
					}
					x0 = (m.cols - 1) - x0;
				}

				mapx.at<float>(y0, x0) = x1;
				mapy.at<float>(y0, x0) = y1;
			}
		}

		return 1;
	}


	// Covert a polar coordinate image in a fish eye image
	static int polar2fisheyeMap(cv::Mat &src, bool direction, cv::Mat &mapx, cv::Mat &mapy) {

		if (src.empty()) return 0;
		mapx = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));
		mapy = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));

		cv::Mat m = src;
		int kCut = 0;
		m = m(cv::Rect(0, kCut, m.cols, m.rows - kCut));

		// Output image size
		cv::Mat m0(1630, 1630, CV_8UC3, cv::Scalar(0, 255));
		for (float r = 0; r < m0.rows / 2; r += 0.5) {
			for (float theta = -CV_PI; theta < CV_PI; theta += 0.001) {
				float x, y;
				CmnMath::coordinatesystem::CoordinateSystemConversion2D<float>::polar2cartesian(r, theta, x, y);
				//float r_, theta_;
				//CoordinateSystemConversion2D::cartesian2polar(x, y, r_, theta_);
				//std::cout << r << " " << theta << " " << r_ << " " << theta_ << " " << x << " " << y << std::endl;


				int y0, x1, y1, x0 = ((theta + CV_PI) / (2 * CV_PI)) * m.cols;
				y1 = y + m0.rows / 2;
				x1 = x + m0.cols / 2;
				if (direction) {
					y0 = (r / (m0.rows / 2)) * m.rows;
				}
				else {
					y0 = (m.rows - 1) - (r / (m0.rows / 2)) * m.rows;
					if (x0 < m.cols / 2) {
						x0 += m.cols / 2;
					}
					else {
						x0 -= m.cols / 2;
					}
					x0 = (m.cols - 1) - x0;
				}

				if (x1 >= 0 && y1 >= 0 && x1 < m0.cols && y1 < m0.rows &&
					x0 >= 0 && y0 >= 0 && x0 < m.cols && y0 < m.rows) {

					mapx.at<float>(y1, x1) = x0;
					mapy.at<float>(y1, x1) = y0;
				}
			}
		}
	}


};


}  // namespace transform
}	// namespace CmnIP

#endif /* CMNIP_TRANSFORM_FISHEYE2POLAR_HPP__ */
