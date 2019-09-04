/**
* @file quaternion.hpp
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
* @original author Will Perone (will.perone@gmail.com)
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_NUMERICSYSTEM_QUATERNION_HPP__
#define CMNMATH_NUMERICSYSTEM_QUATERNION_HPP__

/*
 * Notes:  
 * if |q|=1 then q is a unit quaternion
 * if q=(0,v) then q is a pure quaternion 
 * if |q|=1 then q conjugate = q inverse
 * if |q|=1 then q= [cos(angle), u*sin(angle)] where u is a unit vector 
 * q and -q represent the same rotation 
 * q*q.conjugate = (q.length_squared, 0) 
 * ln(cos(theta),sin(theta)*v)= ln(e^(theta*v))= (0, theta*v)

*/

#include "algebralinear/inc/algebralinear/matrix4.hpp"
#include "cmnmathcore/inc/cmnmathcore/assert.hpp"

namespace CmnMath
{
namespace numericsystem
{


/** Class for the quaternions operations
*/
template <typename _Ty>
class Quaternion
{
public:

	union {
		struct {
			CMN_32F    s; //!< the real component
			_Ty v;		//!< the imaginary components
		};

		struct { CMN_32F elem[4]; }; //! the raw elements of the quaternion
	};


	//! ctors
	Quaternion() {}
	Quaternion(const Quaternion &obj) {
		*this = obj;
	}
	Quaternion(CMN_32F real, CMN_32F x, CMN_32F y, CMN_32F z): s(real), v(x,y,z) {}
	Quaternion(CMN_32F real, const _Ty &i): s(real), v(i) {}

	//! from 3 euler angles
	Quaternion(CMN_32F theta_z, CMN_32F theta_y, CMN_32F theta_x)//CMN_32F heading, CMN_32F attitude, CMN_32F bank) 
	{
		/*CMN_32F angle, sr, sp, sy, cr, cp, cy;

		angle = bank/2;
		sy = sinf(angle);
		cy = cosf(angle);
		angle = attitude/2;
		sp = sinf(angle);
		cp = cosf(angle);
		angle = heading/2;
		sr = sinf(angle);
		cr = cosf(angle);

		CMN_64F crcp = cr*cp, srsp = sr*sp;

		v.z = (CMN_32F)( sr*cp*cy-cr*sp*sy );
		v.y = (CMN_32F)( cr*sp*cy+sr*cp*sy );
		v.x = (CMN_32F)( crcp*sy-srsp*cy );
		s = (CMN_32F)( crcp*cy+srsp*sy ); */

		CMN_32F cos_z_2 = 0.5f * cosf(theta_z);
		CMN_32F cos_y_2 = 0.5f * cosf(theta_y);
		CMN_32F cos_x_2 = 0.5f * cosf(theta_x);

		CMN_32F sin_z_2 = 0.5f * sinf(theta_z);
		CMN_32F sin_y_2 = 0.5f * sinf(theta_y);
		CMN_32F sin_x_2 = 0.5f * sinf(theta_x);

		// and now compute quaternion
		s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
		v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
		v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
		v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
	}
			
