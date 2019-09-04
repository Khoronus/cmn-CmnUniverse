/**
* @file matrix2.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_MATRIX2_HPP__
#define CMNMATH_ALGEBRALINEAR_MATRIX2_HPP__

#include "matrixN.hpp"
#include "vector2.hpp"


namespace CmnMath
{
namespace algebralinear
{


//! matrix is in column major form (compatible with openGL)
//! normal C arrays must be transposed before converting
class Matrix2
{
public:
	MATRIX_COMMON_INTERNAL(2)

	Matrix2(const Vector2f &v0, const Vector2f &v1)
	{	col[0]= v0, col[1]= v1;  }

	Matrix2(CMN_32F m00, CMN_32F m01, CMN_32F m10, CMN_32F m11)
	{  
		col[0].x= m00, col[0].y= m01;
		col[1].x= m10, col[1].y= m11;
	}	

	//! construct a rotation matrix
	inline static void rotate(Matrix2 &m, CMN_32F angle)
	{
		m.col[0][0]= cosf(angle); m.col[0][1]= sinf(angle);
		m.col[1][0]= -sinf(angle); m.col[1][1]= cosf(angle);
	}

	//! multiplication by a matrix
	const Matrix2 &operator *=(const Matrix2 &m)
	{
		Matrix2 temp(Vector2f(col[0].x*m.col[0].x + col[1].x*m.col[0].y,
								col[0].y*m.col[0].x + col[1].y*m.col[0].y),
						Vector2f(col[0].x*m.col[1].x + col[1].x*m.col[1].y,
								col[0].y*m.col[1].x + col[1].y*m.col[1].y));
		return *this= temp;
	}

	//! multiplication by a vector
	const Vector2f operator *(const Vector2f &v) const
	{	return Vector2f(v.x*col[0].x + v.y*col[1].x, v.x*col[0].y + v.y*col[1].y);	}			

	//! multiplication by a scalar
	const Matrix2 &operator *=(const CMN_32F s)
	{
		col[0]*=s; col[1]*=s;		
		return *this;
	}

	//! division by a scalar
	const Matrix2 &operator /=(const CMN_32F s)
	{
		col[0]/=s; col[1]/=s;		
		return *this;
	}

	//! addition	
	const Matrix2 operator +(const Matrix2 &m) const
	{   return Matrix2(col[0]+m.col[0], col[1]+m.col[1]);	 }	

	//! addition
	const Matrix2 &operator +=(const Matrix2 &m)
	{
		col[0]+= m.col[0];
		col[1]+= m.col[1];		
		return *this;
	}

	//! subtraction	
	const Matrix2 operator -(const Matrix2 &m) const
	{   return Matrix2(col[0]-m.col[0], col[1]-m.col[1]);	 }	

	//! subtraction
	const Matrix2 &operator -=(const Matrix2 &m)
	{
		col[0]-= m.col[0];
		col[1]-= m.col[1];		
		return *this;
	}

	//! compute the trace
	CMN_32F trace() const
	{   return col[0][0] + col[1][1];  }

	//! compute the determinant
	CMN_32F determinant() const
	{	return col[0][0]*col[1][1] - col[0][1]*col[1][0];  }

	//! invert the matrix
	void invert()
	{
		// [!]
		//Swap(col[0].x, col[1].y);
		std::swap(col[0].x, col[1].y);
		col[0].y= -col[0].y;
		col[1].x= -col[1].x;		
		*this/=determinant();
	}	

	//! matrix inversion by the tilde operator
	const Matrix2 operator ~(void) const
	{   
		Matrix2 m(*this);
		m.invert(); 	 
		return m;
	}
};

MATRIX_COMMON_EXTERNAL(2)

}	// namespace algebralinear
}	// namespace CmnMath

#endif