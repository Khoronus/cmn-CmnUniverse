/**
* @file sample_geometry_geometry.cpp
* @brief Sample geometry.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.2.0.0
*
*/

#include <iostream>
#include <cmath>

#include "geometricprimitive/geometricprimitive_geometricprimitive.hpp"
#include "geometry/geometry_geometry.hpp"

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif

namespace
{


//// intersect3D_SegmentPlane(): find the 3D intersection of a segment and a plane
////    Input:  S = a segment, and Pn = a plane = {Point V0;  Vector n;}
////    Output: *I0 = the intersect point (when it exists)
////    Return: 0 = disjoint (no intersection)
////            1 =  intersection in the unique point *I0
////            2 = the  segment lies in the plane
//int intersect3D_SegmentPlane(CmnMath::geometricprimitive::Lineseg3 &S, 
//	CmnMath::geometricprimitive::Plane &Pn, 
//	float kSmallNum,
//	CmnMath::algebralinear::Vector3f &I)
//{
//	CmnMath::algebralinear::Vector3f    u = S.dir;
//	CmnMath::algebralinear::Vector3f    w = S.p - Pn.p;
//
//	float     D = CmnMath::algebralinear::AlgebraOperation3D<CmnMath::algebralinear::Vector3f, float>::dot(Pn.n, u);
//	float     N = -CmnMath::algebralinear::AlgebraOperation3D<CmnMath::algebralinear::Vector3f, float>::dot(Pn.n, w);
//
//	if (fabs(D) < kSmallNum) {           // segment is parallel to plane
//		if (N == 0)                      // segment lies in plane
//			return 2;
//		else
//			return 0;                    // no intersection
//	}
//	// they are not parallel
//	// compute intersect param
//	float sI = N / D;
//	if (sI < 0 || sI > 1)
//		return 0;                        // no intersection
//
//	I = S.p + u * sI;                  // compute segment intersect point
//	return 1;
//}

#ifdef USE_OPENCV

/**
Pn.n: [0.0916458,-0.389495,0.916458]
Pn.p: [-3,-2,0.1]
*/
void test_Householder() {
	cv::Mat n(3, 1, CV_32FC1);
	n.at<float>(0, 0) = 0.0916458;
	n.at<float>(1, 0) = -0.389495;
	n.at<float>(2, 0) = 0.916458;

	cv::Mat p(3, 1, CV_32FC1);
	p.at<float>(0, 0) = -3;
	p.at<float>(1, 0) = -2;
	p.at<float>(2, 0) = 0.1;

	cv::Mat w0 = n.clone();
	cv::Mat w1 = n.clone();
	w0.at<float>(0, 0) += 1;
	w1.at<float>(0, 0) -= 1;
	cv::Mat w = w1.clone();

	cv::Mat I = cv::Mat::eye(3, 3, CV_32FC1);
	cv::Mat A = 2 * w * w.t();
	cv::Mat B = w.t() * w;
	std::cout << "A: " << A << std::endl;
	std::cout << "B: " << B << std::endl;
	float Bval = B.at<float>(0, 0);
	cv::Mat H = I - A / Bval;
	std::cout << "H: " << H << std::endl;

	cv::Mat u(3, 1, CV_32FC1);
	u.at<float>(0, 0) = H.at<float>(1, 0);
	u.at<float>(1, 0) = H.at<float>(1, 1);
	u.at<float>(2, 0) = H.at<float>(1, 2);

	cv::Mat v(3, 1, CV_32FC1);
	v.at<float>(0, 0) = H.at<float>(2, 0);
	v.at<float>(1, 0) = H.at<float>(2, 1);
	v.at<float>(2, 0) = H.at<float>(2, 2);

	std::cout << "u: " << u << std::endl;
	std::cout << "v: " << v << std::endl;

	std::cout << "P1: " << (p + u).t();
	std::cout << "P2: " << (p + v).t();
}

#endif // USE_OPENCV


/** @brief Function to test the classes and functions
*/
void test()
{
	CmnMath::algebralinear::Vector3f point(1, 5, 6);
	CmnMath::algebralinear::Vector3f start(0, 0, 0);
	CmnMath::algebralinear::Vector3f end(1, 1, 1);
	CmnMath::algebralinear::Vector3f p = CmnMath::geometry::ProjectOneDimLineXYZ< CmnMath::algebralinear::Vector3f >::point2line(point, start, end);
	std::cout << "Point coordinate: " << p << std::endl;
	CmnMath::CMN_32F distance = CmnMath::geometry::DistanceOneDimLine::point_line<CmnMath::algebralinear::Vector3f, CmnMath::CMN_32F>(point, start, end);
	std::cout << "Distance: " << distance << std::endl;
	// Test the vector operation
	auto vres1 = CmnMath::geometry::VectorOperationXYZ<CmnMath::algebralinear::Vector3f>::cross(
		CmnMath::algebralinear::Vector3f(1, 0, 0), CmnMath::algebralinear::Vector3f(0, 1, 0));
	std::cout << "Cross ProductXYZ: " << vres1 << std::endl;
	std::cout << "Dot ProductXYZ: " << CmnMath::geometry::VectorOperationXYZ<CmnMath::algebralinear::Vector3f>::dot_product<CmnMath::CMN_32F>(
		CmnMath::algebralinear::Vector3f(1, 0, 0), CmnMath::algebralinear::Vector3f(0, 1, 0)) << std::endl;
	std::cout << "MagnitudeXYZ: " << CmnMath::geometry::VectorOperationXYZ<CmnMath::algebralinear::Vector3f>::magnitude_3d<CmnMath::CMN_32F>(
		CmnMath::algebralinear::Vector3f(1, 0, 0)) << std::endl;
	auto vres2 = CmnMath::geometry::VectorOperationXYZ<CmnMath::algebralinear::Vector3f>::unit(
		CmnMath::algebralinear::Vector3f(1, 0, 0));
	std::cout << "UnitXYZ: " << vres2 << std::endl;

	// Test the vector operation
	std::vector<float> a, b, c;
	a.push_back(1); a.push_back(0); a.push_back(0);
	b.push_back(0); b.push_back(1); b.push_back(0);
	c.push_back(0); c.push_back(0); c.push_back(0);
	CmnMath::geometry::VectorOperation<std::vector<float>&>::cross(a, b, c);
	std::cout << "Cross Product: " << c[0] << " " << c[1] << " " << c[2] << std::endl;
	std::cout << "Dot Product: " << CmnMath::geometry::VectorOperation<std::vector<float>&>::dotf(a, b) << std::endl;

	// Interstection
	CmnMath::algebralinear::Vector3f pa, pb;
	CmnMath::CMN_32F mua = 0, mub = 0;
	std::cout << "Intersection: " << CmnMath::geometry::IntersectionOneDimLineXYZ<CmnMath::algebralinear::Vector3f>::line_linef(
		CmnMath::algebralinear::Vector3f(1, 1, 1), CmnMath::algebralinear::Vector3f(2, 2, 2),
		CmnMath::algebralinear::Vector3f(3, 3, -1), CmnMath::algebralinear::Vector3f(5, 5, -2), &pa, &pb, &mua, &mub) << " -> ";
	std::cout << pa << " " << pb << " " << mua << " " << mub << std::endl;

	// Intersection Ray Triangle
	{
		float p[3] = { 0, 0, 0 };
		float d[3] = { 1, 0, 0 };
		float v0[3] = { 3, -1, -2 };
		float v1[3] = { 2, -1, 1 };
		float v2[3] = { 2, 1, 1 };
		float t = 0;
		if (CmnMath::geometry::IntersectionTwoDimTriangle<float>::RayTriangle(p, d, v0, v1, v2, 0.00001f, t)) {
			std::cout << "IntersectionTwoDimTriangle::Intersect at: " << p[0] + d[0] * t << " " << p[1] + d[1] * t << " " << p[2] + d[2] * t << std::endl;
		}
	}
	{
		CmnMath::algebralinear::Vector3f p(0, 0, 0);
		CmnMath::algebralinear::Vector3f d(1, 0, 0);
		CmnMath::algebralinear::Vector3f v0(3, -1, -2);
		CmnMath::algebralinear::Vector3f v1(2, -1, 1);
		CmnMath::algebralinear::Vector3f v2(2, 1, 1);
		CmnMath::CMN_32F t = 0;
		if (CmnMath::geometry::IntersectionTwoDimTriangleXYZ<CmnMath::algebralinear::Vector3f, CmnMath::CMN_32F >::RayTriangle(p, d, v0, v1, v2, 0.00001f, false, t)) {
			std::cout << "IntersectionTwoDimTriangleXYZ::Intersect at: " << p.x + d.x * t << " " << p.y + d.y * t << " " << p.z + d.z * t << std::endl;
		}
	}
	{
		//CmnMath::algebralinear::Vector3f p(0.57, -1.19, -1.54);
		//CmnMath::algebralinear::Vector3f d(-0.52, 1.97, 0.16);
		////CmnMath::algebralinear::Vector3f v0(3, -1, -2);
		////CmnMath::algebralinear::Vector3f v1(2, -1, 1);
		////CmnMath::algebralinear::Vector3f v2(2, 1, 1);
		//CmnMath::algebralinear::Vector3f v0(0.3, 0, 0.3);
		//CmnMath::algebralinear::Vector3f v1(0.3, 0, -0.3);
		//CmnMath::algebralinear::Vector3f v2(-0.3, 0, -0.3);

		CmnMath::algebralinear::Vector3f p(-0.3711, 0.09573, -0.73223);
		CmnMath::algebralinear::Vector3f d(0.133041, 1.43129, 1.39058);
		//CmnMath::algebralinear::Vector3f v0(3, -1, -2);
		//CmnMath::algebralinear::Vector3f v1(2, -1, 1);
		//CmnMath::algebralinear::Vector3f v2(2, 1, 1);
		//CmnMath::algebralinear::Vector3f v0(-5, 2, -5);
		//CmnMath::algebralinear::Vector3f v1(5, 2, -5);
		//CmnMath::algebralinear::Vector3f v2(5, 2, 5);
		//CmnMath::algebralinear::Vector3f v0(3, 1, 2);
		//CmnMath::algebralinear::Vector3f v1(3, 1, -2);
		//CmnMath::algebralinear::Vector3f v2(3, -1, 2);
		CmnMath::algebralinear::Vector3f v0(-3, -2, 0);
		CmnMath::algebralinear::Vector3f v1(3, -2, 0);
		CmnMath::algebralinear::Vector3f v2(3, 2, 0);


		CmnMath::CMN_32F t = 0;
		std::vector<CmnMath::algebralinear::Vector3f> plane;
		plane.push_back(v0);
		plane.push_back(v1);
		plane.push_back(v2);
		CmnMath::algebralinear::Vector3f intersection;
		if (CmnMath::geometry::IntersectionTwoDimPlane<CmnMath::algebralinear::Vector3f>::RayPlane(
			p, d, plane, intersection)) {
			std::cout << "IntersectionTwoDimPlane::Intersect at: " << intersection << std::endl;
		}
		{
			CmnMath::CMN_32F line[6], plane[9], intersection[3];
			line[0] = p.x; line[1] = p.y; line[2] = p.z;
			line[3] = d.x; line[4] = d.y; line[5] = d.z;
			plane[0] = v0.x; plane[1] = v0.y; plane[2] = v0.z;
			plane[3] = v1.x; plane[4] = v1.y; plane[5] = v1.z;
			plane[6] = v2.x; plane[7] = v2.y; plane[8] = v2.z;
			CmnMath::geometry::IntersectionTwoDimPlane<CmnMath::algebralinear::Vector3f>::RayPlane(line, plane, intersection);
			std::cout << "IntersectionTwoDimPlane::Intersection: " << intersection[0] << " " << intersection[1] << " " << intersection[2] << std::endl;
		}

		// Intersection segment/plane
		// http://geomalgorithms.com/a05-_intersect-1.html
		{
			// two extreme of the segment (NOT starting point and direction)
			CmnMath::geometricprimitive::Lineseg3 S(CmnMath::algebralinear::Vector3f(0, 0, 1), CmnMath::algebralinear::Vector3f(0, 0, 0.5));
			CmnMath::geometricprimitive::Plane Pn(CmnMath::algebralinear::Vector3f(-3, -2, 0), CmnMath::algebralinear::Vector3f(3, -2, 0), CmnMath::algebralinear::Vector3f(3, 2, 0));
			CmnMath::algebralinear::Vector3f I;
			if (CmnMath::geometry::IntersectionTwoDimPlane<CmnMath::algebralinear::Vector3f>::intersect3D_SegmentPlane<float>(S, Pn, 0.00001, I)) {
				std::cout << "Intersection: " << I << std::endl;
			}
			else {
				std::cout << "Disjoint" << std::endl;
			}
		}

		// Generate 3 points of the plane
		// https://math.stackexchange.com/questions/64430/find-extra-arbitrary-two-points-for-a-plane-given-the-normal-and-a-point-that-l
		{
			// two extreme of the segment (NOT starting point and direction)
			CmnMath::geometricprimitive::Plane Pn(CmnMath::algebralinear::Vector3f(-3, -2, 0.1), CmnMath::algebralinear::Vector3f(3, -2, -.5), CmnMath::algebralinear::Vector3f(3, 2, 1.2));
			float val_min = std::abs(Pn.n.x);
			CmnMath::algebralinear::Vector3f w(1, 0, 0);
			if (std::abs(Pn.n.y) < val_min) {
				val_min = std::abs(Pn.n.y);
				w = CmnMath::algebralinear::Vector3f(0, 1, 0);
			}
			if (std::abs(Pn.n.z) < val_min) {
				val_min = std::abs(Pn.n.z);
				w = CmnMath::algebralinear::Vector3f(0, 0, 1);
			}
			CmnMath::algebralinear::Vector3f u = w.cross(Pn.n);
			CmnMath::algebralinear::Vector3f v = Pn.n.cross(u);
			std::cout << "w: " << w << std::endl;
			std::cout << "Pn.n: " << Pn.n << std::endl;
			std::cout << "u: " << u << std::endl;
			std::cout << "v: " << v << std::endl;
			CmnMath::algebralinear::Vector3f P1 = Pn.p + u;
			CmnMath::algebralinear::Vector3f P2 = Pn.p + v;

			// generate a new plane to verify
			CmnMath::geometricprimitive::Plane PnVerify(Pn.p, P1, P2);
			std::cout << "Pn.n: " << Pn.n << std::endl;
			std::cout << "Pn.p: " << Pn.p << std::endl;
			std::cout << "Pn.n verify: " << PnVerify.n << std::endl;
			std::cout << "Pn.p verify: " << PnVerify.p << std::endl;

			CmnMath::geometricprimitive::Plane PnV2(
				CmnMath::algebralinear::Vector3f(-3, -2, 0.1), 
				CmnMath::algebralinear::Vector3f(-3.3894949, -1.1670122, 0.49296966), 
				CmnMath::algebralinear::Vector3f(-2.0835423, -1.6070304, 0.17536619));
			std::cout << "PnV2.p: " << PnV2.p << std::endl;
			std::cout << "PnV2.n: " << PnV2.n << std::endl;
			////
			//CmnMath::algebralinear::Vector3f w0 = Pn.n + CmnMath::algebralinear::Vector3f(1, 0, 0);
			//CmnMath::algebralinear::Vector3f w1 = Pn.n + CmnMath::algebralinear::Vector3f(-1, 0, 0);
			//CmnMath::algebralinear::Vector3f w;
			//if (std::abs(w0.x) > std::abs(w1.x)) {
			//	w = w0;
			//} else {
			//	w = w1;
			//}
			////
			//CmnMath::algebralinear::Matrix3 Householder;
			//Householder.identity();
			//Householder = Householder * 2 * w + w.

#ifdef USE_OPENCV
			test_Householder();
#endif // USE_OPENCV
		}

	}

	// Area triangle
	{
		float area = CmnMath::geometry::AreaTwoDimTriangle::area_triangle<CmnMath::algebralinear::Vector3f, float>(
			CmnMath::algebralinear::Vector3f(1, -4, -2),
			CmnMath::algebralinear::Vector3f(3, -3, -3),
			CmnMath::algebralinear::Vector3f(5, -1, -2));
		std::cout << "Area Triangle: " << area << std::endl;
	}

#ifdef USE_OPENCV
	// Points generator
	std::vector<CmnMath::algebralinear::Vector3f> points;
	CmnMath::geometry::GeneratorZeroDimLoxodrome<CmnMath::algebralinear::Vector3f>::loxodrome(1, 1, 
		0.09, 0, -100, 100, 2000, points);
	std::vector<CmnMath::algebralinear::Vector3f> points_prune;
	// Alternatively
	//CmnMath::geometry::GeneratorZeroDimPoint<cv::Point3f>::prune_loxodrome(
	//	points, 20, points_prune);
	CmnMath::geometry::SubsetZeroDimPoint::equidistant<CmnMath::algebralinear::Vector3f>(points, 
		1000, points_prune);
	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
	for (auto it = points_prune.begin(); it != points_prune.end(); ++it)
	{
		cv::circle(m, 
			cv::Point2f(it->x * m.cols / 2 + m.cols / 2, it->y * m.rows / 2 + m.rows / 2), 
			2, cv::Scalar(0, 0, 255));
	}
	cv::imshow("loxodrome", m);
	cv::waitKey();
#endif


#ifdef USE_OPENCV
	// Points generator
	CmnMath::CMN_32S levels = 4;
	CmnMath::geometry::GeneratorZeroDimIcoSphere<CmnMath::algebralinear::Vector3f> icosphere(levels);
	std::vector<CmnMath::algebralinear::Vector3f> vertices;
	std::vector<int> index;
	icosphere.vertex_index(levels - 1, vertices, index);

	m = cv::Mat(512, 512, CV_8UC3, cv::Scalar::all(0));
	for (auto &it : vertices)
	{
		cv::circle(m,
			cv::Point2f(it.x * m.cols / 2 + m.cols / 2, it.y * m.rows / 2 + m.rows / 2),
			2, cv::Scalar(0, 0, 255));
	}
	cv::imshow("icosphere", m);
	cv::waitKey();
#endif


	// Rotation 2d
	CmnMath::algebralinear::Vector2f in(3, 4), center(5, 2), out;
	CmnMath::CMN_32F angle = 0.45f;
	CmnMath::geometry::Rotation2D<CmnMath::algebralinear::Vector2f>::pointf(in, angle, center, out);
	std::cout << in << " rotate around " << center << " of " << angle << " rad -> " << out << std::endl;

	// Rotation 3d
	CmnMath::algebralinear::Vector3f origin0(0, 0, 0), src0(5, 0, 0),
		angle0(0, CmnMath::core::kPIf / 2, 0), dst0;
	CmnMath::CMN_32F angle_tmp[3] = { angle0.x, angle0.y, angle0.z }, src[3] = { src0.x, src0.y, src0.z }, dst[3];
	CmnMath::geometry::TransformZeroDimPoint::RotatePoint(angle_tmp, src, dst);
	std::cout << "src: " << src[0] << " " << src[1] << " " << src[2] << std::endl;
	std::cout << "dst: " << dst[0] << " " << dst[1] << " " << dst[2] << std::endl;

	// Sign
	CmnMath::CMN_32F v = CmnMath::geometry::Sign2D<CmnMath::algebralinear::Vector2f>::sign(in, center, out);
	std::cout << "Sign in 2D: " << v << std::endl;

	// Normal
	CmnMath::algebralinear::Vector3f pv1(0, 0, 0), pv2(1, 0, 0), pv3(1, 1, 0), pva(3, 5, 1);
	CmnMath::algebralinear::Vector3f pvn = 
		CmnMath::geometry::Normal<CmnMath::algebralinear::Vector3f>::calc(pv1, pv2, pv3);
	float res = 
		CmnMath::geometry::Normal<CmnMath::algebralinear::Vector3f>::direction(pvn, pv1, pva);
	std::cout << "Normal: " << pvn << " res: " << res << std::endl;
	//// Intersection ray-sphere
	//CmnMath::algebralinear::Vector3f point_src(-0.1, 2.5, 3);
	//CmnMath::algebralinear::Vector3f hitpoint, normal;
	//CmnMath::CMN_32F sphere_distance = 0;
	//CmnMath::geometry::IntersectionThreeDimSphere<CmnMath::algebralinear::Vector3f>::rayf(
	//	point_src,
	//	CmnMath::algebralinear::Vector3f(0, 0, 0), 
	//	CmnMath::algebralinear::Vector3f(0, 0, 0), 1.0f,
	//	hitpoint, sphere_distance, normal);
	//std::cout << "Cubepoint: " << point_src <<
	//	" expected position on sphere : " << hitpoint <<
	//	std::endl;

	//{
	//	cv::Point3f point_src(5, 0.2, -0.1);
	//	cv::Point3f hitpoint, normal;
	//	CmnMath::CMN_32F sphere_distance = 0;
	//	CmnMath::geometry::IntersectionThreeDimSphere<cv::Point3f>::rayf(
	//		point_src,
	//		cv::Point3f(-2,0,0),
	//		cv::Point3f(0, 0, 0), 1.0f,
	//		hitpoint, sphere_distance, normal);
	//	std::cout << "Direction ray: " << point_src <<
	//		" expected position on sphere : " << hitpoint <<
	//		std::endl;
	//}
	//{
	//	cv::Point3f point_src(-0.1, 2.5, 3);
	//	cv::Point3f point_ori = point_src * 2;
	//	point_src *= -1;
	//	cv::Point3f hitpoint, normal;
	//	CmnMath::CMN_32F sphere_distance = 0;
	//	CmnMath::geometry::IntersectionThreeDimSphere<cv::Point3f>::rayf(
	//		point_src,
	//		point_ori,
	//		cv::Point3f(0, 0, 0), 1.0f,
	//		hitpoint, sphere_distance, normal);
	//	std::cout << "Direction ray: " << point_src <<
	//		" expected position on sphere : " << hitpoint <<
	//		std::endl;
	//}
}

/** @brief Estimate the barycentric coordinates
*/
void barycentric() {

//#ifdef USE_OPENCV
//	CmnMath::geometry::BarycentricTwoDimTriangleXYZ<CmnMath::algebralinear::Vector3f> cbarycentric;
//	CmnMath::algebralinear::Vector3f b = cbarycentric.barycentric(
//		CmnMath::algebralinear::Vector3f(0, 0, 0),
//		CmnMath::algebralinear::Vector3f(1, 1, 0),
//		CmnMath::algebralinear::Vector3f(0.5, 1, 1),
//		CmnMath::algebralinear::Vector3f(0.5, 0.5, 0.5));
//	CmnMath::algebralinear::Vector3f c = cbarycentric.cartesian(
//		CmnMath::algebralinear::Vector3f(0, 0, 0),
//		CmnMath::algebralinear::Vector3f(1, 1, 0),
//		CmnMath::algebralinear::Vector3f(0.5, 1, 1),
//		CmnMath::algebralinear::Vector3f(0.5, 0.5, 0.5));
//	std::cout << "barycentric: " << b.x << " " << b.y << " " << b.z << std::endl;
//	std::cout << "cartesian: " << c.x << " " << c.y << " " << c.z << std::endl;
//#endif

#ifdef USE_OPENCV
	CmnMath::geometry::BarycentricTwoDimTriangleXYZ<cv::Point3f> cbarycentric;
	cv::Point3f b = cbarycentric.barycentric(
		cv::Point3f(0, 0, 0),
		cv::Point3f(1, 1, 0),
		cv::Point3f(0.5, 1, 1),
		cv::Point3f(0.5, 0.5, 0.5));
	cv::Point3f c = cbarycentric.cartesian(
		cv::Point3f(0, 0, 0),
		cv::Point3f(1, 1, 0),
		cv::Point3f(0.5, 1, 1),
		cv::Point3f(0.5, 0.5, 0.5));
	std::cout << "barycentric: " << b.x << " " << b.y << " " << b.z << std::endl;
	std::cout << "cartesian: " << c.x << " " << c.y << " " << c.z << std::endl;
#endif

}

/** @brief It align a cloud of points to its 4 vertexes
*/
void angle_points(std::vector< CmnMath::algebralinear::Vector3f >& vp,
	CmnMath::algebralinear::Vector3f& center,
	std::vector<CmnMath::algebralinear::Vector3f>& vangle) {
	std::cout << "Pointstt: " << vp[0] << std::endl;
	std::cout << "Pointstb: " << vp[1] << std::endl;
	std::cout << "Pointsbt: " << vp[2] << std::endl;
	std::cout << "Pointsbb: " << vp[3] << std::endl;
	CmnMath::algebralinear::Vector3f angle =
		CmnMath::geometry::AngleTwoDimPoint< CmnMath::algebralinear::Vector3f>::vectors2angles(
			vp[1], vp[0]);
	std::cout << "angle10: " << angle.x << " " << angle.y << " " <<
		angle.z << std::endl;
}

/** @brief It align a cloud of points to its 4 vertexes
*/
void align_points2(std::vector< CmnMath::algebralinear::Vector3f >& vp,
	CmnMath::algebralinear::Vector3f& center) {

	//cv::Point3f center(0.410399, 6.2244, -0.475846);

	std::cout << "Pointstt: " << vp[0] << std::endl;
	std::cout << "Pointstb: " << vp[1] << std::endl;
	std::cout << "Pointsbt: " << vp[2] << std::endl;
	std::cout << "Pointsbb: " << vp[3] << std::endl;

	CmnMath::geometricprimitive::Plane plane0(
		CmnMath::algebralinear::Vector3f(vp[0].x, vp[0].y, vp[0].z),
		CmnMath::algebralinear::Vector3f(vp[1].x, vp[1].y, vp[1].z),
		CmnMath::algebralinear::Vector3f(vp[2].x, vp[2].y, vp[2].z));
	std::cout << "Plane: " << plane0.n.x << " " << plane0.n.y << " " << plane0.n.z << std::endl;
	cv::Point3f v0(plane0.n.x, plane0.n.y, plane0.n.z);
	CmnMath::algebralinear::Vector3f v00(plane0.n.x, plane0.n.y, plane0.n.z);

	CmnMath::geometricprimitive::Plane plane1(
		CmnMath::algebralinear::Vector3f(0, 0, 0),
		CmnMath::algebralinear::Vector3f(1, 0, 0),
		CmnMath::algebralinear::Vector3f(0, 1, 0));
	std::cout << "Plane: " << plane1.n.x << " " << plane1.n.y << " " << plane1.n.z << std::endl;
	cv::Point3f v1(plane1.n.x, plane1.n.y, plane1.n.z);
	CmnMath::algebralinear::Vector3f v11(plane1.n.x, plane1.n.y, plane1.n.z);

	// calculate the rotation
	CmnMath::algebralinear::Vector3f Mx = v00.normalized();
	CmnMath::algebralinear::Vector3f Mz = v00.cross(v11).normalized();
	CmnMath::algebralinear::Vector3f My = Mz.cross(v00).normalized();
	//cv::Mat m3x3 = (cv::Mat_<double>(3, 3) << Mx.x, Mx.y, Mx.z,
	//	My.x, My.y, My.z, Mz.x, Mz.y, Mz.z);
	//cv::Mat m3x3 = (cv::Mat_<double>(3, 3) << Mx.x, My.x, Mz.x,
	//	Mx.y, My.y, Mz.y, Mx.z, My.z, Mz.z);
	//cv::Mat m3x3 = (cv::Mat_<double>(3, 3) << Mx.x, Mx.y, Mx.z,
	//	Mz.x, Mz.y, Mz.z, My.x, My.y, My.z);
	//cv::Mat m3x3 = (cv::Mat_<double>(3, 3) << Mz.x, Mz.y, Mz.z, My.x, My.y, My.z, Mx.x, Mx.y, Mx.z);
	cv::Mat m3x3 = (cv::Mat_<double>(3, 3) << Mx.x, Mx.z, Mx.y,
		My.x, My.z, My.y, Mz.x, Mz.z, Mz.y);
	std::cout << "M3x3: " << m3x3 << std::endl;

	auto M3x3V = CmnMath::geometry::AngleTwoDimPoint< CmnMath::algebralinear::Vector3f>::rotation_between_vectors_to_matrix(v00, v11);
	//std::cout << "M3x3V: " << M3x3V << std::endl;
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			std::cout << M3x3V[y][x] << " ";
		}
		std::cout << std::endl;
	}
}

