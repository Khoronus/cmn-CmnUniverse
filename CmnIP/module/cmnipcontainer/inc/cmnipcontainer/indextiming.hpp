/**
* @file algorithm_headers.hpp
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

#ifndef CMNIP_CMNIPCONTAINER_INDEXTIMING_HPP__
#define CMNIP_CMNIPCONTAINER_INDEXTIMING_HPP__

#include <map>
#include <iostream>

namespace CmnIP
{
namespace cmnipcontainer
{


class IndexTiming
{
public:

	void clear() {
		last_index_ = -1;
		last_timestamp_ = 0;
		entries_.clear();
	}

	void add(int value) {
		if (entries_.find(value) != entries_.end()) {
			++entries_[value];
		}
		else {
			entries_[value] = 1;
		}
	}

	void add(int index, int timestamp) {
		if (last_index_ != -1) {
			int difference_frame = timestamp - last_timestamp_ - 1;
			// Update the last index found
			if (entries_.find(last_index_) != entries_.end()) {
				entries_[last_index_] += difference_frame;
			}
			else {
				entries_[last_index_] = difference_frame;
			}
			// Update the current
			if (entries_.find(index) != entries_.end()) {
				entries_[index] += 1;
			}
			else {
				entries_[index] = 1;
			}
		}
		else {
			entries_[index] = timestamp;
		}
		last_index_ = index;
		last_timestamp_ = timestamp;
	}

	bool peak(int &index) {
		if (entries_.size() == 0) return false;
		index = entries_.begin()->first;
		int maxvalue = entries_.begin()->second;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = entries_.begin(); it != entries_.end(); it++)
#else
		for (std::map<int, int>::const_iterator it = entries_.begin(); it != entries_.end(); it++)
#endif
		{
			if (it->second > maxvalue) {
				index = it->first;
				maxvalue = it->second;
			}
		}
		return true;
	}

	void display() {
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = entries_.begin(); it != entries_.end(); it++)
#else
		for (std::map<int, int>::const_iterator it = entries_.begin(); it != entries_.end(); it++)
#endif
		{
			std::cout << "(" << it->first << "," << it->second << ") ";
		}
		std::cout << std::endl;
	}

private:
	int last_index_;
	int last_timestamp_;
	std::map<int, int> entries_;
};


} // namespace cmnipcontainer
} // namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_INDEXTIMING_HPP__ */
