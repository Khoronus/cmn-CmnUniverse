/**
* @file error.hpp
* @brief Header of error classes.
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

#ifndef CMNLIB_CMNLIBCORE_ERROR_HPP__
#define CMNLIB_CMNLIBCORE_ERROR_HPP__

#include <iostream>
#include <string>
#include "exception.hpp"

namespace CmnLib
{
namespace core
{

//*********************** Define error calls **************************************

#ifdef CL_ERROR_DISPLAY_COUT
#define CL_DEFAULT_ERROR_CALLBACK  Error::clCoutReport
#else
#define CL_DEFAULT_ERROR_CALLBACK  Error::clSaveReport
#endif

/************Below is declaration of error handling stuff in PLSuite manner**/

typedef int CLStatus;

/** Define the error callback */
typedef int (CL_CDECL *ClErrorCallback)( int status, const char* func_name,
	                const char* err_msg, const char* file_name, int line, void* userdata );

static ClErrorCallback customErrorCallback = 0;
static void* customErrorCallbackData = 0;
static bool breakOnError = false;

/** Manage the errors of the operations
*	@author Dr. Moro Alessandro
*	@brief Apply the error check to the operations
*	@remarks
*		It is actually used for the main operations.
*/
class CL_EXPORTS Error
{
public:

	/** Construptor */
	//Error(char *FunctionName, char *filename = __FILE__);

	/** everithing is ok                */
	static const int CL_StsOk = 0;  
	/** unknown /unspecified error      */
	static const int CL_StsError = -1;
	/* assertion failed					*/
	static const int CL_StsAssert = -215 ;
		
	// Memory error
	/** the pointer is not NULLPTR */
	static const int CL_NullPtr = 101;
	/** memory is out of range */
	static const int CL_MemOutOfRange = 102;
	/** free bad argument */
	static const int CL_BadArg = 103;
	/** end of memory */
	static const int CL_NoMem = 104;

	// Array error
	/** Matrix: Error step size */
	static const int CL_BadStep = 1001;
	/** Matrix: Error to depth size */
	static const int CL_BadDepth = 1002;

	/**************************** Error handling *******************************/

	// Function name
	char clFuncName[256], clFileName[256];

	/** Call to the error function
	*/
	//void Call( int Code, char *Msg, int line );

	//typedef int (Error::*ClErrorCallback)( int status, char* func_name,
	//									   char* err_msg, char* file_name, int line, void* userdata );

	//*********************** Main structure to manage the error codes **************************************

	// Error context structure and functions
	typedef struct
	{
		char*		file;
		int         line;
	}
	ClStackRecord;

	typedef struct ClContext
	{
		int  err_code;
		void*  userdata;
		char  err_msg[4096];
		//ClErrorCallback error_callback;
		ClStackRecord  err_ctx;
	} ClContext;

	static ClContext*
	iclCreateContext(void)
	{
		std::cout << "iclCreateContext" << std::endl;
		ClContext* context = new ClContext;
		context->err_code = CL_StsOk;
		//context->error_callback = CL_DEFAULT_ERROR_CALLBACK;
		context->userdata = 0;
		//int *simple;
		return context;
	}

	static void
	iclDestroyContext(ClContext* context)
	{
		delete context;
	}

	static ClContext*
	iclGetContext(void)
	{
		/* static single-thread library case */
		static ClContext* context = 0;

		if( !context )
			context = iclCreateContext();

		return context;
	}

	/* Get current Program error status */
	//int clGetErrStatus( void );

	/* Sets error status silently */
	//void clSetErrStatus( int status );

	#define CL_ErrModeLeaf     0   /* Print error and exit program */
	#define CL_ErrModeParent   1   /* Print error and continue */
	#define CL_ErrModeSilent   2   /* Don't print and continue */

	/* Retrives current error processing mode */
	//int clGetErrMode( void );

	/* Sets error processing mode, returns previously used mode */
	//int clSetErrMode( int mode );

	/* Retrieves textual description of the error given its code */
	//static char* clErrorStr( int status );

	///* Sets error status and performs some additonal actions (displaying message box,
	//   writing message to stderr, terminating application etc.)
	//   depending on the current error mode */
	//void clError( int status, char* func_name,
	//					 char* err_msg, char* file_name, int line );

