/* @file interpolation.hpp
 * @brief Set of classes to perform points interpolation (2D and 3D)
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

#ifndef CMNMATH_NUMERICALANALYSIS_INTERPOLATION_HPP__
#define CMNMATH_NUMERICALANALYSIS_INTERPOLATION_HPP__

#include <iostream>
#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace numericalanalysis
{

/** @brief Class to perform numeric interpolation.
*/
template <typename T>
class Interpolate
{
public:

	static T interpolate1D(T v1, T v2, T x) {
		return v1*(1.0 - x) + v2 * x;
	}

	static T interpolate2D(T v1, T v2, T v3, T v4, T x, T y) {
		T s = interpolate1D(v1, v2, x);
		T t = interpolate1D(v3, v4, x);
		return interpolate1D(s, t, y);
	}

	static T interpolate3D(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8,
		T x, T y, T z) {
		T a = interpolate1D(v1, v2, x);
		T b = interpolate1D(v3, v4, x);
		T c = interpolate1D(v5, v6, x);
		T d = interpolate1D(v7, v8, x);
		return interpolate2D(a, b, c, d, y, z);
	}

	static T CosineInterpolate(
		T y1, T y2, T mu)
	{
		CMN_64F mu2;

		mu2 = (1 - std::cos(mu * CmnMath::core::kPI)) / 2;
		return(y1*(1 - mu2) + y2*mu2);
	}

	static T CubicInterpolate(
		T y0, T y1,
		T y2, T y3,
		T mu)
	{
		T a0, a1, a2, a3, mu2;

		mu2 = mu*mu;
		a0 = y3 - y2 - y0 + y1;
		a1 = y0 - y1 - a0;
		a2 = y2 - y0;
		a3 = y1;

		return(a0*mu*mu2 + a1*mu2 + a2*mu + a3);
	}
	/*
	Tension: 1 is high, 0 normal, -1 is low
	Bias: 0 is even,
	positive is towards first segment,
	negative towards the other
	*/
	static T HermiteInterpolate(
		T y0, T y1,
		T y2, T y3,
		T mu,
		T tension,
		T bias)
	{
		T m0, m1, mu2, mu3;
		T a0, a1, a2, a3;

		mu2 = mu * mu;
		mu3 = mu2 * mu;
		m0 = (y1 - y0)*(1 + bias)*(1 - tension) / 2;
		m0 += (y2 - y1)*(1 - bias)*(1 - tension) / 2;
		m1 = (y2 - y1)*(1 + bias)*(1 - tension) / 2;
		m1 += (y3 - y2)*(1 - bias)*(1 - tension) / 2;
		a0 = 2 * mu3 - 3 * mu2 + 1;
		a1 = mu3 - 2 * mu2 + mu;
		a2 = mu3 - mu2;
		a3 = -2 * mu3 + 3 * mu2;

		return(a0*y1 + a1*m0 + a2*m1 + a3*y2);
	}


	//! linear interpolation of 2 points
	static T interp_lin(const T &a, const T &b, CMN_32F t)
	{
		return a*(1 - t) + b*t;
	}

	//! cosine interpolation of 2 points
	static T interp_cos(const T &a, const T &b, CMN_32F t)
	{
		t = (1 - std::cos(t * core::kPI)) / 2;
		return  a*(1 - t) + b*t;
	}

	//! returns the cubic interpolation of 4 points
	static T interp_cubic(const T &v0, const T &v1, const T &v2, const T &v3, CMN_32F t)
	{
		type P = (v3 - v2) - (v0 - v1);
		type Q = (v0 - v1) - P;
		return ((P*t + Q)*t + (v2 - v0))*t + v1; //using expanded out horner's rule
	}

};



class InterpolateLinear
{
public:

	template <typename T2>
	static T2 linear(T2 x0, T2 y0, T2 x1, T2 y1, T2 x) {
		return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
	}

