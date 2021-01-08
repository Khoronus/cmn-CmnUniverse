/* @file fisheye2perspective.hpp
 * @brief Class to map the points from a fish-eye to perspective and viceversa.
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.2.0.0
 * 
 */

#ifndef CMNIP_TRANSFORM_FISHEYE2PERSPECTIVE_HPP__
#define CMNIP_TRANSFORM_FISHEYE2PERSPECTIVE_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace transform
{


/** Map the points from fish-eye image to rectangular area
	@example
*/
class FishEye2Perspective
{
public:

	FishEye2Perspective(){}// : transform_mode_(0)	{}

	~FishEye2Perspective() {}

	/** Initialize the point mapping containers
	*/
	void initialize(const cv::Size& orig, const cv::Size& dest)
	{
		dest_size_ = dest;

		// memorize the xy coordinate
		src_map_ = cv::Mat::zeros( orig, CV_32SC2 );	// original fish-eye image
		dst_map_ = cv::Mat::zeros( dest, CV_32SC2 );	// destination rectangular image
	}

	/** @brief Load the transformation matrix.

		Load the transformation matrix.
		@param[in] filename File with the transformation information.
		@param[in] size Expected transformation size (check consistency).
		@param[in] bInitialize If TRUE it reset the matrix contents.
		@return Return 1 in case of success. 0 otherwise.
	*/
	int load(const std::string &filename, const cv::Size &size, bool bInitialize)
	{
		if (bInitialize)
		{
			src_map_ = cv::Scalar::all(-1);
			dst_map_ = cv::Scalar::all(-1);
		}

		std::ifstream myfile;
		myfile.open(filename.c_str());
		if (!myfile.is_open()) return 0;

		while (!myfile.eof())
		{
			char buf[512];
			myfile.getline(buf, 512);
			if (strlen(buf) < 5) continue;

			int p0[2], p1[2];
			sscanf(buf, "%i %i %i %i", &p0[0], &p0[1], &p1[0], &p1[1]);

			if ((p1[0] >= 0 && p1[0] < size.width && p1[1] >= 0 && p1[1] < size.height) &&
				(p0[0] >= 0 && p0[0] < src_map_.cols && p0[1] >= 0 && p0[1] < src_map_.rows) )
			{
				src_map_.at<cv::Vec2i>(p0[1], p0[0])[0] = p1[0];
				src_map_.at<cv::Vec2i>(p0[1], p0[0])[1] = p1[1];
				dst_map_.at<cv::Vec2i>(p1[1],p1[0])[0] = p0[0];
				dst_map_.at<cv::Vec2i>(p1[1],p1[0])[1] = p0[1];
			}
		}

		myfile.close();
		return 1;
	}


	/** @brief Calculate the point position on the world with the radius 1 and
	           no camera distortions.
		
		@param[in] s source.
		@param[in] c center.
		@param[in] o output.
	*/
	void camera2world(const cv::Point2f &s, const cv::Point2f &c, 
		cv::Point3f &o) {
		float x = s.x;
		float y = s.y;

		// Calculate the position of the points on the emisphere
		float _x = x / c.x, _y = y / c.y;
		o.x = (_x * 2.0f) / 
			( 1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f) );
		o.y = (_y * 2.0f) / 
			( 1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f) );
		o.z = ( -1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f) ) / 
			  ( 1.0f + std::pow(_x, 2.0f) + std::pow(_y, 2.0f) );
	}

	/** @brief Convert world 2 camera

	    @link http://en.wikipedia.org/wiki/Stereographic_projection
	*/
	void world2camera(const cv::Point3f &s, const cv::Point2f &c, 
		float xmodifier, float ymodifier, cv::Point2f &o)
	{
		// Lens coordinate 3D
		float pscale = std::sqrt( std::pow(s.x, 2) + std::pow(s.y, 2) + 
			std::pow(s.z, 2));
		cv::Point3f q(1.0f / pscale * s.x, 
			1.0f / pscale * s.y, 1.0f / pscale * s.z);

		// Fish eye coordinate (stereographic projection)
		// http://en.wikipedia.org/wiki/Stereographic_projection
		o.x = cvRound((q.x / (xmodifier + q.y)) * 
			c.x + c.x);
		o.y = cvRound((q.z / (ymodifier + q.y)) * 
			c.y + c.y);
	}

	/** @brief Calculate a point over a projective plane.
	*/
	void point2projectiveplane(const cv::Point2f &s, const cv::Point2f &c, 
		float wscale, float hscale, float distance_from_origin, 
		const cv::Point3f &angle,
		cv::Point3f &o) {

		cv::Point3d p( s.x / c.x * wscale, 
					   distance_from_origin, 
					   s.y / c.y * hscale ); 

		// Use quaternion. Used only for test
#ifdef INTERNAL_USEQUATERNION_
		CmnIP::Math::Vector3f origin(0,0,0);
		CmnIP::Math::Vector3f src(p.x, p.y, p.z);
		CmnIP::Math::Vector3f _angle(angle.x, angle.y, angle.z);
		CmnIP::Math::Vector3f dst;
		CmnIP::Math::PointTransformation::PointRotation(origin, src, _angle, dst);
		o.x = dst.x; o.y = dst.y; o.z = dst.z;
#else
		float initial_position[4] = {static_cast<float>(p.x), 
		  static_cast<float>(p.y), 
		  static_cast<float>(p.z), 1.0f }, final_position[4];
		float _angle[3] = {angle.x, angle.y, angle.z };
	    CmnMath::geometry::TransformZeroDimPoint::RotatePoint(
			_angle, initial_position, final_position);
		o.x = final_position[0];
		o.y = final_position[1];
		o.z = final_position[2];
#endif
	}

	///** @brief Convert a type in another
	//*/
	//CmnIP::Math::Vector3f Point3f2Vector3f(
	//	const cv::Point3f &p) {
	//		
	//	return CmnIP::Math::Vector3f(p.x, p.y, p.z);
	//}

	/** @brief Calculate the cartesian to spherical transformation.
	*/
	void cartesian2spherical(float x, float y, float z, 
		float &r, float &theta, float &phi) {
		r = std::sqrt( std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) );
		theta = std::acos( z / r );
		phi = std::atan(y / x);
	}

	/** @brief Calculate the spherical to cartesian transformation.
	*/
	void spherical2cartesian(float r, float theta, float phi,
		float &x, float &y, float &z) {
		x = r * std::sin(theta) * std::cos(phi);
		y = r * std::sin(theta) * std::sin(phi);
		z = r * std::cos(theta);
	}

	/** @brief Create the perspective image.
	*/
	void create_perspective(
		std::vector< std::pair<int, int> > &v_points, 
		const float horizontal_plane_size, const float vertical_plane_size, 
		const float plane_distance,
		const /*CmnIP::Math::geometry::VectorGeneric3*/ cv::Point3f &angle_rot_plane,
		bool bInitialize,
		float xmodifier, float ymodifier
#ifdef POINTMAPPING2DEBUG_
		, cv::Mat &image,
		std::vector< std::pair<cv::Point3f, cv::Point2f> > &points_lens,
		std::vector< std::pair<cv::Point3f, cv::Point2f> > &points_plane
#endif
		)
	{
		if (bInitialize)
		{
			src_map_ = cv::Scalar::all(-1);
			dst_map_ = cv::Scalar::all(-1);
		}

		/// Calculate the point projection
		int h = src_map_.rows;
		int w = src_map_.cols;
		// Set the intersection plane information
		float dist = plane_distance;
		float wsize = horizontal_plane_size;
		float hsize = vertical_plane_size;
		float angle[3] = {angle_rot_plane.x, angle_rot_plane.y, angle_rot_plane.z};
		double kVal = 1;
		float cx = w * 0.5, cy = h * 0.5;

		// Track the point position over the lens
		bool bTrackLens = false;
		// bin theta, phi
		// container theta, phi, original point
		std::map< std::pair<int, int>, std::vector< std::pair< cv::Point2f, cv::Point2f > > > v_s, v_p;
		// Binning of the theta and phi vale
		float kBin = 100;
#ifdef POINTMAPPING2DEBUG_
		cv::Mat perspective(dst_map_.size(),CV_8UC3,cv::Scalar::all(0));
		cv::Mat fisheye(src_map_.size(),CV_8UC3,cv::Scalar::all(0));
		cv::TickMeter tm;
		tm.start();
#endif
		// Map the image in a unitary sphere
		if (bTrackLens)
		{
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = v_points.begin(); it != v_points.end(); it++)
#else
			for (std::vector< std::pair<int, int> >::const_iterator it = v_points.begin(); it != v_points.end(); it++)
#endif
			{
				cv::Point3f p3d;
				camera2world(cv::Point2f(it->first, it->second),
					cv::Point2f(cx, cy), p3d);
				float r, theta, phi;
				//cartesian2spherical(p3d.x, -p3d.z, p3d.y, r, theta, phi);
				theta = std::atan2(p3d.x, -p3d.z);
				phi = std::atan2(p3d.y, -p3d.z);
				int theta_bin = theta * kBin;
				int phi_bin = phi * kBin;
				v_s[ std::make_pair(theta_bin, phi_bin) ].push_back( 
					std::make_pair(cv::Point2f(theta, phi), 
					cv::Point2f(it->first + cx, it->second + cy)) );

#ifdef POINTMAPPING2DEBUG_
				points_lens.push_back( std::make_pair(cv::Point3f(p3d.x, -p3d.z, p3d.y), 
					cv::Point2f(it->first + cx, it->second + cy) ) );
#endif
			}
		}
