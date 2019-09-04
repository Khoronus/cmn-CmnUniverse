/* @file spherefit.hpp
* @brief Class to perform a sphere fitting.
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
* @author From Codeproject (please find the reference)
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_NUMERICALANALYSIS_SPHEREFIT_HPP__
#define CMNMATH_NUMERICALANALYSIS_SPHEREFIT_HPP__

#include <vector>
#include <algorithm>    // std::for_each

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace numericalanalysis
{

/** @brief Auxiliary structure to fit a sphere given a set of points
*/
typedef struct PointsSparse_
{
	CMN_64F npoints;	//sum( number of points )
	CMN_64F Xsum;		//sum( X[n] )
	CMN_64F Xsumsq;		//sum( X[n]^2 )
	CMN_64F Xsumcube;	//sum( X[n]^3 )
	CMN_64F Ysum;		//sum( Y[n] )
	CMN_64F Ysumsq;		//sum( Y[n]^2 )
	CMN_64F Ysumcube;	//sum( Y[n]^3 )
	CMN_64F Zsum;		//sum( Z[n] )
	CMN_64F Zsumsq;		//sum( Z[n]^2 )
	CMN_64F Zsumcube;	//sum( Z[n]^3 )

	CMN_64F XYsum;      //sum( X[n] * Y[n] )
	CMN_64F XZsum;      //sum( X[n] * Z[n] )
	CMN_64F YZsum;      //sum( Y[n] * Z[n] )
	CMN_64F X2Ysum;     //sum( X[n]^2 * Y[n] )
	CMN_64F X2Zsum;     //sum( X[n]^2 * Z[n] )
	CMN_64F Y2Xsum;     //sum( Y[n]^2 * X[n] )
	CMN_64F Y2Zsum;     //sum( Y[n]^2 * Z[n] )
	CMN_64F Z2Xsum;     //sum( Z[n]^2 * X[n] )
	CMN_64F Z2Ysum;     //sum( Z[n]^2 * Y[n] )
} PointsSparse;

/** @brief Functions to fit a sphere given a set of points.
*/
template <typename _Ty>
//class FitThreeDimSphere
class SphereFit
{
public:

	/** @brief It fits a set of sparse points on a sphere.
	*/
	static void points2sphere(std::vector<_Ty> &points,
		_Ty &center, CMN_32F &radius) {

		PointsSparse P;
		sparse2struct(points, P);
		std::vector<CMN_32F> out;
		fit(P, out);
		center.x = out[0]; center.y = out[1]; center.z = out[2];
		radius = out[3];
	}

