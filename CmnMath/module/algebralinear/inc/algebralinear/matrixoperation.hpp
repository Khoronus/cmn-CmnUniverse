/**
* @file matrixoperation.hpp
* @brief Class to perform some operations with matrix
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

#ifndef CMNMATH_ALGEBRALINEAR_CMNMATH_HPP__
#define CMNMATH_ALGEBRALINEAR_CMNMATH_HPP__

#include <memory>
#include <cmath>
#include <vector>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace algebralinear
{


/** Class to provide mat calculation
It provides the math transformation for a 3D point.
This solution use Euler math.
TODO: Implement a quaternion solution

// ###################
//	MATRIX FUNCTIONS
// ###################

*/
class MatrixOperation
{
public:

	// calculate the cofactor of element (row,col)
	static CMN_32S mat_cofactor(CMN_32F *src, CMN_32F *dest, CMN_32S row, CMN_32S col, CMN_32S order)
	{
		// indicate which col and row is being copied to dest
		CMN_32S colCount = 0, rowCount = 0;

		for (CMN_32S i = 0; i < order; ++i)
		{
			if (i != row)
			{
				colCount = 0;
				for (CMN_32S j = 0; j < order; ++j)
				{
					// when j is not the element
					if (j != col)
					{
						dest[rowCount * (order - 1) + colCount] = src[i * order + j];
						colCount++;
					}
				}
				rowCount++;
			}
		}

		return 1;
	}

	// Calculate the determinant recursively.
	static CMN_32F mat_det33(std::vector<CMN_32F> &a)
	{
		if (a.size() != 9) return 0;
		return a[0] * (a[4] * a[8] - a[5] * a[7]) -
			a[2] * (a[3] * a[8] - a[5] * a[6]) +
			a[2] * (a[3] * a[7] - a[4] * a[6]);
	}


	// Calculate the determinant recursively.
	static CMN_32F mat_det(CMN_32F *mat, CMN_32S order)
	{
		// the determinant value
		CMN_32F det = 0;

		// allocate the cofactor matrix
		CMN_32F *minor;

		//DisplayMatrix(mat, order, order, "CD");
		// order must be >= 0
		// stop the recursion when matrix is a single element
		if (order == 1)
			return mat[0 * order + 0];

		// allocate the cofactor matrix
		minor = new CMN_32F[(order - 1)*(order - 1)];
		memset(minor, 0, sizeof(CMN_32F) * (order - 1)*(order - 1));

		for (CMN_32S i = 0; i < order; ++i)
		{
			// get minor of element (0,i)
			mat_cofactor(mat, minor, 0, i, order);
			// the recusion is here!
			//CMN_8S buf[256];
			//sprintf(buf, "Minor %i", order);
			//DisplayMatrix(minor, order, order, buf);

			det += static_cast<CMN_32F>((i % 2 == 1 ? -1.0 : 1.0) * mat[0 * order + i] * mat_det(minor, order - 1));
			//det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
		}

		// release memory
		delete[] minor;

		return det;
	}

	/** Transpose matrix
	*/
	static void mat_transpose(CMN_32F *matA, CMN_32F *matC, CMN_32S r1, CMN_32S c1)
	{
		CMN_32S y, x;
		for (y = 0; y < r1; ++y)
		{
			for (x = 0; x < c1; ++x)
			{
				matC[x * r1 + y] = matA[y * c1 + x];
			}
		}
	}

	/** Sum matrix
	*/
	void mat_sum(CMN_32F *matA, CMN_32F *matB, CMN_32F *matC, CMN_32S r1, CMN_32S c1, CMN_32S r2, CMN_32S c2)
	{
		CMN_32S y, x;

		if (r1 != r2 || c1 != c2) return;
		for (y = 0; y < r1; ++y)
		{
			for (x = 0; x < c1; ++x)
			{
				matC[y * c1 + x] = matA[y * c1 + x] + matB[y * c1 + x];
			}
		}
	}

	/** Subtraction matrix
	*/
	static void mat_sub(CMN_32F *matA, CMN_32F *matB, CMN_32F *matC, CMN_32S r1, CMN_32S c1, CMN_32S r2, CMN_32S c2)
	{
		CMN_32S y, x;

		if (r1 != r2 || c1 != c2) return;
		for (y = 0; y < r1; ++y)
		{
			for (x = 0; x < c1; ++x)
			{
				matC[y * c1 + x] = matA[y * c1 + x] - matB[y * c1 + x];
			}
		}
	}


	/** Function to perform matrix multiplication with squared matrix
	*/
	static void matmul(CMN_32F *matA, CMN_32F *matB, CMN_32F *matC, CMN_32S N)
	{
		CMN_32S i, k, j;
		for (i = 0; i < N; ++i)
		{
			CMN_32F *iRowA = &matA[i * N];
			CMN_32F *iRowC = &matC[i * N];
			for (k = 0; k < N; ++k)
			{
				CMN_32F *kRowB = &matB[k * N];
				CMN_32F ikA = iRowA[k];
				for (j = 0; j < N; ++j)
					iRowC[j] += ikA * kRowB[j];
			}
		}
	}

