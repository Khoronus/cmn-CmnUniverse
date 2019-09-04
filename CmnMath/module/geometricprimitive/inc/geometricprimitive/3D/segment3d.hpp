/**
* @file segment3d.hpp
* @brief Header of all the files related to the segment3D
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


#ifndef CMNMATH_GEOMETRICPRIMITIVE_SEGMENT3D_HPP__
#define CMNMATH_GEOMETRICPRIMITIVE_SEGMENT3D_HPP__

#include <vector>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometricprimitive
{


//! a segment in 3d space
class Segment3D
{
public:
	algebralinear::Vector3f p0; //!< a vertex of the segment
	algebralinear::Vector3f p1; //!< a vertex of the segment


	Segment3D() {}
	Segment3D(const algebralinear::Vector3f &P0,
		const algebralinear::Vector3f &P1) : p0(P0), p1(P1) {}
};

} // namespace geometricprimitive
} // namespace CmnMath

#endif // CMNMATH_GEOMETRICPRIMITIVE_SEGMENT3D_HPP__