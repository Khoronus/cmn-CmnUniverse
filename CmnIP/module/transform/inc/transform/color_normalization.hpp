/* @file color_normalization.hpp
 * @brief Class to perform the color normalization of a source of data.
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

#ifndef CMNIP_TRANSFORM_COLORNORMALIZATION_HPP__
#define CMNIP_TRANSFORM_COLORNORMALIZATION_HPP__


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


namespace CmnIP
{
namespace transform
{


/** @brief It performs the color normalization of a source data.

    It performs the color normalization of a source data.
*/
class ColorNormalization
{
public:

	/** @brief It performs the color normalization on the RGB components of 
	           the image.

        It performs the color normalization on the RGB components of the image.
	*/
	static void normalize_rgb(const cv::Mat &src, cv::Mat &out)
	{
		out = cv::Mat::zeros(src.size(), src.type());
		for (int y = 0; y < src.rows; y++)
		{
			for (int x = 0; x < src.cols; x++)
			{
				float s = src.at<cv::Vec3b>(y, x)[0] +
					src.at<cv::Vec3b>(y, x)[1] +
					src.at<cv::Vec3b>(y, x)[2];
				if (s > 0) {
					//float r = (float)src.at<cv::Vec3b>(y, x)[2] / s;
					//float g = (float)src.at<cv::Vec3b>(y, x)[1] / s;
					////float b = (float)src.at<cv::Vec3b>(y, x)[0] / s;

					//out.at<cv::Vec3b>(y, x)[2] = (uchar)(r / g * src.at<cv::Vec3b>(y, x)[1]);
					//out.at<cv::Vec3b>(y, x)[1] = (uchar)(src.at<cv::Vec3b>(y, x)[1]);
					//out.at<cv::Vec3b>(y, x)[0] = (uchar)((1.0f - r - g) / g * src.at<cv::Vec3b>(y, x)[1]);

					for (int c = 0; c < 3; c++)
					{
						float v = (float)src.at<cv::Vec3b>(y, x)[c] / s;
						out.at<cv::Vec3b>(y, x)[c] = 255 * v;
					}

				}
			}
		}
	}


	/** @brief It performs the color normalization on the RGB components of
	the image.

	It performs the color normalization on the RGB components of the image.
	*/
	static void rg(const cv::Mat &src, cv::Mat &out)
	{
		out = cv::Mat::zeros(src.size(), src.type());
		for (int y = 0; y < src.rows; y++)
		{
			for (int x = 0; x < src.cols; x++)
			{
				float s = src.at<cv::Vec3b>(y, x)[0] +
					src.at<cv::Vec3b>(y, x)[1] +
					src.at<cv::Vec3b>(y, x)[2];
				if (s > 0) {
					float r = (float)src.at<cv::Vec3b>(y, x)[2] / s;
					float g = (float)src.at<cv::Vec3b>(y, x)[1] / s;
					//float b = (float)src.at<cv::Vec3b>(y, x)[0] / s;

					out.at<cv::Vec3b>(y, x)[2] = (uchar)(r / g * src.at<cv::Vec3b>(y, x)[1]);
					out.at<cv::Vec3b>(y, x)[1] = (uchar)(src.at<cv::Vec3b>(y, x)[1]);
					out.at<cv::Vec3b>(y, x)[0] = (uchar)((1.0f - r - g) / g * src.at<cv::Vec3b>(y, x)[1]);
				}
			}
		}
	}

};


} // namespace transform
} // namespace CmnIP

#endif /* CMNIP_TRANSFORM_COLORNORMALIZATION_HPP__ */
