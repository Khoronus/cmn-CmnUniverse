/**
* @file sample_drawing_chartradar.cpp
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
	std::vector<float> features;
	std::vector< std::pair<float, float> > features_mM;
	{
		for (int k = 0; k < 3; k++)
		{
			features.clear();
			for (int i = 0; i < 10; i++)
			{
				features.push_back( ((float)std::rand() / RAND_MAX) * 200);
			}
			CmnLib::container::ContainerCoreOperations<float>::container_minmax(features, 
				features_mM);
		}
	}

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = features_mM.begin(); it != features_mM.end(); it++) 
#else
	for (std::vector< std::pair<float, float> >::const_iterator it = features_mM.begin(); it != features_mM.end(); it++) 
#endif
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	CmnIP::draw::ChartRadar cr(512, 0, 200);
	cr.draw(features_mM, cv::Scalar(190,255));
	cr.draw(features, cv::Scalar(0,255));
	cv::imshow("chart", cr.chart());
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