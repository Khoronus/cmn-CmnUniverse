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

#ifndef CMNIP_TRANSFORM_FISHEYE2HAMMERAITOFF_HPP__
#define CMNIP_TRANSFORM_FISHEYE2HAMMERAITOFF_HPP__

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
class FishEye2HammerAitoff
{
public:

	// Transform a fish eye image in panoramic
	static void testHammerAitoff(cv::Mat &image, const std::string &name, cv::Mat &out) {

		cv::Mat m(image.size(), CV_8UC3, cv::Scalar(0));

		for (int y = 0; y < m.rows; ++y)
		{
			for (int x = 0; x < m.cols; ++x)
			{
				float k = 0, k1 = 0;
				if (y < m.rows / 2) {
					k = (1 - (float)y / (m.rows / 2)) * k1;
				}
				else {
					k = ((float)y / (m.rows / 2)) * k1;
				}
				float longitude = ((((float)x / (float)(m.cols + k)) - 0.5) * 2) * CV_PI;
				float latitude = ((((float)y / (float)m.rows) - 0.5) * 2) * CV_PI / 2;
				cv::Point3f d;
				CmnMath::coordinatesystem::CoordinateSystemConversion3D<float>::HammerAitoff(latitude,
					longitude, d.x, d.y, d.z);
				float latitude0, longitude0;
				//std::cout << d << std::endl;
				int x0 = (d.x + 1) / 2 * m.cols;
				int y0 = (d.y + 1) / 2 * m.rows;
				if (x0 >= 0 && y0 >= 0 && x0 < m.cols && y0 < m.rows) {
					m.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(y0, x0);
				}
			}
		}

		//cv::imwrite("img1.jpg", m);
		//cv::resize(m, m, cv::Size(512, 512));
		cv::imshow(name, m);
		out = m;
	}


	// Transform a fish eye image in panoramic
	static int HammerAitoff2Map(cv::Mat &src, cv::Mat &mapx, cv::Mat &mapy) {

		if (src.empty()) return 0;
		mapx = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));
		mapy = cv::Mat(src.size(), CV_32FC1, cv::Scalar(0));

		for (int y = 0; y < src.rows; ++y)
		{
			for (int x = 0; x < src.cols; ++x)
			{
				float k = 0, k1 = 0;
				if (y < src.rows / 2) {
					k = (1 - (float)y / (src.rows / 2)) * k1;
				}
				else {
					k = ((float)y / (src.rows / 2)) * k1;
				}
				float longitude = ((((float)x / (float)(src.cols + k)) - 0.5) * 2) * CV_PI;
				float latitude = ((((float)y / (float)src.rows) - 0.5) * 2) * CV_PI / 2;
				cv::Point3f d;
				CmnMath::coordinatesystem::CoordinateSystemConversion3D<float>::HammerAitoff(latitude,
					longitude, d.x, d.y, d.z);
				float latitude0, longitude0;
				//std::cout << d << std::endl;
				int x0 = (d.x + 1) / 2 * src.cols;
				int y0 = (d.y + 1) / 2 * src.rows;
				if (x0 >= 0 && y0 >= 0 && x0 < src.cols && y0 < src.rows) {
					mapx.at<float>(y, x) = x0;
					mapy.at<float>(y, x) = y0;
				}
			}
		}
		return 1;
	}
};


}  // namespace transform
}	// namespace CmnIP

#endif /* CMNIP_TRANSFORM_FISHEYE2HAMMERAITOFF_HPP__ */