	template <typename T>
	static void estimate(std::vector< T > &v_points,
		std::vector< T > &out)
	{
		out.clear();

		// Try to interpolate all the points
		size_t size = v_points.size();
		for (CMN_32S i = 0; i < size - 1; ++i)
		{
			CMN_32S idx2 = (i + 1) % size;
			CMN_32S iterations = std::sqrt(
				std::pow(v_points[idx2].x - v_points[i].x, 2) +
				std::pow(v_points[idx2].y + v_points[i].y, 2)) + 1;

			if (v_points[idx2].x != v_points[i].x) {
				CMN_32F x = v_points[i].x;
				CMN_32F diff_x = v_points[idx2].x - v_points[i].x;
				CMN_32F bin = diff_x / iterations;
				CMN_32S iter = 0;
				while (iter < iterations)
				{
					CMN_32F y = linear<CMN_32F>(v_points[i].x, v_points[i].y,
						v_points[idx2].x, v_points[idx2].y, x);
					++iter;
					out.push_back(T(x, y));
					x += bin;
				}
			}
			else if (v_points[idx2].y != v_points[i].y) {
				// reverse xy (also the points coordinate)
				CMN_32F y = v_points[i].y;
				CMN_32F diff_y = v_points[idx2].y - v_points[i].y;
				CMN_32F bin = diff_y / iterations;
				CMN_32S iter = 0;
				while (iter < iterations)
				{
					CMN_32F x = linear<CMN_32F>(v_points[i].y, v_points[i].x,
						v_points[idx2].y, v_points[idx2].x, y);
					++iter;
					out.push_back(T(x, y));
					y += bin;
				}
			}
		}
	}


	template <typename T>
	static T estimate(T v1, T v2, T mu) {
		return (v1 * (1. - mu) + v2 * mu);
	}
};


// Link:
// http://paulbourke.net/geometry/bezier/

template <typename T>
class BezierCurves
{
public:

	/** Estimate the point
	*/
	static void estimate(std::vector< T > &v_points,
		CMN_32S LOD, std::vector< T > &out)
	{
		out.clear();
		// for each section of curve, draw LOD number of divisions
		for (CMN_32S i = 0; i != LOD; ++i) {

			CMN_64F mu = static_cast<CMN_64F>(i) / LOD;
			out.push_back(Bezier(v_points, mu));
		}
	}

	/** Estimate the point
	*/
	static void estimatef(std::vector< T > &v_points,
		CMN_32S LOD, std::vector< T > &out)
	{
		out.clear();
		// for each section of curve, draw LOD number of divisions
		for (CMN_32S i = 0; i != LOD; ++i) {

			CMN_32F mu = static_cast<CMN_32F>(i) / LOD;
			out.push_back(Bezierf(v_points, mu));
		}
	}


	/*
	Three control point Bezier interpolation
	mu ranges from 0 to 1, start to end of the curve
	*/
	static T Bezier(T p1, T p2, T p3, CMN_64F mu)
	{
		CMN_64F mum1, mum12, mu2;
		T p;

		mu2 = mu * mu;
		mum1 = 1 - mu;
		mum12 = mum1 * mum1;
		p.x = p1.x * mum12 + 2 * p2.x * mum1 * mu + p3.x * mu2;
		p.y = p1.y * mum12 + 2 * p2.y * mum1 * mu + p3.y * mu2;
		p.z = p1.z * mum12 + 2 * p2.z * mum1 * mu + p3.z * mu2;

		return(p);
	}

	/*
	Three control point Bezier interpolation
	mu ranges from 0 to 1, start to end of the curve
	*/
	static T Bezierf(T p1, T p2, T p3, CMN_32F mu)
	{
		CMN_32F mum1, mum12, mu2;
		T p;

		mu2 = mu * mu;
		mum1 = 1 - mu;
		mum12 = mum1 * mum1;
		p.x = p1.x * mum12 + 2 * p2.x * mum1 * mu + p3.x * mu2;
		p.y = p1.y * mum12 + 2 * p2.y * mum1 * mu + p3.y * mu2;
		p.z = p1.z * mum12 + 2 * p2.z * mum1 * mu + p3.z * mu2;

		return(p);
	}