	/* Sets error status and performs some additonal actions (displaying message box,
		writing message to stderr, terminating application etc.)
		depending on the current error mode */
	//void clError( int status, const char* func_name,
	//                    const char* err_msg, const char* file_name, int line );

	/*
		Output to:
			clStdErrReport - console(fprintf(stderr,...))
			clGuiBoxReport - MessageBox(WIN32)
	*/
	//int clCoutReport( int status, const char* func_name, const char* err_msg,
	//						  const char* file_name, int line, void* userdata );

	//int clSaveReport( int status, const char* func_name, const char* err_msg,
	//						  const char* file_name, int line, void* userdata );
		
	/* Retrieves detailed information about the last error occured */
	//int clGetErrInfo( const char** errcode_desc, const char** description,
	//                        const char** filename, int* line );
		
	/* Maps IPP error codes to the counterparts from OpenCV */
	//int clErrorFromIppStatus( int ipp_status );
					
	/* Assigns a new error-handling function */
	//ClErrorCallback clRedirectError( ClErrorCallback error_handler,
	//                                       void* userdata CL_DEFAULT(NULLPTR),
	//                                       void** prev_userdata CL_DEFAULT(NULLPTR) );
		
	/*
		Output to:
		    clNulDevReport - nothing
		    clStdErrReport - console(fprintf(stderr,...))
		    clGuiBoxReport - MessageBox(WIN32)
	*/
	//int clNulDevReport( int status, const char* func_name, const char* err_msg,
	//                          const char* file_name, int line, void* userdata );
		
	//int clStdErrReport( int status, const char* func_name, const char* err_msg,
	//                          const char* file_name, int line, void* userdata );
		
	//int clGuiBoxReport( int status, const char* func_name, const char* err_msg,
	//                          const char* file_name, int line, void* userdata );

	//static void error( const Exception& exc );
	//bool setBreakOnError(bool value);
	//ClErrorCallback redirectError( ClErrorCallback errCallback,
	//										  void* userdata=0, void** prevUserdata=0);








