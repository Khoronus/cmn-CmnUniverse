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

#include "pointcloud/pointcloud_pointcloud.hpp"
#include "noise/noise_noise.hpp"

namespace
{

/** @brief It finds a peak of values in a set
*/
float find_peak(std::map<int, std::vector< std::pair< std::pair< CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector3f>,
	std::pair<CmnMath::algebralinear::Vector3f, float> > > > &items,
	float bin) {
	// container with the bin points
	std::map<int, std::vector<CmnMath::algebralinear::Vector3f>> m_pts;
	// Show the points
	for (auto it : items) {
		for (auto it2 : it.second) {
			//std::cout << it.first << " " << it2.first.first << " " << it2.first.second << " " << it2.second.first << " " << it2.second.second << std::endl;
			m_pts[static_cast<int>(it2.first.first.z * bin)].push_back(CmnMath::algebralinear::Vector3f(it2.first.first.x, it2.first.first.y, it2.first.first.z));
		}
	}
	//std::cout << "###########" << std::endl;
	float maxval = 0;
	float maxid = 0;
	for (auto it : m_pts) {
		//std::cout << it.first << " " << it.second.size() << std::endl;
		if (it.second.size() > maxval) {
			maxval = it.second.size();
			maxid = it.first / bin;
		}
	}
	return maxid;
}


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
	srand(time(0));
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

	//// Show the points
	//std::map<int, std::vector<CmnMath::algebralinear::Vector3f>> m_pts;
	//for (auto it : items) {
	//	for (auto it2 : it.second) {
	//		std::cout << it.first << " " << it2.first.first << " " << it2.first.second << " " << it2.second.first << " " << it2.second.second << std::endl;
	//		m_pts[static_cast<int>(it2.first.first.z * 10)].push_back(CmnMath::algebralinear::Vector3f(it2.first.first.x, it2.first.first.y, it2.first.first.z));
	//	}
	//}
	//std::cout << "###########" << std::endl;
	//for (auto it : m_pts) {
	//	std::cout << it.first << " " << it.second.size() << std::endl;
	//}


	std::vector<float> vavg, vmode, vmode_peak;
	// https://stackoverflow.com/questions/11062804/measuring-the-runtime-of-a-c-code
	auto start = std::chrono::system_clock::now();
	// find the peak
	float peak = find_peak(items, 10);
	std::cout << "peak: " << peak << std::endl;
	int num_iterations = 5;
	for (int k = 0; k < num_iterations; ++k) {

		float dAvg = CmnMath::pointcloud::EstimateHeight<CmnMath::algebralinear::Vector3f>::average(5000, items[0]);
		float dMode = CmnMath::pointcloud::EstimateHeight<CmnMath::algebralinear::Vector3f>::mode(5000, 1000, items[0]);
		float dModeP = CmnMath::pointcloud::EstimateHeight<CmnMath::algebralinear::Vector3f>::mode(5000, 1000, items[0], peak, 0.2);
		vavg.push_back(dAvg);
		vmode.push_back(dMode);
		vmode_peak.push_back(dModeP);
	}
	auto end = std::chrono::system_clock::now();
	// this constructs a duration object using milliseconds
	auto elapsed =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	CmnMath::CMN_64F mean = 0, stdev = 0;
	CmnMath::statistics::classic::SeriesAnalysis<float>::mean_var(vavg, mean, stdev);
	std::cout << "dAvg: " << mean << " " << stdev << std::endl;
	CmnMath::statistics::classic::SeriesAnalysis<float>::mean_var(vmode, mean, stdev);
	std::cout << "dMode: " << mean << " " << stdev << std::endl;
	CmnMath::statistics::classic::SeriesAnalysis<float>::mean_var(vmode_peak, mean, stdev);
	std::cout << "dModeP: " << mean << " " << stdev << std::endl;
	std::cout << "et(ms): " << elapsed.count() / num_iterations << std::endl;
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test pointcloud" << std::endl;
	test();
	return 0;
}