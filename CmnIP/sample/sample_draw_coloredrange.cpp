/**
* @file sample_drawing_pairs.cpp
* @brief Example of the drawing of pairs of data.
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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "draw/inc/draw/draw_headers.hpp"

namespace
{

	void test()
	{

		// Point/Angle 2 image
		cv::Mat m = cv::Mat(200, 200, CV_8UC3, cv::Scalar::all(0));
		for (int y = 0; y < m.rows; y++)
		{
			for (int x = 0; x < m.cols; x++)
			{
				std::vector<float> rgb;
				CmnIP::transform::ConversionAngleToColor::convert_point(
					m.cols / 2, m.rows / 2, x, y, 0, m.cols / 2, rgb);
				for (int c = 0; c < 3; c++)
					m.at<cv::Vec3b>(y, x)[c] = rgb[c] * 255;
			}
		}
		cv::imshow("angle", m);
		cv::waitKey();
	}

}  // namespace anonymous


/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Color normalization" << std::endl;
	test();
	return 0;
}
