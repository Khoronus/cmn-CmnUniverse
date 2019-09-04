/**
* @file vector_operation.hpp
* @brief Class to perform vector operation over non structured data.
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
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_VECTOROPERATION_HPP__
#define CMNMATH_GEOMETRY_VECTOROPERATION_HPP__

#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{

///* a = b - c */
//#define vector(a,b,c) \
//	(a)[0] = (b)[0] - (c)[0];	\
//	(a)[1] = (b)[1] - (c)[1];	\
//	(a)[2] = (b)[2] - (c)[2];
//
//#define crossProduct(a,b,c) \
//	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
//	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
//	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];
//
//// dot
//#define innerProduct(v,q) \
//	((v)[0] * (q)[0] + \
//	(v)[1] * (q)[1] + \
//	(v)[2] * (q)[2])


/** @brief Class to perform elementary operations on a vector.
           _Ty can be float[], or vector
*/
template <typename _Ty>
class VectorOperation
{
public:

	/* a = b - c */
	static void vector(_Ty a, _Ty b, _Ty c) {
		(c)[0] = (a)[0] - (b)[0];
		(c)[1] = (a)[1] - (b)[1];
		(c)[2] = (a)[2] - (b)[2];
	}

	/* a = b - c */
	static void cross(_Ty a, _Ty b, _Ty c) {
		(c)[0] = (a)[1] * (b)[2] - (b)[1] * (a)[2];
		(c)[1] = (a)[2] * (b)[0] - (b)[2] * (a)[0];
		(c)[2] = (a)[0] * (b)[1] - (b)[0] * (a)[1];
	}

	/* a = b - c */
	static CMN_32F dotf(_Ty v, _Ty q) {
		return ((v)[0] * (q)[0] + (v)[1] * (q)[1] + (v)[2] * (q)[2]);
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_VECTOROPERATION_HPP__ */
