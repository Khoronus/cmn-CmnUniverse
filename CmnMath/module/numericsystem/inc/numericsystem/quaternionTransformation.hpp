/**
* @file quaternionTransformation.hpp
* @brief Header related to the quaternion transformations.
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

#ifndef CMNMATH_NUMERICSYSTEM_QUATERNIONTRANSFORMATION_HPP__
#define CMNMATH_NUMERICSYSTEM_QUATERNIONTRANSFORMATION_HPP__

/*
 * Notes:  
 * if |q|=1 then q is a unit quaternion
 * if q=(0,v) then q is a pure quaternion 
 * if |q|=1 then q conjugate = q inverse
 * if |q|=1 then q= [cos(angle), u*sin(angle)] where u is a unit vector 
 * q and -q represent the same rotation 
 * q*q.conjugate = (q.length_squared, 0) 
 * ln(cos(theta),sin(theta)*v)= ln(e^(theta*v))= (0, theta*v)

*/

#include "quaternion.hpp"

namespace CmnMath
{
namespace numericsystem
{


/** Class to perform 3D point transformation using Quaternions
*/
template <typename _Ty>
class PointTransformation
{
public:

  /** Rotate a point around the origin with quatertions
      Angle: tilt, roll, pan in radians
  */
  static void PointRotation(const _Ty &src,
	  const _Ty &angle,
	  _Ty &dst)
  {
	  // copy the source
	  algebralinear::Vector3f src_(src.x, src.y, src.z);
	  // [!]
	  //_Ty angle_(angle);
	  algebralinear::Vector3f angle_(angle.x, angle.y, angle.z);
	  angle_ /= 2;
	  Quaternion<algebralinear::Vector3f> q(angle_);
	  q.normalize();
	  // dst = q.rotate(src);
	  algebralinear::Vector3f dst_ = q.rotate(src_);
	  dst.x = dst_.x;
	  dst.y = dst_.y;
	  dst.z = dst_.z;
  }

  /** Rotate a point around a point with quatertions
      Angle: tilt, roll, pan in radians
  */
  static void PointRotation(const _Ty &origin,
	  const _Ty &src,
	  const _Ty &angle,
	  _Ty &dst)
  {
	  // [!]
	  //_Ty angle_(angle);
	  algebralinear::Vector3f angle_(angle.x, angle.y, angle.z);
	  angle_ /= 2;
	  Quaternion<algebralinear::Vector3f> q(angle_);
	  q.normalize();
	  algebralinear::Vector3f src_(src.x - origin.x, 
		  src.y - origin.y, src.z - origin.z);
	  //src_ -= origin;
	  algebralinear::Vector3f dst_ = q.rotate(src_);
	  dst.x = dst_.x + origin.x;
	  dst.y = dst_.y + origin.y;
	  dst.z = dst_.z + origin.z;
  }
};


}	// namespace numericspace
}	// namespace CmnMath

#endif /* CMNMATH_NUMERICSYSTEM_QUATERNIONTRANSFORMATION_HPP__ */
