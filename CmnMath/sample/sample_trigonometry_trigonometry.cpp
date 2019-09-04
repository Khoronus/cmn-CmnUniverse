/* @file sample_math_trigonometry.hpp
* @brief Perform a sample trigonometric operations.
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
* @author Various
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "trigonometry/inc/trigonometry/trigonometry_headers.hpp"

namespace
{

/** @brief Function to test the classes and functions
*/
void test()
{
	CmnMath::CMN_64F l = CmnMath::trigonometry::Circumference<CmnMath::CMN_64F>::length_from_angle(
		0.4, 1.0);
	CmnMath::CMN_64F a = CmnMath::trigonometry::Circumference<CmnMath::CMN_64F>::angle_from_length(
		l, 1.0);
	CmnMath::CMN_64F x = 0, y = 0;
	CmnMath::trigonometry::Circumference<CmnMath::CMN_64F>::coordinate(a, 1.0, x, y);
	std::cout << "l: " << l << " a: " << a << " x: " << x << " y: " << y << std::endl;
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test trigonometry" << std::endl;
	test();
	return 0;
}