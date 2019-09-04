///	@file Line3.hpp
///	Describe specific vectors for image operations. Vectors are 2,3 or 4 dimensions.
/// Originally based on the work of
/// Will Perone (will.perone@gmail.com)
///	@brief Vectors for image operations.


#ifndef CMNMATH_GEOMETRICPRIMITIVE_LINE3D_HPP__
#define CMNMATH_GEOMETRICPRIMITIVE_LINE3D_HPP__

#include <vector>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometricprimitive
{


//! a line in 3d space
class Line3D
{
public:
	algebralinear::Vector3f p;   //!< a point on the line
	algebralinear::Vector3f dir; //!< the direction of the line


	Line3D() {}
	Line3D(const algebralinear::Vector3f &P, 
		const algebralinear::Vector3f &Dir) : p(P), dir(Dir) {}

	//! returns the distance from this line to a point
	float distance(const algebralinear::Vector3f &P) {
		return ((algebralinear::Vector3f)(dir % (P - p))).length() / dir.length();
	}

	//! returns the angle between l and this line
	float angle(const Line3D &l)
	{	return (CMN_32F)acos((dir*l.dir)/(dir.length()*l.dir.length()));	}	
};


//! a ray in 3d space
class Ray3D: public Line3D
{
public:
};


//! a line segment in 3d space
class Lineseg3: public Line3D
{
public:
	Lineseg3() {}
	Lineseg3(const algebralinear::Vector3f &P1, 
		const algebralinear::Vector3f &P2) : Line3D(P1, P2 - P1) {}
};


} // namespace geometricprimitive
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRICPRIMITIVE_LINE3D_HPP__ */