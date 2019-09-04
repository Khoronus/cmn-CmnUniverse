/**
* @file heatmap.hpp
* @brief Header to draw a matrix as images
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
* @version 1.0.0.0
*
*/

#ifndef CMNIP_DRAW_HEATMAP_HPP__
#define CMNIP_DRAW_HEATMAP_HPP__

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace CmnIP
{
namespace draw
{

/** @brief Draw the contents of a data in a heat map.
*/
class HeatMap
{
public:

	/** @brief Function to draw a matrix of floats as colored data.
	
		Function to draw a matrix of floats as colored data.
		@param[in] src A normalized matrix.
		@param[out] image The image to display.
		@return Return 1 in case of success. 0 otherwise.
		@remarks The source matrix MUST be a normalized matrix.
	*/
	static int draw(const cv::Mat &src, cv::Mat &image)
	{
		if (src.empty() || image.empty()) return 0;
		int xbin = image.cols / src.cols;
		int ybin = image.rows / src.rows;

		for (int y = 0; y < src.rows; y++)
		{
			for (int x = 0; x < src.cols; x++)
			{
				int xmin = x * xbin;
				int xmax = (x + 1) * xbin;
				int ymin = y * ybin;
				int ymax = (y + 1) * ybin;
				cv::Rect r(cv::Point(xmin, ymin), cv::Point(xmax, ymax));
				//std::cout << r << std::endl;
				cv::Scalar color(255 - 255 * src.at<float>(y, x), 0, 
					255 * src.at<float>(y, x));
				if (src.at<float>(y, x) == 0) color = cv::Scalar::all(0);
				cv::rectangle(image, r, color, -1);
			}
		}

		return 1;
	}
};


} // namespace draw
} // namespace CmnIP

#endif /* CMNIP_DRAW_HEATMAP_HPP__ */