#ifdef POINTMAPPING2DEBUG_
		tm.stop();
		std::cout << "Sphere coord time(ms): " << tm.getTimeMilli() << std::endl;
		tm.reset();
		tm.start();
#endif


		// Calculate the points of the plane where are located and which
		// point of the sphere project on the plane.
		// Once the point on the sphere is estimated, the image point position
		// is extracted.
		float npoints = v_points.size();
		float ipoints = 0;
		// Compute the destination points
		npoints = dst_map_.rows * dst_map_.cols;

		for (int _yperspective = -dst_map_.rows / 2; _yperspective <= dst_map_.rows / 2; _yperspective++)
		{
			for (int _xperspective = -dst_map_.cols / 2; _xperspective <= dst_map_.cols / 2; _xperspective++)
			{
				int x = _xperspective, y = _yperspective;
				++ipoints;
				float perc = ipoints / npoints;
#ifdef POINTMAPPING2DEBUG_
				if ((int)ipoints % 1000 == 0) {
					std::cout << "completed: " << perc * 100.0f << "%" << std::endl;
					cv::imshow("perspective", perspective);
					cv::waitKey(1);
				}
#endif
				// Calculate the position of the point on the plane in 3D space
				cv::Point3f p3d;
				point2projectiveplane(cv::Point2f(x, y), cv::Point2f(cx, cy), 
						wsize, hsize, dist,	cv::Point3f(angle[0], angle[1], 
						angle[2]), p3d);

				// Fish eye coordinate
				int xfisheye = 0;
				int yfisheye = 0;
				// Perspective coordinate
				int xperspective = _xperspective + dst_map_.rows / 2;
				int yperspective = _yperspective + dst_map_.cols / 2;

				if (bTrackLens)
				{
					// Draw a point which connect the line to the center
					float r, theta, phi;
					//cartesian2spherical(p3d.x, p3d.y, p3d.z, r, theta, phi);
					theta = std::atan2(p3d.x, p3d.y);
					phi = std::atan2(p3d.z, p3d.y);
					int theta_bin = theta * kBin;
					int phi_bin = phi * kBin;
			
					if (v_s.find(std::make_pair(theta_bin, phi_bin)) == v_s.end()) {
						//std::cout << "miss : " << theta_bin << " " << phi_bin;
						float thresholds = 10.0;
						// [e] to use the numeric limit causes error probably
						//     need to use UNDEF_MINMAX
						//std::numeric_limits<float>::max(); 
						float best[2] = {1000000, 1000000};
						float bt = theta_bin;
						float bp = phi_bin;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
						for (auto it2 = v_s.begin(); it2 != v_s.end(); it2++)
#else
						for (std::map< std::pair<int, int>, std::vector< std::pair< cv::Point2f, cv::Point2f > > >::const_iterator it2 = v_s.begin(); it2 != v_s.end(); it2++)
#endif
						{
							float _t = it2->first.first - theta_bin;
							float _p = it2->first.second - phi_bin;
							if (std::abs(_t) < thresholds &&
								std::abs(_p) < thresholds)
							{
								double d1 = std::sqrt( std::pow(std::abs(_t), 2.0f) + 
									std::pow(std::abs(_p), 2.0f ) );
								double d2 = std::sqrt( 
									std::pow(best[0], 2) + std::pow(best[1], 2) ); 
								
								if (d1 < d2)
								{
									best[0] = std::abs(_t);
									best[1] = std::abs(_p);
									// Intersection point and color
									bt = it2->first.first;
									bp = it2->first.second;
								}
							}
						}
						theta_bin = bt;
						phi_bin = bp;
					}

					// Get the nearest
					int s = v_s[std::make_pair(theta_bin, phi_bin)].size();
					int idx = -1;
					// [e] to use the numeric limit causes error probably
					//     need to use UNDEF_MINMAX
					//std::numeric_limits<float>::max(); 
					float best[2] = {1000000, 1000000};
					float thresholds = 0.1;
					for (int i = 0; i < s; i++)
					{
						// Search the point that better project the ray 
						// (center of the sphere -> intersection plane).
						float _t = v_s[std::make_pair(theta_bin, phi_bin)][i].first.x - theta;
						float _p = v_s[std::make_pair(theta_bin, phi_bin)][i].first.y - phi;
						if (std::abs(_t) < thresholds &&
							std::abs(_p) < thresholds)
						{
							double d1 = std::sqrt( std::pow(std::abs(_t), 2.0f) + 
								std::pow(std::abs(_p), 2.0f ) );
							double d2 = std::sqrt( 
								std::pow(best[0], 2) + std::pow(best[1], 2) ); 
								
							if (d1 < d2)
							{
								best[0] = std::abs(_t);
								best[1] = std::abs(_p);
								// Intersection point and color
								idx = i;
							}
						}
					}
					if (idx < 0) {
#ifdef POINTMAPPING2DEBUG_
						std::cout << "continue1" << std::endl;
#endif
						continue;
					}

					// Fish eye coordinate
					xfisheye = v_s[std::make_pair(theta_bin, phi_bin)][idx].second.x;
					yfisheye = v_s[std::make_pair(theta_bin, phi_bin)][idx].second.y;
				} else {
					cv::Point2f o;
					world2camera(p3d, cv::Point2f(cx, cy), xmodifier, ymodifier, o);
					xfisheye = o.x;
					yfisheye = o.y;
				}


				// Check that the projection is inside the index map
				if (yfisheye >= 0 && yfisheye < src_map_.rows && 
					xfisheye >= 0 && xfisheye < src_map_.cols &&
					yperspective >= 0 && yperspective < dst_map_.rows && 
					xperspective >= 0 && xperspective < dst_map_.cols)
				{
#ifdef POINTMAPPING2DEBUG_
					for (int c = 0; c < 3; c++)
					{
						perspective.at<cv::Vec3b>(yperspective, xperspective)[c] = 
							image.at<cv::Vec3b>(yfisheye, xfisheye)[c];
					}
					for (int c = 0; c < 3; c++)
					{
						fisheye.at<cv::Vec3b>(yfisheye, xfisheye)[c] = 
							perspective.at<cv::Vec3b>(yperspective, xperspective)[c];
					}
					points_plane.push_back( std::make_pair(p3d, cv::Point2f(xfisheye, yfisheye) ) );
#endif

					// Set the mapping indexes
					src_map_.at<cv::Vec2i>(yfisheye, xfisheye)[0] = xperspective;
					src_map_.at<cv::Vec2i>(yfisheye, xfisheye)[1] = yperspective;
					dst_map_.at<cv::Vec2i>(yperspective, xperspective)[0] = xfisheye;
					dst_map_.at<cv::Vec2i>(yperspective, xperspective)[1] = yfisheye;
				}
			}
		}

