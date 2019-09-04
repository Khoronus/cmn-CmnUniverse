/**
* @file STDStringFunc.hpp
* @brief Class to manage a std string functions.
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
* @author Unknown
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNLIB_STRING_STDSTRINGFUNC_HPP__
#define CMNLIB_STRING_STDSTRINGFUNC_HPP__

#include <set>
#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <chrono>

namespace commctrl
{

/** @brief Class to perform some functions on a string
*/
class STDStringFunc
{
public:

	/** @brief It split a string
	*/
	template<typename Out>
	static void split(const std::string &s, char delim, Out result) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			if (!item.empty()) {
				*(result++) = item;
			}
		}
	}

	/** @brief It split a string.

		@return It returns the strings found
	*/
	static std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, std::back_inserter(elems));
		return elems;
	}

	/** @brief It appends a set of chars in front of a number.

		It appends a set of chars in front of a number.
		i.e. 16 becomes 000016
	*/
	static std::string append_front_chars(
		int n_zero, int num_frame, char c) {
		std::string old_string = std::to_string(num_frame);
		std::string new_string = std::string(n_zero - old_string.length(), c) +
			old_string;
		return new_string;
	}

};


} // namespace commctrl

#endif // CMNLIB_STRING_STDSTRINGFUNC_HPP__