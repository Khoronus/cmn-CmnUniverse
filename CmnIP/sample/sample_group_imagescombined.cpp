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


/** Example of use of a sample combine image
*/
void test1()
{
	// Number of images
	int n_hor_images = 4;
	int n_ver_images = 3;
	// Images container
	std::vector< cv::Mat > v_images;
	// Color the images with a random color
	cv::RNG rng(12345);
	for (int y = 0; y < n_ver_images; y++)
	{
		for (int x = 0; x < n_hor_images; x++)
		{
			v_images.push_back(cv::Mat(120, 160, CV_8UC3,
				cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
				rng.uniform(0, 255))));
		}
	}
	// Display
	cv::Mat res = CmnIP::group::ImagesCombined::combine(v_images,
		n_hor_images, n_ver_images, v_images[0].cols * n_hor_images,
		v_images[0].rows * n_ver_images);
	std::cout << "Focus on the image and push a key to quit." << std::endl;
	cv::imshow("Result", res);
	cv::waitKey(0);
}

void test2()
{
	// Number of images
	int n_hor_images = 2;
	int n_ver_images = 2;
	// Images container
	for (int i = 0; i < 1000; i++)
	{
		std::vector< cv::Mat > v_images;
		char buf[512];
		v_images.push_back(cv::Mat(512, 512, CV_8UC3, cv::Scalar(0, 0, 255)));
		v_images.push_back(cv::Mat(512, 512, CV_8UC3, cv::Scalar(0, 255)));
		v_images.push_back(cv::Mat(512, 512, CV_8UC3, cv::Scalar(255)));
		v_images.push_back(cv::Mat(512, 512, CV_8UC3, cv::Scalar(255, 0, 255)));
		if (v_images[0].empty() || v_images[1].empty() ||
			v_images[2].empty() || v_images[3].empty()) continue;
		// Display
		cv::Mat res = CmnIP::group::ImagesCombined::combine(v_images,
			n_hor_images, n_ver_images, v_images[0].cols * n_hor_images,
			v_images[0].rows * n_ver_images);
		//std::cout << "Focus on the image and push a key to quit." << std::endl;
		cv::resize(res, res, cv::Size(res.cols / 2, res.rows / 2));
		cv::imshow("Result", res);
		if (cv::waitKey(0) > 0) break;
	}
}


}	// namespace

#ifdef CmnLib

CMNLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test drawing pairs" << std::endl;
	test1();
	test2();
	return 0;
}

#endif