/**
* @file plane.hpp
* @brief Description of a plane
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

#ifndef CMNMATH_GEOMETRICPRIMITIVE_PLANE_HPP__
#define CMNMATH_GEOMETRICPRIMITIVE_PLANE_HPP__

#include <vector>
#include <cmath>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/vector3.hpp"

namespace CmnMath
{
namespace geometricprimitive
{

//! a plane
class Plane
{
public:
	algebralinear::Vector3f p;   //!< a point on the plane
	algebralinear::Vector3f n;   //!< the normal to the plane


	Plane() {}
	Plane(const algebralinear::Vector3f &P, const algebralinear::Vector3f &N) : p(P), n(N) {}
	Plane(const algebralinear::Vector3f &P1, const algebralinear::Vector3f &P2, const algebralinear::Vector3f &P3) : p(P1), n(algebralinear::Vector3f((P2 - P1) % (P3 - P1)).normalized()) {}

	//! It sets the plane params
	void set(const algebralinear::Vector3f &P1, const algebralinear::Vector3f &P2, const algebralinear::Vector3f &P3) {
		p = P1;
		n = algebralinear::Vector3f((P2 - P1) % (P3 - P1)).normalized();
	}

	//! returns the distance from this plane to a point
	CMN_32F distance_squared(const algebralinear::Vector3f &P) const
	{
		return ((algebralinear::Vector3f)(P - p)).projected(n).length_squared();
	}

	//! returns the distance from this plane to a point
	CMN_32F distance(const algebralinear::Vector3f &P) const
	{
		return ((algebralinear::Vector3f)(P - p)).projected(n).length();
	}

	//! returns the angle between 2 planes with arbitrary length normals
	CMN_32F angle(const Plane &p) const
	{
		return algebralinear::Vector3f::angle(n, p.n);
	}

	//! returns the angle between 2 planes with normalized normals
	CMN_32F angle_normalized(const Plane &p) const
	{
		return algebralinear::Vector3f::angle_normalized(n, p.n);
	}
};


} // namespace geometricprimitive
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRICPRIMITIVE_PLANE_HPP__ */