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
 * @author  Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 1.1.1.0
 * 
 */

#ifndef CMNLIB_SYSTEM_TIME_HPP__
#define CMNLIB_SYSTEM_TIME_HPP__

#include <ctime>

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <sys/types.h>
#include <sys/time.h>
#endif

namespace CmnLib
{
namespace system
{

/*! Class to manage the time functions
\brief Time functions are located here.
*/
class TimeManager
{
public:

#ifdef WIN32

	/** Get the system elapsed time since is turn on
	@return Return the current time in milliseconds.
	*/
	static double ElapsedMicroseconds();
#endif

	/** Get the system elapsed time since is turn on
	@return Return the current time in milliseconds.
	*/
	static double gettime();
};


}   // namespace system
}	// namespace CmnLib


#endif /* CMNLIB_SYSTEM_TIME_HPP__ */