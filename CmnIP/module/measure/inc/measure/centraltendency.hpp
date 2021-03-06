/**
* @file centraltendency.hpp
* @brief Measure the central tendency
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
* @author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNIP_MEASURE_CENTRALTENDENCY_HPP__
#define CMNIP_MEASURE_CENTRALTENDENCY_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief A class to measure the central tendency.

    A class to measure the central tendency.
	@link http://en.wikipedia.org/wiki/Central_tendency
*/
template <typename _Ty>
class CentralTendency
{
public:

	/** @brief Calculate the mean point of a set of points.

	@param[in] points The set of points.
	@note The type of data is expected to have direct access to x,y members.
	@return Return the mean position of the set of points.
	*/
	static _Ty points_mean(const std::vector<_Ty> &points)
	{
		std::vector<float> x, y;
		for (auto it = points.begin(); it != points.end(); it++)
		{
			x.push_back(it->x);
			y.push_back(it->y);
		}
		double xr = 0, yr = 0;
		CmnMath::statistics::classic::SeriesAnalysis<float>::mean(x, xr);
		CmnMath::statistics::classic::SeriesAnalysis<float>::mean(y, yr);
		return _Ty(xr, yr);
	}

};

} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_CENTRALTENDENCY_HPP__
