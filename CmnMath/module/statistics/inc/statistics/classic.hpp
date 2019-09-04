/**
* @file classic.hpp
* @brief Classic statistics
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
* @version 1.1.0.0
*
*/

#ifndef CMNMATH_STATISTICS_CLASSIC_HPP__ 
#define CMNMATH_STATISTICS_CLASSIC_HPP__ 

#include <vector>

namespace CmnMath
{
namespace statistics
{
namespace classic
{

///** @brief Class to perform
//*/
//template<typename REAL>
//class SeriesAnalysis
//{
//public:
//
//	/** @brief Calculate the mean of a series.
//	*/
//	static bool mean(std::vector< REAL > &container, CMN_64F &result)
//	{
//		if (container.size() == 0) return false;
//		CMN_32S s = container.size();
//		result = 0;
//		for (std::vector< REAL >::const_iterator it = container.begin();
//			it != container.end(); it++)
//		{
//			result += *it;
//		}
//		result /= s;
//		return true;
//	}
//
//	/** @brief Calculate the variance of a series.
//	*/
//	static bool variance(std::vector< REAL > &container, CMN_64F mean, CMN_64F &result)
//	{
//		if (container.size() == 0) return false;
//		CMN_32S s = container.size();
//		result = 0;
//		for (std::vector< REAL >::const_iterator it = container.begin();
//			it != container.end(); it++)
//		{
//			result += std::pow(*it - mean, 2);
//		}
//		result /= s;
//		return true;
//	}
//
//	// @brief Calculate the variance of a series.
//	// http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
//	// Simple test
//	// http://www.mathsisfun.com/data/standard-deviation.html
//	// 600 470 170 430 300 | mean = 394 | variance = 21704 | 
//	//                       standard deviation = 147.32...
//	static bool naive_variance(std::vector< REAL > &container, CMN_64F &result)
//	{
//		if (container.size() == 0) return false;
//		CMN_32S n = 0;
//		CMN_64F Sum = 0;
//		CMN_64F Sum_sqr = 0;
//
//		for (std::vector< REAL >::const_iterator it = container.begin();
//			it != container.end(); ++it)
//		{
//			n = n + 1;
//			Sum = Sum + (*it);
//			Sum_sqr = Sum_sqr + std::pow((*it), 2);
//		}
//		result = (Sum_sqr - (Sum*Sum) / n) / n;
//		return true;
//	}
//
//	static void mean_var(const std::vector<REAL> &v, REAL &mean,
//		REAL &stdev) {
//		REAL sum = std::accumulate(v.begin(), v.end(), 0.0);
//		//double mean = sum / v.size();
//		mean = sum / v.size();
//
//		std::vector<REAL> diff(v.size());
//		std::transform(v.begin(), v.end(), diff.begin(), [mean](REAL x) {
//			return x - mean; });
//		double sq_sum = std::inner_product(diff.begin(), diff.end(),
//			diff.begin(), 0.0);
//		//double stdev = std::sqrt(sq_sum / v.size());
//		stdev = std::sqrt(sq_sum / v.size());
//	}
//
//};


	/** @brief Class to perform
*/
template<typename _Ty, typename REAL = CMN_64F>
class SeriesAnalysis
{
public:

	/** @brief Calculate the mean of a series.
	*/
	static bool mean(std::vector< _Ty > &container, REAL &result)
	{
		if (container.size() == 0) return false;
		size_t s = container.size();
		result = 0;
		for (std::vector< _Ty >::const_iterator it = container.begin();
			it != container.end(); it++)
		{
			result += *it;
		}
		result /= static_cast<REAL>(s);
		return true;
	}

	/** @brief Calculate the variance of a series.
	*/
	static bool variance(std::vector< _Ty > &container, REAL mean, REAL &result)
	{
		if (container.size() == 0) return false;
		size_t s = container.size();
		result = 0;
		for (std::vector< _Ty >::const_iterator it = container.begin();
			it != container.end(); it++)
		{
			result += std::pow(*it - mean, 2);
		}
		result /= s;
		return true;
	}

	// @brief Calculate the variance of a series.
	// http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
	// Simple test
	// http://www.mathsisfun.com/data/standard-deviation.html
	// 600 470 170 430 300 | mean = 394 | variance = 21704 | 
	//                       standard deviation = 147.32...
	static bool naive_variance(std::vector< _Ty > &container, REAL &result)
	{
		if (container.size() == 0) return false;
		CMN_32S n = 0;
		REAL Sum = 0;
		REAL Sum_sqr = 0;

		for (std::vector< _Ty >::const_iterator it = container.begin();
			it != container.end(); ++it)
		{
			n = n + 1;
			Sum = Sum + (*it);
			Sum_sqr = Sum_sqr + std::pow((*it), 2);
		}
		result = (Sum_sqr - (Sum*Sum) / n) / n;
		return true;
	}

	/** @brief It estimates the mean and variance from a vector
	*/
	static void mean_var(const std::vector<_Ty> &v, REAL &mean,
		REAL &stdev) {
		REAL sum = std::accumulate(v.begin(), v.end(), 0.0);
		//double mean = sum / v.size();
		mean = sum / v.size();

		std::vector<_Ty> diff(v.size());
		std::transform(v.begin(), v.end(), diff.begin(), [mean](REAL x) {
			return x - mean; });
		double sq_sum = std::inner_product(diff.begin(), diff.end(),
			diff.begin(), 0.0);
		//double stdev = std::sqrt(sq_sum / v.size());
		stdev = std::sqrt(sq_sum / v.size());
	}

};


} // namespace classic
} // namespace statistics
} // namespace CmnMath

#endif /* CMNMATH_STATISTICS_CLASSIC_HPP__ */
