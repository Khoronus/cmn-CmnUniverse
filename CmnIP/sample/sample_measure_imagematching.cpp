/**
* @file sample_matching_image_matching.cpp
* @brief Test the matching between two images to find it they are similar
*        using the cross-correlation.
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
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <fstream>
#include <bitset>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "measure/inc/measure/measure_headers.hpp"

namespace
{

/** @brief Test the object of the file.
*/
void test()
{
	cv::Mat model;
	cv::Rect region_out;
	cv::VideoCapture vc(0);

	CmnIP::measure::ImageChanged image_chanded(0.8, 10);
	CmnIP::measure::TIMESTAMP ts_ = 0;
	while (true)
	{
		cv::Mat src;
		vc >> src;
		if (src.empty()) continue;
		// Prepare the source image
		cv::resize(src, src, cv::Size(32, 32));
		cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
		clahe->setClipLimit(4);
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src, src, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
#endif
		clahe->apply(src, src);
		cv::imshow("src", src);
		//std::cout << "ms: " << tm.getTimeMilli() << std::endl;

		// Detect if the image changed
		double likelihood = 0;
		bool is_changed = image_chanded.is_changed(src, ts_, true, likelihood);
		std::cout << "changed: " << is_changed << " " << likelihood << " " << 
			std::endl;
		if (cv::waitKey(1) == 27) break;
		ts_ += 1;
	}

}

} // namespace anonymous

// ############################################################################

void main()
{
	test();
}
