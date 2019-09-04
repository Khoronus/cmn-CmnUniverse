/**
* @file main.cpp
* @brief It calculates all the ray reprojection on an observer camera
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
* @original author 
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNLIB_STRING_STRINGITERATOR_HPP__
#define CMNLIB_STRING_STRINGITERATOR_HPP__

#include <string>
#include <iostream>
#include <vector>

namespace CmnLib
{
namespace text
{

/** @brief It split a string in substrings

@link: https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
*/
class StringIterator
{
public:

	template<typename Out>
	static void split(const std::string &s, char delim, Out result) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}

	static std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, std::back_inserter(elems));
		return elems;
	}
};

}  // namespace text
}  // namespace CmnLib

#endif // CMNLIB_STRING_STRINGITERATOR_HPP__