#ifdef POINTMAPPING2DEBUG_
		tm.stop();
		std::cout << "Plane coord time(ms): " << tm.getTimeMilli() << std::endl;
		tm.reset();
		tm.start();

		cv::imshow("perspective", perspective);
		cv::imwrite("perspective.png", perspective);
		cv::imshow("fisheye", fisheye);
		cv::waitKey();
#endif
	}


	void create_perspective(		
		const float horizontal_plane_size, const float vertical_plane_size, 
		const float plane_distance,
		const /*CmnIP::Math::geometry::VectorGeneric3*/ cv::Point3f &angle_rot_plane,
		bool bInitialize,
		float xmodifier, float ymodifier
#ifdef POINTMAPPING2DEBUG_
		, cv::Mat &image,
		std::vector< std::pair<cv::Point3f, cv::Point2f> > &points_lens,
		std::vector< std::pair<cv::Point3f, cv::Point2f> > &points_plane
#endif
		)
	{
		/// Calculate the point projection
		int h = src_map_.rows;
		int w = src_map_.cols;

		// collect the image points
		std::vector< std::pair<int, int> > v_points;

		// Map the image in a unitary sphere
		for (int y = -h/2; y <= h/2; y++)
		{
			for (int x = -w/2; x <= w/2; x++)
			{
				v_points.push_back( std::make_pair(x, y) );
			}
		}
		// set the spherical mapping with the points selected
		create_perspective(
			v_points, horizontal_plane_size, 
			vertical_plane_size, plane_distance, angle_rot_plane,
			bInitialize, xmodifier, ymodifier
#ifdef POINTMAPPING2DEBUG_
			, image,
			points_lens, points_plane
#endif
			);
	}

	/// Transform an image
	int transform(const cv::Mat& src, const cv::Rect& roi, cv::Mat& dst)
	{
		// Source image and rectification image are not compatible
		// in size
		if (src.cols != src_map_.cols || src.rows != src_map_.cols)
		{
			return 0;
		}

		if (dst.cols != dest_size_.width || dst.rows != dest_size_.height)
			dst = cv::Mat(dest_size_.height, dest_size_.width, CV_8UC3);

		int h = dst.rows;
		int w = dst.cols;
		//for (int y = 0; y < h; y++)
		//	for (int x = 0; x < w; x++)
		//		for (int c = 0; c < 3; c++)
		//			dst.at<cv::Vec3b>(y, x)[c] = src.at<cv::Vec3b>( dst_map_.at<cv::Vec2i>(y,x)[1], dst_map_.at<cv::Vec2i>(y,x)[0])[c];

		/// Direct access for performance reason
		unsigned char* pixelSrcPtr = (unsigned char*)src.data;
		unsigned char* pixelDstPtr = (unsigned char*)dst.data;
		unsigned int* pixelMapPtr = (unsigned int*)dst_map_.data;
		int cnSrc = src.channels();
		int cnDst = dst.channels();
		int cnDstMap = dst_map_.channels();
		int wMap = dst_map_.cols;
		int wSrc = src.cols;
		int ys = roi.y, xs = roi.x, ye = roi.height + roi.y, xe = roi.width + roi.x;
		ys = ys < 0 ? 0 : ys;
		ye = ye >= dst.rows ? dst.rows - 1 : ye;
		xs = xs < 0 ? 0 : xs;
		xe = xe >= dst.cols ? dst.cols - 1 : xe;

		cv::Mat stmp = src.clone();

		//std::cout << xs << " " << xe << " <> " << ys << " " << ye << std::endl;
		//cv::Point2f p, q;
		for (int y = ys; y < ye; y++)
		{
			for (int x = xs; x < xe; x++)
			{
				register int _mapid = y * wMap * cnDstMap + x * cnDstMap;
				register int _ymapid = pixelMapPtr[_mapid + 1];
				register int _xmapid = pixelMapPtr[_mapid];
				register int _srcid = _ymapid * wSrc * cnSrc + _xmapid * cnSrc;
				register int _dstid = y * w * cnDst + x * cnDst;

				//if (y == ye / 2 && x == xe / 2)
				//{
				//	std::cout << x << " " << y << " # " << _xmapid << " " << _ymapid << " $ " << std::endl;//<< src_map_.at<cv::Vec2i>((int)_ymapid,(int)_xmapid)[0] << " " << src_map_.at<cv::Vec2i>((int)_ymapid,(int)_xmapid)[1] << std::endl;
				//	//cv::circle( stmp, cv::Point( x, y ), 3, cv::Scalar(0,0,255), -1);
				//	p.x = x; p.y = y;
				//	q.x = _xmapid; q.y = _ymapid;
				//}

				//if (y >= 228 && y < 230 && x >= 195 && x < 200)
				//{

				//	std::cout << x << " " << y << " # " << _xmapid << " " << _ymapid << " $ " << src_map_.at<cv::Vec2i>((int)_ymapid,(int)_xmapid)[0] << " " << src_map_.at<cv::Vec2i>((int)_ymapid,(int)_xmapid)[1] << std::endl;
				//}
				if (_dstid >= 0 && _srcid >= 0) {
					pixelDstPtr[_dstid] = pixelSrcPtr[_srcid];
					pixelDstPtr[_dstid+1] = pixelSrcPtr[_srcid+1];
					pixelDstPtr[_dstid+2] = pixelSrcPtr[_srcid+2];
				}
			}
		}

		return 1;
	}


	int fisheye2perspective(const cv::Point2f& src, cv::Point2f& dst)
	{
		int x = (int)src.x, y = (int)src.y;
		int frame = 2;
		cv::Point2f p(0,0);
		int ipt = 0;
		for (int _y = y - frame; _y <= y + frame; _y++) {
			for (int _x = x - frame; _x <= x + frame; _x++) {
				if (_x >= 0 && _x < src_map_.cols && _y >= 0 && _y < src_map_.rows)
				{
					int __x = src_map_.at<cv::Vec2i>(_y,_x)[0];
					int __y = src_map_.at<cv::Vec2i>(_y,_x)[1];
					if (__x > 0 && __y > 0)
					{
						p.x += (float)__x;
						p.y += (float)__y;
						++ipt;
					}
				}
			}
		}
		if (ipt != 0)
		{
			p.x /= ipt;
			p.y /= ipt;
		}
		if (x >= 0 && x < src_map_.cols && y >= 0 && y < src_map_.rows) {
			dst = p;
		} else {
			dst = cv::Point2f(0,0);
			return 0;
		}
		return 1;
	}

	/** @brief Transform a point from the perspective image to the fish eye
	*/
	int perspective2fisheye(const cv::Point2f& src, cv::Point2f& dst)
	{
		int x = (int)src.x, y = (int)src.y;
		int frame = 2;
		cv::Point2f p(0,0);
		int ipt = 0;
		for (int _y = y - frame; _y <= y + frame; _y++) {
			for (int _x = x - frame; _x <= x + frame; _x++) {
				if (_x >= 0 && _x < dst_map_.cols && _y >= 0 && _y < dst_map_.rows)
				{
					int __x = dst_map_.at<cv::Vec2i>(_y,_x)[0];
					int __y = dst_map_.at<cv::Vec2i>(_y,_x)[1];
					if (__x > 0 && __y > 0)
					{
						p.x += (float)__x;
						p.y += (float)__y;
						++ipt;
					}
				}
			}
		}
		if (ipt != 0)
		{
			p.x /= ipt;
			p.y /= ipt;
		}
		if (x >= 0 && x < dst_map_.cols && y >= 0 && y < dst_map_.rows) {
			dst = p;
		} else {
			dst = cv::Point2f(0,0);
			return 0;
		}
		return 1;
	}




	/// Transform an input set of points
	//int fromDestinationToOrigin(const std::vector<cv::Point2f>& src, std::vector<cv::Point2f>& dst)
	int fisheye2perspective(const std::vector<cv::Point2f>& src, std::vector<cv::Point2f>& dst)
	{
		dst.clear();
		for (std::vector<cv::Point2f>::const_iterator it = src.begin(); it != src.end(); it++)
		{
			int x = (int)it->x, y = (int)it->y;
			int frame = 2;
			cv::Point2f p(0,0);
			int ipt = 0;
			for (int _y = y - frame; _y <= y + frame; _y++)
				for (int _x = x - frame; _x <= x + frame; _x++)
				{
					int __x = 0, __y = 0;
					if (_x >= 0 && _x < src_map_.cols && _y >= 0 && _y < src_map_.rows)
					{
						__x = src_map_.at<cv::Vec2i>(_y,_x)[0];
						__y = src_map_.at<cv::Vec2i>(_y,_x)[1];
						if (__x > 0 && __y > 0)
						{
							p.x += (float)__x;
							p.y += (float)__y;
							++ipt;
						}
					}
				}
			if (ipt != 0)
			{
				p.x /= ipt;
				p.y /= ipt;
			}
			if (x >= 0 && x < src_map_.cols && y >= 0 && y < src_map_.rows)
				dst.push_back( p );
			else
				dst.push_back( cv::Point2f(0,0) );
		}
		return 1;
	}

	/// Transform an input set of points
	//int fromOriginToDestination(const std::vector<cv::Point2f>& src, std::vector<cv::Point2f>& dst)
	int perspective2fisheye(const std::vector<cv::Point2f>& src, std::vector<cv::Point2f>& dst)
	{
		dst.clear();
		for (std::vector<cv::Point2f>::const_iterator it = src.begin(); it != src.end(); it++)
		{
			int x = (int)it->x, y = (int)it->y;
			int frame = 2;
			cv::Point2f p(0,0);
			int ipt = 0;
			for (int _y = y - frame; _y <= y + frame; _y++)
				for (int _x = x - frame; _x <= x + frame; _x++)
				{
					int __x = 0, __y = 0;
					if (_x >= 0 && _x < dst_map_.cols && _y >= 0 && _y < dst_map_.rows)
					{
						__x = dst_map_.at<cv::Vec2i>(_y,_x)[0];
						__y = dst_map_.at<cv::Vec2i>(_y,_x)[1];
						if (__x > 0 && __y > 0)
						{
							p.x += (float)__x;
							p.y += (float)__y;
							++ipt;
						}
					}
				}
			if (ipt != 0)
			{
				p.x /= ipt;
				p.y /= ipt;
			}
			//std::cout << x << " " << y << " " << src_map_.cols << " " << src_map_.rows << " " << p << std::endl;
			if (x >= 0 && x < dst_map_.cols && y >= 0 && y < dst_map_.rows) {
				dst.push_back( p );
			} else {
				dst.push_back( cv::Point2f(0,0) );
			}
		}
		return 1;
	}

	/** Return the source original position map
		This matrix contains the coordinate to transform the 
		original fish eye image in a perspective image.
		Note: It is better to call the function:
		fromOriginToDestination
	*/
	cv::Mat src_map() const {
		return src_map_;
	}

	/** Return the destination original position map
		This matrix contains the coordinate to transform the 
		destination perspective image in a fish eye image.
		Note: It is better to call the function:
		fromDestinationToOrigin
	*/
	cv::Mat dst_map() const {
		return dst_map_;
	}

	/** @brief Get the transform mode.

		Get the transform mode.
	*/
	int transform_mode() {
		return transform_mode_;
	}

	/** @brief Set the transform mode.

		Set the transform mode.
	*/
	void set_transform_mode(int transform_mode) {
		transform_mode_ = transform_mode;
	}

	/** @brief Create the fisheye to perspective LUT.

		@param[in] map_x Map for the x coordinate.
		@param[in] map_y Map for the y coordinate.
	*/
	void create_fisheye2perspective_LUT(cv::Mat &map_x, cv::Mat &map_y) {
		map_x.create( dst_map_.size(), CV_32FC1 );
		map_y.create( dst_map_.size(), CV_32FC1 );
		for (int y = 0; y < dst_map_.rows; y++)
		{
			for (int x = 0; x < dst_map_.cols; x++)
			{
				map_x.at<float>(y,x) = dst_map_.at<cv::Vec2i>(y,x)[0]; 
				map_y.at<float>(y,x) = dst_map_.at<cv::Vec2i>(y,x)[1];
			}
		}
	}

	/** @brief Create the perspective to fisheye LUT.

		@param[in] map_x Map for the x coordinate.
		@param[in] map_y Map for the y coordinate.
	*/
	void create_perspective2fisheye_LUT(cv::Mat &map_x, cv::Mat &map_y) {
		map_x.create( src_map_.size(), CV_32FC1 );
		map_y.create( src_map_.size(), CV_32FC1 );
		for (int y = 0; y < src_map_.rows; y++)
		{
			for (int x = 0; x < src_map_.cols; x++)
			{
				map_x.at<float>(y,x) = src_map_.at<cv::Vec2i>(y,x)[0]; 
				map_y.at<float>(y,x) = src_map_.at<cv::Vec2i>(y,x)[1];
			}
		}
	}


private:

	/** @brief It defines the transformation mode.
		0: No calibration. 1: OCamCalib
	*/
	int transform_mode_;

	/** @brief Original fish-eye image.
	           It contains the points from the fish-eye to perspective.
	*/
	cv::Mat src_map_;

	/** @brief Destination perspective image.
	           It contains the points from the perspective to fish-eye.
	*/
	cv::Mat dst_map_;

	/** @brief Size of the destination matrix
	*/
	cv::Size dest_size_;
};


}  // namespace transform
}	// namespace CmnIP

#endif /* CMNIP_TRANSFORM_FISHEYE2PERSPECTIVE_HPP__ */
