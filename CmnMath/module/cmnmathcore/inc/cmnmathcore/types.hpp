/**
* @file types.hpp
* @brief Header of constants values
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

#ifndef CMNMATH_CMNMATHCORE_TYPES_HPP__
#define CMNMATH_CMNMATHCORE_TYPES_HPP__

//*****************************************************************************
// Common type declarations
//*****************************************************************************

//#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER >= 1600)
//
//#ifndef NULLPTR
//#define NULLPTR nullptr
//#endif
//
//#else
//
//#ifndef NULLPTR
//#define NULLPTR 0
//#endif
//
//#endif
//
//#ifndef CMN_8S
//#define CMN_8S char
//#endif
//#ifndef CMN_8U
//#define CMN_8U unsigned char
//#endif
//#ifndef CMN_16S
//#define CMN_16S short
//#endif
//#ifndef CMN_16U
//#define CMN_16U unsigned short
//#endif
//#ifndef CMN_32S
//#define CMN_32S int
//#endif
//#ifndef CMN_32U
//#define CMN_32U unsigned int
//#endif
//#ifndef CMN_32F
//#define CMN_32F float
//#endif
//#ifndef CMN_64F
//#define CMN_64F double
//#endif
//#ifndef CMN_64L
//#define CMN_64L long long
//#endif
//#ifndef CMN_128F
//#define CMN_128F long double
//#endif


#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER >= 1600)

#ifndef NULLPTR
#define NULLPTR nullptr
#endif

#else

#ifndef NULLPTR
#define NULLPTR 0
#endif

#endif

//#ifndef CMN_8S
//#define CMN_8S char
//#endif
//#ifndef CMN_8U
//#define CMN_8U unsigned char
//#endif
//#ifndef CMN_16S
//#define CMN_16S short
//#endif
//#ifndef CMN_16U
//#define CMN_16U unsigned short
//#endif
//#ifndef CMN_32S
//#define CMN_32S int
//#endif
//#ifndef CMN_32U
//#define CMN_32U unsigned int
//#endif
//#ifndef CMN_32F
//#define CMN_32F float
//#endif
//#ifndef CMN_64F
//#define CMN_64F double
//#endif
//#ifndef CMN_64L
//#define CMN_64L long long
//#endif
//#ifndef CMN_128F
//#define CMN_128F long double
//#endif

namespace CmnMath
{

typedef bool CMN_BOOL;
typedef char CMN_8S;
typedef unsigned char CMN_8U;
typedef short CMN_16S;
typedef unsigned short CMN_16U;
typedef int CMN_32S;
typedef unsigned int CMN_32U;
typedef float CMN_32F;
typedef double CMN_64F;
typedef long long CMN_64L;
typedef unsigned long long CMN_64U;
typedef long double CMN_128F;

} // namespace CmnMath

#endif /* CMNMATH_CMNMATHCORE_DEFINE_HPP__ */
