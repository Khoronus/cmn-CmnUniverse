/**
* @file transform_twodim_triangle.hpp
* @brief Perform a transformation over a triangle in a 3D space.
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

#ifndef CMNMATH_GEOMETRY_TRANSFORMTWODIMTRIANGLE_HPP__
#define CMNMATH_GEOMETRY_TRANSFORMTWODIMTRIANGLE_HPP__

#include <cmath>
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"
#include "vector_operation_xyz.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to perform a remap coordinate from a space to another.
*/
template <typename _Ty1, typename _Ty2>
//class transform_twodim_triangle
class TransformTwoDimTriangle
{

public:

	/**

		@param[in] p1 3D Vetex coordinate of a triangle.
		@param[in] p2 3D Vetex coordinate of a triangle.
		@param[in] p3 3D Vetex coordinate of a triangle.
		@param[in] f Point to map in uv coordinate
		@param[in] uv1 2D Vertex in uv map related to p1.
		@param[in] uv2 2D Vertex in uv map related to p2.
		@param[in] uv3 2D Vertex in uv map related to p3.
		@param[out] uv UV coordinate of the point f.

	@link http://answers.unity3d.com/questions/383804/calculate-uv-coordinates-of-3d-point-on-plane-of-m.html
	*/
	static void XYZ2UV(_Ty1 &p1, _Ty1 &p2, _Ty1 &p3, _Ty1 &f,
		_Ty2 &uv1, _Ty2 &uv2, _Ty2 &uv3, _Ty2 &uv)
	{
		// calculate vectors from point f to vertices p1, p2 and p3:
		_Ty1 f1 = p1 - f;
		_Ty1 f2 = p2 - f;
		_Ty1 f3 = p3 - f;
		// calculate the areas and factors (order of parameters doesn't matter):
		float a = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>((p1 - p2).cross(p1 - p3)); // main triangle area a
		float a1 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f2.cross(f3)) / a; // p1's triangle area / a
		float a2 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f3.cross(f1)) / a; // p2's triangle area / a
		float a3 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f1.cross(f2)) / a; // p3's triangle area / a
		// find the uv corresponding to point f (uv1/uv2/uv3 are associated to p1/p2/p3):
		uv = uv1 * a1 + uv2 * a2 + uv3 * a3;
	}


	static void XYZ2UV(std::vector<_Ty1> &p, _Ty1 &f,
		std::vector<_Ty2> &uv, _Ty2 &uvout)
	{
		// calculate vectors from point f to vertices p1, p2 and p3:
		_Ty1 f1 = p[0] - f;
		_Ty1 f2 = p[1] - f;
		_Ty1 f3 = p[2] - f;
		// calculate the areas and factors (order of parameters doesn't matter):
		float a = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>((p[0] - p[1]).cross(p[0] - p[2])); // main triangle area a
		float a1 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f2.cross(f3)) / a; // p1's triangle area / a
		float a2 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f3.cross(f1)) / a; // p2's triangle area / a
		float a3 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f1.cross(f2)) / a; // p3's triangle area / a
		// find the uv corresponding to point f (uv1/uv2/uv3 are associated to p1/p2/p3):
		uvout = uv[0] * a1 + uv[1] * a2 + uv[2] * a3;
	}

	static void XYZ2UV(const std::vector<_Ty1> &p, const _Ty1 &f,
		const std::vector<_Ty2> &uv, _Ty2 &uvout)
	{
		// calculate vectors from point f to vertices p1, p2 and p3:
		_Ty1 f1 = p[0] - f;
		_Ty1 f2 = p[1] - f;
		_Ty1 f3 = p[2] - f;
		// calculate the areas and factors (order of parameters doesn't matter):
		float a = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>((p[0] - p[1]).cross(p[0] - p[2])); // main triangle area a
		float a1 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f2.cross(f3)) / a; // p1's triangle area / a
		float a2 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f3.cross(f1)) / a; // p2's triangle area / a
		float a3 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(f1.cross(f2)) / a; // p3's triangle area / a
		// find the uv corresponding to point f (uv1/uv2/uv3 are associated to p1/p2/p3):
		uvout = uv[0] * a1 + uv[1] * a2 + uv[2] * a3;
	}


	/** Generic solution for the XYZ to UV transformation.
	 
		@param[in] p1 3D Vetex coordinate of a triangle.
		@param[in] p2 3D Vetex coordinate of a triangle.
		@param[in] p3 3D Vetex coordinate of a triangle.
		@param[in] f Point to map in uv coordinate
		@param[in] uv1 2D Vertex in uv map related to p1.
		@param[in] uv2 2D Vertex in uv map related to p2.
		@param[in] uv3 2D Vertex in uv map related to p3.
		@param[out] uv UV coordinate of the point f.

	    @link http://answers.unity3d.com/questions/383804/calculate-uv-coordinates-of-3d-point-on-plane-of-m.html
	*/
	static void XYZ2UV_generic(_Ty1 &p1, _Ty1 &p2, _Ty1 &p3, _Ty1 &f,
		_Ty2 &uv1, _Ty2 &uv2, _Ty2 &uv3, _Ty2 &uv)
	{
		// calculate vectors from point f to vertices p1, p2 and p3:
		_Ty1 f1 = p1 - f;
		_Ty1 f2 = p2 - f;
		_Ty1 f3 = p3 - f;
		// calculate the areas (parameters order is essential in this case):
		_Ty1 va = (p1 - p2).cross(p1 - p3); // main triangle cross product
		_Ty1 va1 = f2.cross(f3); // p1's triangle cross product
		_Ty1 va2 = f3.cross(f1); // p2's triangle cross product
		_Ty1 va3 = f1.cross(f2); // p3's triangle cross product
		float a = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(va); // main triangle area
		// calculate barycentric coordinates with sign:
		float a1 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(va1) / a * signf(va.dot(va1));
		float a2 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(va2) / a * signf(va.dot(va2));
		float a3 = VectorOperationXYZ<_Ty1>::template magnitude_3df<float>(va3) / a * signf(va.dot(va3));
		// find the uv corresponding to point f (uv1/uv2/uv3 are associated to p1/p2/p3):
		uv = uv1 * a1 + uv2 * a2 + uv3 * a3;
	}

private:

	static float signf(float v)
	{
		return v >= 0 ? 1 : -1;
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_TRANSFORMTWODIMTRIANGLE_HPP__ */
