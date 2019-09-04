/**
* @file define.hpp
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

#ifndef CMNMATH_CMNMATHCORE_DEFINE_HPP__
#define CMNMATH_CMNMATHCORE_DEFINE_HPP__

#if defined(WIN32)
#if !defined(_MSC_VER) || _MSC_VER < 1800
#error Microsoft Visual Studio 2013 or later is required.
#endif

// Debug build values (choose_your_value is 0, 1, or 2)
// 0:  Disables checked iterators and disables iterator debugging.
// 1:  Enables checked iterators and disables iterator debugging.
// 2:  (default) Enables iterator debugging; checked iterators are not relevant.
//
// Release build values (choose_your_value is 0 or 1)
// 0:  (default) Disables checked iterators.
// 1:  Enables checked iterators; iterator debugging is not relevant.
//
// #define _ITERATOR_DEBUG_LEVEL choose_your_value

#endif

// TODO: Windows DLL configurations have not yet been added to the project,
// but these defines are required to support them (when we do add them).
//
// Add GTE_EXPORT to project preprocessor options for dynamic library
// configurations to export their symbols.
#if defined(GTE_EXPORT)
// For the dynamic library configurations.
#define GTE_IMPEXP __declspec(dllexport)
#else
// For a client of the dynamic library or for the static library
// configurations.
#define GTE_IMPEXP
#endif

// Expose exactly one of these.
#define GTE_USE_ROW_MAJOR
//#define GTE_USE_COL_MAJOR

// Expose exactly one of these.
#define GTE_USE_MAT_VEC
//#define GTE_USE_VEC_MAT

#if (defined(GTE_USE_ROW_MAJOR) && defined(GTE_USE_COL_MAJOR)) || (!defined(GTE_USE_ROW_MAJOR) && !defined(GTE_USE_COL_MAJOR))
#error Exactly one storage order must be specified.
#endif

#if (defined(GTE_USE_MAT_VEC) && defined(GTE_USE_VEC_MAT)) || (!defined(GTE_USE_MAT_VEC) && !defined(GTE_USE_VEC_MAT))
#error Exactly one multiplication convention must be specified.
#endif




// cast CMN_32F to it's bitwise representation
#define FLOAT_AS_INT(f)			(reinterpret_cast<const unsigned long &>(f))
#define INT_AS_FLOAT(i)			(reinterpret_cast<const CMN_32F &>(i))

#endif /* CMNMATH_CMNMATHCORE_DEFINE_HPP__ */
