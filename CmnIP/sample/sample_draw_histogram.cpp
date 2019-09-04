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

#include "feature/inc/feature/feature_headers.hpp"
#include "draw/inc/draw/draw_headers.hpp"


namespace
{

/** @brief Test function.
*/
void test()
{
	cv::Mat m = cv::imread("../../data/horses.jpg");
	if (m.empty()) {
		std::cout << "Unable to open the source image" << std::endl;
		return;
	}
	cv::Mat histo;
	CmnIP::feature::Image2Histogram::grayscale(m, histo, 256, 0, 255, 
		true, true);
	cv::Mat img_histo(128, 256, CV_8UC3, cv::Scalar::all(0));
	CmnIP::draw::Histogram2Image::onechannel_hist(img_histo, histo, 
		img_histo.cols, img_histo.rows, 256, cv::Scalar(0, 0, 255));
	cv::imshow("histogram", img_histo);
	cv::waitKey();
}

}	// namespace

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test histogram display" << std::endl;
	test();
	return 0;
}

#endif