/**
* @file StringFormatConversion.cpp
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

#include "string/inc/string/StringFormatConversion.hpp"


//-----------------------------------------------------------------------------
std::wstring CmnLib::text::StringFormatConversion::s2ws(
	const std::string& s)
{
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	//std::vector<wchar_t> buf;
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &buf[0], len);
	std::wstring r(&buf[0]);
	delete[] buf;
#else
	std::wstring r;
#endif
	return r;
}
//-----------------------------------------------------------------------------
std::string CmnLib::text::StringFormatConversion::ws2s(
	const std::wstring& s)
{
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	//std::vector<char> buf;
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &buf[0], len, 0, 0);
	std::string r(&buf[0]);
	delete[] buf;
#else
	std::string r;
#endif
	return r;
}
//-----------------------------------------------------------------------------
std::wstring CmnLib::text::StringFormatConversion::toUnicode(
	const std::string &s)
{
	return s2ws(s);
}
//-----------------------------------------------------------------------------
std::string CmnLib::text::StringFormatConversion::toUnicode(
	const std::wstring &s)
{
	return ws2s(s);
}
//-----------------------------------------------------------------------------
LPCWSTR CmnLib::text::StringFormatConversion::toLPCWSTR(
	const std::string &s)
{
	#ifdef UNICODE
		std::wstring stemp = s2ws(s); // Temporary buffer is required
		LPCWSTR result = stemp.c_str();
	#else
		LPCWSTR result = (LPCWSTR)s.c_str();
	#endif

	return result;
}