/** @brief Test angle between two points
*/
void test_angle_point3d() {
	std::vector<CmnMath::algebralinear::Vector3f> vp;

	//cv::Point3f center = cv::Point3f(-3.676499843597412, 4.086901187896729, -0.2089430093765259);
	CmnMath::algebralinear::Vector3f center = CmnMath::algebralinear::Vector3f(-0.5, -0.5, 0);
	// Valid sequence (top view). X plus right side of the observer (camera). 
	//                            Y plus near the observer (camera). 
	// 0 1 -- +-
	// 3 2 -+ ++
	vp.push_back(CmnMath::algebralinear::Vector3f(-0.5, -0.5, 0));
	vp.push_back(CmnMath::algebralinear::Vector3f(0.5, -0.5, 0));
	vp.push_back(CmnMath::algebralinear::Vector3f(0.5, 0.5, 0));
	vp.push_back(CmnMath::algebralinear::Vector3f(-0.5, 0.5, 0));

	// Invalid sequence
	//// 3 2 -+ ++
	//// 0 1 -- +-
	//vp.push_back(cv::Point3f(-0.5, 0.5, 0));
	//vp.push_back(cv::Point3f(0.5, 0.5, 0));
	//vp.push_back(cv::Point3f(0.5, -0.5, 0));
	//vp.push_back(cv::Point3f(-0.5, -0.5, 0));

	// 0 2
	std::vector<CmnMath::algebralinear::Vector3f> vangle;
	angle_points(vp, center, vangle);

	// aligne points
	align_points2(vp, center);
}

}	// namespace




/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test geometry" << std::endl;
	test();
	barycentric();
	test_angle_point3d();
	return 0;
}
