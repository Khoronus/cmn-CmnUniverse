/**
* @file quadricequation.hpp
* @brief Solve a quadric equation
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
* @original author Will Perone (will.perone@gmail.com)
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_ALGEBRALINEAR_QUADRICEQUATION_HPP__
#define CMNMATH_ALGEBRALINEAR_QUADRICEQUATION_HPP__

#include <vector>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace algebralinear
{

class QuadricEquation
{
public:

	/** @brief Find solution of a quadric equation.

	Find solution of a quadric equation (elementary algebra).
	*/
	static CMN_32S solve(CMN_64F a, CMN_64F b, CMN_64F c,
		std::vector<CMN_64F>&x, std::vector<CMN_64F> &i)
	{
		if (a == 0) return 0;
		CMN_64F d = std::pow(b, 2) - 4 * a * c;
		if (d == 0) {
			x.push_back(-b / 2 * a);
			return 1;
		}
		if (d > 0) {
			x.push_back((-b + std::sqrt(d)) / (2 * a));
			x.push_back((-b - std::sqrt(d)) / (2 * a));
			return 2;
		}
		if (d < 0) {
			x.push_back(-b / 2 * a);
			x.push_back(-b / 2 * a);
			i.push_back(std::sqrt(-d) / (2 * a));
			i.push_back(-std::sqrt(-d) / (2 * a));
			return -2;
		}
		return 0;
	}

	/** @brief Find solution of a quadric equation.

	Find solution of a quadric equation (elementary algebra).
	*/
	static CMN_32S solvef(CMN_32F a, CMN_32F b, CMN_32F c,
		std::vector<CMN_32F>&x, std::vector<CMN_32F> &i)
	{
		if (a == 0) return 0;
		CMN_32F d = std::pow(b, 2) - 4 * a * c;
		if (d == 0) {
			x.push_back(-b / 2 * a);
			return 1;
		}
		if (d > 0) {
			x.push_back((-b + std::sqrt(d)) / (2 * a));
			x.push_back((-b - std::sqrt(d)) / (2 * a));
			return 2;
		}
		if (d < 0) {
			x.push_back(-b / 2 * a);
			x.push_back(-b / 2 * a);
			i.push_back(std::sqrt(-d) / (2 * a));
			i.push_back(-std::sqrt(-d) / (2 * a));
			return -2;
		}
		return 0;
	}


};

} // namespace algebralinear
} // namespace CmnMath

#endif // CMNMATH_ALGEBRALINEAR_QUADRICEQUATION_HPP__
