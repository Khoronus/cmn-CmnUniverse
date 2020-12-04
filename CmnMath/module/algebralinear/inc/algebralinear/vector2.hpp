/**
* @file vector2.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_VECTOR2_HPP__
#define CMNMATH_ALGEBRALINEAR_VECTOR2_HPP__

#include <vector>
#include <cmath>
#include <iostream>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace algebralinear
{

/** Class to manage a 2 dimensional vector
	@brief 2 dimensional vector
*/
template <typename T>
class Vector2
{
public:

	/** \brief X value for a vector 2D x,y */
	T x;
	/** \brief X value for a vector 2D x,y */
	T y;
			
	/** Default constructor
	*/
	Vector2<T>() { 
		//static_cast<T>(x) = 0; 
		//static_cast<T>(y) = 0;
		x = 0; 
		y = 0;
	}

	/** Constructor with parameters
		@param[in] x0 X value
		@param[in] y0 Y value
	*/
	Vector2<T>(const T x0, const T y0): x(x0), y(y0) {}

	/** Constructor with parameters
	*/
	Vector2<T>(const Vector2<T> &v) : x(v.x), y(v.y) {}	

	/** array indexing 
	*/ 
	T &operator [](CMN_32U i) 
	{   return *(&x+i);   }

	/** array indexing 
	*/ 
	const T &operator [](CMN_32U i) const 
	{	return *(&x+i);   }  

	//! function call operator
	void operator ()(const T x0, const T y0) 
	{	x= x0; y= y0;	}

	//! test for equality
	bool operator==(const Vector2<T> &v)
	{	return (x==v.x && y==v.y);	}

	//! test for inequality
	bool operator!=(const Vector2<T> &v)
	{	return (x!=v.x || y!=v.y);	}
			
	//! set to value
	const Vector2<T> &operator =(const Vector2<T> &v)
	{	
		x= v.x; y= v.y;			
		return *this;
	}
			
	//! negation
	const Vector2<T> operator -(void) const
	{	return Vector2<T>(-x, -y);	}

	//! addition
	const Vector2<T> operator +(const Vector2<T> &v) const
	{	return Vector2<T>(x+v.x, y+v.y);	}
			
	//! subtraction
	const Vector2<T> operator -(const Vector2<T> &v) const
	{   return Vector2<T>(x-v.x, y-v.y);	}
				
	//! uniform scaling
	const Vector2<T> operator *(const T num) const
	{
		Vector2<T> temp(*this);			
		return temp*=num;
	}

	//! uniform scaling
	const Vector2<T> operator /(const T num) const
	{
		Vector2<T> temp(*this);			
		return temp/=num;
	}		

	//! addition
	const Vector2<T> &operator +=(const Vector2<T> &v)
	{
		x+=v.x;	y+=v.y;						
		return *this;
	}

	//! subtraction
	const Vector2<T> &operator -=(const Vector2<T> &v) 
	{ 
		x-=v.x;	y-=v.y;						
		return *this;	
	}

	//! uniform scaling
	const Vector2<T> &operator *=(const T num)
	{
		x*=num;	y*=num;										
		return *this;
	}
			
	//! uniform scaling
	const Vector2<T> &operator /=(const T num)
	{
		x/=num;	y/=num;										
		return *this;
	}

	//! dot product
	T operator *(const Vector2<T> &v) const
	{	return x*v.x + y*v.y;	}	

	friend std::ostream& operator<<(std::ostream &out, Vector2<T>& obj) {
		out << "[" << obj.x << "," << obj.y << "]";
		return out;
	}

};


// macro to make creating the ctors for derived vectors easier
//#define VECTOR2_CTORS(name, type)   \
//	/* trivial ctor */				\
//	name() {}						\
//	/* down casting ctor */			\
//	name(const Vector2<type> &v): Vector2<type>(v.x, v.y) {}	\
//	/* make x,y combination into a vector */					\
//	name(type x0, type y0): Vector2<type>(x0, y0) {}
			    

/** Class that extend the generic class for CMN_32F version
*/
class Vector2f: public Vector2<CMN_32F>
{
public:

	/* trivial ctor */				
	Vector2f() {}					
	/* down casting ctor */			
	Vector2f(const Vector2<CMN_32F> &v): Vector2<CMN_32F>(v.x, v.y) {}	
	/* make x,y combination into a vector */					
	Vector2f(CMN_32F x0, CMN_32F y0): Vector2<CMN_32F>(x0, y0) {}

	//! gets the length of this vector squared
	CMN_32F length_squared() const
	{	return (CMN_32F)(*this * *this);   }

	//! gets the length of this vector
	CMN_32F length() const
	{	return (CMN_32F)sqrt(*this * *this);   }

	//! normalizes this vector
	void normalize()
	{	*this/=length();	}

	//! returns the normalized vector
	Vector2f normalized() const
	{   return  *this/length();  }

	//! reflects this vector about n
	void reflect(const Vector2f &n)
	{
		Vector2f orig(*this);
		project(n);
		*this= *this*2.0f - orig;
	}

	//! projects this vector onto v
	void project(const Vector2f &v)
	{	*this= v * (*this * v)/(v*v);	}

	//! returns this vector projected onto v
	Vector2f projected(const Vector2f &v)
	{   return v * (*this * v)/(v*v);	}

	//! computes the angle between 2 arbitrary vectors
	static inline CMN_32F angle(const Vector2f &v1, const Vector2f &v2)
	{   return acosf((v1*v2) / (v1.length()*v2.length()));  }

	//! computes the angle between 2 normalized arbitrary vectors
	static inline CMN_32F angle_normalized(const Vector2f &v1, const Vector2f &v2)
	{   return acosf(v1*v2);  }
};

typedef Vector2<CMN_32S> Vector2i;
typedef Vector2<CMN_32U> Vector2ui;

}	// namespace algebralinear
}	// namespace CmnMath

#endif