	//! from 3 euler angles 
	Quaternion(const _Ty &angles)
	{	
		CMN_32F cos_z_2 = 0.5f * cosf(angles.z);
		CMN_32F cos_y_2 = 0.5f * cosf(angles.y);
		CMN_32F cos_x_2 = 0.5f * cosf(angles.x);

		CMN_32F sin_z_2 = 0.5f * sinf(angles.z);
		CMN_32F sin_y_2 = 0.5f * sinf(angles.y);
		CMN_32F sin_x_2 = 0.5f * sinf(angles.x);

		// and now compute quaternion
		s   = cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
		v.x = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
		v.y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
		v.z = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;

		/*CMN_32F c1,c2,c3,s1,s2,s3;

		// something strange is going on here
		c1 = cosf(-angles.z / 2);
		s1 = sinf(-angles.z / 2); 
		c2 = cosf(-angles.y / 2); 
		s2 = sinf(-angles.y / 2); 
		c3 = cosf(angles.x / 2); 
		s3 = sinf(angles.x / 2); 

		s= c1*c2*c3 + s1*s2*s3;
		v.x= c1*c2*s3 - s1*s2*c3;
		v.y= c1*s2*c3 + s1*c2*s3;
		v.z= s1*c2*c3 - c1*s2*s3;*/

		/*CMN_32F angle, sr, sp, sy, cr, cp, cy;

		angle = angles.z/2;
		sy = sinf(angle);
		cy = cosf(angle);
		angle = angles.y/2;
		sp = sinf(angle);
		cp = cosf(angle);
		angle = angles.x/2;
		sr = sinf(angle);
		cr = cosf(angle);

		CMN_64F crcp = cr*cp, srsp = sr*sp;

		v.z = (CMN_32F)( sr*cp*cy-cr*sp*sy );
		v.y = (CMN_32F)( cr*sp*cy+sr*cp*sy );
		v.x = (CMN_32F)( crcp*sy-srsp*cy );
		s = (CMN_32F)( crcp*cy+srsp*sy ); */
	} 
				
	//! basic operations
	Quaternion &operator =(const Quaternion &q)		
	{	s= q.s; v= q.v;	return *this;		}

	const Quaternion operator +(const Quaternion &q) const	
	{	return Quaternion(s+q.s, v+q.v);	}

	const Quaternion operator -(const Quaternion &q) const	
	{	return Quaternion(s-q.s, v-q.v);	}

	const Quaternion operator *(const Quaternion &q) const	
	{	return Quaternion(s*q.s - v*q.v,
							v.y*q.v.z - v.z*q.v.y + s*q.v.x + v.x*q.s,
							v.z*q.v.x - v.x*q.v.z + s*q.v.y + v.y*q.s,
							v.x*q.v.y - v.y*q.v.x + s*q.v.z + v.z*q.s);
	}

	/*const quaternion operator /(const quaternion &q) const
	{
		CMN_32F denominator = q.length();
		       
		// unsure if this is correct 
		return quaternion((s*q.s + v*q.v)/denominator,  
							(-s*q.v.x + v.x*q.s - v.y*q.v.z + v.z*q.v.y)/denominator,  
							(-s*q.v.y + v.x*q.v.z + v.y*q.s - v.z*q.v.x)/denominator,  
							(-s*q.v.z - v.x*q.v.y + v.y*q.v.x + v.z*q.s)/denominator);  
	}*/
	const Quaternion operator /(const Quaternion &q) const	
	{	
			Quaternion p(q); 
			p.invert(); 
			return *this * p;
	}

	const Quaternion operator *(CMN_32F scale) const			
		{	return Quaternion(s*scale,v*scale);		}

	const Quaternion operator /(CMN_32F scale) const
		{	return Quaternion(s/scale,v/scale);		}

	const Quaternion operator -() const						
		{	return Quaternion(-s, -v);				}
			
	const Quaternion &operator +=(const Quaternion &q)		
		{	v+=q.v; s+=q.s; return *this;			}

	const Quaternion &operator -=(const Quaternion &q)		
		{	v-=q.v; s-=q.s; return *this;			}

	const Quaternion &operator *=(const Quaternion &q)		
	{	
			CMN_32F x= v.x, y= v.y, z= v.z, sn= s*q.s - v*q.v;
			v.x= y*q.v.z - z*q.v.y + s*q.v.x + x*q.s;
			v.y= z*q.v.x - x*q.v.z + s*q.v.y + y*q.s;
			v.z= x*q.v.y - y*q.v.x + s*q.v.z + z*q.s;
			s= sn;
			return *this;
	}
			
	const Quaternion &operator *= (CMN_32F scale)			
		{	v*=scale; s*=scale; return *this;		}

	const Quaternion &operator /= (CMN_32F scale)			
		{	v/=scale; s/=scale; return *this;		}
			

