///	@file Line2.hpp
///	Describe specific vectors for image operations. Vectors are 2,3 or 4 dimensions.
/// Originally based on the work of
/// Will Perone (will.perone@gmail.com)
///	@brief Vectors for image operations.


#ifndef CMNMATH_GEOMETRICPRIMITIVE_LINE2D_HPP__
#define CMNMATH_GEOMETRICPRIMITIVE_LINE2D_HPP__

#include <vector>
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometricprimitive
{


//! a line in 2d space
class Line2D
{
public:

	algebralinear::Vector2f p;   //!< a point on the line
	algebralinear::Vector2f dir; //!< the direction of the line


	Line2D() {}
	Line2D(const algebralinear::Vector2f &P, 
		const algebralinear::Vector2f &Dir) : p(P), dir(Dir) {}

	//! returns the distance from this line to a point
	//float distance(const vector2f &P)
	//{	return ((vector3f)(dir%(P-p))).length()/dir.length();	}

	//! returns the angle between l and this line
	float angle(const Line2D &l)
	{	return (CMN_32F)acos((dir*l.dir)/(dir.length()*l.dir.length()));  }
};


//! a ray in 2d space
class Ray2D: public Line2D
{
};


//! a line segment in 2d space
class Lineseg2: public Line2D
{
public:
	Lineseg2() {}
	Lineseg2(const algebralinear::Vector2f &P1, 
		const algebralinear::Vector2f &P2) : Line2D(P1, P2 - P1) {}
};

} // namespace geometricprimitive
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRICPRIMITIVE_LINE2D_HPP__ */