/**
* @file matrix4.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_MATRIX4_HPP__
#define CMNMATH_ALGEBRALINEAR_MATRIX4_HPP__

#include "matrix3.hpp"
#include "vector4.hpp"


namespace CmnMath
{
namespace algebralinear
{

//! matrix is in column major form (compatible with openGL)
//! normal C arrays must be transposed before converting
class Matrix4
{
public:

	MATRIX_COMMON_INTERNAL(4)
			

	Matrix4(const Vector4f &v0, const Vector4f &v1, const Vector4f &v2, const Vector4f &v3)
	{	col[0]= v0, col[1]= v1, col[2]= v2, col[3]= v3;  }

	Matrix4(CMN_32F m00, CMN_32F m01, CMN_32F m02, CMN_32F m03,
			CMN_32F m10, CMN_32F m11, CMN_32F m12, CMN_32F m13,
			CMN_32F m20, CMN_32F m21, CMN_32F m22, CMN_32F m23,
			CMN_32F m30, CMN_32F m31, CMN_32F m32, CMN_32F m33)
	{  
		col[0].x= m00, col[0].y= m01, col[0].z= m02, col[0].w= m03;
		col[1].x= m10, col[1].y= m11, col[1].z= m12, col[1].w= m13;
		col[2].x= m20, col[2].y= m21, col[2].z= m22, col[2].w= m23;
		col[3].x= m30, col[3].y= m31, col[3].z= m32, col[3].w= m33;
	}

	//! builds a matrix from a 3x3 basis matrix and a translation vector
	Matrix4(const Vector3f &top, const Vector3f &mid, const Vector3f &bot, const Vector3f &trans)
	{
		col[0].x= top.x; col[1].x= top.y; col[2].x= top.z; col[3].x= trans.x;		
		col[0].y= mid.x; col[1].y= mid.y; col[2].y= mid.z; col[3].y= trans.y;		
		col[0].z= bot.x; col[1].z= bot.y; col[2].z= bot.z; col[3].z= trans.z;	
		col[0].w= 0;     col[1].w= 0;     col[2].w= 0;     col[3].w= 1;

		/*col[0].x= top.x; col[1].x= mid.x; col[2].x= bot.x; col[3].x= trans.x;		
		col[0].y= top.y; col[1].y= mid.y; col[2].y= bot.y; col[3].y= trans.y;		
		col[0].z= top.z; col[1].z= mid.z; col[2].z= bot.z; col[3].z= trans.z;	
		col[0].w= 0;     col[1].w= 0;     col[2].w= 0;     col[3].w= 1;*/
	}

	//! builds a matrix from a 3x3 basis matrix and a translation vector
	Matrix4(const Matrix3 &m, const Vector3f &trans)
	{
		col[0].x= m[0].x; col[1].x= m[1].x; col[2].x= m[2].x; col[3].x= trans.x;		
		col[0].y= m[0].y; col[1].y= m[1].y; col[2].y= m[2].y; col[3].y= trans.y;		
		col[0].z= m[0].z; col[1].z= m[1].z; col[2].z= m[2].z; col[3].z= trans.z;	
		col[0].w= 0;      col[1].w= 0;      col[2].w= 0;      col[3].w= 1;
	}

	//! construct an x axis rotation matrix on 3x3 submatrix
	inline static void rotate_x(Matrix4 &m, CMN_32F angle)
	{
		m.col[0][0]= 1; m.col[0][1]= 0; m.col[0][2]= 0;
		m.col[1][0]= 0; m.col[1][1]= cosf(angle); m.col[1][2]= sinf(angle);
		m.col[2][0]= 0; m.col[2][1]= -sinf(angle); m.col[2][2]= cosf(angle);
	}

	//! construct an y axis rotation matrix on 3x3 submatrix
	inline static void rotate_y(Matrix4 &m, CMN_32F angle)
	{
		m.col[0][0]= cosf(angle); m.col[0][1]= 0; m.col[0][2]= -sinf(angle);
		m.col[1][0]= 0; m.col[1][1]= 0; m.col[1][2]= 0;
		m.col[2][0]= sinf(angle); m.col[2][1]= 0; m.col[2][2]= cosf(angle);
	}

	//! construct an z axis rotation matrix on 3x3 submatrix
	inline static void rotate_z(Matrix4 &m, CMN_32F angle)
	{
		m.col[0][0]= cosf(angle); m.col[0][1]= sinf(angle); m.col[0][2]= 0;
		m.col[1][0]= -sinf(angle); m.col[1][1]= cosf(angle); m.col[1][2]= 0;
		m.col[2][0]= 0; m.col[2][1]= 0; m.col[2][2]= 1;
	}	

	//! sets a rotation matrix up by euler angles
	//! uses pitch, roll, yaw (xyz) form
	inline static void rotate_euler(Matrix4 &m, CMN_32F x, CMN_32F y, CMN_32F z)
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

	//! sets a rotation matrix up for the 3x3 submatrix by euler angles
	//! uses pitch, roll, yaw (xyz) form
	inline static void rotate_euler(Matrix4 &m, const Vector3f &angles)
	{	rotate_euler(m, angles.x, angles.y, angles.z);	}

	//! sets the translation values for a matrix
	inline static void translation(Matrix4 &m, CMN_32F x, CMN_32F y, CMN_32F z)
	{
		m.col[3].x= x;		
		m.col[3].y= y;		
		m.col[3].z= z;		
	}

	//! sets the translation values for a matrix
	inline static void translation(Matrix4 &m, const Vector3f &t)
	{	translation(m, t.x, t.y, t.z);		}

	//! generates a perspective transformation matrix in the same manner opengl does
	inline static Matrix4 frustum(CMN_32F left, CMN_32F right, CMN_32F bottom, CMN_32F top, CMN_32F Near, CMN_32F Far)
	{
		CMN_32F width= right-left,
				height= top-bottom,
				depth= Far-Near,
				near2= Near*2;

		return Matrix4(near2/width, 0, (right+left)/width, 0,
						0, near2/height, (top+bottom)/height, 0, 
						0, 0, -(Far+Near)/depth, -near2*Far/depth,
						0, 0, -1, 0);
	}

	//! generates an orthographic projection matrix in the same manner opengl does
	inline static Matrix4 orthographic(CMN_32F left, CMN_32F right, CMN_32F bottom, CMN_32F top, CMN_32F Near, CMN_32F Far)
	{
		CMN_32F width= right-left,
				height= top-bottom,
				depth= Far-Near;

		return Matrix4(2/width, 0,0, -(right+left)/width,
						0, 2/height, 0, -(top+bottom)/height,
						0,0,-2/depth, (Far+Near)/depth,
						0,0,0,1);
	}

	//! generates a perspective projection matrix just like gluPerspective
	inline static Matrix4 perspective(CMN_32F fovy, CMN_32F aspect, CMN_32F zNear, CMN_32F zFar)
	{
		CMN_32F f= 1/tanf(fovy/2);
		return Matrix4(f/aspect, 0,0,0,
						0,f,0,0,
						0,0, (zNear+zFar)/(zNear-zFar), 2*zNear*zFar/(zNear-zFar),
						0,0,-1,0);
	}
				
	//! multiplication by a matrix
	const Matrix4 &operator *=(const Matrix4 &m)
	{
		Matrix4 temp(col[0].x*m.col[0].x + col[1].x*m.col[0].y + col[2].x*m.col[0].z + col[3].x*m.col[0].w,
						col[0].y*m.col[0].x + col[1].y*m.col[0].y + col[2].y*m.col[0].z + col[3].y*m.col[0].w,
						col[0].z*m.col[0].x + col[1].z*m.col[0].y + col[2].z*m.col[0].z + col[3].z*m.col[0].w,
						col[0].w*m.col[0].x + col[1].w*m.col[0].y + col[2].w*m.col[0].z + col[3].w*m.col[0].w,

						col[0].x*m.col[1].x + col[1].x*m.col[1].y + col[2].x*m.col[1].z + col[3].x*m.col[1].w,
						col[0].y*m.col[1].x + col[1].y*m.col[1].y + col[2].y*m.col[1].z + col[3].y*m.col[1].w,
						col[0].z*m.col[1].x + col[1].z*m.col[1].y + col[2].z*m.col[1].z + col[3].z*m.col[1].w,
						col[0].w*m.col[1].x + col[1].w*m.col[1].y + col[2].w*m.col[1].z + col[3].w*m.col[1].w,

						col[0].x*m.col[2].x + col[1].x*m.col[2].y + col[2].x*m.col[2].z + col[3].x*m.col[2].w,
						col[0].y*m.col[2].x + col[1].y*m.col[2].y + col[2].y*m.col[2].z + col[3].y*m.col[2].w,
						col[0].z*m.col[2].x + col[1].z*m.col[2].y + col[2].z*m.col[2].z + col[3].z*m.col[2].w,
						col[0].w*m.col[2].x + col[1].w*m.col[2].y + col[2].w*m.col[2].z + col[3].w*m.col[2].w,
							  
						col[0].x*m.col[3].x + col[1].x*m.col[3].y + col[2].x*m.col[3].z + col[3].x*m.col[3].w,
						col[0].y*m.col[3].x + col[1].y*m.col[3].y + col[2].y*m.col[3].z + col[3].y*m.col[3].w,
						col[0].z*m.col[3].x + col[1].z*m.col[3].y + col[2].z*m.col[3].z + col[3].z*m.col[3].w,
						col[0].w*m.col[3].x + col[1].w*m.col[3].y + col[2].w*m.col[3].z + col[3].w*m.col[3].w);
		return *this= temp;
	}

	//! multiplication by a vector
	const Vector4f operator *(const Vector4f &v) const
	{	return Vector4f(v.x*col[0].x + v.y*col[1].x + v.z*col[2].x + v.w*col[3].x, 
						v.x*col[0].y + v.y*col[1].y + v.z*col[2].y + v.w*col[3].y, 
						v.x*col[0].z + v.y*col[1].z + v.z*col[2].z + v.w*col[3].z,
						v.x*col[0].w + v.y*col[1].w + v.z*col[2].w + v.w*col[3].w);	}			
			
	//! multiplication by a scalar
	const Matrix4 &operator *=(const CMN_32F s)
	{
		col[0]*=s; col[1]*=s; col[2]*=s; col[3]*=s;
		return *this;
	}

	//! division by a scalar
	const Matrix4 &operator /=(const CMN_32F s)
	{
		col[0]/=s; col[1]/=s; col[2]/=s; col[3]/=s;
		return *this;
	}

	//! addition	
	const Matrix4 operator +(const Matrix4 &m) const
	{   return Matrix4(Vector4f(col[0]+m.col[0]), Vector4f(col[1]+m.col[1]), 
						Vector4f(col[2]+m.col[2]), Vector4f(col[3]+m.col[3]));	 }	

	//! addition
	const Matrix4 &operator +=(const Matrix4 &m)
	{
		col[0]+= m.col[0];
		col[1]+= m.col[1];
		col[2]+= m.col[2];
		col[3]+= m.col[3];
		return *this;
	}

	//! subtraction	
	const Matrix4 operator -(const Matrix4 &m) const
	{   return Matrix4(Vector4f(col[0]-m.col[0]), Vector4f(col[1]-m.col[1]), 
						Vector4f(col[2]-m.col[2]), Vector4f(col[3]-m.col[3]));	 }	

	//! subtraction
	const Matrix4 &operator -=(const Matrix4 &m)
	{
		col[0]-= m.col[0];
		col[1]-= m.col[1];
		col[2]-= m.col[2];
		col[3]-= m.col[3];
		return *this;
	}

	//! compute the trace
	CMN_32F trace() const
	{   return col[0].x + col[1].y + col[2].z + col[3].w;  }

	//! returns the 3x3 submatrix with row i, column j deleted
	Matrix3 submatrix(CMN_8U i, CMN_8U j) const
	{
		switch(i)
		{
		case 0: switch(j)
				{
				case 0: return Matrix3(col[1].y,col[1].z,col[1].w, 
										col[2].y,col[2].z,col[2].w,
										col[3].y,col[3].z,col[3].w);									   
				case 1: return Matrix3(col[0].y,col[0].z,col[0].w, 
										col[2].y,col[2].z,col[2].w,
										col[3].y,col[3].z,col[3].w);									   
				case 2: return Matrix3(col[0].y,col[0].z,col[0].w, 
										col[1].y,col[1].z,col[1].w,
										col[3].y,col[3].z,col[3].w);
				default:return Matrix3(col[0].y,col[0].z,col[0].w, // case 3
										col[1].y,col[1].z,col[1].w, 
										col[2].y,col[2].z,col[2].w);
				} 
		case 1: switch(j)
				{
				case 0: return Matrix3(col[1].x,col[1].z,col[1].w, 
										col[2].x,col[2].z,col[2].w,
										col[3].x,col[3].z,col[3].w);									   
				case 1: return Matrix3(col[0].x,col[0].z,col[0].w, 
										col[2].x,col[2].z,col[2].w,
										col[3].x,col[3].z,col[3].w);									   
				case 2: return Matrix3(col[0].x,col[0].z,col[0].w, 
										col[1].x,col[1].z,col[1].w,
										col[3].x,col[3].z,col[3].w);
				default:return Matrix3(col[0].x,col[0].z,col[0].w, // case 3
										col[1].x,col[1].z,col[1].w, 
										col[2].x,col[2].z,col[2].w);
				} 
		case 2: switch(j) 
				{
				case 0: return Matrix3(col[1].x,col[1].y,col[1].w, 
										col[2].x,col[2].y,col[2].w,
										col[3].x,col[3].y,col[3].w);									   
				case 1: return Matrix3(col[0].x,col[0].y,col[0].w, 
										col[2].x,col[2].y,col[2].w,
										col[3].x,col[3].y,col[3].w);									   
				case 2: return Matrix3(col[0].x,col[0].y,col[0].w, 
										col[1].x,col[1].y,col[1].w,
										col[3].x,col[3].y,col[3].w);
				default:return Matrix3(col[0].x,col[0].y,col[0].w, // case 3
										col[1].x,col[1].y,col[1].w, 
										col[2].x,col[2].y,col[2].w);
				} 
		default: switch(j) // case 3
				{
				case 0: return Matrix3(col[1].x,col[1].y,col[1].z, 
										col[2].x,col[2].y,col[2].z,
										col[3].x,col[3].y,col[3].z);									   
				case 1: return Matrix3(col[0].x,col[0].y,col[0].z, 
										col[2].x,col[2].y,col[2].z,
										col[3].x,col[3].y,col[3].z);									   
				case 2: return Matrix3(col[0].x,col[0].y,col[0].z, 
										col[1].x,col[1].y,col[1].z,
										col[3].x,col[3].y,col[3].z);
				default:return Matrix3(col[0].x,col[0].y,col[0].z, // case 3
										col[1].x,col[1].y,col[1].z, 
										col[2].x,col[2].y,col[2].z);
				} 
		}
	}
	//! compute the determinant
	CMN_32F determinant() const
	{	
		return col[0].x*submatrix(0,0).determinant() - col[0].y*submatrix(0,1).determinant() + 
				col[0].z*submatrix(0,2).determinant() - col[0].w*submatrix(0,3).determinant();		
	}

	//! invert the matrix
	void invert()
	{
		CMN_8U i, k;
		CMN_32F	detA= determinant();
		Matrix4 invmat;
		bool    sign= false;

				
		if (!detA) return;						
		for (i=0; i < 4; ++i, sign= !sign)
		for (k=0; k < 4; ++k, sign= !sign) 
		{	
			sign ? invmat[i][k]= -submatrix(i,k).determinant()/detA
					: invmat[i][k]= submatrix(i,k).determinant()/detA;			
		}
		*this= invmat;
	}	

	//! matrix inversion by the tilde operator
	const Matrix4 operator ~(void) const
	{   
		Matrix4 m(*this);
		m.invert(); 	 
		return m;
	}
};


MATRIX_COMMON_EXTERNAL(4)

}	// namespace algebralinear
}	// namespace CmnMath


#endif