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

#include "transform/inc/transform/transform_headers.hpp"

namespace
{

/** @brief Test function.
*/
int test()
{
	cv::Mat src = cv::imread("../../data/horses.jpg");
	if (src.empty()) {
		std::cout << "Unable to open the source image" << std::endl;
		return 0;
	}

	cv::Mat out;
	CmnIP::transform::ColorNormalization::normalize_rgb(src, out);
	cv::imshow("original", src);
	cv::imshow("normalized", out);
	cv::waitKey();

	return 1;
}

}	// namespace


/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Color normalization" << std::endl;
	test();
	return 0;
}
