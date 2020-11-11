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


#include "system/inc/system/time.hpp"

namespace CmnLib
{
namespace system
{

//-----------------------------------------------------------------------------
#ifdef WIN32
double TimeManager::ElapsedMicroseconds()
{
	LARGE_INTEGER TicksPerSecond = { 0, 0 }; // Global ticks per second
	double TicksPerMicrosecond = 0;       // Global ticks/microsecond

	LARGE_INTEGER StopTime; // ticks of stop time
	double delta;           // dif as a normalized float

	QueryPerformanceCounter(&StopTime); // read current clock
	if (TicksPerSecond.LowPart == 0)
	{
		QueryPerformanceFrequency(&TicksPerSecond);
		TicksPerMicrosecond = (float)(TicksPerSecond.LowPart / 1E6);
	}
	delta = StopTime.QuadPart / TicksPerMicrosecond; // low part 

	return delta;
};
#endif
//-----------------------------------------------------------------------------
double TimeManager::gettime()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
	/*	return GetTickCount()*0.001;*/
	return ElapsedMicroseconds() / 1E6;
#elif __linux__
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (double)(tv.tv_sec + tv.tv_usec / 1000000.0);
#endif
}


} // namespace system
} // namespace CmnLib