/**
* @file quaternionNaive.hpp
* @brief Header related to quaternions.
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
* @version 0.2.0.0
*
*/



#ifndef CMNMATH_NUMERICSYSTEM_QUATERNIONNAIVE_HPP__
#define CMNMATH_NUMERICSYSTEM_QUATERNIONNAIVE_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/constants.hpp"

namespace CmnMath
{
namespace numericsystem
{

///////////////////////////////
// Quaternion struct
// Simple incomplete quaternion struct for demo purpose
///////////////////////////////
template <typename REAL = double>
struct QuaternionNaive {
	QuaternionNaive() :x(0), y(0), z(0), w(1) {};
	QuaternionNaive(REAL x, REAL y, REAL z, REAL w) :x(x), y(y), z(z), w(w) {};

	void normalize() {
		REAL norm = std::sqrt(x*x + y*y + z*z + w*w);
		x /= norm;
		y /= norm;
		z /= norm;
		w /= norm;
	}

	REAL norm() {
		return std::sqrt(x*x + y*y + z*z + w*w);
	}

	REAL x;
	REAL y;
	REAL z;
	REAL w;

	QuaternionNaive operator*(QuaternionNaive& q2) {
		QuaternionNaive q;
		q.w = w*q2.w - x*q2.x - y*q2.y - z*q2.z;
		q.x = w*q2.x + x*q2.w + y*q2.z - z*q2.y;
		q.y = w*q2.y - x*q2.z + y*q2.w + z*q2.x;
		q.z = w*q2.z + x*q2.y - y*q2.x + z*q2.w;
		return q;
	}

};

//QuaternionNaive operator*(QuaternionNaive& q1, QuaternionNaive& q2) {
//	QuaternionNaive q;
//	q.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
//	q.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
//	q.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
//	q.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
//	return q;
//}

template <typename REAL = double>
class QuaternionNaiveTransform
{
public:

	/**
	@link http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche52.html
	*/
	static void rotationmatrix2quaternion_inconsinstentresult(
		REAL r11, REAL r12, REAL r13,
		REAL r21, REAL r22, REAL r23,
		REAL r31, REAL r32, REAL r33,
		REAL&q0, REAL&q1, REAL&q2, REAL&q3) {

		q0 = (r11 + r22 + r33 + 1.0f) / 4.0f;
		q1 = (r11 - r22 - r33 + 1.0f) / 4.0f;
		q2 = (-r11 + r22 - r33 + 1.0f) / 4.0f;
		q3 = (-r11 - r22 + r33 + 1.0f) / 4.0f;
		if (q0 < 0.0f) q0 = 0.0f;
		if (q1 < 0.0f) q1 = 0.0f;
		if (q2 < 0.0f) q2 = 0.0f;
		if (q3 < 0.0f) q3 = 0.0f;
		q0 = sqrt(q0);
		q1 = sqrt(q1);
		q2 = sqrt(q2);
		q3 = sqrt(q3);
		if (q0 >= q1 && q0 >= q2 && q0 >= q3) {
			q0 *= +1.0f;
			q1 *= SIGN(r32 - r23);
			q2 *= SIGN(r13 - r31);
			q3 *= SIGN(r21 - r12);
		}
		else if (q1 >= q0 && q1 >= q2 && q1 >= q3) {
			q0 *= SIGN(r32 - r23);
			q1 *= +1.0f;
			q2 *= SIGN(r21 + r12);
			q3 *= SIGN(r13 + r31);
		}
		else if (q2 >= q0 && q2 >= q1 && q2 >= q3) {
			q0 *= SIGN(r13 - r31);
			q1 *= SIGN(r21 + r12);
			q2 *= +1.0f;
			q3 *= SIGN(r32 + r23);
		}
		else if (q3 >= q0 && q3 >= q1 && q3 >= q2) {
			q0 *= SIGN(r21 - r12);
			q1 *= SIGN(r31 + r13);
			q2 *= SIGN(r32 + r23);
			q3 *= +1.0f;
		}
		else {
			printf("coding error\n");
		}
		REAL r = NORM(q0, q1, q2, q3);
		q0 /= r;
		q1 /= r;
		q2 /= r;
		q3 /= r;
	}

