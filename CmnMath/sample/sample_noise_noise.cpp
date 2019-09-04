/* @file sample_math_trigonometry.hpp
* @brief Perform a sample trigonometric operations.
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
* @author Various
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>

#include "algebralinear/algebralinear_algebralinear.hpp"
#include "noise/noise_noise.hpp"

namespace
{


CmnMath::algebralinear::Vector3f rand_point() {
	return CmnMath::algebralinear::Vector3f(
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX);
}

/** @brief Function to test the classes and functions
*/
void test()
{
	// Load items
	std::map<int, std::vector< std::pair< std::pair< CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector3f>,
		std::pair<CmnMath::algebralinear::Vector3f, float> > > > items;

	for (int i = 0; i < 1000; ++i) {
		items[0].push_back(std::make_pair(std::make_pair(
			rand_point(), rand_point()),
			std::make_pair(CmnMath::algebralinear::Vector3f(255, 0, 255), 0.1f)));
	}

	// modifier
	std::vector<CmnMath::algebralinear::Vector3f> vpts;
	vpts.push_back(CmnMath::algebralinear::Vector3f(0.6, 0.4, 2.3));
	vpts.push_back(CmnMath::algebralinear::Vector3f(-1.1, -0.2, 2.4));
	CmnMath::noise::Noise<CmnMath::algebralinear::Vector3f>::localized_adjustment(vpts, 0.5, 1.0, items);
	vpts.clear();
	vpts.push_back(CmnMath::algebralinear::Vector3f(0.8, -0.7, 2.4));
	CmnMath::noise::Noise<CmnMath::algebralinear::Vector3f>::localized_adjustment(vpts, 0.7, 1.5, items);
	CmnMath::noise::Noise<CmnMath::algebralinear::Vector3f>::random_noise(0.0, 0.1, items);
	//Noise<CmnMath::algebralinear::Vector3f>::localized_random_noise(vpts, 0.5, 0.8, 0.1, items);

	// Show the points
	std::map<int, std::vector<CmnMath::algebralinear::Vector3f>> m_pts;
	for (auto it : items) {
		for (auto it2 : it.second) {
			std::cout << it.first << " " << it2.first.first << " " << it2.first.second << " " << it2.second.first << " " << it2.second.second << std::endl;
			m_pts[static_cast<int>(it2.first.first.z * 10)].push_back(CmnMath::algebralinear::Vector3f(it2.first.first.x, it2.first.first.y, it2.first.first.z));
		}
	}
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test trigonometry" << std::endl;
	test();
	return 0;
}