	//! gets the length of this quaternion
	CMN_32F length() const
	{	return (CMN_32F)sqrt(s*s + v*v);   }

	//! gets the squared length of this quaternion
	CMN_32F length_squared() const
	{	return (CMN_32F)(s*s + v*v);   }

	//! normalizes this quaternion
	void normalize()
	{	*this/=length();	}

	//! returns the normalized version of this quaternion
	Quaternion normalized() const
	{   return  *this/length();  }

	//! computes the conjugate of this quaternion
	void conjugate()
	{	v=-v;   }

	//! inverts this quaternion
	void invert()
	{	conjugate(); *this/=length_squared(); 	}
			
	//! returns the logarithm of a quaternion = v*a where q = [cos(a),v*sin(a)]
	Quaternion log() const
	{
		CMN_32F a = (CMN_32F)acos(s);
		CMN_32F sina = (CMN_32F)sin(a);
		Quaternion ret;

		ret.s = 0;
		if (sina > 0)
		{
			ret.v.x = a*v.x/sina;
			ret.v.y = a*v.y/sina;
			ret.v.z = a*v.z/sina;
		} else {
			ret.v.x= ret.v.y= ret.v.z= 0;
		}
		return ret;
	}

	//! returns e^quaternion = exp(v*a) = [cos(a),vsin(a)]
	Quaternion exp() const
	{
		CMN_32F a = (CMN_32F)v.length();
		CMN_32F sina = (CMN_32F)sin(a);
		CMN_32F cosa = (CMN_32F)cos(a);
		Quaternion ret;

		ret.s = cosa;
		if (a > 0)
		{
			ret.v.x = sina * v.x / a;
			ret.v.y = sina * v.y / a;
			ret.v.z = sina * v.z / a;
		} else {
			ret.v.x = ret.v.y = ret.v.z = 0;
		}
		return ret;
	}

	//! casting to a 4x4 isomorphic matrix for right multiplication with vector
	operator algebralinear::Matrix4() const
	{			
		return algebralinear::Matrix4(s,  -v.x, -v.y,-v.z,
						v.x,  s,  -v.z, v.y,
						v.y, v.z,    s,-v.x,
						v.z,-v.y,  v.x,   s);
	}

	//! casting to a 4x4 isomorphic matrix for left multiplication with vector
	/*operator matrix4() const
	{			
		return matrix4(   s, v.x, v.y, v.z,
						-v.x,   s,-v.z, v.y,
						-v.y, v.z,   s,-v.x,
						-v.z,-v.y, v.x,   s);
	}*/

	//! casting to 3x3 rotation matrix
	operator algebralinear::Matrix3() const
	{
		Assert(length() > 0.9999 && length() < 1.0001, "quaternion is not normalized");		
		return Matrix3(1-2*(v.y*v.y+v.z*v.z), 2*(v.x*v.y-s*v.z),   2*(v.x*v.z+s*v.y),   
						2*(v.x*v.y+s*v.z),   1-2*(v.x*v.x+v.z*v.z), 2*(v.y*v.z-s*v.x),   
						2*(v.x*v.z-s*v.y),   2*(v.y*v.z+s*v.x),   1-2*(v.x*v.x+v.y*v.y));
	}

	//! computes the dot product of 2 quaternions
	static inline CMN_32F dot(const Quaternion &q1, const Quaternion &q2) 
	{   return q1.v*q2.v + q1.s*q2.s;  }

	//! linear quaternion interpolation
	static Quaternion lerp(const Quaternion &q1, const Quaternion &q2, CMN_32F t) 
	{	return (q1*(1-t) + q2*t).normalized();	}