	/*
	Four control point Bezier interpolation
	mu ranges from 0 to 1, start to end of curve
	*/
	static T Bezier(T p1, T p2, T p3, T p4, CMN_64F mu)
	{
		CMN_64F mum1, mum13, mu3;
		T p;

		mum1 = 1 - mu;
		mum13 = mum1 * mum1 * mum1;
		mu3 = mu * mu * mu;

		p.x = mum13*p1.x + 3 * mu*mum1*mum1*p2.x + 3 * mu*mu*mum1*p3.x + mu3*p4.x;
		p.y = mum13*p1.y + 3 * mu*mum1*mum1*p2.y + 3 * mu*mu*mum1*p3.y + mu3*p4.y;
		p.z = mum13*p1.z + 3 * mu*mum1*mum1*p2.z + 3 * mu*mu*mum1*p3.z + mu3*p4.z;

		return(p);
	}

	/*
	General Bezier curve
	Number of control points is n+1
	0 <= mu < 1    IMPORTANT, the last point is not computed
	*/
	static T Bezier(std::vector< T > &p, CMN_64F mu)
	{
		CMN_32S kn, nn, nkn;
		CMN_64F blend, muk, munk;
		T b(0.0, 0.0, 0.0);

		size_t n = p.size() - 1;

		muk = 1;
		munk = std::pow(1 - mu, (CMN_64F)n);

		for (size_t k = 0; k <= n; k++) {
			nn = static_cast<CMN_32S>(n);
			kn = static_cast<CMN_32S>(k);
			nkn = static_cast<CMN_32S>(n - k);
			blend = muk * munk;
			muk *= mu;
			munk /= (1 - mu);
			while (nn >= 1) {
				blend *= nn;
				nn--;
				if (kn > 1) {
					blend /= (CMN_64F)kn;
					kn--;
				}
				if (nkn > 1) {
					blend /= (CMN_64F)nkn;
					nkn--;
				}
			}
			b.x += p[k].x * blend;
			b.y += p[k].y * blend;
			b.z += p[k].z * blend;
		}

		return(b);
	}

	/*
	General Bezier curve
	Number of control points is n+1
	0 <= mu < 1    IMPORTANT, the last point is not computed
	*/
	static T Bezierf(std::vector< T > &p, CMN_32F mu)
	{
		CMN_32S kn, nn, nkn;
		CMN_32F blend, muk, munk;
		T b(0.0, 0.0, 0.0);

		CMN_64L n = p.size() - 1;

		muk = 1;
		munk = std::powf(1 - mu, (CMN_32F)n);

		for (CMN_64L k = 0; k <= n; k++) {
			nn = n;
			kn = k;
			nkn = n - k;
			blend = muk * munk;
			muk *= mu;
			munk /= (1 - mu);
			while (nn >= 1) {
				blend *= nn;
				nn--;
				if (kn > 1) {
					blend /= (CMN_32F)kn;
					kn--;
				}
				if (nkn > 1) {
					blend /= (CMN_32F)nkn;
					nkn--;
				}
			}
			b.x += p[k].x * blend;
			b.y += p[k].y * blend;
			b.z += p[k].z * blend;
		}

		return(b);
	}

};



// Link:
// http://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html


template <typename T>
class Chaikin
{
public:

