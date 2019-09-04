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

static cv::Mat& getMat(cv::Mat &d) {
	return d;
}

/** @brief Test function.
*/
void test_single()
{
	std::vector< cv::Mat  > container;
	std::vector< std::vector< cv::Mat > > containers;
	std::map<int, std::vector< cv::Mat* > > groups_container;
	for (int i = 0; i < 10; i++)
	{
		container.clear();
		for (int j = 0; j < i + 2; j++) {
			container.push_back( 
				cv::Mat(100, 100, CV_8UC3, cv::Scalar(rand() % 255, rand() % 255, rand() % 255)) );
		}
		containers.push_back(container);
		std::vector< cv::Mat* > tmp;
		for (int j = 0; j < containers[containers.size()-1].size(); j++) {
			tmp.push_back(&containers[containers.size()-1][i]);
		}
		groups_container[i] = tmp;
	}

	cv::Mat image(700,700,CV_8UC3), image_group(700,700,CV_8UC3);
	CmnIP::group::ImagesOrganized<cv::Mat>::container(container, getMat, image);
	CmnIP::group::ImagesOrganized<cv::Mat>::groups(groups_container, getMat, image_group);
	cv::imshow("image", image);
	cv::imshow("image_group", image_group);
	cv::waitKey();
}


void test_double()
{
	std::vector< std::pair< cv::Mat, cv::Mat > > container;
	std::vector< std::vector< std::pair< cv::Mat, cv::Mat > > > containers;
	std::map<int, std::vector< std::pair< cv::Mat, cv::Mat >* > > groups_container;
	for (int i = 0; i < 10; i++)
	{
		container.clear();
		for (int j = 0; j < i + 2; j++) {
			container.push_back( std::make_pair( 
				cv::Mat(100, 100, CV_8UC3, cv::Scalar(rand() % 255, rand() % 255, rand() % 255)),  
				cv::Mat(100, 100, CV_8UC3, cv::Scalar(rand() % 255, rand() % 255, rand() % 255)) ) );
		}
		containers.push_back(container);
		std::vector< std::pair< cv::Mat, cv::Mat >* > tmp;
		for (int j = 0; j < containers[containers.size()-1].size(); j++) {
			tmp.push_back(&containers[containers.size()-1][i]);
		}
		groups_container[i] = tmp;
	}

	cv::Mat image(700,700,CV_8UC3), image_group(700,700,CV_8UC3);
	CmnIP::group::ImagesOrganized<cv::Mat>::container(container, getMat, image);
	CmnIP::group::ImagesOrganized<cv::Mat>::groups(groups_container, getMat, image_group);
	cv::imshow("image", image);
	cv::imshow("image_group", image_group);
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
	test_single();
	test_double();
	return 0;
}

#endif