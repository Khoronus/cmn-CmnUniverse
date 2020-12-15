/**
* @file normal_threedim_surface.hpp
* @brief Header to class to estimate the normal of a 3D plane
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

#ifndef CMNMATH_GEOMETRY_NORMALTHREEDIMTHREEDIMSURFACE_HPP__
#define CMNMATH_GEOMETRY_NORMALTHREEDIMTHREEDIMSURFACE_HPP__

namespace CmnMath
{
namespace geometry
{

/** @brief Class to calculate the normal of a plane
*/
template <typename _Ty3>
class Normal
{
public:

	//  Modified from http://www.fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf
	static _Ty3 calc(const _Ty3 &p1, const _Ty3 &p2, const _Ty3 &p3)
	{
		_Ty3 V1 = (p2 - p1);
		_Ty3 V2 = (p3 - p1);
		_Ty3 surfaceNormal;
		surfaceNormal.x = (V1.y*V2.z) - (V1.z - V2.y);
		surfaceNormal.y = -((V2.z * V1.x) - (V2.x * V1.z));
		surfaceNormal.z = (V1.x*V2.y) - (V1.y*V2.x);


		// Dont forget to normalize if needed
		normalize(surfaceNormal);
		return surfaceNormal;
	}

	/** https://math.stackexchange.com/questions/1330210/how-to-check-if-a-point-is-in-the-direction-of-the-normal-of-a-plane
	*/
	[[deprecated("One line function. It will be removed. Please use: n.dot(p - a)")]]
	static float direction(const _Ty3 &n, const _Ty3 &p, const _Ty3 &a) {
		_Ty3 pp = p, aa = a, nn = n;
		return nn.dot(pp - aa);
	}

private:

	static void normalize(_Ty3 &v3) {

		double length = sqrt(v3.x*v3.x + v3.y*v3.y + v3.z*v3.z);

		v3.x = v3.x / length;
		v3.y = v3.y / length;
		v3.z = v3.z / length;
	}


	static _Ty3 cross(const _Ty3 &v3, const _Ty3 &rhs)
	{
		return _Ty3(v3.y*rhs.z - v3.z*rhs.y,
			v3.z*rhs.x - v3.x*rhs.z,
			v3.x*rhs.y - v3.y*rhs.x);
	}


	//static void computePlane(_Ty3 &A, _Ty3 &B, _Ty3 &C)
	//{
	//	_Ty3 N = (A - B) % (B - C); //perform cross product of two lines on plane
	//	if (N.getMagnitude() > 0)
	//	{
	//		N.normalize();  //normalize
	//		m_n = N;         //assign new normal to member normal
	//		m_d = n * A;   //offset plane from origin
	//	}
	//}

	/**
	https://stackoverflow.com/questions/2582367/c-opengl-how-to-find-normalized-vectors-for-a-quad
	https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
	Newell's method
	*/
	static _Ty3 normal(_Ty3 &A, _Ty3 &B, _Ty3 &C) {
		_Ty3 vertex[3] = { A, B, C };
		_Ty3 normal(0, 0, 0);

		for (int i = 0; i<4; i++)
		{
			normal += cross(vertex[i], vertex[(i + 1) % 4]); // cross product
		}
		normalize(normal);
		// normal is the unit normal to the quad
		return normal;
	}

};

} // namespace geometry
} // namespace CmnMath

#endif // CMNMATH_GEOMETRY_NORMALTHREEDIMTHREEDIMSURFACE_HPP__
