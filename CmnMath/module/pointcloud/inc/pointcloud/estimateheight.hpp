/**
* @file plane.hpp
* @brief Description of a plane
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
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef ESTIMATEHEIGHT_ESTIMATEHEIGHT_HPP__
#define ESTIMATEHEIGHT_ESTIMATEHEIGHT_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <functional>
#include <numeric>
#include <random>

#include "geometricprimitive/geometricprimitive_geometricprimitive.hpp"
#include "noise/noise_noise.hpp"
#include "statistics/inc/statistics/statistics_headers.hpp"

namespace CmnMath
{
namespace pointcloud
{

/** @brief Class to estimate the distance height of a sensor
from a given set of points
*/
template <typename _Ty3>
class EstimateHeight
{
public:

	/** @brief It calculates the average from a random samples points

	It calculates the average from a random samples points.
	@param[in] num_random_samples The total random samples
	@param[in] items Container with the points from the sensor
	*/
	static float average(
		int num_random_samples,
		std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > &items) {

		if (num_random_samples <= 0) return 0;

		float dsum = 0;
		int nelems = 0;

		for (int i = 0; i < num_random_samples; ++i) {
			_Ty3 p1 = items[rand() % items.size()].first.first;
			_Ty3 p2 = items[rand() % items.size()].first.first;
			_Ty3 p3 = items[rand() % items.size()].first.first;
			//noise(0.1, p1); noise(0.1, p2); noise(0.1, p3);
			//std::cout << p1 << " " << p2 << " " << p3 << " ";
			CmnMath::geometricprimitive::Plane plane(p1, p2, p3);
			//std::cout << plane.n << " " << plane.p << std::endl;
			float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));
			if (std::isnan(d)) continue;
			if (std::isinf(d)) continue;
			dsum += d;
			++nelems;
			//std::cout << d << " " << dsum / nelems << std::endl;
			//std::cout << "d: " << plane.distance(
			//	CmnMath::algebralinear::Vector3f(0, 0, 0)
			//) << std::endl;
		}
		if (nelems == 0) return 0;
		return dsum / nelems;
	}

	/** @brief It calculates the mode statistic from a random samples points

	It calculates the mode statistic from a random samples points.
	@param[in] num_random_samples The total random samples
	@param[in] items Container with the points from the sensor
	*/
	static float mode(
		int num_random_samples, float bin,
		std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > &items) {

		if (num_random_samples <= 0) return 0;

		// container with all the distances measured
		std::vector<int> distances_in;
		std::vector<float> distances;
		for (int i = 0; i < num_random_samples; ++i) {
			_Ty3 p1 = items[rand() % items.size()].first.first;
			_Ty3 p2 = items[rand() % items.size()].first.first;
			_Ty3 p3 = items[rand() % items.size()].first.first;
			//noise(0.1, p1); noise(0.1, p2); noise(0.1, p3);
			//std::cout << p1 << " " << p2 << " " << p3 << " ";
			CmnMath::geometricprimitive::Plane plane(p1, p2, p3);
			//std::cout << plane.n << " " << plane.p << std::endl;
			float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));
			if (std::isnan(d)) continue;
			if (std::isinf(d)) continue;
			distances.push_back(d);
			distances_in.push_back(static_cast<int>(d * bin));
		}
		return statistical_mode(distances_in) / bin;
	}

	/** @brief It calculates the mode statistic from a random samples points

	It calculates the mode statistic from a random samples points.
	@param[in] num_random_samples The total random samples
	@param[in] items Container with the points from the sensor
	*/
	static float mode(
		int num_random_samples, float bin,
		std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > &items, float peak, float margin) {

		if (num_random_samples <= 0) return 0;

		// container with all the distances measured
		std::vector<int> distances_in;
		std::vector<float> distances;
		for (int i = 0; i < num_random_samples; ++i) {
			_Ty3 p1 = items[rand() % items.size()].first.first;
			_Ty3 p2 = items[rand() % items.size()].first.first;
			_Ty3 p3 = items[rand() % items.size()].first.first;
			float d1 = std::abs(p1.z - peak);
			float d2 = std::abs(p2.z - peak);
			float d3 = std::abs(p3.z - peak);
			if (d1 > margin || d2 > margin || d3 > margin) continue;
			//noise(0.1, p1); noise(0.1, p2); noise(0.1, p3);
			//std::cout << p1 << " " << p2 << " " << p3 << " ";
			CmnMath::geometricprimitive::Plane plane(p1, p2, p3);
			//std::cout << plane.n << " " << plane.p << std::endl;
			float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));
			//std::cout << p1 << " " << p2 << " " << p3 << " " << d << std::endl;
			if (std::isnan(d)) continue;
			if (std::isinf(d)) continue;
			distances.push_back(d);
			distances_in.push_back(static_cast<int>(d * bin));
		}
		return statistical_mode(distances_in) / bin;
	}


	/** @brief Estimate the mode from an array
	*/
	static float mode(
		int num_random_samples, float bin,
		float *items, size_t size) {

		if (num_random_samples <= 0) return 0;
		// map with the normals
		//_Ty3 p0(0, 0, 0);

		//
		// Engines 
		//
		std::mt19937 e2(rd());
		//std::knuth_b e2(rd());
		//std::default_random_engine e2(rd()) ;
		// Distribtuions
		std::uniform_real_distribution<> dist(0, size / 3);

		std::vector<int> distances_in;
		for (int i = 0; i < num_random_samples; ++i) {

			size_t idx = std::floor(dist(e2));
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p1(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);
			idx = std::floor(dist(e2));
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p2(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);
			idx = std::floor(dist(e2));
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p3(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);
			//std::cout << p1 << " " << p2 << " " << p3 << " ";
			//f << p1 << " " << p2 << " " << p3 << " ";
			CmnMath::geometricprimitive::Plane plane(p1, p2, p3);

			//// It is used only to check if the best normal
			//// matches with the average plane normals
			//std::vector<_Ty3> triangle = { p1, p2, p3 }, triangle_oriented;
			//orient_triangles(p0, triangle, false, triangle_oriented);
			//CmnMath::geometricprimitive::Plane plane(triangle_oriented[0],
			//	triangle_oriented[1], triangle_oriented[2]);

			//f << plane.n << " " << plane.p << std::endl;
			float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));

			//std::cout << "i: " << i << " => " << plane.n << " " <<
			//	plane.p << " d= " << d << std::endl;
			//float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0), CmnMath::algebralinear::Vector3f(0, 0, 1));
			//std::cout << "d: " << d << std::endl;
			if (std::isnan(d)) continue;
			if (std::isinf(d)) continue;
			distances_in.push_back(static_cast<int>(d * bin));
		}

		//std::map<int, int> counters;
		////std::cout << "d: ";
		//for (auto &it : distances_in) {
		//	//std::cout << it << " ";
		//	counters[it]++;
		//}
		//std::cout << std::endl;
		//std::cout << "counters" << std::endl;
		//for (auto &it : counters) {
		//	std::cout << it.first << " = " << it.second << std::endl;
		//}
		return statistical_mode(distances_in) / bin;
	}





	/** @brief Estimate the mode from an array
	*/
	static float mode(
		int num_random_samples, float bin,
		float *items, size_t size, float peak, float margin) {

		if (num_random_samples <= 0) return 0;

		// container with all the distances measured
		std::vector<int> distances_in;
		std::vector<float> distances;
		for (int i = 0; i < num_random_samples; ++i) {
			size_t idx = rand() % (size / 3);
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p1(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);
			idx = rand() % (size / 3);
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p2(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);
			idx = rand() % (size / 3);
			//f << idx << " ";
			if (idx >= size - 2) continue;
			_Ty3 p3(items[idx * 3], items[idx * 3 + 1], items[idx * 3 + 2]);

			float d1 = std::abs(p1.z - peak);
			float d2 = std::abs(p2.z - peak);
			float d3 = std::abs(p3.z - peak);
			if (d1 > margin || d2 > margin || d3 > margin) continue;

			//std::cout << p1 << " " << p2 << " " << p3 << " ";
			//f << p1 << " " << p2 << " " << p3 << " ";
			CmnMath::geometricprimitive::Plane plane(p1, p2, p3);
			//std::cout << plane.n << " " << plane.p << std::endl;
			//f << plane.n << " " << plane.p << std::endl;
			float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));
			if (std::isnan(d)) continue;
			if (std::isinf(d)) continue;
			distances.push_back(d);
			distances_in.push_back(static_cast<int>(d * bin));
		}
		return statistical_mode(distances_in) / bin;
	}


	/** @brief It finds a peak of values in a set

		@return it return the value where the peak is located (no good for bivariate or multivariate)
	*/
	static float find_peak(
		float *items, 
		size_t size,
		float bin) {
		
		// container with the bin points
		std::map<int, int> m_pts;
		// Show the points
		for (size_t i = 0; i < size; i += 3) {
			m_pts[static_cast<int>(items[i + 2] * bin)]++;
		}
		//std::cout << "###########" << std::endl;
		float maxval = 0;
		float maxid = 0;
		for (auto it : m_pts) {
			//std::cout << it.first << " " << it.second.size() << std::endl;
			if (it.second > maxval) {
				maxval = it.second;
				maxid = it.first / bin;
			}
		}
		return maxid;
	}


	/** @brief Function used to perform the test over some sample data
	*/
	static void test_height()
	{
		_Ty3 p0(0, 0, 0);

		_Ty3 p1(0.8447993, 4.204894, 1.863186);
		_Ty3 p2(4.716443, 1.822652, 1.385437);
		_Ty3 p3(4.784367, 0.1356559, 1.047116);

		// It is used only to check if the best normal
		// matches with the average plane normals
		std::vector<_Ty3> triangle = { p1, p2, p3 }, triangle_oriented;
		orient_triangles(p0, triangle, false, triangle_oriented);
		CmnMath::geometricprimitive::Plane plane(triangle_oriented[0],
			triangle_oriented[1], triangle_oriented[2]);
		std::cout << plane.n << " " << plane.p << std::endl;
		float d = plane.distance(CmnMath::algebralinear::Vector3f(0, 0, 0));
		std::cout << "d: " << d << std::endl;
	}


