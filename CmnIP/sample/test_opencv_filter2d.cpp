/* @file sample_classification_classifycolor.cpp
* @brief Main file with the example for the hog descriptor and visualization.
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

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
//#include <opencv2/gpu/gpu.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/ml/ml.hpp>


namespace
{

int test()
{
	cv::Mat src = cv::imread("..\\..\\data\\horses.jpg");
	if (src.empty()) return 0;
	/// Declare variables
	cv::Mat dst;

	cv::Mat kernel;
	cv::Point anchor;
	double delta;
	int ddepth;
	int kernel_size;
	char* window_name = "filter2D Demo";

	int c;

	/// Create window
#if CV_MAJOR_VERSION == 3
	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
#endif

	/// Initialize arguments for the filter
	anchor = cv::Point(-1, -1);
	delta = 0;
	ddepth = -1;

	// you reserve 9 integers on the stack (9*4=36bytes)
	float vals9[] = { -1, -1, -1, 2, 2, 2, -1, -1, -1 };
	float vals25[] = { 0, 0, -1, 0, 0, 0, -1, -2, -1, 0, -1, -2, 16, -2, -1, 0, -1, -2, -1, 0, 0, 0, -1, 0, 0 };
	float vals49[] = {
		0, 0, 0, 5, 0, 0, 0,
		0, 5, 18, 32, 18, 5, 0,
		0, 18, 64, 100, 64, 18, 0,
		5, 32, 100, 100, 100, 32, 5,
		0, 18, 64, 100, 64, 18, 0,
		0, 5, 18, 32, 18, 5, 0,
		0, 0, 0, 5, 0, 0, 0 };
	float vals9laplacian[] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };
	//kernel = cv::Mat(3, 3, CV_32F, vals9);
	kernel = cv::Mat(5, 5, CV_32F, vals25);
	//kernel = cv::Mat(7, 7, CV_32F, vals49);
	//kernel = cv::Mat(3, 3, CV_32F, vals9laplacian);

	/// Loop - Will filter the image with different kernel sizes each 0.5 seconds
	int ind = 0;
	{
		/// Update kernel size for a normalized box filter
		//kernel_size = 3 + 2*( ind%5 );
		//kernel = cv::Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

		/// Apply filter
		cv::filter2D(src, dst, ddepth, kernel, anchor, delta, cv::BORDER_DEFAULT);
		cv::imshow(window_name, dst);

		cv::waitKey();
	}

	return 0;
}

} // namespace anonymous

// ############################################################################
// ############################################################################
// ############################################################################

/**	 Main code
*/
int main(int argc, char *argv[], char *window_name)
{
	test();
	return 0;
}

