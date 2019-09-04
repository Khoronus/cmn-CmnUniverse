/* @file sample_math_clockwise.hpp
* @brief Check if a set of points are clockwise direction.
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
* @author Moro Alessandro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>

#include "geometry/inc/geometry/geometry_headers.hpp"

namespace
{

/** @brief Function to test the classes and functions
*/
void test()
{
	std::vector<CmnMath::algebralinear::Vector2f> v(3);
	v[0] = CmnMath::algebralinear::Vector2f(150,150);
	v[1] = CmnMath::algebralinear::Vector2f(150,250);
	v[2] = CmnMath::algebralinear::Vector2f(200,200);
	
	CmnMath::algebralinear::Vector2f center;
	for (size_t i = 0; i < v.size(); ++i)
	{
		center += v[i];
	}
	if (v.size() > 0) center *= (1.0f / v.size());

	for (size_t i = 0; i < v.size(); ++i)
	{
		size_t  j = (i + 1) % v.size();
		bool b = CmnMath::geometry::Clockwise2D<CmnMath::algebralinear::Vector2f>::less(
			v[i], v[j], center);
		std::cout << v[i].x << " " << v[i].y << " is less than " << v[j].x 
			<< " " << v[j].y << "? " << b << std::endl;
	}

	
}


}	// namespace

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test inside" << std::endl;
	test();
	return 0;
}