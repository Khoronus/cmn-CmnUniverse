/**
* @file matrix3.hpp
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

/// Notes: singular matrix is a matrix whose determinant = 0
///        inverse of A = adjoint(A) / determinant(A)
///        a matrix (A) is positive definite if x(transpose)*A*x > 0 (where x is any non zero vector)

#ifndef CMNMATH_ALGEBRALINEAR_MATRIX3_HPP__
#define CMNMATH_ALGEBRALINEAR_MATRIX3_HPP__

#include "matrix2.hpp"
#include "vector3.hpp"


namespace CmnMath
{
namespace algebralinear
{

//! matrix is in column major form (compatible with openGL)
//! normal C arrays must be transposed before converting
class Matrix3
{
public:
	MATRIX_COMMON_INTERNAL(3)


	//! casting from a vector3f to a matrix is the tilde operator
	Matrix3(const Vector3f &v)
	{
		col[0].x= 0,   col[0].y= -v.z, col[0].z= v.y;
		col[1].x= v.z, col[1].y=  0,   col[1].z=-v.x; 
		col[2].x= -v.y,col[2].y=  v.x, col[2].z= 0;
	}

	Matrix3(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2)
	{	col[0]= v0, col[1]= v1, col[2]= v2;  }

	Matrix3(CMN_32F m00, CMN_32F m01, CMN_32F m02,
			CMN_32F m10, CMN_32F m11, CMN_32F m12,
			CMN_32F m20, CMN_32F m21, CMN_32F m22)
	{  
		col[0].x= m00, col[0].y= m01, col[0].z= m02;
		col[1].x= m10, col[1].y= m11, col[1].z= m12;
		col[2].x= m20, col[2].y= m21, col[2].z= m22;
	}
			
	//! reorthogonalizes a matrix
	void reorthogonalize()
	{
		col[0].normalize();
		// using iterated Gram-Schmidt procedure
		col[1]= col[1] - col[0]*(col[1]*col[0]);
		col[1].normalize();
		col[2]= col[0]%col[1];
		//col[2].normalize(); // should already be normalized because 0 & 1 are normalized
	}
			
	//! construct an x axis rotation matrix
	inline static void rotate_x(Matrix3 &m, CMN_32F angle)
	{
		m.col[0][0]= 1; m.col[0][1]= 0; m.col[0][2]= 0;
		m.col[1][0]= 0; m.col[1][1]= cosf(angle); m.col[1][2]= sinf(angle);
		m.col[2][0]= 0; m.col[2][1]= -sinf(angle); m.col[2][2]= cosf(angle);
	}

	//! construct an y axis rotation matrix
	inline static void rotate_y(Matrix3 &m, CMN_32F angle)
	{
		m.col[0][0]= cosf(angle); m.col[0][1]= 0; m.col[0][2]= -sinf(angle);
		m.col[1][0]= 0; m.col[1][1]= 0; m.col[1][2]= 0;
		m.col[2][0]= sinf(angle); m.col[2][1]= 0; m.col[2][2]= cosf(angle);
	}

	//! construct an z axis rotation matrix
	inline static void rotate_z(Matrix3 &m, CMN_32F angle)
	{
		m.col[0][0]= cosf(angle); m.col[0][1]= sinf(angle); m.col[0][2]= 0;
		m.col[1][0]= -sinf(angle); m.col[1][1]= cosf(angle);  m.col[1][2]= 0;
		m.col[2][0]= 0;           m.col[2][1]= 0;            m.col[2][2]= 1;
	}

	//! constructs a rotation matrix around an arbitrary vector
	inline static void rotate(Matrix3 &m, const Vector3f &v, const CMN_32F angle)
	{
		CMN_32F c= 1-cosf(angle), s= sinf(angle), cxy= c*v.x*v.y, cxz= c*v.x*v.z, cyz= c*v.y*v.z;

		m.col[0][0]= c*v.x*v.x + 1-c; m.col[0][1]= cxy     - v.z*s;	m.col[0][2]= cxz + v.y*s; 
		m.col[1][0]= cxy     + v.z*s; m.col[1][1]= c*v.y*v.y + 1-c; m.col[1][2]= cyz - v.x*s; 
		m.col[2][0]= cxz     - v.y*s; m.col[2][1]= cyz     + v.x*s; m.col[2][2]= c*v.z*v.z + 1-c; 
	}

	//! sets a rotation matrix up by euler angles
	//! uses pitch, roll, yaw (xyz) form
	inline static void rotate_euler(Matrix3 &m, CMN_32F x, CMN_32F y, CMN_32F z)
	{
		CMN_64F cx = cos(x);
		CMN_64F sx = sin(x);
		CMN_64F cy = cos(y);
		CMN_64F sy = sin(y);
		CMN_64F cz = cos(z);
		CMN_64F sz = sin(z);
				
		m.col[0].x = (CMN_32F)(cy*cz); 
		m.col[0].y = (CMN_32F)(cy*sz);
		m.col[0].z = (CMN_32F)(-sy);

		CMN_64F sxsy = sx*sy;
		CMN_64F cxsy = cx*sy;
				
		m.col[1].x = (CMN_32F)(sxsy*cz-cx*sz);
		m.col[1].y = (CMN_32F)(sxsy*sz+cx*cz);
		m.col[1].z = (CMN_32F)(sx*cy);
			
		m.col[2].x = (CMN_32F)(cxsy*cz+sx*sz);
		m.col[2].y = (CMN_32F)(cxsy*sz-sx*cz);
		m.col[2].z = (CMN_32F)(cx*cy);
	}

	//! sets a rotation matrix up by euler angles
	//! uses pitch, roll, yaw (xyz) form
	inline static void rotate_euler(Matrix3 &m, const Vector3f &angles)
	{	rotate_euler(m, angles.x, angles.y, angles.z);	}

	//! multiplication by a matrix
	const Matrix3 &operator *=(const Matrix3 &m)
	{
		Matrix3 temp(Vector3f(col[0].x*m.col[0].x + col[1].x*m.col[0].y + col[2].x*m.col[0].z,
								col[0].y*m.col[0].x + col[1].y*m.col[0].y + col[2].y*m.col[0].z,
								col[0].z*m.col[0].x + col[1].z*m.col[0].y + col[2].z*m.col[0].z),
						Vector3f(col[0].x*m.col[1].x + col[1].x*m.col[1].y + col[2].x*m.col[1].z,
								col[0].y*m.col[1].x + col[1].y*m.col[1].y + col[2].y*m.col[1].z,
								col[0].z*m.col[1].x + col[1].z*m.col[1].y + col[2].z*m.col[1].z),
						Vector3f(col[0].x*m.col[2].x + col[1].x*m.col[2].y + col[2].x*m.col[2].z,
								col[0].y*m.col[2].x + col[1].y*m.col[2].y + col[2].y*m.col[2].z,
								col[0].z*m.col[2].x + col[1].z*m.col[2].y + col[2].z*m.col[2].z));		
		return *this= temp;
	}

	//! multiplication by a vector
	const Vector3f operator *(const Vector3f &v) const
	{	return Vector3f(v.x*col[0].x + v.y*col[1].x + v.z*col[2].x, 
						v.x*col[0].y + v.y*col[1].y + v.z*col[2].y, 
						v.x*col[0].z + v.y*col[1].z + v.z*col[2].z);	}			

	//! multiplication by a scalar
	const Matrix3 &operator *=(const CMN_32F s)
	{
		col[0]*=s; col[1]*=s; col[2]*=s;		
		return *this;
	}

	//! division by a scalar
	const Matrix3 &operator /=(const CMN_32F s)
	{
		col[0]/=s; col[1]/=s; col[2]/=s;		
		return *this;
	}

	//! addition	
	const Matrix3 operator +(const Matrix3 &m) const
	{   return Matrix3(col[0]+m.col[0], col[1]+m.col[1], col[2]+m.col[2]);	 }	

	//! addition
	const Matrix3 &operator +=(const Matrix3 &m)
	{
		col[0]+= m.col[0];
		col[1]+= m.col[1];
		col[2]+= m.col[2];
		return *this;
	}

	//! subtraction	
	const Matrix3 operator -(const Matrix3 &m) const
	{   return Matrix3(col[0]-m.col[0], col[1]-m.col[1], col[2]-m.col[2]);	 }	

	//! subtraction
	const Matrix3 &operator -=(const Matrix3 &m)
	{
		col[0]-= m.col[0];
		col[1]-= m.col[1];
		col[2]-= m.col[2];
		return *this;
	}

	//! compute the trace
	CMN_32F trace() const
	{   return col[0].x + col[1].y + col[2].z;  }

	//! returns the 2x2 submatrix with row i, column j deleted
	Matrix2 submatrix(CMN_8U i, CMN_8U j) const
	{	
		switch(i)
		{
		case 0: switch(j)
				{
				case 0: return Matrix2(col[1].y,col[1].z, col[2].y,col[2].z);
				case 1: return Matrix2(col[0].y,col[0].z, col[2].y,col[2].z);
				default:return Matrix2(col[0].y,col[0].z, col[1].y,col[1].z);// case 2
				} 
		case 1: switch(j)
				{
				case 0: return Matrix2(col[1].x,col[1].z, col[2].x,col[2].z);
				case 1: return Matrix2(col[0].x,col[0].z, col[2].x,col[2].z);
				default:return Matrix2(col[0].x,col[0].z, col[1].x,col[1].z); // case 2
				} 
		default: switch(j) // case 2
				{
				case 0: return Matrix2(col[1].x,col[1].y, col[2].x,col[2].y);
				case 1: return Matrix2(col[0].x,col[0].y, col[2].x,col[2].y);
				default:return Matrix2(col[0].x,col[0].y, col[1].x,col[1].y); // case 2
				} 
		}
	}

	//! compute the determinant
	CMN_32F determinant() const
	{	return col[0].x*(col[1].y*col[2].z-col[1].z*col[2].y) - 
				col[1].x*(col[0].y*col[2].z-col[0].z*col[2].y) + 
				col[2].x*(col[0].y*col[1].z-col[0].z*col[1].y);  }

	//! invert the matrix
	void invert()
	{
		CMN_8U i, k;
		CMN_32F	detA= determinant();
		Matrix3 invmat;
		bool    sign= false;

				
		if (!detA) return;		
		for (i=0; i < 3; ++i)
		for (k=0; k < 3; ++k, sign= !sign) 
		{			
			sign ? invmat[i][k]= -submatrix(i, k).determinant()/detA
					: invmat[i][k]= submatrix(i, k).determinant()/detA;			
		}
		*this= invmat;
	}	

	//! matrix inversion by the tilde operator
	const Matrix3 operator ~(void) const
	{   
		Matrix3 m(*this);
		m.invert(); 	 
		return m;
	}
};

MATRIX_COMMON_EXTERNAL(3)


}	// namespace algebralinear
}	// namespace CmnMath

#endif