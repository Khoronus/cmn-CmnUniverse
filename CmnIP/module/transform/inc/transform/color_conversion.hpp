/* @file color_conversion.hpp
 * @brief Class to convert a color space in another.
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.2.0.0
 * 
 */

#ifndef CMNIP_TRANSFORM_COLOR_CONVERSION_HPP__
#define CMNIP_TRANSFORM_COLOR_CONVERSION_HPP__


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


namespace CmnIP
{
namespace transform
{


/** Color Conversion
	@remarks
		It the case are passed vectors, only the first three values are accepted
*/
class ColorConversion
{
public:
	// Description:
	// Convert color in RGB format (Red, Green, Blue) to HSV format
	// (Hue, Saturation, Value). The input color is not modified.
	static void RGBToHSV(const float rgb[3], float hsv[3])
	{ RGBToHSV(rgb[0], rgb[1], rgb[2], hsv, hsv+1, hsv+2); }
	//static void RGBToHSV(float r, float g, float b, float *h, float *s, float *v);
	//static double* RGBToHSV(const double rgb[3]);
	//static double* RGBToHSV(double r, double g, double b);
	static void RGBToHSV(const double rgb[3], double hsv[3])
	{ RGBToHSV(rgb[0], rgb[1], rgb[2], hsv, hsv+1, hsv+2); }
	//static void RGBToHSV(double r, double g, double b, double *h, double *s, double *v);

	// Description:
	// Convert color in HSV format (Hue, Saturation, Value) to RGB
	// format (Red, Green, Blue). The input color is not modified.
	static void HSVToRGB(const float hsv[3], float rgb[3])
	{ HSVToRGB(hsv[0], hsv[1], hsv[2], rgb, rgb+1, rgb+2); }
	//static void HSVToRGB(float h, float s, float v, float *r, float *g, float *b);
	//static double* HSVToRGB(const double hsv[3]);
	//static double* HSVToRGB(double h, double s, double v);
	static void HSVToRGB(const double hsv[3], double rgb[3])
	{ HSVToRGB(hsv[0], hsv[1], hsv[2], rgb, rgb+1, rgb+2); }
	//static void HSVToRGB(double h, double s, double v, double *r, double *g, double *b);

	// Description:
	// Convert color in RGB format (Red, Green, Blue) to HSI format
	// (Hue, Saturation, Intensity). The input color is not modified.
	static void RGBToHSI(const float rgb[3], float hsi[3])
	{ RGBToHSI(rgb[0], rgb[1], rgb[2], hsi, hsi+1, hsi+2); }
	//static void RGBToHSI(float r, float g, float b, float *h, float *s, float *i);
	//static double* RGBToHSI(const double rgb[3]);
	//static double* RGBToHSI(double r, double g, double b);
	static void RGBToHSI(const double rgb[3], double hsi[3])
	{ RGBToHSI(rgb[0], rgb[1], rgb[2], hsi, hsi+1, hsi+2); }
	//static void RGBToHSI(double r, double g, double b, double *h, double *s, double *i);

	// Description:
	// Convert color from the CIE-L*ab system to CIE XYZ.
	static void LabToXYZ(const double lab[3], double xyz[3]) {
	LabToXYZ(lab[0], lab[1], lab[2], xyz+0, xyz+1, xyz+2);
	}
	//static void LabToXYZ(double L, double a, double b,
	//					 double *x, double *y, double *z);
	//static double *LabToXYZ(const double lab[3]);

	// Description:
	// Convert Color from the CIE XYZ system to CIE-L*ab.
	static void XYZToLab(const double xyz[3], double lab[3]) {
	XYZToLab(xyz[0], xyz[1], xyz[2], lab+0, lab+1, lab+2);
	}
	//static void XYZToLab(double x, double y, double z,
	//			   double *L, double *a, double *b);
	//static double *XYZToLab(const double xyz[3]);

	// Description:
	// Convert color from the CIE XYZ system to RGB.
	static void XYZToRGB(const double xyz[3], double rgb[3]) {
	XYZToRGB(xyz[0], xyz[1], xyz[2], rgb+0, rgb+1, rgb+2);
	}
	//static void XYZToRGB(double x, double y, double z,
	//					 double *r, double *g, double *b);
	//static double *XYZToRGB(const double xyz[3]);

	// Description:
	// Convert color from the RGB system to CIE XYZ.
	static void RGBToXYZ(const double rgb[3], double xyz[3]) {
	RGBToXYZ(rgb[0], rgb[1], rgb[2], xyz+0, xyz+1, xyz+2);
	}
	//static void RGBToXYZ(double r, double g, double b,
	//			   double *x, double *y, double *z);
	//static double *RGBToXYZ(const double rgb[3]);

