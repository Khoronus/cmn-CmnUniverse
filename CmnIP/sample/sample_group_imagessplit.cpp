/**
* @file sample_drawing_organizedimages.cpp
* @brief Example of the drawing organized images.
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

#include "container/inc/container/container_headers.hpp"
#include "group/inc/group/group_headers.hpp"


namespace
{


void test()
{
	cv::Mat m = cv::imread("../../data/horses.jpg");
	if (m.empty()) {
		std::cout << "Unable to open the source image" << std::endl;
		return;
	}

	CmnIP::group::ImageSplit is;
	//is.split(m, m.cols, m.rows, 8, 8);
	is.split(m, m.cols, m.rows, 40, 40);
	for (auto it = is.rois_img_.begin(); it != is.rois_img_.end(); it++)
	{
		cv::imshow("xxx", it->second);
		if (cv::waitKey(10) == 27) break;
	}
}


}	// namespace anonymous

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test group split" << std::endl;
	test();
	return 0;
}

#endif