	//----------------------------------------------------------------------------
	Error(char *FunctionName, const char *filename = __FILE__)
	{
		strcpy(clFuncName, FunctionName);
		strcpy(clFileName, filename);
	}
	//----------------------------------------------------------------------------
	void Call( int Code, char *Msg, int line )
	{                                                                  
			clError( (Code), clFuncName, Msg, clFileName, line );
	}
	//----------------------------------------------------------------------------
	int clGetErrStatus()
	{
		return iclGetContext()->err_code;
	}
	//----------------------------------------------------------------------------
	void clSetErrStatus( int code )
	{
		iclGetContext()->err_code = code;
	}
	//----------------------------------------------------------------------------
	int
	clCoutReport( int code, const char *func_name, const char *err_msg,
					const char *file, int line, void* )
	{
		std::cout << "ERROR: " << clErrorStr(code) << " (" << (err_msg ? err_msg : "no description") << ") in function ";
		std::cout << (func_name ? func_name : "<unknown>") << ", " << (file != NULLPTR ? file : "") << "(" << line << ")" << std::endl;
		std::cout << "Terminating the application..." << std::endl;
		return 1;
	}
	//----------------------------------------------------------------------------
	int
	clSaveReport( int code, const char *func_name, const char *err_msg,
					const char *file, int line, void* )
	{
		std::ofstream error_message;
		error_message.open("Error.txt");
		error_message << "ERROR: " << clErrorStr(code) << " (" << (err_msg ? err_msg : "no description") << ") in function ";
		error_message << (func_name ? func_name : "<unknown>") << ", " << (file != NULLPTR ? file : "") << "(" << line << ")" << std::endl;
		error_message << "Terminating the application..." << std::endl;
		error_message.close();
		return 1;
	}
	//----------------------------------------------------------------------------
	//char* clErrorStr( int status )
	std::string clErrorStr(int status)
	{
		std::string tmp = status >= 0 ? "status":"error";
		std::string msg = "Unknown " + tmp + " code " + std::to_string(status);

		switch (status)
		{
		case CL_StsOk :			msg = "No Error"; break;
		case CL_StsError :		msg = "Unspecified error"; break;
		default :				msg = "Unknown command"; break;
		};

		return msg;
	}
	//----------------------------------------------------------------------------
	void clError( int code, const char* func_name,
								const char* err_msg,
								const char* file_name, int line )
	{
		if( code == CL_StsOk )
		{
		}
		else
		{
			ClContext *context = iclGetContext();
			char* message = context->err_msg;
			context->err_code = code;
				
			strcpy( message, err_msg );
			strcpy( context->err_ctx.file, file_name);
			context->err_ctx.line = line;

			int terminate_execution = CL_DEFAULT_ERROR_CALLBACK( code, func_name, err_msg,
													 				file_name, line, context->userdata );
				
			iclDestroyContext(context);
			if( terminate_execution )
			{
				// Save the memory data
				exit(-abs(terminate_execution));
			}
		}
	}
	//----------------------------------------------------------------------------
	bool setBreakOnError(bool value)
	{
		bool prevVal = breakOnError;
		breakOnError = value;
		return prevVal;
	}        
	//----------------------------------------------------------------------------
	Error( const Exception& exc )
	{
		if (customErrorCallback != 0) {
			customErrorCallback(exc.code, exc.func.c_str(), exc.err.c_str(),
								exc.file.c_str(), exc.line, customErrorCallbackData);
		} else {
			//const char* errorStr = Error::clErrorStr(exc.code);
			std::string errorStr = Error::clErrorStr(exc.code);
			char buf[1 << 16];

			sprintf( buf, "CL Error: %s (%s) in %s, file %s, line %d",
				errorStr.c_str(), exc.err.c_str(), exc.func.size() > 0 ?
				exc.func.c_str() : "unknown function", exc.file.c_str(), exc.line );
			fprintf( stderr, "%s\n", buf );
			fflush( stderr );
		}
		if(breakOnError)
		{
			static volatile int* p = 0;
			*p = 0;
		}
		throw exc;
	}
	//----------------------------------------------------------------------------		    
	ClErrorCallback
	redirectError( ClErrorCallback errCallback, void* userdata, void** prevUserdata = 0)
	{
		if( prevUserdata )
			*prevUserdata = customErrorCallbackData;
		ClErrorCallback prevCallback = customErrorCallback;
		customErrorCallback = errCallback;
		customErrorCallbackData = userdata;
		    
		return prevCallback;
	}


		    
};

#ifdef _DEBUG
#define CL_DbgAssert(expr) CL_Assert(expr)
#else
#define CL_DbgAssert(expr)
#endif

#ifdef __GNUC__
#define CL_Error( code, msg )  Error err( Exception(code, msg, __func__, __FILE__, __LINE__) )
#define CL_Error_( code, args )  Error err( Exception(code, format args, __func__, __FILE__, __LINE__) )
#define CL_Assert( expr ) { if(!(expr))  Error err( Exception(CL_StsAssert, #expr, __func__, __FILE__, __LINE__) ); }
#else
#define CL_Error( code, msg ) Error err( Exception(code, msg, "", __FILE__, __LINE__) )
#define CL_Error_( code, args ) Error err( Exception(code, format args, "", __FILE__, __LINE__) )
#define CL_Assert( expr ) { if(!(expr)) Error err( Exception(Error::CL_StsAssert, #expr, "", __FILE__, __LINE__) ); }

#define CL_Error2( code, msg ) CmnLib::Error err( CmnLib::Exception(code, msg, "", __FILE__, __LINE__) )
#define CL_Error2_( code, args ) CmnLib::Error err( CmnLib::Exception(code, format args, "", __FILE__, __LINE__) )
#define CL_Assert2( expr ) { if(!(expr)) CmnLib::Error err( CmnLib::Exception(CmnLib::Error::CL_StsAssert, #expr, "", __FILE__, __LINE__) ); }

#endif


// Use the error manager
#ifdef CL_ERROR_MANAGEMENT

#define CLERROR_SET(name) Error err(name, __FILE__)
#define CLERROR_CALL(Code, Msg) err.Call(Code, Msg, __LINE__)

#else

#define CLERROR_SET(name)
#define CLERROR_CALL(Code, Msg)

#endif

}	// namespace core
}	// namespace CmnLib

#endif /* CMNLIB_CMNLIBCORE_ERROR_HPP__ */
