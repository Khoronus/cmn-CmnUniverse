/**
* @file vector3.hpp
* @brief Header related to linear algebra structures
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

#ifndef CMNMATH_ALGEBRALINEAR_VECTOR3_HPP__
#define CMNMATH_ALGEBRALINEAR_VECTOR3_HPP__

 /// Notes:
 /// if a*b = 0 then a & b are orthogonal
 /// a%b = -b%a
 /// a*(b%c) = (a%b)*c
 /// a%b = a(cast to matrix)*b
 /// (a%b).length() = area of parallelogram formed by a & b
 /// (a%b).length() = a.length()*b.length() * sin(angle between a & b)
 /// (a%b).length() = 0 if angle between a & b = 0 or a.length() = 0 or b.length() = 0
 /// a * (b%c) = volume of parallelpiped formed by a, b, c
 /// vector triple product: a%(b%c) = b*(a*c) - c*(a*b)
 /// scalar triple product: a*(b%c) = c*(a%b) = b*(c%a)
 /// vector quadruple product: (a%b)*(c%d) = (a*c)*(b*d) - (a*d)*(b*c)
 /// if a is unit vector along b then a%b = -b%a = -b(cast to matrix)*a = 0
 /// vectors a1...an are linearly dependant if there exists a vector of scalars (b) where a1*b1 + ... + an*bn = 0
 ///           or if the matrix (A) * b = 0

#include <vector>
#include <cmath>
#include <iostream>

#include "vector2.hpp"

namespace CmnMath
{
namespace algebralinear
{

/** Class to manage a 2 dimensional vector
	@brief 2 dimensional vector
*/
template <typename T>
class Vector3: public Vector2<T>
{
public:
	/** \brief Z coordinate */
	T z;

	//! trivial ctor
	Vector3<T>() : Vector2<T>() {
		//static_cast<T>(z) = 0;
		z = 0;
	}

	//! setting ctor
	Vector3<T>(const T x0, const T y0, const T z0): Vector2<T>(x0, y0), z(z0) {}

	/** Constructor with parameters
	*/
	Vector3<T>(const Vector3<T> &v) : Vector2<T>(v.x, v.y), z(v.z)  {}	

	//! function call operator
	void operator ()(const T x0, const T y0, const T z0) 
	{	this->x= x0; this->y= y0; z= z0;  }

	//! test for equality
	bool operator==(const Vector3<T> &v)
	{	return (this->x==v.x && this->y==v.y && z==v.z);	}

	//! test for inequality
	bool operator!=(const Vector3<T> &v)
	{	return (this->x!=v.x || this->y!=v.y || z!=v.z);	}

	//! set to value
	const Vector3<T> &operator =(const Vector3<T> &v)
	{	
		this->x= v.x; this->y= v.y;	z= v.z;		
		return *this;
	}
			
	//! negation
	const Vector3<T> operator -(void) const
	{	return Vector3<T>(-this->x,-this->y,-z);	}

	//! addition	
	const Vector3<T> operator +(const Vector3<T> &v) const
	{   return Vector3<T>(this->x+v.x, this->y+v.y, z+v.z);	 }	

	//! subtraction
	const Vector3<T> operator -(const Vector3<T> &v) const
	{   return Vector3<T>(this->x-v.x, this->y-v.y, z-v.z);	 }	

	//! uniform scaling
	const Vector3<T> operator *(const T num) const
	{
		Vector3<T> temp(*this);			
		return temp*=num;
	}

	//! uniform scaling
	const Vector3<T> operator /(const T num) const
	{
		Vector3<T> temp(*this);			
		return temp/=num;
	}			

	//! addition
	const Vector3<T> &operator +=(const Vector3<T> &v)
	{
		this->x+=v.x;	this->y+=v.y;	z+=v.z;					
		return *this;
	}

	//! subtraction
	const Vector3<T> &operator -=(const Vector3<T> &v) 
	{ 
		this->x-=v.x;	this->y-=v.y;	z-=v.z;					
		return *this;	
	}

	//! uniform scaling
	const Vector3<T> &operator *=(const T num)
	{
		this->x*=num; this->y*=num; z*=num;									
		return *this;
	}
			
	//! uniform scaling
	const Vector3<T> &operator /=(const T num)
	{
		this->x/=num; this->y/=num; z/=num;									
		return *this;
	}