	//! spherical linear interpolation
	static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, CMN_32F t) 
	{
		Quaternion q3;
		CMN_32F dot = Quaternion::dot(q1, q2);

		/*	dot = cos(theta)
			if (dot < 0), q1 and q2 are more than 90 degrees apart,
			so we can invert one to reduce spinning	*/
		if (dot < 0)
		{
			dot = -dot;
			q3 = -q2;
		} else q3 = q2;
				
		if (dot < 0.95f)
		{
			CMN_32F angle = acosf(dot);
			return (q1*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
		} else // if the angle is small, use linear interpolation								
			return lerp(q1,q3,t);		
	}

	//! This version of slerp, used by squad, does not check for theta > 90.
	static Quaternion slerpNoInvert(const Quaternion &q1, const Quaternion &q2, CMN_32F t) 
	{
		CMN_32F dot = Quaternion::dot(q1, q2);

		if (dot > -0.95f && dot < 0.95f)
		{
			CMN_32F angle = acosf(dot);			
			return (q1*sinf(angle*(1-t)) + q2*sinf(angle*t))/sinf(angle);
		} else  // if the angle is small, use linear interpolation								
			return lerp(q1,q2,t);			
	}

	//! spherical cubic interpolation
	static Quaternion squad(const Quaternion &q1,const Quaternion &q2,const Quaternion &a,const Quaternion &b,CMN_32F t)
	{
		Quaternion c= slerpNoInvert(q1,q2,t),
					d= slerpNoInvert(a,b,t);		
		return slerpNoInvert(c,d,2*t*(1-t));
	}

	//! Shoemake-Bezier interpolation using De Castlejau algorithm
	static Quaternion bezier(const Quaternion &q1,const Quaternion &q2,const Quaternion &a,const Quaternion &b,CMN_32F t)
	{
		// level 1
		Quaternion q11= slerpNoInvert(q1,a,t),
					q12= slerpNoInvert(a,b,t),
					q13= slerpNoInvert(b,q2,t);		
		// level 2 and 3
		return slerpNoInvert(slerpNoInvert(q11,q12,t), slerpNoInvert(q12,q13,t), t);
	}

	//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
	static Quaternion spline(const Quaternion &qnm1,const Quaternion &qn,const Quaternion &qnp1)
	{
		Quaternion qni(qn.s, -qn.v);		
				
		return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
	}

	//! converts from a normalized axis - angle pair rotation to a quaternion
	static inline Quaternion from_axis_angle(const _Ty &axis, CMN_32F angle)
	{	return Quaternion(cosf(angle/2), axis*sinf(angle/2)); 	}

	//! returns the axis and angle of this unit quaternion
	void to_axis_angle(_Ty &axis, CMN_32F &angle) const
	{
		angle = acosf(s);

		// pre-compute to save time
		CMN_32F sinf_theta_inv = 1.0/sinf(angle);

		// now the vector
		axis.x = v.x*sinf_theta_inv;
		axis.y = v.y*sinf_theta_inv;
		axis.z = v.z*sinf_theta_inv;

		// multiply by 2
		angle*=2;
	}

	//! rotates v by this quaternion (quaternion must be unit)
	_Ty rotate(const _Ty &v)
	{   
		Quaternion V(0, v);
		Quaternion conjugate(*this);
		conjugate.conjugate();
		return (*this * V * conjugate).v;
	}

	//! returns the euler angles from a rotation quaternion
	_Ty euler_angles(bool homogenous=true) const
	{
		CMN_32F sqw = s*s;    
		CMN_32F sqx = v.x*v.x;    
		CMN_32F sqy = v.y*v.y;    
		CMN_32F sqz = v.z*v.z;    

		_Ty euler;
		if (homogenous) {
			euler.x = atan2f(2.f * (v.x*v.y + v.z*s), sqx - sqy - sqz + sqw);    		
			euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
			euler.z = atan2f(2.f * (v.y*v.z + v.x*s), -sqx - sqy + sqz + sqw);    
		} else {
			euler.x = atan2f(2.f * (v.z*v.y + v.x*s), 1 - 2*(sqx + sqy));
			euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
			euler.z = atan2f(2.f * (v.x*v.y + v.z*s), 1 - 2*(sqy + sqz));
		}
		return euler;
	}
};


}	// namespace numericspace
}	// namespace CmnMath

#endif /* CMNMATH_NUMERICSYSTEM_QUATERNION_HPP__ */
