/* @file ConsoleText.hpp
 * @brief Body of the functions for the console text.
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
 * @author  Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 1.1.1.0
 * 
 */


#include "system/inc/system/console_text.hpp"

namespace CmnLib
{
namespace system
{

//-----------------------------------------------------------------------------
void ConsoleText::write(const std::string &msg, int attribute)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  const int saved_colors = GetConsoleTextAttribute(hConsole);
  SetConsoleTextAttribute(hConsole, attribute);
#elif __linux__
  switch (attribute)
  {
    case CTC_BLACK:
      std::cout << BLACK;
      break;
    case CTC_BLUE_DARK:
      std::cout << BLUE;
      break;
    case CTC_GREEN_DARK:
      std::cout << GREEN;
      break;
    case CTC_CYAN_DARK:
      std::cout << CYAN;
      break;
    case CTC_RED_DARK:
      std::cout << RED;
      break;
    case CTC_PURPLE_DARK:
      std::cout << MAGENTA;
      break;
    case CTC_YELLOW_DARK:
      std::cout << YELLOW;
      break;
    case CTC_WHITE_DARK:
      std::cout << WHITE;
      break;
    case CTC_BLUE_LIGHT:
      std::cout << BOLDBLUE;
      break;
    case CTC_GREEN_LIGHT:
      std::cout << BOLDGREEN;
      break;
    case CTC_CYAN_LIGHT:
      std::cout << BOLDCYAN;
      break;
    case CTC_RED_LIGHT:
      std::cout << BOLDRED;
      break;
    case CTC_PURPLE_LIGHT:
      std::cout << BOLDMAGENTA;
      break;
    case CTC_YELLOW_LIGHT:
      std::cout << BOLDYELLOW;
      break;
    case CTC_WHITE_LIGHT:
      std::cout << BOLDWHITE;
      break;
    default:
      std::cout << RESET;
  }
#endif

  std::cout << msg;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
  SetConsoleTextAttribute(hConsole, saved_colors);
#elif __linux__
  std::cout << RESET;
#endif

}
//-----------------------------------------------------------------------------
void ConsoleText::write_line(const std::string &msg, int attribute)
{
  write(msg, attribute);
  std::cout << std::endl;
}
//-----------------------------------------------------------------------------
#ifdef WIN32
WORD ConsoleText::GetConsoleTextAttribute (HANDLE hCon)
{
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}
#endif

} // namespace system
} // namespace CmnLib