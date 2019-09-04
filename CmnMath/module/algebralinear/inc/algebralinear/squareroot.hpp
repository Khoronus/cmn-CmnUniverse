/**
* @file squareroot.hpp
* @brief Simple square root calculation
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
* @original author Will Perone (will.perone@gmail.com)
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_ALGEBRALINEAR_SQUAREROOT_HPP__
#define CMNMATH_ALGEBRALINEAR_SQUAREROOT_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace algebralinear
{


/** @brief It performs approximation calculation over some popular functions.
*/
class AppriximateCompute
{
public:

	/** @brief Square root

		Square root
		@remarks
		requires
			- value <= 2^32 - 1
		ensures
			- returns the square root of value.  if the square root is not an
				integer then it will be rounded up to the nearest integer.
	*/
	static inline unsigned long square_root(unsigned long value)
	{
		unsigned long x;

		// set the initial guess for what the root is depending on 
		// how big value is
		if (value < 3)
			return value;
		else if (value < 4096) // 12
			x = 45;
		else if (value < 65536) // 16
			x = 179;
		else if (value < 1048576) // 20
			x = 717;
		else if (value < 16777216) // 24
			x = 2867;
		else if (value < 268435456) // 28
			x = 11469;
		else   // 32
			x = 45875;

		// find the root
		x = (x + value/x)>>1;
		x = (x + value/x)>>1;
		x = (x + value/x)>>1;
		x = (x + value/x)>>1;

		if (x*x < value)
			return x+1;
		else
			return x;
	}


	/* fast math routines from Doom3 SDK
	*/
	static inline CMN_32F invSqrt(CMN_32F x)
	{
		CMN_32F xhalf = 0.5f * x;
		CMN_32S i = *(CMN_32S*)&x;          // get bits for floating value
		i = 0x5f3759df - (i >> 1);    // gives initial guess
		x = *(CMN_32F*)&i;            // convert bits back to CMN_32F
		x = x * (1.5f - xhalf*x*x); // Newton step
		return x;
	}

};

} // namespace algebralinear
} // namespace CmnMath

#endif