private:

	// https://stackoverflow.com/questions/686353/c-random-float-number-generation
	static std::random_device rd;

	static float statistical_mode(const std::vector<int> &inputs) {
		std::unordered_map<int, size_t> counts;
		for (int i : inputs)
			++counts[i];

		std::multimap<size_t, int, std::greater<size_t> > inv;
		for (auto p : counts)
			inv.insert(std::make_pair(p.second, p.first));

		auto e = inv.upper_bound(inv.begin()->first);

		double sum = std::accumulate(inv.begin(),
			e,
			0.0,
			[](double a, std::pair<size_t, int> const &b) {return a + b.second; });

		return sum / std::distance(inv.begin(), e);
	}


	/** @brief Orient the triangles of a mesh according to an observer position.

	@param[in] v Observer
	@note: It supports opencv point3f structure.
	*/
	static void orient_triangles(
		CmnMath::algebralinear::Vector3f &v,
		std::vector<CmnMath::algebralinear::Vector3f> &triangle,
		bool face_inside,
		std::vector<CmnMath::algebralinear::Vector3f> &triangle_oriented)
	{
		// Map the points of the image
		CmnMath::algebralinear::Vector3f a = triangle[0];
		CmnMath::algebralinear::Vector3f b = triangle[1];
		CmnMath::algebralinear::Vector3f c = triangle[2];
		CmnMath::algebralinear::Vector3f tmp = (b - a);
		CmnMath::algebralinear::Vector3f n = tmp.cross(c - a);
		float r = n.dot(a - v);
		//std::cout << "r: " << r << std::endl;

		if (r > 0 && face_inside ||
			r < 0 && !face_inside) {
			triangle_oriented.push_back(c); triangle_oriented.push_back(b); 
			triangle_oriented.push_back(a);
		} else {
			triangle_oriented.push_back(a); triangle_oriented.push_back(b); 
			triangle_oriented.push_back(c);
		}
	}
};


} // namespace pointcloud
} // namespace CmnMath

#endif // ESTIMATEHEIGHT_ESTIMATEHEIGHT_HPP__