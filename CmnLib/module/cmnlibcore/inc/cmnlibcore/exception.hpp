/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

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

