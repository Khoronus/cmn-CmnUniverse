/**
* @file intersection_twodim_ellipse.hpp
* @brief Header of all the files related to the statistics
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTWODIMELLIPSE_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTWODIMELLIPSE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with two dimension geometrical
           structures.

	Class to perform interpolations with two dimension geometrical
	structures.
*/
class IntersectionTwoDimEllipse
{
public:

	// Return only the positive intersection. Change the sign of x,y to get the
	// other intersection point
	// http://www.ambrsoft.com/TrigoCalc/Circles2/Ellipse/EllipseLine.htm
	static void line(CMN_64F a, CMN_64F b, CMN_64F x0, CMN_64F y0,
		CMN_64F &x, CMN_64F &y)
	{
		if (x0 == 0)
		{
			x = 0; y = b;
		}
		else if (y0 == 0) {
			x = a; y = 0;
		}
		else {
			//double m = -y0 / x0;
			//double num0 = a * b;
			//double num1 = a * b * m;
			//double den = std::sqrt( std::pow(a, 2.0) * std::pow(m, 2.0) + 
			//				  std::pow(b, 2.0) );
			//x = num0 / den;
			//y = num1 / den;
			CMN_64F num = a * b;
			CMN_64F den = std::sqrt(std::pow(a, 2.0) * std::pow(y0, 2.0) +
				std::pow(b, 2.0) * std::pow(x0, 2.0));
			x = num / den * x0;
			y = num / den * y0;
		}
	}

};




} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMELLIPSE_HPP__ */