	//------------------------------------------------------------	IncreaseLod()
	// When we increase the LOD we will have to re-create the points
	// array inserting the new intermediate points into it.
	//
	//	Basically the subdivision works like this. each line,
	//
	//            A  *------------*  B
	//
	//	will be split into 2 new points, Q and R.
	//
	//                   Q    R
	//            A  *---|----|---*  B
	//
	//	Q and R are given by the equations :
	//
	// 		Q = 3/4*A + 1/4*B
	// 		R = 3/4*B + 1/4*A
	//
	static void IncreaseLod(std::vector< T > &v_points) {
		std::vector<T> NewPoints;

		// keep the first point
		NewPoints.push_back(v_points[0]);
		for (CMN_32U i = 0; i<(v_points.size() - 1); ++i) {

			// get 2 original points
			const T& p0 = v_points[i];
			const T& p1 = v_points[i + 1];
			T Q;
			T R;

			// average the 2 original points to create 2 new points. For each
			// CV, another 2 verts are created.
			Q.x = 0.75f*p0.x + 0.25f*p1.x;
			Q.y = 0.75f*p0.y + 0.25f*p1.y;
			Q.z = 0.75f*p0.z + 0.25f*p1.z;

			R.x = 0.25f*p0.x + 0.75f*p1.x;
			R.y = 0.25f*p0.y + 0.75f*p1.y;
			R.z = 0.25f*p0.z + 0.75f*p1.z;

			NewPoints.push_back(Q);
			NewPoints.push_back(R);
		}
		// keep the last point
		NewPoints.push_back(v_points[v_points.size() - 1]);

		// update the points array
		v_points = NewPoints;
	}
	//------------------------------------------------------------	DecreaseLod()
	// When we decrease the LOD, we can rather niftily get back
	// to exactly what we had before. Since the original subdivision
	// simply required a basic ratio of both points, we can simply
	// reverse the ratio's to get the previous point...
	//
	static void DecreaseLod(std::vector< T > &v_points) {

		// make sure we dont loose any points!!
		if (v_points.size() <= 4)
			return;

		std::vector<T> NewPoints;

		// keep the first point
		NewPoints.push_back(v_points[0]);

		// step over every 2 points
		for (CMN_32U i = 1; i<(v_points.size() - 1); i += 2) {

			// get last point found in reduced array
			const T& pLast = NewPoints[NewPoints.size() - 1];

			// get 2 original point
			const T& p0 = v_points[i];
			T Q;

			// calculate the original point
			Q.x = p0.x - 0.75f*pLast.x;
			Q.y = p0.y - 0.75f*pLast.y;
			Q.z = p0.z - 0.75f*pLast.z;

			Q.x *= 4.0f;
			Q.y *= 4.0f;
			Q.z *= 4.0f;

			// add to new curve
			NewPoints.push_back(Q);
		}

		// copy over points
		v_points = NewPoints;
	}
};


template <typename T>
class clamped_bSpline
{
public:

	static void estimate(std::vector< T > &v_points,
		CMN_32S LOD,
		std::vector< T > &out)
	{
		out.clear();
		// in total i am going to draw (NUM_POINTS+1) curves. I will start
		// the curves at the imaginary index -3. Each section of the curve
		// will start on the next vertex index.
		// 
		size_t num_segments = v_points.size() + 1;
		for (size_t start_cv = -3, j = 0; j != num_segments; ++j, ++start_cv)
		{
			// for each section of curve, draw LOD number of divisions
			for (CMN_32S i = 0; i != LOD; ++i) {

				// use the parametric time value 0 to 1 for this curve
				// segment.
				CMN_32F t = (CMN_32F)i / LOD;

				// the t value inverted
				CMN_32F it = 1.0f - t;

				// calculate blending functions for cubic bspline
				CMN_32F b[4];
				b[0] = it*it*it / 6.0f;
				b[1] = (3 * t*t*t - 6 * t*t + 4) / 6.0f;
				b[2] = (-3 * t*t*t + 3 * t*t + 3 * t + 1) / 6.0f;
				b[3] = t*t*t / 6.0f;

				// calculate the x,y and z of the curve point
				CMN_32F x = 0, y = 0, z = 0;
				for (size_t c = 0, id = start_cv; c < 4; ++c, ++id)
				{
					if (id < 0) {
						x += b[c] * v_points[0].x;
						y += b[c] * v_points[0].y;
						z += b[c] * v_points[0].z;
					}
					else if (id >= v_points.size()) {
						x += b[c] * v_points[v_points.size() - 1].x;
						y += b[c] * v_points[v_points.size() - 1].y;
						z += b[c] * v_points[v_points.size() - 1].z;
					}
					else {
						x += b[c] * v_points[id].x;
						y += b[c] * v_points[id].y;
						z += b[c] * v_points[id].z;
					}
				}
				out.push_back(T(x, y, z));
			}
		}
	}
};



