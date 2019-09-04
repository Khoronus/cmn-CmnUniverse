/**
* @file directional.hpp
* @brief Classes to manage some simple statistics operations
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
* @version 1.0.0.0
*
*/

#ifndef CMNMATH_STATISTICS_DIRECTIONAL_HPP__ 
#define CMNMATH_STATISTICS_DIRECTIONAL_HPP__ 

#include <vector>

namespace CmnMath
{
namespace statistics
{
namespace directional
{

/** @brief Class to perform
*/
template<typename _Ty>
class SeriesAnalysis
{
public:

	static bool naive_mean(const std::vector<_Ty> &angles, _Ty &result) {
		if (angles.size() == 0) return false;
		//std::vector<_Ty> v_s, v_c;
		_Ty s_sum = 0, c_sum = 0;
		for (std::vector<_Ty>::const_iterator it = angles.begin(); it != angles.end(); ++it)
		{
			s_sum += std::sin(*it);
			c_sum += std::cos(*it);
		}
		_Ty s = s_sum / angles.size();
		_Ty c = c_sum / angles.size();

		return naive_theta(s, c, result);
	}

	static bool naive_variance(const std::vector<_Ty> &angles, _Ty mean, _Ty &result) {
		if (angles.size() == 0) return false;
		result = 0;
		for (std::vector<_Ty>::const_iterator it = angles.begin(); it != angles.end(); ++it)
		{
			_Ty s = std::sin(*it);
			_Ty c = std::cos(*it);

			_Ty r = 0;
			if (naive_theta(s, c, r)) {
				_Ty d = r - mean;
				result += std::pow(d, 2);
			}
		}
		result /= angles.size();
		return true;
	}

	static bool mean(const std::vector<_Ty> &angles, _Ty &theta, _Ty &R) {
		if (angles.size() == 0) return false;
		//std::vector<_Ty> v_s, v_c;
		std::complex<_Ty> phi;
		for (std::vector<_Ty>::const_iterator it = angles.begin(); it != angles.end(); ++it)
		{
			phi += std::complex<_Ty>(std::cos(*it), std::sin(*it));
		}
		phi /= angles.size();
		theta = std::arg(phi);
		R = std::abs(phi);

		return true;
	}

	static _Ty variance(_Ty R) {
		return 1 - R;
	}

	static _Ty standard_deviation(_Ty R) {
		return std::sqrt(-2 * std::log(R));
	}

private:

	static bool naive_theta(_Ty s, _Ty c, _Ty &result) {
		// Check the match
		if (s > 0 && c > 0) {
			result = std::atan(s / c);
		}
		else if (s < 0 && c > 0) {
			result = std::atan(s / c) + 2 * CV_PI;
		}
		else if (c < 0) {
			result = std::atan(s / c) + CV_PI;
		}
		else {
			return false;
		}
		return true;
	}
};


} // namespace directional
} // namespace statistics
} // namespace CmnMath

#endif /* CMNMATH_STATISTICS_DIRECTIONAL_HPP__  */
