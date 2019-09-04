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

#include "container/inc/container/container_headers.hpp"
#include "draw/inc/draw/draw_headers.hpp"

namespace
{

/** @brief Test function.
*/
void test()
{
	CmnIP::draw::Map2D map;
	map.set_natural_size(512, 512);
	map.set_range(-3000, -3000, 3000, 3000);
	map.reset_paint();
	float x = 0, y = 0;
	map.original2scaled(1239, 738, x, y);
	cv::circle(map.image(), cv::Point(x, y), 2, cv::Scalar::all(255));
	float xin = 0, yin = 0;
	map.scaled2original(x, y, xin, yin);
	std::vector<cv::Point2f> points;
	map.scaled_marker(500, 350, 1.8, 100, points);
	cv::line(map.image(), points[0], points[1], cv::Scalar(0,255));
	cv::line(map.image(), points[2], points[3], cv::Scalar(0,255));
	map.scaled_marker(2400, 1350, 2.6, 100, points);
	cv::line(map.image(), points[0], points[1], cv::Scalar(0,0,255));
	cv::line(map.image(), points[2], points[3], cv::Scalar(0,0,255));

	std::cout << xin << " " << yin << std::endl;
	cv::imshow("map", map.image());
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
	std::cout << "Test chart radar" << std::endl;
	test();
	return 0;
}

#endif