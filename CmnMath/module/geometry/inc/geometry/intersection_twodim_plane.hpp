/**
* @file intersection_twodim_plane.hpp
* @brief Header of all the files related to the statistics
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
* @version 0.2.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_INTERSECTIONTWODIMPLANE_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONTWODIMPLANE_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "algebralinear/algebralinear_algebralinear.hpp"
#include "geometricprimitive/geometricprimitive_geometricprimitive.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with one dimension geometrical
           structures.

	Class to perform interpolations with one dimension geometrical
	structures.
*/
template <typename _Ty>
class IntersectionTwoDimPlane
{
public:

	/** Given two points of a line and three points of a plane, calculate the intersection point position
	line: x0,y0,z0,x1,y1,z1 (known points)
	plane: x0,y0,z0,x1,y1,z1,x2,y2,z2
	intersection: x0,y0,z0
		@src: https://en.wikipedia.org/wiki/line-plane_intersection
	*/
	static void RayPlane(CMN_32F *line, CMN_32F *plane, CMN_32F *intersection)
	{
		CMN_32F matA[9] = { line[0] - line[3], plane[3] - plane[0], plane[6] - plane[0],
			line[1] - line[4], plane[4] - plane[1], plane[7] - plane[1],
			line[2] - line[5], plane[5] - plane[2], plane[8] - plane[2] };
		CMN_32F matB[3] = { line[0] - plane[0], line[1] - plane[1], line[2] - plane[2] };
		CMN_32F matO[3];

		CMN_32F matY[9];
		algebralinear::MatrixOperation::mat_inv(matA, 3, matY);
		algebralinear::MatrixOperation::mat_mul(matY, matB, matO, 3, 3, 3, 1);

		intersection[0] = line[0] + (line[3] - line[0]) * matO[0];
		intersection[1] = line[1] + (line[4] - line[1]) * matO[0];
		intersection[2] = line[2] + (line[5] - line[2]) * matO[0];
	}

	/** @brief Wrapper to the ray-plane intersection wikipedia version
	*/
	static CMN_32S RayPlane(const _Ty &line0,
		const _Ty &line1,
		const std::vector<_Ty> &vplane,
		_Ty &intersection)
	{
		CmnMath::CMN_32F line[6], plane[9], intersection_tmp[3];
		line[0] = line0.x; line[1] = line0.y; line[2] = line0.z;
		line[3] = line1.x; line[4] = line1.y; line[5] = line1.z;
		plane[0] = vplane[0].x; plane[1] = vplane[0].y; plane[2] = vplane[0].z;
		plane[3] = vplane[1].x; plane[4] = vplane[1].y; plane[5] = vplane[1].z;
		plane[6] = vplane[2].x; plane[7] = vplane[2].y; plane[8] = vplane[2].z;
		RayPlane(line, plane, intersection_tmp);
		intersection.x = intersection_tmp[0];
		intersection.y = intersection_tmp[1];
		intersection.z = intersection_tmp[2];

		return 1;
	}


	// intersect3D_SegmentPlane(): find the 3D intersection of a segment and a plane
	//    Input:  S = a segment, and Pn = a plane = {Point V0;  Vector n;}
	//    Output: *I0 = the intersect point (when it exists)
	//    Return: 0 = disjoint (no intersection)
	//            1 =  intersection in the unique point *I0
	//            2 = the  segment lies in the plane
	template <typename REAL>
	static int intersect3D_SegmentPlane(CmnMath::geometricprimitive::Lineseg3 &S,
		CmnMath::geometricprimitive::Plane &Pn,
		REAL kSmallNum,
		CmnMath::algebralinear::Vector3f &I)
	{
		CmnMath::algebralinear::Vector3f    u = S.dir;
		CmnMath::algebralinear::Vector3f    w = S.p - Pn.p;

		REAL     D = CmnMath::algebralinear::AlgebraOperation3D<CmnMath::algebralinear::Vector3f, REAL>::dot(Pn.n, u);
		REAL     N = -CmnMath::algebralinear::AlgebraOperation3D<CmnMath::algebralinear::Vector3f, REAL>::dot(Pn.n, w);

		if (fabs(D) < kSmallNum) {           // segment is parallel to plane
			if (N == 0)                      // segment lies in plane
				return 2;
			else
				return 0;                    // no intersection
		}
		// they are not parallel
		// compute intersect param
		REAL sI = N / D;
		if (sI < 0 || sI > 1)
			return 0;                        // no intersection

		I = S.p + u * sI;                  // compute segment intersect point
		return 1;
	}


	/** Calculate the line plane intersection given three points on the plane
		and two points of the line
		src: http://mathworld.wolfram.com/Line-PlaneIntersection.html

		@warning Error. Wrong implementation of the matrix division
	*/
	//static CMN_32S RayPlane(const _Ty &line0,
	//	const _Ty &line1,
	//	const std::vector<_Ty> &plane,
	//	_Ty &intersection)
	//{
	//	if (plane.size() < 3) return 0;
	//	CMN_64F line_[6] = { line0.x, line0.y, line0.z, line1.x, line1.y, line1.z };
	//	CMN_64F plane_[9] = { plane[0].x, plane[0].y, plane[0].z,
	//		plane[1].x, plane[1].y, plane[1].z,
	//		plane[2].x, plane[2].y, plane[2].z };
	//	CMN_64F intersection_[3] = { 0 };

	//	//algebralinear::Matrix4 m(1, 1, 1, 1,
	//	//	plane_[0], plane_[3], plane_[6], line_[0],
	//	//	plane_[1], plane_[4], plane_[7], line_[1],
	//	//	plane_[2], plane_[5], plane_[8], line_[2]);
	//	//m.transpose();
	//	//CMN_64F d1 = m.determinant();
	//	//algebralinear::Matrix4 m2(1, 1, 1, 0,
	//	//	plane_[0], plane_[3], plane_[6], line_[3] - line_[0],
	//	//	plane_[1], plane_[4], plane_[7], line_[4] - line_[1],
	//	//	plane_[2], plane_[5], plane_[8], line_[5] - line_[2]);
	//	//m2.transpose();

	//	algebralinear::Matrix4 m(1, plane_[0], plane_[1], plane_[2],
	//		1, plane_[3], plane_[4], plane_[5],
	//		1, plane_[6], plane_[7], plane_[8],
	//		1, line_[0], line_[1], line_[2]);
	//	CMN_64F d1 = m.determinant();
	//	algebralinear::Matrix4 m2(1, plane_[0], plane_[1], plane_[2],
	//		1, plane_[3], plane_[4], plane_[5],
	//		1, plane_[6], plane_[7], plane_[8], 
	//		0, line_[0] - line_[3], line_[1] - line_[4], line_[2] - line_[5]);
	//		//0, line_[3] - line_[0], line_[4] - line_[1], line_[5] - line_[2]);

	//	CMN_64F d2 = m2.determinant();

	//	if (d2 == 0) return 0;
	//	CMN_32F t = -d1 / d2;

	//	CMN_32F x = line_[0] + (line_[3] - line_[0]) * t;
	//	CMN_32F y = line_[1] + (line_[4] - line_[1]) * t;
	//	CMN_32F z = line_[2] + (line_[5] - line_[2]) * t;

	//	intersection.x = x;
	//	intersection.y = y;
	//	intersection.z = z;
	//	return 1;
	//}

};




} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONTWODIMPLANE_HPP__ */