	//! dot product
	T operator *(const Vector3<T> &v) const
	{	return this->x*v.x + this->y*v.y + z*v.z;	}

	//! cross product
	const Vector3<T> operator %(const Vector3<T> &v) const 
	{
		Vector3<T> temp(this->y*v.z - z*v.y, z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
		return temp;
	}	

	friend std::ostream& operator<<(std::ostream &out, Vector3<T>& obj) {
		out << "[" << obj.x << "," << obj.y << "," << obj.z << "]";
		return out;
	}
};



//// macro to make creating the ctors for derived vectors easier
//#define VECTOR3_CTORS(name, type)   \
//	/* trivial ctor */				\
//	name() {}						\
//	/* down casting ctor */			\
//	name(const vector3<type> &v): vector3<type>(v.x, v.y, v.z) {}	\
//	/* make x,y,z combination into a vector */						\
//	name(type x0, type y0, type z0): vector3<type>(x0, y0, z0) {}
//	    



//struct vector3i: public vector3<CMN_32S>
//{
//	VECTOR3_CTORS(vector3i, CMN_32S)
//};


//struct vector3ui: public vector3<CMN_32U>
//{
//	VECTOR3_CTORS(vector3ui, CMN_32U)
//};


class Vector3f: public Vector3<CMN_32F>
{
public:

	//! trivial ctor
	Vector3f() {}

	//! setting ctor
	Vector3f(CMN_32F x0, CMN_32F y0, CMN_32F z0): Vector3<CMN_32F>(x0, y0, z0) {}

	/** Constructor with parameters
	*/
	Vector3f(const Vector3<CMN_32F> &v) : Vector3<CMN_32F>(v.x, v.y, v.z)  {}	

	//! gets the length of this vector squared
	CMN_32F length_squared() const
	{	return (CMN_32F)(*this * *this);   }

	//! gets the length of this vector
	CMN_32F length() const
	{	return (CMN_32F)sqrt(*this * *this);   }

	//! normalizes this vector
	void normalize()
	{	*this/=length();	}

	//! returns the normalized version of this vector
	Vector3f normalized() const
	{   return  *this/length();  }
			
	//! reflects this vector about n
	void reflect(const Vector3f &n)
	{
		Vector3f orig(*this);
		project(n);
		*this= *this*2 - orig;
	}

	//! projects this vector onto v
	void project(const Vector3f &v)
	{	*this= v * (*this * v)/(v*v);	}

	//! returns this vector projected onto v
	Vector3f projected(const Vector3f &v)
	{   return v * (*this * v)/(v*v);	}
			
	//! computes the angle between 2 arbitrary vectors
	static inline CMN_32F angle(const Vector3f &v1, const Vector3f &v2)
	{   return acosf((v1*v2) / (v1.length()*v2.length()));  }

	//! computes the angle between 2 arbitrary normalized vectors
	static inline CMN_32F angle_normalized(const Vector3f &v1, const Vector3f &v2)
	{   return acosf(v1*v2);  }

	//! converts a normalized axis angle rotation to euler angles
	// doesnt work
/*	static inline vector3f axis_angle_to_euler(const vector3f &axis, CMN_32F angle)
	{
		vector3f euler;
		CMN_32F    c= 1-cosf(angle), s= sinf(angle);

		euler.x = atan2f(axis.x*axis.y*c + axis.z*s, 1 - (axis.y*axis.y-axis.z*axis.z)*c);
		euler.y = atan2f(axis.y*axis.z*c + axis.x*s, 1 - (axis.x*axis.x-axis.y*axis.y)*c);
		euler.z = asinf(-axis.x*axis.z*c - axis.y*s);
		return euler;
	}*/

	//! cross
	inline Vector3f cross(const Vector3f &v)
	{
		Vector3f r(0,0,0);
		r.x = y * v.z - z * v.y;
		r.y = z * v.x - x * v.z;
		r.z = x * v.y - y * v.x;
		return r;
	}

	//! dot
	inline CMN_32F dot(const Vector3f &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
};

typedef Vector3<CMN_32S> Vector3i;
typedef Vector3<CMN_32U> Vector3ui;

}	// namespace algebralinear
}	// namespace CmnMath

#endif