/** @brief Class to estimate the nurbs curve

	Class to estimate the nurbs curve.
	@note It requires that the template item implements the structure x,y,z.
*/
template <typename T>
class nurbsCurve
{
public:

	static CMN_32S estimate(std::vector< T > &v_points,
		CMN_32S LOD,
		std::vector< T > &out)
	{
		out.clear();

		size_t g_num_cvs = v_points.size();
		CMN_32U g_degree = g_num_cvs / 2;
		CMN_32U g_order = g_degree + 1;
		CMN_32U g_num_knots = g_num_cvs + g_order;
		std::vector< CMN_32F > g_Knots;
		for (CMN_32U i = 0; i < g_num_knots; i++)
		{
			g_Knots.push_back(0);
		}
		for (CMN_32U i = g_num_knots - 1; i >= g_num_knots - 1 - g_order; 
			i--)
		{
			g_Knots[i] = static_cast<CMN_32F>(g_order);
		}
		for (CMN_32U i = g_num_knots - g_order, j = 0; 
			i >= g_num_knots - 1 - g_order - g_degree; i--, j--)
		{
			if (i < 0 || g_order + j < 0) return 0;
			g_Knots[i] = static_cast<CMN_32F>(g_order + j);
		}
		for (CMN_32S i = 0; i != LOD; ++i) {

			CMN_32F t = g_Knots[g_num_knots - 1] * i / (CMN_32F)(LOD - 1);

			if (i == LOD - 1)
				t -= 0.001f;

			CMN_32F Outpoint[3] = { 0, 0, 0 };

			GetOutpoint(v_points, g_Knots, g_order,
				t, Outpoint);

			out.push_back( T(Outpoint[0], Outpoint[1], Outpoint[2]));
		}
		return 1;
	}

private:

	//------------------------------------------------------------	CoxDeBoor()
	//
	static CMN_32F CoxDeBoor(CMN_32F u, CMN_32S i, CMN_32S k, std::vector< CMN_32F > &Knots) {
		if (k == 1)
		{
			if (Knots[i] <= u && u <= Knots[i + 1]) {
				return 1.0f;
			}
			return 0.0f;
		}
		CMN_32F Den1 = Knots[i + k - 1] - Knots[i];
		CMN_32F Den2 = Knots[i + k] - Knots[i + 1];
		CMN_32F Eq1 = 0, Eq2 = 0;
		if (Den1>0) {
			Eq1 = ((u - Knots[i]) / Den1) * CoxDeBoor(u, i, k - 1, Knots);
		}
		if (Den2>0) {
			Eq2 = (Knots[i + k] - u) / Den2 * CoxDeBoor(u, i + 1, k - 1, Knots);
		}
		return Eq1 + Eq2;
	}

	//------------------------------------------------------------	GetOutpoint()
	//
	static void GetOutpoint(std::vector< T > v_points,
		std::vector< CMN_32F > &g_Knots,
		CMN_32U g_order,
		CMN_32F t, CMN_32F OutPoint[]) {

		size_t g_num_cvs = v_points.size();
		// sum the effect of all CV's on the curve at this point to 
		// get the evaluated curve point
		// 
		for (size_t i = 0; i != g_num_cvs; ++i) {

			// calculate the effect of this point on the curve
			CMN_32F Val = CoxDeBoor(t, i, g_order, g_Knots);

			if (Val>0.001f) {

				// sum effect of CV on this part of the curve
				OutPoint[0] += Val * v_points[i].x;
				OutPoint[1] += Val * v_points[i].y;
				OutPoint[2] += Val * v_points[i].z;
			}
		}
	}
};

}	// namespace numericalanalysis
}	// namespace CmnMath


#endif