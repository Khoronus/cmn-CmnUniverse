/**
* @file conversion3d.hpp
* @brief Header to perform the conversion of a coordinate system in a 3d space.
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
* @author Alessandro Moro
* @bug No known bugs.
* @version 0.2.0.0
*
*/

#ifndef CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION3D_HPP__
#define CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION3D_HPP__


#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace coordinatesystem
{


/** @brief Class to change popular coordinate system.
*/
template <typename _Ty>
class CoordinateSystemConversion3D
{
public:

	/** r [0,inf) theta [0, pi] phi [0, 2pi)
	*/
	template <typename _Ty2>
	static void spherical2cartesian(_Ty r, _Ty theta, _Ty phi,
		_Ty2 &d) {
		d.x = r * std::sin(theta) * std::cos(phi);
		d.y = r * std::sin(theta) * std::sin(phi);
		d.z = r * std::cos(theta);
	}

	template <typename _Ty2>
	static void cartesian2spherical(_Ty2 &s, _Ty &r, _Ty &theta,
		_Ty &phi) {

		r = std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2) +
			std::pow(s.z, 2));
		theta = std::acos(s.z / r);
		if (s.x != 0) {
			phi = std::atan(s.y / s.x);
		}
		else if (s.y != 0) {
			phi = std::acos(s.x /
				std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2)));
		}
		else {
			phi = 0;
		}
	}

	/** r [0,inf) elevation [0, pi] azimuth [0, 2pi)
	*/
	template <typename _Ty2>
	static void spherical2cartesianV2(_Ty r, _Ty elevation, _Ty azimuth,
		_Ty2 &d) {
		d.x = r * std::sin(elevation) * std::cos(azimuth);
		d.y = r * std::sin(elevation) * std::sin(azimuth);
		d.z = r * std::cos(elevation);
	}


	/** @link: http://jp.mathworks.com/help/matlab/ref/cart2sph.html
	    @param[out] elevation [-PI/2, PI/2]
		@param[out] azimuth [-PI, PI]
	*/
	template <typename _Ty2>
	static void cartesian2sphericalV2(_Ty2 &s, _Ty &r, _Ty &elevation,
		_Ty &azimuth) {

		r = std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2) +
			std::pow(s.z, 2));
		elevation = std::atan2(s.z, std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2)));
		azimuth = std::atan2(s.y, s.x);
	}

	/** @link: http://jp.mathworks.com/help/matlab/ref/cart2sph.html
		@link (geodesic coord): https://gis.stackexchange.com/questions/58923/calculating-view-angle
		It converts cartesian coordinates in spherical cordinates.
		The cartesian coordinates are in the form
		X right (Xr) Y up (Yu) Z front (Zf)
		@param[out] elevation [-PI/2, PI/2]
		@param[out] azimuth [-PI, PI]
	*/
	template <typename _Ty2>
	static void cartesian2sphericalXrYuZf(_Ty2 &s, _Ty &r, _Ty &elevation,
		_Ty &azimuth) {

		r = std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2) +
			std::pow(s.z, 2));
		elevation = std::atan2(s.y, std::sqrt(std::pow(s.x, 2) + std::pow(s.z, 2)));
		azimuth = std::atan2(s.z, s.x);
	}

	/** @link: https://jp.mathworks.com/help/matlab/ref/sph2cart.html

		@note Compared to the matlabl specs, the Y and Z are inverted.
			  The output of cartesian2spericalXrYuZf has YZ axes inverted.
	*/
	template <typename _Ty2>
	static void sphericalXrYuZf2cartesian(_Ty r, _Ty elevation, _Ty azimuth,
		_Ty2 &d) {
		d.x = r * std::cos(elevation) * std::cos(azimuth);
		d.z = r * std::cos(elevation) * std::sin(azimuth);
		d.y = r * std::sin(elevation);
	}

	/** @link: http://jp.mathworks.com/help/matlab/ref/cart2sph.html
		@link (geodesic coord): https://gis.stackexchange.com/questions/58923/calculating-view-angle
		It converts cartesian coordinates in spherical cordinates.
		The cartesian coordinates are in the form
		X right (Xr) Y front (Yf) Z up (Zu)
		@param[out] elevation [-PI/2, PI/2]
		@param[out] azimuth [-PI, PI]
	*/
	template <typename _Ty2>
	static void cartesian2sphericalXrYfZu(_Ty2 &s, _Ty &r, _Ty &elevation,
		_Ty &azimuth) {

		r = std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2) +
			std::pow(s.z, 2));
		elevation = std::atan2(s.z, std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2)));
		azimuth = std::atan2(s.y, s.x);
	}

	/** @link: https://jp.mathworks.com/help/matlab/ref/sph2cart.html
	*/
	template <typename _Ty2>
	static void sphericalXrYfZu2cartesian(_Ty r, _Ty elevation, _Ty azimuth,
		_Ty2 &d) {
		d.x = r * std::cos(elevation) * std::cos(azimuth);
		d.y = r * std::cos(elevation) * std::sin(azimuth);
		d.z = r * std::sin(elevation);
	}

	static void cylindrical2cartesian(_Ty r, _Ty theta, _Ty h,
		_Ty &x, _Ty &y, _Ty &z) {
		x = r * std::cos(theta);
		y = r * std::sin(theta);
		z = h;
	}

	static void cylindrical2spherical(_Ty r, _Ty phi, _Ty h,
		_Ty &sr, _Ty &sphi, _Ty &stheta) {
		sr = std::sqrt(std::pow(r, 2) + std::pow(h, 2));
		sphi = phi;
		stheta = std::atan(r / h);
	}

	static void cartesian2cylindrical(_Ty x, _Ty y, _Ty z,
		_Ty &r, _Ty &ctheta, _Ty &h) {
		r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		ctheta = std::atan2(y, x);
		//if (x == 0 && y == 0) {
		//	ctheta = 0;
		//} else if (x >= 0) {
		//	ctheta = std::asin(y / r);
		//} else {
		//	ctheta = -std::asin(y / r) + CV_PI;
		//}
		h = z;
	}

	static void spherical2cylindrical(_Ty r, _Ty theta, _Ty phi,
		_Ty &cr, _Ty &ctheta, _Ty &ch) {
		cr = r * std::sin(phi);
		ctheta = theta;
		ch = r * std::cos(phi);
	}


	static void HammerAitoff(_Ty latitude, _Ty longitude,
		_Ty &x, _Ty &y, _Ty &z)
	{
		z = std::sqrt(1 + std::cos(latitude) * std::cos(longitude / 2));
		x = std::cos(latitude) * std::sin(longitude / 2) / z;
		y = std::sin(latitude) / z;
	}

	static void HammerAitoffInv(_Ty x, _Ty y, _Ty &latitude, _Ty &longitude) {
		_Ty z2 = 1 - std::pow(x, 2) / 2 - std::pow(y, 2) / 2;
		_Ty z = std::sqrt(z2);
		longitude = 2 * std::atan(std::sqrt(2.0f) * x * z / (2 * z2 - 1));
		latitude = std::asin(std::sqrt(2.0f) * y * z);
	}


	/** @brief x,y are [0,max], a & b in [-1,1] range
	*/
	static CMN_32S changeRange(_Ty x, _Ty y, _Ty maxx, _Ty maxy, _Ty &a, _Ty &b) {
		a = x / maxx; b = y / maxy;
		_Ty a0 = ((x / maxx) - 0.5) * 2;
		_Ty b0 = ((y / maxy) - 0.5) * 2;
		if (std::sqrt(std::pow(a0, 2) + std::pow(b0, 2)) > 1) return 0;
		a = a0; b = b0;
		//a = (a + 1) / 2; b = (b + 1) / 2;
		return 1;
		//std::cout << x << " " << y << " " << a << " " << b << " " << std::sqrt(std::pow(a, 2) + std::pow(b, 2)) << std::endl;
	}

	/** Calculate the Z distance from 2 points.
	s & d are in range [-1,1]

	*/
	static void transform2D3D(
		_Ty &sx, _Ty &sy, _Ty &dx, _Ty &dy, _Ty &dz)
	{
		dx = sx;
		dz = sy;
		_Ty den = 1 - (std::pow(sx, 2) + std::pow(sy, 2));
		dy = den > 0 ? std::sqrt(den) : 0;
	}

	template <typename _Ty2, typename _Ty3>
	static void transform2D3D(const _Ty2 &s, _Ty3 &d)
	{
		d.x = s.x;
		d.z = s.y;
		_Ty den = 1 - (std::pow(s.x, 2) + std::pow(s.y, 2));
		d.y = den > 0 ? std::sqrt(den) : 0;
	}

	template <typename _Ty2, typename _Ty3>
	static void MercatorMapping(_Ty2 &xy, CMN_32F R, CMN_32F w, CMN_32F h, 
		_Ty3 &xyz)
	{
		// current position shifted to the center
		CMN_32F x = xy.x - (w / 2.0f);
		CMN_32F  y = xy.y - (h / 2.0f);
		// ratio [-1, 1]
		CMN_32F  _x = x / (w / 2.0f), _y = y / (h / 2.0f);
		_x *= CmnMath::core::kPIf / 2;
		_y *= CmnMath::core::kPIf / 2;
		CMN_32F longitude = _x / R;
		CMN_32F latitude = 2 * std::atan(std::exp(_y / R)) - CmnMath::core::kPIf / 2;
		CMN_32F S = 1.0f;
		xyz.z = -S * std::cos(latitude) * std::cos(longitude);
		xyz.y = -S * std::cos(latitude) * std::sin(longitude);
		xyz.x = S * std::sin(latitude);
	}

	/** @brief Convert world 2 camera

	@link http://en.wikipedia.org/wiki/Stereographic_projection
	*/
	template <typename _Ty2, typename _Ty3>
	static void world2camera(const _Ty3 &s, const _Ty2 &c,
		float xmodifier, float ymodifier, _Ty2 &o)
	{
		// Lens coordinate 3D
		float pscale = std::sqrt(std::pow(s.x, 2) + std::pow(s.y, 2) +
			std::pow(s.z, 2));
		_Ty3 q(1.0f / pscale * s.x,
			1.0f / pscale * s.y, 1.0f / pscale * s.z);

		// Fish eye coordinate (stereographic projection)
		// http://en.wikipedia.org/wiki/Stereographic_projection
		o.x = algebralinear::Round::round((q.x / (xmodifier + q.y)) *
			c.x + c.x);
		o.y = algebralinear::Round::round((q.z / (ymodifier + q.y)) *
			c.y + c.y);
	}

};


} // namespace coordinatesystem
} // namespace CmnMath



#endif // CMNMATH_COORDINATESYSTEM_COORDINATESYSTEMCONVERSION3D_HPP__
