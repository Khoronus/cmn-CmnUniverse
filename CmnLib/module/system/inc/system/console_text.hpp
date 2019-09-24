/* @file ConsoleText.hpp
 * @brief Class to manage the writing of the text in console.
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
 * @author  Unknwon
 * @modify Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 1.1.1.0
 * 
 */

#ifndef CMNLIB_SYSTEM_CONSOLETEXT_HPP__
#define CMNLIB_SYSTEM_CONSOLETEXT_HPP__

#include <iostream>
#include <sstream>
#include <string>

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <sys/types.h>
#include <sys/time.h>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif

namespace CmnLib
{
namespace system
{

/** @brief Class to write text in console.

    Class to write colored text in a console.
*/
class ConsoleText
{
 public:

	 /** @brief Set colors
	 */
	 //static enum ConsoleTextColor {
	 enum ConsoleTextColor {
		 CTC_BLACK = 0,
		 CTC_BLUE_DARK,
		 CTC_GREEN_DARK,
		 CTC_CYAN_DARK,
		 CTC_RED_DARK,
		 CTC_PURPLE_DARK,
		 CTC_YELLOW_DARK,
		 CTC_WHITE_DARK,
		 CTC_GRAY_DARK,
		 CTC_BLUE_LIGHT,
		 CTC_GREEN_LIGHT,
		 CTC_CYAN_LIGHT,
		 CTC_RED_LIGHT,
		 CTC_PURPLE_LIGHT,
		 CTC_YELLOW_LIGHT,
		 CTC_WHITE_LIGHT
	 };

	/** @brief Display colored text.

		Show in the console a colored text.
	*/
	static void write(const std::string &msg, int attribute);

	/** @brief Display colored text.

		Show in the console a colored text.
	*/
	static void write_line(const std::string &msg, int attribute);

 private:

	#ifdef WIN32

	/** Get the console text attribute
		@return the current attributes
	*/
	static WORD GetConsoleTextAttribute (HANDLE hCon);

	#endif

};

}	// namespace system
}	// namespace CmnLib

#endif /* CMNLIB_SYSTEM_CONSOLETEXT_HPP__ */