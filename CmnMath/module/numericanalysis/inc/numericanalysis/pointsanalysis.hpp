/* @file pointsanalysis.hpp
* @brief Class to perform a curve fitting.
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
* @author From Codeproject (please find the reference)
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_NUMERICALANALYSIS_POINTSANALYSIS_HPP__
#define CMNMATH_NUMERICALANALYSIS_POINTSANALYSIS_HPP__

#include <vector>
#include <algorithm>    // std::for_each

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace numericalanalysis
{

/** @brief Class to perform some analysis over a set of points
*/
template <typename _Ty>
class PointsAnalysis
{
public:

	/** @brief It calculates the min and max value over three entries.

	    It calculates the min and max value over three entries.
	*/
	static void minmax(_Ty a, _Ty b, _Ty c, _Ty &m, _Ty &M)
	{
		m = (std::min)((std::min)(a, b), c);
		M = (std::max)((std::max)(a, b), c);
	}

	/** @brief It normalize an input value in a min and max range.

	    It normalize an input value in a min and max range.
	*/
	static void normalize(_Ty m, _Ty M, _Ty v, _Ty &o)
	{
		o = (v - m) / (M - m);
	}

};


}	// namespace numericalanalysis
}	// namespace CmnMath


#endif /* CMNMATH_NUMERICALANALYSIS_POINTSANALYSIS_HPP__ */