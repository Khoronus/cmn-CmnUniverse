/**
* @file ContainerNearestKey.hpp
* @brief Class to identify the nearest key in a std container.
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

#ifndef CMNLIB_CONTAINER_CONTAINERNEARESTKEY_HPP__
#define CMNLIB_CONTAINER_CONTAINERNEARESTKEY_HPP__

#include <vector>
#include <map>
#include <algorithm>

namespace CmnLib
{
namespace container
{

/** @brief Class to detect the value matching with the nearest key.

	Class to detect the value matching with the nearest key
*/
template< typename T0, typename T1>
class ContainerNearestKey
{
public:

	/** @brief Get the associated value to the nearest key.

		Get the associated value to the nearest key.
		@param[in] container The container to analyze.
		@param[in] key_in The key to search.
		@param[in] tolerance The acceptable distance to find an element.
		@param[out] out Value associated to the nearest key.
		@return Return TRUE in case an element has been found.
	*/
	static bool get_value(std::map<T0, T1> &container,
		T0 key_in, T0 tolerance, T1 &out)
	{
		if (container.size() > 0)
		{
			T0 key = container.begin()->first;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			T0 min_diff = std::numeric_limits<T0>::max();
#else
			T0 min_diff = 1000000;
#endif
			bool bFound = false;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = container.begin(); it != container.end(); it++) {
#else
			//for (std::map<T0, T1>::const_iterator it = container.begin(); it != container.end(); it++) {
			for (auto &it : container) {
#endif
				T0 diff = std::abs(it->first - key_in);
				if (diff < tolerance && diff < min_diff) {
					min_diff = diff;
					key = it->first;
					bFound = true;
				}
			}

			out = container[key];
			return bFound;
		}
		return false;
	}

	/** @brief Get the associated value to the nearest key.

	Get the associated value to the nearest key.
	@param[in] container The container to analyze.
	@param[in] key_in The key to search.
	@param[in] tolerance The acceptable distance to find an element.
	@param[out] out Value associated to the nearest key.
	@return Return TRUE in case an element has been found.
	*/
	static bool get_value(std::vector< std::pair<T0, T1> > &container,
		T0 key_in, T0 tolerance, T1 &out)
	{
		if (container.size() > 0)
		{
			int idx_selected = -1;
			int idx = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			T0 min_diff = std::numeric_limits<T0>::max();
			for (auto it = container.begin(); it != container.end(); it++) {
#else
			T0 min_diff = 10000000;
			//for (std::vector< std::pair<T0, T1> >::const_iterator it = container.begin(); it != container.end(); it++) {
			for (auto &it : container) {
#endif
				T0 diff = std::abs(it->first - key_in);
				if (diff < tolerance && diff < min_diff) {
					min_diff = diff;
					idx_selected = idx;
				}
				++idx;
			}

			if (idx_selected >= 0) {
				out = container[idx_selected].second;
				return true;
			}
		}
		return false;
	}


	/** @brief Get the min and max value in between of the associated value 
	           to the nearest key.

	Get the min and max value in between of the associated value to the nearest 
	key.
	@param[in] container The container to analyze.
	@param[in] key_in The key to search.
	@param[in] tolerance The acceptable distance to find an element.
	@param[out] out Min and Max associated element in between of the requested key.
	@return Return the number of the detected values. 
	*/
	static int get_value(std::vector< std::pair<T0, T1> > &container,
		T0 key_in, T0 tolerance, 
		std::pair< std::pair<T0, T1>, std::pair<T0, T1>> &out)
	{
		int idfound = 0;
		if (container.size() > 0)
		{
			int idx = 0;
			int idx_selected[2] = {-1, -1};
			T0 min_diff[2] = {std::numeric_limits<T0>::max(), std::numeric_limits<T0>::max()};

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = container.begin(); it != container.end(); it++)
#else
			//for (std::vector< std::pair<T0, T1> >::const_iterator it = container.begin(); it != container.end(); it++)
			for (auto &it : container) 
#endif
			{
				T0 diff = it->first - key_in;
				int item = 0;
				if (diff < 0) item = 1;
				//std::cout << "diff: " << diff << std::endl;
				diff = std::abs(diff);
				if (diff < tolerance && diff < min_diff[item] ) {
					//std::cout << item << " min_diff[item]: " << diff << " idx_selected[item]: " << idx_selected[item] << " " << idx << std::endl;

					min_diff[item] = diff;
					idx_selected[item] = idx;
				}
				++idx;
			}

			// Todo: Change this code with a clean one
			if (idx_selected[0] >= 0) {
				out.first = container[ idx_selected[0] ];
				++idfound;
			} else {
				out.first = std::make_pair(-1, -1);
			}

			if (idx_selected[1] >= 0) {
				out.second = container[ idx_selected[1] ];
				++idfound;
			} else {
				out.second = std::make_pair(-1, -1);
			}
		}
		return idfound;
	}

}; 

}  // namespace container
}  // namespace CmnLib

#endif
