/**
* @file matrixN.hpp
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

#ifndef CMNMATH_ALGEBRALINEAR_MATRIXN_HPP__
#define CMNMATH_ALGEBRALINEAR_MATRIXN_HPP__

#include <cmath>
#include <algorithm>

#pragma inline_depth( 255 )
#pragma inline_recursion( on )

namespace CmnMath
{
namespace algebralinear
{

//! used in creating an identity matrix
template<class Mtx, unsigned N> 
class IdentityMtx
{
public:
	static inline void eval(Mtx &mtx)
	{  IdentityMtxImpl<Mtx, N, 0, 0, 0>::eval(mtx);  }
};

//! Used in creating an identity matrix 
//! Assigns each element of the matrix
template<class Mtx, unsigned N, unsigned C, unsigned R, unsigned I>
class IdentityMtxImpl
{
public:
	enum
	{
		NxtI = I + 1,          // Counter
		NxtR = NxtI % N,       // Row (inner loop)
		NxtC = NxtI / N % N    // Column (outer loop)
	};
	static inline void eval( Mtx& mtx )
	{
		mtx[C][R] = ( C == R ) ? 1.0 : 0.0;
		IdentityMtxImpl<Mtx, N, NxtC, NxtR, NxtI>::eval(mtx);
	}
};


//! Used in creating an identity matrix
//! \remarks Makes the template appear like a function
#define IdentityMtxT(MtxType, Mtx, N) IdentityMtx< MtxType, N >::eval(Mtx)




//! used in matrix initialization
//! \remarks N is matrix size
template <class Mtx, unsigned N, class F, CMN_32S Init> 
class InitMtx
{
public:
	static inline void eval(Mtx &mtx)
	{  InitMtxImpl<Mtx, N, F, Init, 0, 0, 0>::eval(mtx);   }
};

//! used in matrix initialization
//! \remarks Assigns each element of the matrix
template <class Mtx, unsigned N, class F, CMN_32S Init, unsigned C, unsigned R, unsigned I>
class InitMtxImpl
{
public:
	enum
	{
		NxtI = I + 1,          // Counter
		NxtR = NxtI % N,       // Row (inner loop)
		NxtC = NxtI / N % N    // Column (outer loop)
	};
	static inline void eval(Mtx &mtx)
	{
		mtx[C][R] = static_cast<F>(Init);
		InitMtxImpl<Mtx, N, F, Init, NxtC, NxtR, NxtI>::eval(mtx);
	}
};


//! Used in matrix initialization
//! \remarks Makes the template appear like a function
#define InitMtxT(MtxType, Mtx, N, F, Init) InitMtx<MtxType, N, F, Init >::eval(Mtx)



//! Used in transposing a matrix; N is matrix size
template<class Mtx, unsigned N> 
class TransposeMtx
{
public:
	static inline void eval(Mtx &mtx)
	{  TransposeMtxImpl<Mtx, N, 0, 1, 0>::eval(mtx);  }
};

//! Used in transposing a matrix
template<class Mtx, unsigned N, unsigned C, unsigned R, unsigned I>
class TransposeMtxImpl
{
public:
	enum
	{
		NxtI = I + 1,
		NxtC = NxtI / N % N,
		NxtR = ( NxtI % N ) + NxtC + 1
	};
	static inline void eval(Mtx &mtx)
	{
		// [!]
		//if (R < N) Swap(mtx[C][R], mtx[R][C]);
		if (R < N) std::swap(mtx[C][R], mtx[R][C]);
		TransposeMtxImpl<Mtx, N, NxtC, NxtR, NxtI>::eval(mtx);
	}
};


//! Used in transposing a matrix
//! \remarks Makes the template appear like a function 
#define TransposeMtxT(MtxType, Mtx, N) TransposeMtx<MtxType, N >::eval(Mtx)


//! internal matrix class definition macros
#define MATRIX_COMMON_INTERNAL(dimension)                                   \
	/* the data of the matrix */											\
	union																	\
	{																		\
		struct { Vector##dimension##f col[dimension]; };					\
		struct { CMN_32F     elem[dimension*dimension]; };					\
	};																		\
																			\
	/* trivial ctor */														\
	Matrix##dimension () {}													\
	/* C array ctor */														\
	Matrix##dimension (bool colmajor, CMN_32F *entries)						\
	{																		\
		memcpy((CMN_32F *)&col, entries, dimension*dimension*sizeof(CMN_32F));	\
		if (!colmajor) transpose();											\
	}																		\
	/* Array indexing */													\
	Vector##dimension##f &operator [] (CMN_32U i)						\
	{  	return(Vector##dimension##f &)col[i];   }							\
	/* Array indexing */													\
	const Vector##dimension##f &operator [] (CMN_32U i) const			\
	{  return(Vector##dimension##f &)col[i];  }								\
	/* perform a fast identity */											\
	void identity()															\
	{   IdentityMtxT(Matrix##dimension, *this, dimension);   }				\
	/* perform a fast zero */												\
	void zero()																\
	{   InitMtxT(Matrix##dimension, *this, dimension, CMN_32F, 0);  }			\
	/* perform a fast transpose */											\
	void transpose()														\
	{   TransposeMtxT(Matrix##dimension, *this, dimension);   }				\
	/* multiplication by a matrix */                                        \
	const Matrix##dimension operator *(const Matrix##dimension &m) const	\
	{																		\
		Matrix##dimension temp(*this);										\
		return temp*=m;														\
	}																		\
	/* multiplication by a scalar */										\
	const Matrix##dimension operator *(const CMN_32F s) const					\
	{																		\
		Matrix##dimension temp(*this);										\
		return temp*=s;														\
	}																		\
	/* division by a scalar */												\
	const Matrix##dimension operator /(const CMN_32F s) const					\
	{																		\
		Matrix##dimension temp(*this);										\
		return temp/=s;														\
	}																		\
	Matrix##dimension(const Matrix##dimension& obj) {						\
		*this = obj;														\
	}													                    \
	Matrix##dimension& operator=(const Matrix##dimension& obj) {			\
		*this = obj;														\
	}																        \

//! external matrix class defines
#define MATRIX_COMMON_EXTERNAL(dimension)									\
/* base case specialization for Identity matrix*/							\
template<> class IdentityMtxImpl<Matrix##dimension, dimension, 0, 0, dimension*dimension>	\
{  public: static inline void eval(Matrix##dimension &) {}  };						\
/* base case specialization for initializing a matrix */					\
template<> class InitMtxImpl<Matrix##dimension, dimension, CMN_32F, 0, 0, 0, dimension*dimension>	\
{  public: static inline void eval(Matrix##dimension &) {}  };						\
/* base case specialization for transposing a matrix */						\
template<> class TransposeMtxImpl<Matrix##dimension, dimension, 0, 1, dimension*dimension>	\
{   public: static inline void eval(Matrix##dimension &) {}  };						\

} // namespace algebralinear
} // namespace CmnMath

#endif