	// Description:
	// Convert color from the RGB system to CIE-L*ab.
	static void RGBToLab(const double rgb[3], double lab[3]) {
	RGBToLab(rgb[0], rgb[1], rgb[2], lab+0, lab+1, lab+2);
	}
	//static void RGBToLab(double red, double green, double blue,
	//					 double *L, double *a, double *b);
	//static double *RGBToLab(const double rgb[3]);

	// Description:
	// Convert color from the CIE-L*ab system to RGB.
	static void LabToRGB(const double lab[3], double rgb[3]) {
	LabToRGB(lab[0], lab[1], lab[2], rgb+0, rgb+1, rgb+2);
	}
	//static void LabToRGB(double L, double a, double b,
	//					 double *red, double *green, double *blue);
	//static double *LabToRGB(const double lab[3]);

	//----------------------------------------------------------------------------
	static void ColorConversion::RGBToHSV(float r, float g, float b,
							float *h, float *s, float *v)
	{
		double dh,ds,dv;
		ColorConversion::RGBToHSV(r,g,b,&dh,&ds,&dv);
		*h = static_cast<float>(dh);
		*s = static_cast<float>(ds);
		*v = static_cast<float>(dv);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::RGBToHSV(const double rgb[3])
	{
		return ColorConversion::RGBToHSV(rgb[0], rgb[1], rgb[2]);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::RGBToHSV(double r, double g, double b)
	{
		static double hsv[3];
		ColorConversion::RGBToHSV(r, g, b, hsv, hsv + 1, hsv + 2);
		return hsv;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::RGBToHSV(double r, double g, double b,
							double *h, double *s, double *v)
	{
		double onethird = 1.0 / 3.0;
		double onesixth = 1.0 / 6.0;
		double twothird = 2.0 / 3.0;

		double cmax, cmin;

		cmax = r;
		cmin = r;
		if (g > cmax)
		{
		cmax = g;
		}
		else if (g < cmin)
		{
		cmin = g;
		}
		if (b > cmax)
		{
		cmax = b;
		}
		else if (b < cmin)
		{
		cmin = b;
		}
		*v = cmax;

		if (*v > 0.0)
		{
		*s = (cmax - cmin) / cmax;
		}
		else
		{
		*s = 0.0;
		}
		if (*s > 0)
		{
		if (r == cmax)
			{
			*h = onesixth * (g - b) / (cmax - cmin);
			}
		else if (g == cmax)
			{
			*h = onethird + onesixth * (b - r) / (cmax - cmin);
			}
		else
			{
			*h = twothird + onesixth * (r - g) / (cmax - cmin);
			}
		if (*h < 0.0)
			{
			*h += 1.0;
			}
		}
		else
		{
		*h = 0.0;
		}
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::HSVToRGB(float h, float s, float v,
							float *r, float *g, float *b)
	{
		double dr,dg,db;
		ColorConversion::HSVToRGB(h,s,v,&dr,&dg,&db);
		*r = static_cast<float>(dr);
		*g = static_cast<float>(dg);
		*b = static_cast<float>(db);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::HSVToRGB(const double hsv[3])
	{
		return ColorConversion::HSVToRGB(hsv[0], hsv[1], hsv[2]);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::HSVToRGB(double h, double s, double v)
	{
		static double rgb[3];
		ColorConversion::HSVToRGB(h, s, v, rgb, rgb + 1, rgb + 2);
		return rgb;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::HSVToRGB(double h, double s, double v,
							double *r, double *g, double *b)
	{
		const double onethird = 1.0 / 3.0;
		const double onesixth = 1.0 / 6.0;
		const double twothird = 2.0 / 3.0;
		const double fivesixth = 5.0 / 6.0;

		// compute RGB from HSV
		if (h > onesixth && h <= onethird) // green/red
		{
		*g = 1.0;
		*r = (onethird - h) / onesixth;
		*b = 0.0;
		}
		else if (h > onethird && h <= 0.5) // green/blue
		{
		*g = 1.0;
		*b = (h - onethird) / onesixth;
		*r = 0.0;
		}
		else if (h > 0.5 && h <= twothird) // blue/green
		{
		*b = 1.0;
		*g = (twothird - h) / onesixth;
		*r = 0.0;
		}
		else if (h > twothird && h <= fivesixth) // blue/red
		{
		*b = 1.0;
		*r = (h - twothird) / onesixth;
		*g = 0.0;
		}
		else if (h > fivesixth && h <= 1.0) // red/blue
		{
		*r = 1.0;
		*b = (1.0 - h) / onesixth;
		*g = 0.0;
		}
		else // red/green
		{
		*r = 1.0;
		*g = h / onesixth;
		*b = 0.0;
		}

		// add Saturation to the equation.
		*r = (s * *r + (1.0 - s));
		*g = (s * *g + (1.0 - s));
		*b = (s * *b + (1.0 - s));

		*r *= v;
		*g *= v;
		*b *= v;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::RGBToHSI(float r, float g, float b,
							float *h, float *s, float *i)
	{
		double dh,ds,di;
		ColorConversion::RGBToHSI(r,g,b,&dh,&ds,&di);
		*h = static_cast<float>(dh);
		*s = static_cast<float>(ds);
		*i = static_cast<float>(di);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::RGBToHSI(const double rgb[3])
	{
		return ColorConversion::RGBToHSI(rgb[0], rgb[1], rgb[2]);
	}

	//----------------------------------------------------------------------------
	static double* ColorConversion::RGBToHSI(double r, double g, double b)
	{
		static double hsi[3];
		ColorConversion::RGBToHSI(r, g, b, hsi, hsi + 1, hsi + 2);
		return hsi;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::RGBToHSI(double r, double g, double b,
							double *h, double *s, double *i)
	{
		double onethird = 1.0 / 3.0;
		double onesixth = 1.0 / 6.0;
		double twothird = 2.0 / 3.0;
		double radixsixth = std::sqrt(6.0f);
		double oneradixsixth = 1.0f / radixsixth;

		double V1, V2;

		*i = onethird * r + onethird * g + onethird * b;
		V1 = -radixsixth * onesixth * r - radixsixth * onesixth * g + radixsixth * onethird * b; 
		V2 = oneradixsixth * r - 2  * oneradixsixth * g;
		*s = std::sqrt(V1 * V1 + V2 * V2);
		if (V1 != 0)
			*h = std::atan(V2 / V1);
		else
			*h = 1;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::LabToXYZ(double L, double a, double b,
							double *x, double *y, double *z)
	{
		//LAB to XYZ
		double var_Y = ( L + 16 ) / 116;
		double var_X = a / 500 + var_Y;
		double var_Z = var_Y - b / 200;

		if ( std::pow(var_Y,3) > 0.008856 ) var_Y = std::pow(var_Y,3);
		else var_Y = ( var_Y - 16.0 / 116.0 ) / 7.787;

		if ( std::pow(var_X,3) > 0.008856 ) var_X = std::pow(var_X,3);
		else var_X = ( var_X - 16.0 / 116.0 ) / 7.787;

		if ( std::pow(var_Z,3) > 0.008856 ) var_Z = std::pow(var_Z,3);
		else var_Z = ( var_Z - 16.0 / 116.0 ) / 7.787;
		const double ref_X = 0.9505;
		const double ref_Y = 1.000;
		const double ref_Z = 1.089;
		*x = ref_X * var_X;     //ref_X = 0.9505  Observer= 2 deg Illuminant= D65
		*y = ref_Y * var_Y;     //ref_Y = 1.000
		*z = ref_Z * var_Z;     //ref_Z = 1.089
	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::LabToXYZ(const double lab[3])
	{
		static double xyz[3];
		ColorConversion::LabToXYZ(lab[0], lab[1], lab[2], xyz+0, xyz+1, xyz+2);
		return xyz;
	}

	//-----------------------------------------------------------------------------
	static void ColorConversion::XYZToLab(double x, double y, double z,
							double *L, double *a, double *b)
	{
		const double ref_X = 0.9505;
		const double ref_Y = 1.000;
		const double ref_Z = 1.089;
		double var_X = x / ref_X;  //ref_X = 0.9505  Observer= 2 deg, Illuminant= D65
		double var_Y = y / ref_Y;  //ref_Y = 1.000
		double var_Z = z / ref_Z;  //ref_Z = 1.089

		if ( var_X > 0.008856 ) var_X = std::pow(var_X, 1.0/3.0);
		else                    var_X = ( 7.787 * var_X ) + ( 16.0 / 116.0 );
		if ( var_Y > 0.008856 ) var_Y = std::pow(var_Y, 1.0/3.0);
		else                    var_Y = ( 7.787 * var_Y ) + ( 16.0 / 116.0 );
		if ( var_Z > 0.008856 ) var_Z = std::pow(var_Z, 1.0/3.0);
		else                    var_Z = ( 7.787 * var_Z ) + ( 16.0 / 116.0 );

		*L = ( 116 * var_Y ) - 16;
		*a = 500 * ( var_X - var_Y );
		*b = 200 * ( var_Y - var_Z );
	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::XYZToLab(const double xyz[3])
	{
		static double lab[3];
		ColorConversion::XYZToLab(xyz[0], xyz[1], xyz[2], lab+0, lab+1, lab+2);
		return lab;
	}

	//----------------------------------------------------------------------------
	static void ColorConversion::XYZToRGB(double x, double y, double z,
							double *r, double *g, double *b)
	{
		//double ref_X = 0.9505;        //Observer = 2 deg Illuminant = D65
		//double ref_Y = 1.000;
		//double ref_Z = 1.089;

		*r = x *  3.2406 + y * -1.5372 + z * -0.4986;
		*g = x * -0.9689 + y *  1.8758 + z *  0.0415;
		*b = x *  0.0557 + y * -0.2040 + z *  1.0570;

		// The following performs a "gamma correction" specified by the sRGB color
		// space.  sRGB is defined by a canonical definition of a display monitor and
		// has been standardized by the International Electrotechnical Commission (IEC
		// 61966-2-1).  The nonlinearity of the correction is designed to make the
		// colors more perceptually uniform.  This color space has been adopted by
		// several applications including Adobe Photoshop and Microsoft Windows color
		// management.  OpenGL is agnostic on its RGB color space, but it is reasonable
		// to assume it is close to this one.
		if (*r > 0.0031308) *r = 1.055 * (std::pow(*r, ( 1 / 2.4 ))) - 0.055;
		else *r = 12.92 * (*r);
		if (*g > 0.0031308) *g = 1.055 * (std::pow(*g ,( 1 / 2.4 ))) - 0.055;
		else  *g = 12.92 * (*g);
		if (*b > 0.0031308) *b = 1.055 * (std::pow(*b, ( 1 / 2.4 ))) - 0.055;
		else *b = 12.92 * (*b);

		// Clip colors. ideally we would do something that is perceptually closest
		// (since we can see colors outside of the display gamut), but this seems to
		// work well enough.
		double maxVal = *r;
		if (maxVal < *g) maxVal = *g;
		if (maxVal < *b) maxVal = *b;
		if (maxVal > 1.0)
		{
		*r /= maxVal;
		*g /= maxVal;
		*b /= maxVal;
		}
		if (*r<0) *r=0;
		if (*g<0) *g=0;
		if (*b<0) *b=0;

	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::XYZToRGB(const double xyz[3])
	{
		static double rgb[3];
		ColorConversion::XYZToRGB(xyz[0], xyz[1], xyz[2], rgb+0, rgb+1, rgb+2);
		return rgb;
	}

	//-----------------------------------------------------------------------------
	static void ColorConversion::RGBToXYZ(double r, double g, double b,
							double *x, double *y, double *z)
	{
		// The following performs a "gamma correction" specified by the sRGB color
		// space.  sRGB is defined by a canonical definition of a display monitor and
		// has been standardized by the International Electrotechnical Commission (IEC
		// 61966-2-1).  The nonlinearity of the correction is designed to make the
		// colors more perceptually uniform.  This color space has been adopted by
		// several applications including Adobe Photoshop and Microsoft Windows color
		// management.  OpenGL is agnostic on its RGB color space, but it is reasonable
		// to assume it is close to this one.
		if ( r > 0.04045 ) r = std::pow(( r + 0.055 ) / 1.055, 2.4);
		else               r = r / 12.92;
		if ( g > 0.04045 ) g = std::pow(( g + 0.055 ) / 1.055, 2.4);
		else               g = g / 12.92;
		if ( b > 0.04045 ) b = std::pow(( b + 0.055 ) / 1.055, 2.4);
		else               b = b / 12.92;

		//Observer. = 2 deg, Illuminant = D65
		*x = r * 0.4124 + g * 0.3576 + b * 0.1805;
		*y = r * 0.2126 + g * 0.7152 + b * 0.0722;
		*z = r * 0.0193 + g * 0.1192 + b * 0.9505;
	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::RGBToXYZ(const double rgb[3])
	{
		static double xyz[3];
		ColorConversion::RGBToXYZ(rgb[0], rgb[1], rgb[2], xyz+0, xyz+1, xyz+2);
		return xyz;
	}

	//-----------------------------------------------------------------------------
	static void ColorConversion::RGBToLab(double red, double green, double blue,
							double *L, double *a, double *b)
	{
		double x, y, z;
		ColorConversion::RGBToXYZ(red, green, blue, &x, &y, &z);
		ColorConversion::XYZToLab(x, y, z, L, a, b);
	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::RGBToLab(const double rgb[3])
	{
		return ColorConversion::XYZToLab(ColorConversion::RGBToXYZ(rgb));
	}

	//-----------------------------------------------------------------------------
	static void ColorConversion::LabToRGB(double L, double a, double b,
							double *red, double *green, double *blue)
	{
		double x, y, z;
		ColorConversion::LabToXYZ(L, a, b, &x, &y, &z);
		ColorConversion::XYZToRGB(x, y, z, red, green, blue);
	}

	//-----------------------------------------------------------------------------
	static double *ColorConversion::LabToRGB(const double lab[3])
	{
		return ColorConversion::XYZToRGB(ColorConversion::LabToXYZ(lab));
	}

};

} // namespace transform
} // namespace CmnIP

#endif /* CMNIP_TRANSFORM_COLOR_CONVERSION_HPP__ */
