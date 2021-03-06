/**
* @file distancehamming.hpp
* @brief Header of all the files related to the algorithm
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNIP_MEASURE_DISTANCEHAMMING_HPP__
#define CMNIP_MEASURE_DISTANCEHAMMING_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

namespace CmnIP
{
namespace measure
{


/** @brief Calculate the Hamming distance
*/
template <typename t>
class DistanceHamming
{
public:

	static unsigned int calculate(t x, t y)
	{
		unsigned int dist = 0;
		t val = x ^ y;
		while (val)
		{
			++dist;
			val &= val - 1;
		}
		return dist;
	}

	static unsigned int calculate(std::vector<t> &x,
		std::vector<t> &y)
	{
		unsigned int d = 0;
		if (x.size() != y.size()) return -1;
		size_t s = x.size();
		for (int i = 0; i < s; i++)
		{
			d += calculate(x[i], y[i]);
		}
		return d;
	}

	static unsigned int calculate(t *x, unsigned int xsize,
		t *y, unsigned int ysize)
	{
		if (xsize != ysize) return -1;
		unsigned int d = 0;
		size_t s = xsize;
		for (int i = 0; i < s; i++)
		{
			d += calculate(x[i], y[i]);
		}
		return d;
	}

};


} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_DISTANCEHAMMING_HPP__
