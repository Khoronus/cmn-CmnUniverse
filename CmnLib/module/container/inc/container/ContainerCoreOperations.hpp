/**
* @file ContainerCoreOperations.hpp
* @brief Class to perform some core operations over a container.
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

#ifndef CMNLIB_CONTAINER_CONTAINERCOREOPERATIONS_HPP__
#define CMNLIB_CONTAINER_CONTAINERCOREOPERATIONS_HPP__

#include <vector>
#include <algorithm>

namespace CmnLib
{
namespace container
{

/** @brief Class to perform some simple operations over STD containers.
*/
template<typename _Ty>
class ContainerCoreOperations
{
public:

	/** @brief Collect the min and max value of a sequence of values.

		Collect the min and max value of a sequence of values.
		@sample
		  Input
		      3 5 7 10
			  -1 2 9 5
			  2 9 30 -5
		   Container min max
		      (min)
			  -1 2 7 -5
			  (max)
			  3 9 30 10

		@param[in] container Container with the data.
		@param[out] container_mM Container with the minimum and maximum values
		           for the features.
		@note The size of the min and max container is adjusted to fit the 
		      input. All the previous data is lost.
	*/
	static void container_minmax(const std::vector<_Ty> &container,
		std::vector<std::pair<_Ty, _Ty>> &container_mM) 
	{
		// Adjust the container size
		if (container_mM.size() != container.size()) {
			container_mM.clear();
			container_mM.resize( container.size() );
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = container_mM.begin(); it != container_mM.end(); it++) {
				it->first = std::numeric_limits<_Ty>::max();
				it->second = std::numeric_limits<_Ty>::min();
#else
			//for (std::vector<std::pair<_Ty, _Ty>>::iterator it = container_mM.begin(); it != container_mM.end(); it++) {
			for (auto &it : container_mM) {
				it.first = 1000000;
				it.second = -1000000;
#endif
			}
		}

		// Update the container
		size_t s = container.size();
		for (size_t i = 0; i < s; i++) {
			container_mM[i].first = (std::min)(container_mM[i].first, 
				container[i]);
			container_mM[i].second = (std::max)(container_mM[i].second, 
				container[i]);
		}
	}

	/** @brief Split a vector with pair of data in two.

		Split a vector with pair of data in two.
		@param[in] container Container with the data.
		@param[out] v1 Container with one of the vector data.
		@param[out] v2 Container with other vector data.
	*/
	static void split(const std::vector<std::pair<_Ty, _Ty> > &container,
		std::vector<_Ty> &v1, std::vector<_Ty> &v2) {
	
		v1.clear(); v2.clear();
//#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
//		for (auto it = container.begin(); it != container.end(); it++) {
//#else
//		//for (std::vector<std::pair<_Ty, _Ty> >::const_iterator it = container.begin(); it != container.end(); it++) {
//		for (auto &it : container) {
//#endif

		for (auto &it : container) {
			v1.push_back( it.first );
			v2.push_back( it.second );
		}
	}

	/** @brief Merge two vector in a single container data.

		Merge two vector in a single container data.
		@param[in] v1 Container with one of the vector data.
		@param[in] v2 Container with other vector data.
		@param[out] container Container with the data.
	*/
	static void merge(const std::vector<_Ty> &v1, 
		const std::vector<_Ty> &v2,
		std::vector<std::pair<_Ty, _Ty> > &container) {
	
		if (v1.size() != v2.size()) return;
		container.clear();

		size_t s = v1.size();

		for (size_t i = 0; i < s; i++) {
			container.push_back( std::make_pair(v1[i], v2[i]) );
		}
	}
};


}  // namespace container
}  // namespace CmnLib

#endif
