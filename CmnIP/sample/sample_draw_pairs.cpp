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

#include <iostream>

#include "container/inc/container/container_headers.hpp"
#include "draw/inc/draw/draw_headers.hpp"

namespace
{

/** @brief Test function.
*/
void test()
{
	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
	std::vector<cv::Point2f> v1, v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(cv::Point2f(std::rand() % m.cols / 2, std::rand() % m.rows));
		v2.push_back(cv::Point2f(std::rand() % m.cols / 2 + m.cols / 2, std::rand() % m.rows));
	}
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	CmnIP::draw::Pairs::line<cv::Point2f>(v1, v2, nullptr, 2, m);
#else
	CmnIP::draw::Pairs::line<cv::Point2f>(v1, v2, NULL, 2, m);
#endif
	CmnIP::draw::Pairs::points<cv::Point2f>(v1, v2, m.cols / 2, 3, 5, m);
	cv::imshow("m", m);
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
	std::cout << "Test drawing pairs" << std::endl;
	test();
	return 0;
}

#endif