	/** Function to perform matrix multiplication with squared matrix
	@remarks Check Tiling method.
	*/
	static void matmul_tile(CMN_32F *matA, CMN_32F *matB, CMN_32F *matC, CMN_32S N, CMN_32S tile_size)
	{
		CMN_32S i, k, j, ii, jj, kk;
		for (i = 0; i < N; i += tile_size)
		{
			for (j = 0; j < N; j += tile_size)
			{
				for (k = 0; k < N; k += tile_size)
				{
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
					for (ii = i; ii < (std::fmin)(i + tile_size, N); ++ii)
					{
						for (jj = j; jj < (std::fmin)(j + tile_size, N); ++jj)
						{
							for (kk = k; kk < (std::fmin)(k + tile_size, N); ++kk)
							{
								matC[ii*N + jj] += matA[ii*N + kk] * matB[kk*N + jj];
							}
						}
					}
#else
					for (ii = i; ii < (std::min)(i + tile_size, N); ++ii)
					{
						for (jj = j; jj < (std::min)(j + tile_size, N); ++jj)
						{
							for (kk = k; kk < (std::min)(k + tile_size, N); ++kk)
							{
								matC[ii*N + jj] += matA[ii*N + kk] * matB[kk*N + jj];
							}
						}
					}
#endif

				}
			}
		}
	}

	/** Function to perform matrix multiplication
	@remarks For bigger matrix, use Tilng method
	wikipedia: Matrix multiplication
	www.daniweb.com: optimizing matrix multiplication
	*/
	static void mat_mul(CMN_32F *matA, CMN_32F *matB, CMN_32F *matC, CMN_32S r1, CMN_32S c1, CMN_32S r2, CMN_32S c2)
	{
		CMN_32S y, x;

		// If the matrix are squared, uses a faster implementation
		if (r1 == r2 && c1 == c2 && r1 == c1)
		{
			matmul(matA, matB, matC, r1);
			return;
		}

		if (c1 != r2) return;
		for (y = 0; y < r1; ++y)
		{
			for (x = 0; x < c2; ++x)
			{
				CMN_32F sum = 0;
				CMN_32S k = 0;
				//cout << x << "-" << y << endl;
				for (k = 0; k < c1; ++k)
				{
					//	cout << " -> " << matA[y * c1 + k] << " * " << matB[k * c2 + x] << " - " << matA[y * c1 + k] * matB[k * c2 + x] << " " << sum << endl;
					sum += matA[y * c1 + k] * matB[k * c2 + x];
				}
				matC[y * c2 + x] = sum;
			}
		}
	}



	// matrix inversion
	// the result is put in Y
	static void mat22_inv(CMN_32F *A, CMN_32F *Y)
	{
		CMN_32F det_1;
		CMN_32F det = A[0] * A[3] - A[1] * A[2];
		if (det == 0) return;
		det_1 = 1.0f / det;

		Y[0] = A[3] * det_1;
		Y[1] = -A[1] * det_1;
		Y[2] = -A[2] * det_1;
		Y[3] = A[0] * det_1;
	}


	// matrix inversion
	// the result is put in Y
	//  0 1 2
	//  3 4 5
	//  6 7 8
	static void mat33_inv(CMN_32F *A, CMN_32F *Y)
	{
		CMN_32F det_1;
		CMN_32F det = A[0] * (A[8] * A[4] - A[7] * A[5]) - A[3] * (A[9] * A[1] - A[7] * A[2]) + A[6] * (A[5] * A[1] - A[4] * A[2]);
		if (det == 0) return;
		det_1 = 1.0f / det;

		Y[0] = (A[9] * A[4] - A[7] * A[5]) * det_1;
		Y[1] = -(A[9] * A[1] - A[7] * A[2]) * det_1;
		Y[2] = (A[5] * A[1] - A[4] * A[2]) * det_1;
		Y[3] = -(A[9] * A[3] - A[6] * A[5]) * det_1;
		Y[4] = (A[9] * A[0] - A[6] * A[2]) * det_1;
		Y[5] = -(A[5] * A[0] - A[3] * A[2]) * det_1;
		Y[6] = (A[7] * A[3] - A[6] * A[4]) * det_1;
		Y[7] = -(A[7] * A[0] - A[6] * A[1]) * det_1;
		Y[8] = (A[4] * A[0] - A[3] * A[1]) * det_1;
	}

	// square matrix inversion
	// the result is put in Y
	static void mat_inv(CMN_32F *A, CMN_32S order, CMN_32F *Y)
	{
		// get the determinant of a
		CMN_32F det = 1 / mat_det(A, order);

		//cout << "D: " << det << endl;
		//return;

		// memory allocation
		CMN_32F *minor = new CMN_32F[(order - 1)*(order - 1)];
		memset(minor, 0, sizeof(CMN_32F) * (order - 1)*(order - 1));

		for (CMN_32S j = 0; j<order; ++j)
		{
			for (CMN_32S i = 0; i<order; ++i)
			{
				// get the co-factor (matrix) of A(j,i)
				mat_cofactor(A, minor, j, i, order);
				//DisplayMatrix(minor, order - 1, order - 1, "GetMinor");
				Y[i * order + j] = det*mat_det(minor, order - 1);
				if ((i + j) % 2 == 1)
					Y[i * order + j] = -Y[i * order + j];
			}
		}

		// release memory
		//delete [] minor[0];
		delete[] minor;
	}


	/** C display matrix content
	*/
	static void DisplayMatrix(CMN_32F *mat, CMN_32S r, CMN_32S c, CMN_8S *header)
	{
		printf("%s\n", header);
		CMN_32S y, x;
		for (y = 0; y < r; ++y)
		{
			for (x = 0; x < c; ++x)
			{
				printf("%5.3f ", mat[y * c + x]);
			}
			printf("\n");
		}
	}
};


} // namespace algebralinear
} // namespace CmnMath

#endif /* CMNMATH_ALGEBRALINEAR_CMNMATH_HPP__ */
