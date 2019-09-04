/**
* @file assert.hpp
* @brief Header of assert files
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

#ifndef CMNMATH_CMNMATHCORE_ASSERT_HPP__
#define CMNMATH_CMNMATHCORE_ASSERT_HPP__

#include "types.hpp"

namespace CmnMath
{

#ifdef WIN32 // running on windows platform

#ifdef _DEBUG // if in debug mode use my assert message box 

	// comment this line out if you don't want the assert text to automatically be
	// copied to to the clipboard if the user presses Abort on the message box
	//#define ASSERT_COPY_TO_CLIPBOARD
#pragma message("Asserts enabled")

#ifdef __cplusplus 
	extern "C"
#endif 
		CMN_8S VCAssert(CMN_8S expression, const CMN_8S *exptext, const CMN_8S *description, const CMN_8S *fileline, CMN_32S line, CMN_8S *ignorealways);

#define Assert(exp, description) \
				{  static CMN_8S ignoreAlways = 0; \
				if (!ignoreAlways) \
					if (VCAssert(exp, "Expression " #exp " failed\n", description, \
								"Source file " __FILE__ " compiled on " __TIMESTAMP__ "\nLine ", __LINE__, &ignoreAlways))  \
						{ _asm { CMN_32S 3 } } \
				}

#else // not in debug mode, don't compile asserts, {} done so that "else Assert(exp, desc);" works
#pragma message("Asserts disabled")
#define Assert(exp, description) {}
#endif

#else // not running on windows
#define Assert(exp, description)  assert((exp) && (description));

#endif

// useful utility for when you are dealing with STL file IO stuff
// this will print out filename: description in an assert
// filename is a std::string
#ifdef __cplusplus
#define AssertFileName(exp, filename, description) Assert(exp, (filename + ": " + description).c_str())
#endif


// override the normal assert (this only works if Assert.h is included before everything else)
#ifndef assert
#define assert(exp)  Assert(exp, "Unhandled exception")
#endif

} // namespace CmnMath

#endif /* CMNMATH_CMNMATHCORE_ASSERT_HPP__ */
