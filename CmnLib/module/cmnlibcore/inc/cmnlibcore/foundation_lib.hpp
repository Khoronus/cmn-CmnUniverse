/**
* @file Foundation_lib.hpp
* @brief Header of foundation classes.
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

#ifndef CMNLIB_CMNLIBCORE_FOUNDATIONLIB_HPP__
#define CMNLIB_CMNLIBCORE_FOUNDATIONLIB_HPP__

// For the DLL library.
#ifdef CL_EXPORT
#define CL_FOUNDATION_ITEM __declspec(dllexport)

// For a client of the DLL library.
#else
#ifdef CL_IMPORT
#define CL_FOUNDATION_ITEM __declspec(dllimport)

// For the static library.
#else
#define CL_FOUNDATION_ITEM

#endif
#endif


//****************************************************************************************
//                            Common macros and inline functions                         
//****************************************************************************************

#if defined WIN32 || defined _WIN32
    #define CL_CDECL __cdecl
    #define CL_STDCALL __stdcall
#else
    #define CL_CDECL
    #define CL_STDCALL
#endif

#ifndef CL_EXTERN_C
    #ifdef __cplusplus
        #define CL_EXTERN_C extern "C"
        #define CL_DEFAULT(val) = val
    #else
        #define CL_EXTERN_C
        #define CL_DEFAULT(val)
    #endif
#endif

#ifndef CL_EXTERN_C_FUNCPTR
    #ifdef __cplusplus
        #define CL_EXTERN_C_FUNCPTR(x) extern "C" { typedef x; }
    #else
        #define CL_EXTERN_C_FUNCPTR(x) typedef x
    #endif
#endif

#ifndef CL_INLINE
#if defined __cplusplus
    #define CL_INLINE inline
#elif (defined WIN32 || defined _WIN32 || defined WINCE) && !defined __GNUC__
    #define CL_INLINE __inline
#else
    #define CL_INLINE static
#endif
#endif /* CL_INLINE */

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined CLAPI_EXPORTS
    #define CL_EXPORTS __declspec(dllexport)
#else
    #define CL_EXPORTS
#endif

#ifndef CLAPI
    #define CLAPI(rettype) CL_EXTERN_C CL_EXPORTS rettype CL_CDECL
#endif

#if defined _MSC_VER || defined __BORLANDC__
typedef __int64 int64;
typedef unsigned __int64 uint64;
#define CL_BIG_INT(n)   n##I64
#define CL_BIG_UINT(n)  n##UI64
#else
typedef int64_t int64;
typedef uint64_t uint64;
#define CL_BIG_INT(n)   n##LL
#define CL_BIG_UINT(n)  n##ULL
#endif


//****************************************************************************************
//                            Common types
//****************************************************************************************

typedef unsigned char uchar;

#endif // CMNLIB_CMNLIBCORE_FOUNDATIONLIB_HPP__
