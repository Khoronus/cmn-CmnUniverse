/**
* @file StringFormatConversion.hpp
* @brief Conversion string to number and vice versa
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
* @author  unknown
* @bug No known bugs.
* @version 1.0.0.0
*
*/

#ifndef CMNLIB_STRING_STRINGCONVERSION_HPP__
#define CMNLIB_STRING_STRINGCONVERSION_HPP__

#include <iostream>
#include <sstream>
#include <string>

namespace CmnLib
{
namespace text
{


/** @brief Class to convert string and numbers
*/
class StringConversion
{
public:

	/** @brief Function to conver number to string.

	Function to conver number to string.
	@param[in] Number to convert.
	@return Return the string.
	@code

	NumberToString ( Number );

	@endcode
	*/
	template <typename T>
	static std::string NumberToString(T Number)
	{
		std::ostringstream ss;
		ss << Number;
		return ss.str();
	}

	/** @brief Function to conver string to number.

	Function to conver string to number.
	@param[in] String to convert.
	@return Return the number.
	@code

	StringToNumber<Type> ( String )

	@endcode
	*/
	template <typename T>
	static T StringToNumber(const std::string &Text)
	{
		std::istringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}
};


} // namespace text
} // namespace CmnLib

#endif // CMNLIB_STRING_STRINGCONVERSION_HPP__
