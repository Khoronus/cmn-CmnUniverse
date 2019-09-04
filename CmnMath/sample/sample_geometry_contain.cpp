/* @file sample_math_interpolation.hpp
* @brief Perform a sample interpolation of 2D points.
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

#include "geometry/inc/geometry/geometry_headers.hpp"

namespace
{

/** @brief Function to test the interpolation performances.
*/
void test()
{
	bool b = CmnMath::geometry::Inside::triangle2d<CmnMath::algebralinear::Vector2f>(
		CmnMath::algebralinear::Vector2f(0.5, 0.5),
		CmnMath::algebralinear::Vector2f(0, 0), 
		CmnMath::algebralinear::Vector2f(1, 0), 
		CmnMath::algebralinear::Vector2f(1, 1));
	std::cout << "(0.5, 0.5) Is inside (0,0) (1,0) (1,1): " << b << std::endl;
	b = CmnMath::geometry::Inside::triangle2d<CmnMath::algebralinear::Vector2f>(
		CmnMath::algebralinear::Vector2f(-0.5, 0.5),
		CmnMath::algebralinear::Vector2f(0, 0), 
		CmnMath::algebralinear::Vector2f(1, 0), 
		CmnMath::algebralinear::Vector2f(1, 1));
	std::cout << "(-0.5, 0.5) Is inside (0,0) (1,0) (1,1): " << b << std::endl;
}


}	// namespace

/** main
*/
CmnMath::CMN_32S main(int argc, char *argv[])
{
	std::cout << "Test contain" << std::endl;
	test();
	return 0;
}