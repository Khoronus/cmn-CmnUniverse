/**
* @file StringFormatConversion.hpp
* @brief Conversion ANSI to UNICODE and vice versa.
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

#ifndef CMNLIB_STRING_STRINGFORMATCONVERSION_HPP__
#define CMNLIB_STRING_STRINGFORMATCONVERSION_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "cmnlibcore/inc/cmnlibcore/types.hpp"


#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
#include <windows.h>
#else

#ifndef _MAC
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
#endif
typedef CMN_CONST WCHAR *LPCWSTR, *PCWSTR;

#endif



namespace CmnLib
{
namespace text
{

/** Class to convert strings from ANSI to UNICODE and viceversa
*/
class StringFormatConversion
{
public:

	/** ANSI string to UNICODE
	*/
	static std::wstring toUnicode(const std::string &s);

	/** UNICODE string to ANSI
	*/
	static std::string toUnicode(const std::wstring &s);

	/** ANSI string to LPCWSTR
	*/
	static LPCWSTR toLPCWSTR(const std::string &s);

 private:

	/**	Convert a string in a unicode string
	*/
	static std::wstring s2ws(const std::string& s);
	/** Convert a unicode string in ansi string
	*/
	static std::string ws2s(const std::wstring& s);
};


} // namespace text
} // namespace CmnLib

#endif // CMNLIB_STRING_STRINGFORMATCONVERSION_HPP__
