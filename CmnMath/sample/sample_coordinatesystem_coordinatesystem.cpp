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


/** @brief It tests the conversion between spherical to uv coordinates
]] [-14.2258, -13.9415, 22.4334] [-0.474195, 0.747781, -0.464718] [0.123394, 0.231119] [0.474195, 0.464718, 0.747781]
]] [-18.8562, -5.11617, 22.7655] [-0.628541, 0.75885, -0.170539] [0.0421676, 0.225762] [0.628541, 0.170539, 0.75885]
	*/
void test_conversion_threedim_sphere()
{
	// 1 sample
	if (true) {
		CmnMath::algebralinear::Vector3f xyz_original(-14.2258, -13.9415, 22.4334);
		// normalize
		float magnitude = std::sqrt(std::pow(xyz_original.x, 2) + std::pow(xyz_original.y, 2) + std::pow(xyz_original.z, 2));
		CmnMath::algebralinear::Vector3f p_norm;
		if (magnitude > 0) {
			p_norm = CmnMath::algebralinear::Vector3f(
				xyz_original.x / magnitude,
				xyz_original.y / magnitude,
				xyz_original.z / magnitude);
		}
		CmnMath::algebralinear::Vector3f xyz_out;
		CmnMath::algebralinear::Vector2f uv;
		CmnMath::coordinatesystem::conversion_threedim_sphere<CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector2f>::sphere2uvf(p_norm, uv);
		CmnMath::coordinatesystem::conversion_threedim_sphere<CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector2f>::uv2sphere_ypolef(uv, 1.0f, xyz_out);
		std::cout << "]] " << xyz_original << " " << p_norm << " " << uv << " "
			<< xyz_out << std::endl;
	}

	// cube sample
	for (float z = -10; z <= 10; z += 10) {
		for (float y = -10; y <= 10; y += 10) {
			for (float x = -10; x <= 10; x += 10) {

				CmnMath::algebralinear::Vector3f xyz_original(x, y, z);
				// normalize
				float magnitude = std::sqrt(std::pow(xyz_original.x, 2) + std::pow(xyz_original.y, 2) + std::pow(xyz_original.z, 2));
				CmnMath::algebralinear::Vector3f p_norm;
				if (magnitude > 0) {
					p_norm = CmnMath::algebralinear::Vector3f(
						xyz_original.x / magnitude,
						xyz_original.y / magnitude,
						xyz_original.z / magnitude);
				}
				CmnMath::algebralinear::Vector3f xyz_out;
				CmnMath::algebralinear::Vector2f uv;
				CmnMath::coordinatesystem::conversion_threedim_sphere<CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector2f>::sphere2uvf(p_norm, uv);
				CmnMath::coordinatesystem::conversion_threedim_sphere<CmnMath::algebralinear::Vector3f, CmnMath::algebralinear::Vector2f>::uv2sphere_ypolef(uv, 1.0f, xyz_out);
				std::cout << "]] " << xyz_original << " " << p_norm << " " << uv << " "
					<< xyz_out << std::endl;

			}
		}
	}
}


} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample CoordinateSystem" << std::endl;

	test();
	test_conversion_threedim_sphere();
	return 0;
}


