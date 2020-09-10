/**
* @file Exception.hpp
* @brief Header of exception classes.
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

#ifndef CMNLIB_CMNLIBCORE_EXCEPTION_HPP__
#define CMNLIB_CMNLIBCORE_EXCEPTION_HPP__

#include "foundations.hpp"

namespace CmnLib
{
namespace core
{
CL_INLINE std::string format( const char* fmt, ... )
{
	char buf[1 << 16];
	va_list args;
	va_start( args, fmt );
	vsprintf( buf, fmt, args );
	return std::string(buf);
}

/*!
	The standard cmnlib exception class.
	Instances of the class are thrown by various functions and methods in the case of critical errors.
	*/
class CL_EXPORTS Exception : public std::exception
{
public:
	/*!
		Default constructor
		*/
	Exception() { code = 0; line = 0; }
	/*!
		Full constructor. Normally the constuctor is not called explicitly.
		Instead, the macros CV_Error(), CV_Error_() and CV_Assert() are used.
	*/
	Exception(int _code, const std::string& _err, const std::string& _func, const std::string& _file, int _line)
		: code(_code), err(_err), func(_func), file(_file), line(_line)
	{ formatMessage(); }
	    
	virtual ~Exception() throw() {}

	/*!
		\return the error description and the context as a text string.
	*/ 
	virtual const char *what() const throw() { return msg.c_str(); }

	void formatMessage()
	{
		if( func.size() > 0 )
			msg = format("%s:%d: error: (%d) %s in function %s\n", file.c_str(), line, code, err.c_str(), func.c_str());
		else
			msg = format("%s:%d: error: (%d) %s\n", file.c_str(), line, code, err.c_str());
	}
	    
	std::string msg; ///< the formatted error message

	int code; ///< error code @see CVStatus
	std::string err; ///< error description
	std::string func; ///< function name. Available only when the compiler supports __func__ macro
	std::string file; ///< source file name where the error has occured
	int line; ///< line number in the source file where the error has occured 
};

}	// namespace core
}	// namespace CmnLib

#endif /* CMNLIB_CMNLIBCORE_EXCEPTION_HPP__ */

