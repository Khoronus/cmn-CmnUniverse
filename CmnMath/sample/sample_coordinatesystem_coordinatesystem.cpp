/**
* @file sample_coordinatesystem_coordinatesystem.cpp
* @brief Sample coordinate system file.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include "coordinatesystem/inc/coordinatesystem/coordinatesystem_headers.hpp"

namespace
{


#define cartesian2polarf_ CmnMath::coordinatesystem::CoordinateSystemConversion2D<CmnMath::CMN_32F>::cartesian2polar
#define polar2cartesianf_ CmnMath::coordinatesystem::CoordinateSystemConversion2D<CmnMath::CMN_32F>::polar2cartesian

void test()
{
	for (CmnMath::CMN_32F y = 0; y < 10; ++y)
	{
		for (CmnMath::CMN_32F x = 0; x < 10; ++x)
		{
			CmnMath::CMN_32F r = 0, theta = 0;
			cartesian2polarf_(x, y, r, theta);
			CmnMath::CMN_32F x_ = 0, y_ = 0;
			polar2cartesianf_(r, theta, x_, y_);
			std::cout << x << " " << y << " " << r << " " << theta << " " << 
				x_ << " " << y_ << std::endl;
		}
	}
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample CoordinateSystem" << std::endl;

	test();
}


