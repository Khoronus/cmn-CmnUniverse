/**
* @file sample_statistics_statistics.cpp
* @brief Sample dynamic.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"
#include "statistics/inc/statistics/statistics_headers.hpp"

namespace
{


void point2features(const std::vector< std::pair<CmnMath::algebralinear::Vector2f, CmnMath::algebralinear::Vector2f> > &points,
	std::vector< CmnMath::CMN_64F > &v_angle, std::vector< CmnMath::CMN_64F > &v_magnitude) {
	
	for (std::vector< std::pair<CmnMath::algebralinear::Vector2f, CmnMath::algebralinear::Vector2f> >::const_iterator it = points.begin();
		it != points.end(); it++)
	{
		v_angle.push_back(std::atan2((CmnMath::CMN_64F)(it->second.y - it->first.y),
			(CmnMath::CMN_64F)(it->second.x - it->first.x)));
		v_magnitude.push_back(std::sqrt( 
			std::pow((CmnMath::CMN_64F)(it->second.y - it->first.y), 2) +
			std::pow((CmnMath::CMN_64F)(it->second.x - it->first.x), 2)));
	}
}


/** @brief Function to test the classes and functions
*/
void test()
{
	std::vector< std::pair<CmnMath::algebralinear::Vector2f, CmnMath::algebralinear::Vector2f> > points;
	std::vector< CmnMath::CMN_64F > v_angle, v_magnitude;

	points.push_back(std::make_pair(CmnMath::algebralinear::Vector2f(50, 50), CmnMath::algebralinear::Vector2f(100, 125)));
	points.push_back(std::make_pair(CmnMath::algebralinear::Vector2f(60, 50), CmnMath::algebralinear::Vector2f(90, 125)));
	points.push_back(std::make_pair(CmnMath::algebralinear::Vector2f(50, 70), CmnMath::algebralinear::Vector2f(100, 155)));
	points.push_back(std::make_pair(CmnMath::algebralinear::Vector2f(50, 90), CmnMath::algebralinear::Vector2f(130, 125)));
	points.push_back(std::make_pair(CmnMath::algebralinear::Vector2f(80, 50), CmnMath::algebralinear::Vector2f(120, 125)));

	point2features(points, v_angle, v_magnitude);

	CmnMath::CMN_64F variance_angle = 0, variance_magnitude = 0;
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::naive_variance(v_angle, variance_angle);
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::naive_variance(v_magnitude, variance_magnitude);
	std::cout << std::sqrt(variance_angle) << " " << std::sqrt(variance_magnitude) << std::endl;
}


}	// namespace

void test2()
{
	CmnMath::CMN_64F mean = 0, variance = 0;
	std::vector<CmnMath::CMN_64F> v = { 69.7, 74.4,77.2,75.7,76,75.3,79.4,81.8,83.6,84.9 };
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::mean(v, mean);
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::variance(v, mean, variance);
	std::cout << "mean: " << mean << " variance: " << variance << std::endl;
	std::cout << "stdev: " << sqrt(variance) << std::endl;
}

void test3()
{
	CmnMath::CMN_64F mean = 0, variance = 0;
	std::vector<CmnMath::CMN_64F> v = { 
		63, 57, 92, 87, 70, 61, 75, 58, 63, 71, 
		90, 77, 59, 88, 48, 83, 63, 94, 72, 70,
		67, 81, 93, 55, 71, 71, 86, 98, 60, 90,
		62, 67, 78, 61, 89, 93, 71, 59, 93, 84,
		85, 88, 77, 69, 58, 90, 97, 72, 64, 60,
		60, 57, 79, 83, 64, 94, 86, 64, 92, 74,
		94, 85, 56, 77, 89, 72, 71, 61, 92, 97,
		97, 86, 83, 88, 65, 87, 76, 84, 81, 81,
		94, 90, 76, 88, 65, 93, 86, 87, 94, 63,
		88, 91, 71, 89, 97, 79, 82, 87, 69, 85
	};
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::mean(v, mean);
	CmnMath::statistics::classic::SeriesAnalysis<CmnMath::CMN_64F>::variance(v, mean, variance);
	std::cout << "mean: " << mean << " variance: " << variance << std::endl;
	std::cout << "stdev: " << sqrt(variance) << std::endl;
}


/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test trigonometry" << std::endl;
	test();
	test2();
	test3();
	return 0;
}