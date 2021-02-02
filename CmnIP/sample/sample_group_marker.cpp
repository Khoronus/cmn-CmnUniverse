/**
* @file sample_numericsystem_numericsystem.cpp
* @brief Sample dynamic.
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

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "group/inc/group/group_headers.hpp"

namespace
{

void test()
{
	std::map<std::string, CmnIP::group::Marker> marker;

	// Load in grayscale
	cv::Mat src = cv::imread("..\\..\\data\\test.png", 0);
	if (src.empty()) {
		std::cout << "Unable to open the source file" << std::endl;
		return;
	}
	cv::imshow("src", src);
	// IMPORTANT: It modifies the source
	marker["HSV"].estimate(src);
	cv::imshow("src_after", src);
	cv::Mat out(src.size(), CV_8UC3, cv::Scalar::all(0));
	marker["HSV"].draw(10, out);
	cv::imshow("marker_hsv", out);
	cv::waitKey();

}

} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample Group Marker" << std::endl;

	test();
	
	return 0;
}