	/** @brief Least Squares Fit a sphere A,B,C with radius squared Rsq to 3D
	data.
	Least Squares Fit a sphere A,B,C with radius squared Rsq to 3D data

	P is a structure that has been computed with the data earlier.
	P.npoints is the number of elements; the length of X,Y,Z are identical.
	P's members are logically named.

	X[n] is the x component of point n
	Y[n] is the y component of point n
	Z[n] is the z component of point n

	A is the x coordiante of the sphere
	B is the y coordiante of the sphere
	C is the z coordiante of the sphere
	Rsq is the radius squared of the sphere.

	This method should converge; maybe 5-100 iterations or more.

	@link http://imaginaryz.blogspot.jp/2011/04/least-squares-fit-sphere-to-3d-data.html
	*/
	static void fit(PointsSparse &P, std::vector<CMN_32F> &out)
	{
		CMN_64F Xn = P.Xsum / P.npoints;        //sum( X[n] )
		CMN_64F Xn2 = P.Xsumsq / P.npoints;    //sum( X[n]^2 )
		CMN_64F Xn3 = P.Xsumcube / P.npoints;    //sum( X[n]^3 )
		CMN_64F Yn = P.Ysum / P.npoints;        //sum( Y[n] )
		CMN_64F Yn2 = P.Ysumsq / P.npoints;    //sum( Y[n]^2 )
		CMN_64F Yn3 = P.Ysumcube / P.npoints;    //sum( Y[n]^3 )
		CMN_64F Zn = P.Zsum / P.npoints;        //sum( Z[n] )
		CMN_64F Zn2 = P.Zsumsq / P.npoints;    //sum( Z[n]^2 )
		CMN_64F Zn3 = P.Zsumcube / P.npoints;    //sum( Z[n]^3 )

		CMN_64F XY = P.XYsum / P.npoints;        //sum( X[n] * Y[n] )
		CMN_64F XZ = P.XZsum / P.npoints;        //sum( X[n] * Z[n] )
		CMN_64F YZ = P.YZsum / P.npoints;        //sum( Y[n] * Z[n] )
		CMN_64F X2Y = P.X2Ysum / P.npoints;    //sum( X[n]^2 * Y[n] )
		CMN_64F X2Z = P.X2Zsum / P.npoints;    //sum( X[n]^2 * Z[n] )
		CMN_64F Y2X = P.Y2Xsum / P.npoints;    //sum( Y[n]^2 * X[n] )
		CMN_64F Y2Z = P.Y2Zsum / P.npoints;    //sum( Y[n]^2 * Z[n] )
		CMN_64F Z2X = P.Z2Xsum / P.npoints;    //sum( Z[n]^2 * X[n] )
		CMN_64F Z2Y = P.Z2Ysum / P.npoints;    //sum( Z[n]^2 * Y[n] )

		//Reduction of multiplications
		CMN_64F F0 = Xn2 + Yn2 + Zn2;
		CMN_64F F1 = 0.5*F0;
		CMN_64F F2 = -8.0*(Xn3 + Y2X + Z2X);
		CMN_64F F3 = -8.0*(X2Y + Yn3 + Z2Y);
		CMN_64F F4 = -8.0*(X2Z + Y2Z + Zn3);

		//Set initial conditions:
		CMN_64F A = Xn;
		CMN_64F B = Yn;
		CMN_64F C = Zn;

		//First iteration computation:
		CMN_64F A2 = A*A;
		CMN_64F B2 = B*B;
		CMN_64F C2 = C*C;
		CMN_64F QS = A2 + B2 + C2;
		CMN_64F QB = -2 * (A*Xn + B*Yn + C*Zn);

		//Set initial conditions:
		CMN_64F Rsq = F0 + QB + QS;

		//First iteration computation:
		CMN_64F Q0 = 0.5*(QS - Rsq);
		CMN_64F Q1 = F1 + Q0;
		CMN_64F Q2 = 8 * (QS - Rsq + QB + F0);
		CMN_64F aA, aB, aC, nA, nB, nC, dA, dB, dC;

		//Iterate N times, ignore stop condition.
		int n = 0, N = 1000;
		CMN_64F Nstop = 0.000000001;
		while (n != N){
			n++;

			//Compute denominator:
			aA = Q2 + 16 * (A2 - 2 * A*Xn + Xn2);
			aB = Q2 + 16 * (B2 - 2 * B*Yn + Yn2);
			aC = Q2 + 16 * (C2 - 2 * C*Zn + Zn2);
			aA = (aA == 0) ? 1.0 : aA;
			aB = (aB == 0) ? 1.0 : aB;
			aC = (aC == 0) ? 1.0 : aC;

			//Compute next iteration
			nA = A - ((F2 + 16 * (B*XY + C*XZ + Xn*(-A2 - Q0) + A*(Xn2 + Q1 - C*Zn - B*Yn))) / aA);
			nB = B - ((F3 + 16 * (A*XY + C*YZ + Yn*(-B2 - Q0) + B*(Yn2 + Q1 - A*Xn - C*Zn))) / aB);
			nC = C - ((F4 + 16 * (A*XZ + B*YZ + Zn*(-C2 - Q0) + C*(Zn2 + Q1 - A*Xn - B*Yn))) / aC);

			//Check for stop condition
			dA = (nA - A);
			dB = (nB - B);
			dC = (nC - C);
			if ((dA*dA + dB*dB + dC*dC) <= Nstop){ break; }

			//Compute next iteration's values
			A = nA;
			B = nB;
			C = nC;
			A2 = A*A;
			B2 = B*B;
			C2 = C*C;
			QS = A2 + B2 + C2;
			QB = -2 * (A*Xn + B*Yn + C*Zn);
			Rsq = F0 + QB + QS;
			Q0 = 0.5*(QS - Rsq);
			Q1 = F1 + Q0;
			Q2 = 8 * (QS - Rsq + QB + F0);
		}
		out.push_back(A);
		out.push_back(B);
		out.push_back(C);
		out.push_back(Rsq);
	}

private:

	/** @brief Calculate the necessary information for the fitting given a set
	of points.

	Calculate the necessary information for the fitting given a set
	of points.
	*/
	static void sparse2struct(std::vector<_Ty> &points, PointsSparse &P)
	{
		PointsSparseZero(P);
		P.npoints = static_cast<CMN_64F>(points.size());
		//std::cout << P.npoints << std::endl;
		for (size_t i = 0; i < points.size(); ++i)
		{
			P.Xsum += points[i].x;
			P.Ysum += points[i].y;
			P.Zsum += points[i].z;
			P.Xsumsq += std::pow(points[i].x, 2);
			P.Ysumsq += std::pow(points[i].y, 2);
			P.Zsumsq += std::pow(points[i].z, 2);
			P.Xsumcube += std::pow(points[i].x, 3);
			P.Ysumcube += std::pow(points[i].y, 3);
			P.Zsumcube += std::pow(points[i].z, 3);
			P.XYsum += points[i].x * points[i].y;
			P.XZsum += points[i].x * points[i].z;
			P.YZsum += points[i].y * points[i].z;
			P.X2Ysum += std::pow(points[i].x, 2) * points[i].y;
			P.X2Zsum += std::pow(points[i].x, 2) * points[i].z;
			P.Y2Xsum += std::pow(points[i].y, 2) * points[i].x;
			P.Y2Zsum += std::pow(points[i].y, 2) * points[i].z;
			P.Z2Xsum += std::pow(points[i].z, 2) * points[i].x;
			P.Z2Ysum += std::pow(points[i].z, 2) * points[i].y;
		}
	}

	/** @brief It initializes a PointsSparse structure to zero
	*/
	static void PointsSparseZero(PointsSparse &P)
	{
		P.npoints = 0;
		P.Xsum = P.Xsumsq = P.Xsumcube = 0;
		P.Ysum = P.Ysumsq = P.Ysumcube = 0;
		P.Zsum = P.Zsumsq = P.Zsumcube = 0;

		P.XYsum = P.XZsum = P.YZsum = 0;
		P.X2Ysum = P.X2Zsum = P.Y2Xsum = P.Y2Zsum = P.Z2Xsum = P.Z2Ysum = 0;
	}
};


}	// namespace numericalanalysis
}	// namespace CmnMath


#endif /* CMNMATH_NUMERICALANALYSIS_SPHEREFIT_HPP__ */