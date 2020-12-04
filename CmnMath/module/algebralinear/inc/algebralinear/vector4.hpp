/**
* @file vector4.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_VECTOR4_HPP__
#define CMNMATH_ALGEBRALINEAR_VECTOR4_HPP__

#include <vector>
#include <cmath>
#include "vector3.hpp"

namespace CmnMath
{
namespace algebralinear
{

/** Class to manage a 2 dimensional vector
	@brief 2 dimensional vector
	@remarks the w component isn't really used at all in the class, it's just kept along for the ride
*/
template <typename T>
class Vector4: public Vector3<T>
{
public:
	T w;

	//! trivial ctor
	Vector4<T>() : Vector3<T>() {
		//static_cast<T>(w) = 0;
		w = 0;
	}

	//! setting ctor
	Vector4<T>(const T x0, const T y0, const T z0, const T w0): Vector3<T>(x0, y0, z0), w(w0) {}

	/** Constructor with parameters
	*/
	Vector4<T>(const Vector3<T> &v) : Vector3<T>(v.x, v.y, v.z), w(v.w)  {}	

	//! function call operator
	void operator ()(const T x0, const T y0, const T z0, const T w0) 
	{	this->x= x0; this->y= y0; this->z= z0; w= w0; }

	//! test for equality
	bool operator==(const Vector4<T> &v)
	{	return (this->x==v.x && this->y==v.y && this->z==v.z && w==v.w);	}

	//! test for inequality
	bool operator!=(const Vector4<T> &v)
	{	return (this->x!=v.x || this->y!=v.y || this->z!=v.z || w!=v.w);	}

	//! set to value
	const Vector4<T> &operator =(const Vector4<T> &v)
	{	
		this->x= v.x; this->y= v.y;	this->z= v.z;	w= v.w;	
		return *this;
	}
			
	//! negation
	const Vector4<T> operator -(void) const
	{	return Vector4<T>(-this->x,-this->y,-this->z,w);	}

	//! addition; not sure what to do with w component	
	const Vector4<T> operator +(const Vector4<T> &v) const
	{   return Vector4<T>(this->x+v.x, this->y+v.y, this->z+v.z, w);	 }	

	//! subtraction; results in a vector
	const Vector4<T> operator -(const Vector4<T> &v) const
	{   return Vector4<T>(this->x-v.x, this->y-v.y, this->z-v.z, 0);	 }	

	//! uniform scaling
	const Vector4<T> operator *(const T num) const
	{
		Vector4<T> temp(*this);			
		return temp*=num;
	}

	//! uniform scaling
	const Vector4<T> operator /(const T num) const
	{
		Vector4<T> temp(*this);			
		return temp/=num;
	}			

	//! addition
	const Vector4<T> &operator +=(const Vector4<T> &v)
	{
		this->x+=v.x;	this->y+=v.y;	this->z+=v.z;	
		return *this;
	}

	//! subtraction
	const Vector4<T> &operator -=(const Vector4<T> &v) 
	{ 
		this->x-=v.x;	this->y-=v.y;	this->z-=v.z;	
		return *this;	
	}

	//! uniform scaling, note this scales the w component as well
	const Vector4<T> &operator *=(const T num)
	{
		this->x*=num; this->y*=num; this->z*=num;	w*=num;
		return *this;
	}
			
	//! uniform scaling, note this scales the w component as well
	const Vector4<T> &operator /=(const T num)
	{
		this->x/=num; this->y/=num; this->z/=num;w/=num;								
		return *this;
	}

	//! dot product
	T operator *(const Vector4<T> &v) const
	{	return this->x*v.x + this->y*v.y + this->z*v.z;	}

	//! cross product, returns a vector
	const Vector4<T> operator %(const Vector4<T> &v) const 
	{
		Vector4<T> temp(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x, 0);
		return temp;
	}	
};


/** Class to manage the floating point vector
*/
class Vector4f: public Vector4<CMN_32F>
{
public:

	//! trivial ctor
	Vector4f() {}

	//! setting ctor
	Vector4f(CMN_32F x0, CMN_32F y0, CMN_32F z0, CMN_32F w0): Vector4<CMN_32F>(x0, y0, z0, w0) {}

	/** Constructor with parameters
	*/
	Vector4f(const Vector4<CMN_32F> &v) : Vector4<CMN_32F>(v.x, v.y, v.z, v.w)  {}	

	//! cast from vector3f to vector4f
	Vector4f(const Vector3f &v, CMN_32F w0): Vector4<CMN_32F>(v.x, v.y, v.z, w0) {}

	//! gets the length of this vector squared
	CMN_32F length_squared() const
	{	return (CMN_32F)(*this * *this);   }

	//! gets the length of this vector
	CMN_32F length() const
	{	return (CMN_32F)sqrt(*this * *this);   }

	//! normalizes this vector
	void normalize()
	{	*this/=length();	}
			
	//! reflects this vector about n
	void reflect(const Vector4 &n)
	{
		Vector4 orig(*this);
		project(n);
		*this= *this*2 - orig;
	}

	//! projects this vector onto v
	void project(const Vector4 &v)
	{	*this= v * (*this * v)/(v*v);	}

	//! returns this vector projected onto v
	Vector4 projected(const Vector4 &v)
	{   return v * (*this * v)/(v*v);	}
};

} // namespace algebralinear
} // namespace CmnMath

#endif