	/** @brief It calculates a QuaternionNaive params from a rotation matrix
		@link http://answers.unity3d.com/questions/11363/converting-matrix4x4-to-QuaternionNaive-vector3.html
		// Adapted from: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternionNaive/index.htm
		@test http://www.energid.com/resources/orientation-calculator/
	*/
	static void rotationmatrix2quaternion(
		REAL r11, REAL r12, REAL r13,
		REAL r21, REAL r22, REAL r23,
		REAL r31, REAL r32, REAL r33,
		REAL&x, REAL&y, REAL&z, REAL&w) {

		w = std::sqrt((std::max)(static_cast<REAL>(0.), 
			static_cast<REAL>(1.) + r11 + r22 + r33)) / 2;
		x = std::sqrt((std::max)(static_cast<REAL>(0.), 
			static_cast<REAL>(1.) + r11 - r22 - r33)) / 2;
		y = std::sqrt((std::max)(static_cast<REAL>(0.), 
			static_cast<REAL>(1.) - r11 + r22 - r33)) / 2;
		z = std::sqrt((std::max)(static_cast<REAL>(0.), 
			static_cast<REAL>(1.) - r11 - r22 + r33)) / 2;
		x *= SIGN(x * (r32 - r23));
		y *= SIGN(y * (r13 - r31));
		z *= SIGN(z * (r21 - r12));
	}


	static void rotationmatrix2quaternion(
		REAL r11, REAL r12, REAL r13,
		REAL r21, REAL r22, REAL r23,
		REAL r31, REAL r32, REAL r33,
		QuaternionNaive<REAL> &q) {
		rotationmatrix2quaternion(
			r11, r12, r13,
			r21, r22, r23,
			r31, r32, r33,
			q.x, q.y, q.z, q.w);
	}

	///** @brief

	//@link http://www.euclideanspace.com/maths/geometry/rotations/conversions/QuaternionNaiveToAngle/
	//@test http://www.energid.com/resources/orientation-calculator/
	//*/
	//static void angle_axis(QuaternionNaive &qt, double &x, double&y, double&z, double &angle) {
	//	if (qt.w > 1) qt.normalize(); // if w>1 acos and sqrt will produce errors, this cant happen if QuaternionNaive is normalised
	//	angle = 2 * std::acos(qt.w);
	//	double s = std::sqrt(1 - qt.w * qt.w); // assuming QuaternionNaive normalised then w is less than 1, so term always positive.
	//	if (s < 0.001) { // test to avoid divide by zero, s is always positive due to sqrt
	//						// if s close to zero then direction of axis not important
	//		x = qt.x; // if it is important that axis is normalised then replace with x=1; y=z=0;
	//		y = qt.y;
	//		z = qt.z;
	//	}  else {
	//		x = qt.x / s; // normalise axis
	//		y = qt.y / s;
	//		z = qt.z / s;
	//	}
	//}
	/** @brief

	@link http://www.euclideanspace.com/maths/geometry/rotations/conversions/QuaternionNaiveToAngle/
	@test http://www.energid.com/resources/orientation-calculator/
	*/
	static void axis_angle(QuaternionNaive<REAL> &qt, REAL&x, REAL&y, REAL&z, REAL&angle) {
		if (qt.w > 1) qt.normalize(); // if w>1 acos and sqrt will produce errors, this cant happen if QuaternionNaive is normalised
		angle = 2 * std::acos(qt.w);
		REAL s = std::sqrt(1 - qt.w * qt.w); // assuming QuaternionNaive normalised then w is less than 1, so term always positive.
		if (s < 0.001) { // test to avoid divide by zero, s is always positive due to sqrt
						 // if s close to zero then direction of axis not important
			x = qt.x; // if it is important that axis is normalised then replace with x=1; y=z=0;
			y = qt.y;
			z = qt.z;
		}
		else {
			x = qt.x / s; // normalise axis
			y = qt.y / s;
			z = qt.z / s;
		}
	}

	///////////////////////////////
	// QuaternionNaive to Euler
	///////////////////////////////
	enum RotSeq { zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xyx, xzy, xzx };

	static void twoaxisrot(REAL r11, REAL r12, REAL r21, REAL r31, REAL r32, REAL res[]) {
		res[0] = atan2(r11, r12);
		res[1] = acos(r21);
		res[2] = atan2(r31, r32);
	}

	static void threeaxisrot(REAL r11, REAL r12, REAL r21, REAL r31, REAL r32, REAL res[]) {
		res[0] = atan2(r31, r32);
		res[1] = asin(r21);
		res[2] = atan2(r11, r12);
	}

	static void QuaternionNaive2Euler(const QuaternionNaive<REAL>& q, REAL res[], RotSeq rotSeq)
	{
		switch (rotSeq) {
		case zyx:
			threeaxisrot(2 * (q.x*q.y + q.w*q.z),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				-2 * (q.x*q.z - q.w*q.y),
				2 * (q.y*q.z + q.w*q.x),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				res);
			break;

		case zyz:
			twoaxisrot(2 * (q.y*q.z - q.w*q.x),
				2 * (q.x*q.z + q.w*q.y),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				2 * (q.y*q.z + q.w*q.x),
				-2 * (q.x*q.z - q.w*q.y),
				res);
			break;

		case zxy:
			threeaxisrot(-2 * (q.x*q.y - q.w*q.z),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				2 * (q.y*q.z + q.w*q.x),
				-2 * (q.x*q.z - q.w*q.y),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				res);
			break;

		case zxz:
			twoaxisrot(2 * (q.x*q.z + q.w*q.y),
				-2 * (q.y*q.z - q.w*q.x),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				2 * (q.x*q.z - q.w*q.y),
				2 * (q.y*q.z + q.w*q.x),
				res);
			break;

		case yxz:
			threeaxisrot(2 * (q.x*q.z + q.w*q.y),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				-2 * (q.y*q.z - q.w*q.x),
				2 * (q.x*q.y + q.w*q.z),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				res);
			break;

		case yxy:
			twoaxisrot(2 * (q.x*q.y - q.w*q.z),
				2 * (q.y*q.z + q.w*q.x),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				2 * (q.x*q.y + q.w*q.z),
				-2 * (q.y*q.z - q.w*q.x),
				res);
			break;

		case yzx:
			threeaxisrot(-2 * (q.x*q.z - q.w*q.y),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				2 * (q.x*q.y + q.w*q.z),
				-2 * (q.y*q.z - q.w*q.x),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				res);
			break;

		case yzy:
			twoaxisrot(2 * (q.y*q.z + q.w*q.x),
				-2 * (q.x*q.y - q.w*q.z),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				2 * (q.y*q.z - q.w*q.x),
				2 * (q.x*q.y + q.w*q.z),
				res);
			break;

		case xyz:
			threeaxisrot(-2 * (q.y*q.z - q.w*q.x),
				q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
				2 * (q.x*q.z + q.w*q.y),
				-2 * (q.x*q.y - q.w*q.z),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				res);
			break;

		case xyx:
			twoaxisrot(2 * (q.x*q.y + q.w*q.z),
				-2 * (q.x*q.z - q.w*q.y),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				2 * (q.x*q.y - q.w*q.z),
				2 * (q.x*q.z + q.w*q.y),
				res);
			break;

		case xzy:
			threeaxisrot(2 * (q.y*q.z + q.w*q.x),
				q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
				-2 * (q.x*q.y - q.w*q.z),
				2 * (q.x*q.z + q.w*q.y),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				res);
			break;

		case xzx:
			twoaxisrot(2 * (q.x*q.z - q.w*q.y),
				2 * (q.x*q.y + q.w*q.z),
				q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
				2 * (q.x*q.z + q.w*q.y),
				-2 * (q.x*q.y - q.w*q.z),
				res);
			break;
		default:
			std::cout << "Unknown rotation sequence" << std::endl;
			break;
		}
	}


private:
	static REAL rad2deg(REAL rad) {
		return rad*180.0 / CmnMath::core::kPI;
	}

	static inline REAL SIGN(REAL x) { return (x >= 0.) ? +1. : -1.; }
	static inline REAL NORM(REAL a, REAL b, REAL c, REAL d) { return sqrt(a * a + b * b + c * c + d * d); }

};

}	// namespace numericspace
}	// namespace CmnMath

#endif // CMNMATH_NUMERICSYSTEM_QUATERNIONNAIVE_HPP__
