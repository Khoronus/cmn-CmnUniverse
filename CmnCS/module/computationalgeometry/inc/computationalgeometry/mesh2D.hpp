/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

// File Version 0.1.1.2

#ifndef CMNCS_COMPUTATIONALGEOMETRY_MESH2D_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_MESH2D_HPP__

#include <iostream>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

#include "cmncscore\inc\cmncscore\error.hpp"
#include "cmncscore\inc\cmncscore\deprecated.hpp"
#include "cmnmathworld\inc\cmnmathworld\cmnmathworld_headers.hpp"

namespace CmnCS
{
namespace computationalgeometry
{

/** Structure for the 2D mesh information
*/
class Mesh2D
{
public:

	~Mesh2D() {
		subdiv_.initDelaunay(cv::Rect(0,0,1,1));
	}

	/** Setup the delunay structure
	*/
	void setup(const cv::Rect &rect) {
		rect_ = rect;
		subdiv_.initDelaunay(rect);
	}

	/** clear
	*/
	void clear() {
		points_.clear();
		subdiv_.initDelaunay(rect_);
	}

	/** Add a point to the list
	*/
	void add( const cv::Point2f &pt ) {
		if (pt.x > rect_.x && pt.y > rect_.y &&
			pt.x < rect_.x + rect_.width &&
			pt.y < rect_.y + rect_.height) {

			int index = static_cast<int>(points_.size());
			points_[index] = pt;
			locate_point(pt);
			subdiv_.insert(pt);
		
		}
	}

	/** Add a point to the list.

	    Add a point to the list. It checks that no other points are set near
		to reduce the number of vertexes for a polygon in construction phase.

		@return Return true if succeeded, false otherwise.
	*/
	bool add(const cv::Point2f &pt, const float min_radius) {
		if (pt.x > rect_.x && pt.y > rect_.y &&
			pt.x < rect_.x + rect_.width &&
			pt.y < rect_.y + rect_.height) {

			// check that no points are already nearly placed
			for (auto it : points_)
			{
				float d = CmnMath::geometry::DistanceZeroDimPoint::point_point_2d(
					pt, it.second);
				if (d < min_radius) return false;
			}

			int index = static_cast<int>(points_.size());
			points_[index] = pt;
			locate_point(pt);
			subdiv_.insert(pt);

			return true;
		}
		return false;
	}



	/** Add a point to the list
	*/
	void set( int index, const cv::Point2f &pt ) {
		points_[index] = pt;
		subdiv_.initDelaunay(rect_);
		add_vector_of_points();
		//locate_point(pt);
		//subdiv_.insert(pt);
	}

	/** Get the list of points memorized
	*/
	std::map< int, cv::Point2f > points() const {
		return points_;
	}

	/** Get the points memorized
	*/
	std::map< int, cv::Point2f >& points() {
		return points_;
	}

	/** Get a vector of points
	*/
	std::vector<cv::Point2f> vector_points() {
		std::vector< cv::Point2f > v_points;
		for( std::map< int, cv::Point2f >::const_iterator 
			it = points_.begin(); it != points_.end(); it++)
		{
			v_points.push_back( it->second );
		}
		return v_points;
	}

	/** Get the delunay structure
	*/
	cv::Subdiv2D& subdiv() {
		return subdiv_;
	}

	/** Get the delunay structure
	*/
	cv::Subdiv2D subdiv() const {
		return subdiv_;
	}

	/** Save the mesh information
		@param[in] filename Filename to save the file.
		@return Return 0 in case of failure
	*/
	int save(const std::string &filename) {
		std::ofstream myfile;
		myfile.open(filename.c_str());
		if (!myfile.is_open()) return 0;

		myfile << "Mesh2D Ver 0.2" << std::endl;
		myfile << "Rectangle " << rect_.x << " " << rect_.y << " " << 
			rect_.width << " " << rect_.height << std::endl;
		myfile << "NumPoints " << points_.size() << std::endl;
		for( std::map< int, cv::Point2f >::const_iterator 
			it = points_.begin(); it != points_.end(); it++)
		{
			myfile << it->first << " " << it->second.x << " " << it->second.y << std::endl;
		}

		myfile.close();
		myfile.clear();

		return 1;
	}

	/** Load the mesh information
		@param[in] filename Filename to save the file.
		@return Return 0 in case of failure
	*/
	int load(const std::string &filename) {
		std::ifstream myfile;
		myfile.open(filename.c_str());
		if (!myfile.is_open()) return 0;

		char buf[512];
		// Get the version (not used now)
		myfile.getline(buf, 512);
		// Get the region size
		myfile.getline(buf, 512);
		sscanf(buf, "%i %i %i %i", &rect_.x, &rect_.y, &rect_.width, &rect_.height);
		subdiv_.initDelaunay(rect_);

		// Get the points
		points_.clear();
		int n = 0;
		char buf_tmp[512];
		myfile.getline(buf, 512);
		sscanf(buf, "%s %i", buf_tmp, &n);
		for (int i = 0; i < n; i++)
		{
			myfile.getline(buf, 512);
			if (strlen(buf) < 2) continue;
			float x, y;
			int id;
			sscanf(buf, "%i %f %f", &id, &x, &y);
			points_[id] = cv::Point2f(x, y);
		}

		myfile.close();
		myfile.clear();

		// Add the vector of points
		add_vector_of_points();

		return 1;
	}

	/** Set a vector of points
	*/
	void set(const std::vector< cv::Point2f > &points)
	{
		clear();
		points_.clear();
		int index = 0;
		for (std::vector< cv::Point2f >::const_iterator
			it = points.begin(); it != points.end(); it++)
		{
			if (it->x >= rect_.tl().x && it->x < rect_.br().x &&
				it->y >= rect_.tl().y && it->y < rect_.br().y)
				points_[index++] = *it;
		}
		add_vector_of_points();
	}

	/** Get the subdivisions in triangle form
	*/
	void getSubdivision(std::vector< cv::Vec6f > &triangleList_)
	{
		std::vector<cv::Vec6f> triangleList;
		subdiv_.getTriangleList(triangleList);
		std::vector<cv::Point> pt(3);

		for( size_t i = 0; i < triangleList.size(); i++ )
		{
			cv::Vec6f t = triangleList[i];
			pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
			pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
			pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));

			if (pt[0].inside(rect_) && pt[1].inside(rect_) && pt[2].inside(rect_))
			{
				triangleList_.push_back(triangleList[i]);
			}

		}
	}

private:

	/** @brief Container of the 2D points
	*/
	//std::vector< cv::Point2f > points_;
	std::map< int, cv::Point2f > points_;

	/** @brief Structure for the Delunay points and analysis
	*/
	cv::Subdiv2D subdiv_;

	/** @brief Delunay region size
	*/
	cv::Rect rect_;

	/** Locate the point position
		@param[in] fp Point to use
	*/
	void locate_point( const cv::Point2f fp )
	{
		int e0=0, vertex=0;

		subdiv_.locate(fp, e0, vertex);

		if( e0 > 0 )
		{
			int e = e0;
			do
			{
				cv::Point2f org, dst;
				if( subdiv_.edgeOrg(e, &org) > 0 && subdiv_.edgeDst(e, &dst) > 0 )
				{}//line( img, org, dst, active_color, 3, CV_AA, 0 );

				e = subdiv_.getEdge(e, cv::Subdiv2D::NEXT_AROUND_LEFT);
			}
			while( e != e0 );
		}

		//draw_subdiv_point( img, fp, active_color );
	}

	/** Add the memorized vector of points to the delunay structure.
		Mainly used after load the points
	*/
	void add_vector_of_points()
	{
		cv::redirectError(handleErrorCalib);
		for( std::map< int, cv::Point2f >::const_iterator 
			it = points_.begin(); it != points_.end(); it++)
		{
			//locate_point(it->second);
			try
			{
				subdiv_.insert(it->second);
			}
			catch(cv::Exception &e)
			{
				//std::cout << "Exc: " << e.what();
			}
			catch(...)
			{
				//std::cout << "Exception";
			}
		}
		cv::redirectError(NULL);
	}
};

/** Draw the mesh
*/
class Draw
{
public:

	static void mesh(const Mesh2D &mesh, cv::Mat &img) {
	    cv::Scalar active_facet_color(0, 0, 255), delaunay_color(255,255,255);
		draw_subdiv(img, mesh.subdiv(), active_facet_color);
	}

	static void mesh_voronoi(const Mesh2D &mesh, cv::Mat &img) {
		paint_voronoi(img, mesh.subdiv());
	}

	static void mesh_voronoi(const Mesh2D &mesh, cv::Size &size, 
		std::vector<cv::Mat> &vimg) {
		paint_voronoi(mesh.subdiv(), size, vimg);
	}


	static void mesh_voronoi_index(const Mesh2D &mesh, cv::Mat &img) {
		index_voronoi(img, mesh.subdiv());
	}


private:


	static void draw_subdiv_point( cv::Mat& img, cv::Point2f fp, cv::Scalar color )
	{
#if CV_MAJOR_VERSION == 3
		cv::circle( img, fp, 3, color, CV_FILLED, 8, 0 );
#else if CV_MAJOR_VERSION == 4
		cv::circle(img, fp, 3, color, cv::FILLED, 8, 0);
#endif
	}

	static bool point_valid( const cv::Point &pt, const cv::Point &tl, const cv::Point &br)
	{
		//std::cout << pt << " " << tl << " " << br << std::endl;
		if (pt.x >= tl.x && pt.x < br.x && pt.y >= tl.y && pt.y < br.y) 
			return true;
		return false;
	}

	/** Draw the subdivision
	*/
	static void draw_subdiv( cv::Mat& img, cv::Subdiv2D &subdiv, cv::Scalar &delaunay_color )
	{
	#if 1
		std::vector<cv::Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);
		std::vector<cv::Point> pt(3);

		//std::cout << "Triangles" << std::endl;

		for( size_t i = 0; i < triangleList.size(); i++ )
		{
			cv::Vec6f t = triangleList[i];
			pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
			pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
			pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));
#if CV_MAJOR_VERSION == 3
			if (point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
			if (point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
			if (point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
#else if CV_MAJOR_VERSION == 4
			if (point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[0], pt[1], delaunay_color, 1, cv::LINE_AA, 0);
			if (point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[1], pt[2], delaunay_color, 1, cv::LINE_AA, 0);
			if (point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[2], pt[0], delaunay_color, 1, cv::LINE_AA, 0);
#endif
		}
	#else
		vector<Vec4f> edgeList;
		subdiv.getEdgeList(edgeList);
		for( size_t i = 0; i < edgeList.size(); i++ )
		{
			Vec4f e = edgeList[i];
			Point pt0 = Point(cvRound(e[0]), cvRound(e[1]));
			Point pt1 = Point(cvRound(e[2]), cvRound(e[3]));
			line(img, pt0, pt1, delaunay_color, 1, CV_AA, 0);
		}
	#endif
	}


	static void draw_subdiv( cv::Mat& img, cv::Subdiv2D subdiv, cv::Scalar &delaunay_color )
	{
	#if 1
		std::vector<cv::Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);
		std::vector<cv::Point> pt(3);

		//std::cout << "Triangles" << std::endl;

		for( size_t i = 0; i < triangleList.size(); i++ )
		{
			cv::Vec6f t = triangleList[i];
			pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
			pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
			pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));

#if CV_MAJOR_VERSION == 3
			if (point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
			if (point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
			if (point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
#else if CV_MAJOR_VERSION == 4
			if (point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[0], pt[1], delaunay_color, 1, cv::LINE_AA, 0);
			if (point_valid(pt[1], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[1], pt[2], delaunay_color, 1, cv::LINE_AA, 0);
			if (point_valid(pt[2], cv::Point(0, 0), cv::Point(img.cols, img.rows)) &&
				point_valid(pt[0], cv::Point(0, 0), cv::Point(img.cols, img.rows)))
				cv::line(img, pt[2], pt[0], delaunay_color, 1, cv::LINE_AA, 0);
#endif

		}
	#else
		vector<Vec4f> edgeList;
		subdiv.getEdgeList(edgeList);
		for( size_t i = 0; i < edgeList.size(); i++ )
		{
			Vec4f e = edgeList[i];
			Point pt0 = Point(cvRound(e[0]), cvRound(e[1]));
			Point pt1 = Point(cvRound(e[2]), cvRound(e[3]));
			line(img, pt0, pt1, delaunay_color, 1, CV_AA, 0);
		}
	#endif
	}


	static void paint_voronoi( cv::Mat& img, cv::Subdiv2D &subdiv )
	{
		std::vector<std::vector<cv::Point2f> > facets;
		std::vector<cv::Point2f> centers;
		subdiv.getVoronoiFacetList(std::vector<int>(), facets, centers);

		std::vector<cv::Point> ifacet;
		std::vector<std::vector<cv::Point> > ifacets(1);

		for( size_t i = 0; i < facets.size(); i++ )
		{
			ifacet.resize(facets[i].size());
			for( size_t j = 0; j < facets[i].size(); j++ )
				ifacet[j] = facets[i][j];

			cv::Scalar color;
			color[0] = rand() & 255;
			color[1] = rand() & 255;
			color[2] = rand() & 255;
			cv::fillConvexPoly(img, ifacet, color, 8, 0);

			ifacets[0] = ifacet;
#if CV_MAJOR_VERSION == 3
			cv::polylines(img, ifacets, true, cv::Scalar(), 1, CV_AA, 0);
			cv::circle(img, centers[i], 3, cv::Scalar(), -1, CV_AA, 0);
#else if CV_MAJOR_VERSION == 4
			cv::polylines(img, ifacets, true, cv::Scalar(), 1, cv::LINE_AA, 0);
			cv::circle(img, centers[i], 3, cv::Scalar(), -1, cv::LINE_AA, 0);
#endif
		}
	}

	static void paint_voronoi( cv::Mat& img, cv::Subdiv2D subdiv )
	{
		std::vector<std::vector<cv::Point2f> > facets;
		std::vector<cv::Point2f> centers;
		subdiv.getVoronoiFacetList(std::vector<int>(), facets, centers);

		std::vector<cv::Point> ifacet;
		std::vector<std::vector<cv::Point> > ifacets(1);

		for( size_t i = 0; i < facets.size(); i++ )
		{
			ifacet.resize(facets[i].size());
			for( size_t j = 0; j < facets[i].size(); j++ )
				ifacet[j] = facets[i][j];

			cv::Scalar color;
			color[0] = rand() & 255;
			color[1] = rand() & 255;
			color[2] = rand() & 255;
			cv::fillConvexPoly(img, ifacet, color, 8, 0);

			ifacets[0] = ifacet;
#if CV_MAJOR_VERSION == 3
			cv::polylines(img, ifacets, true, cv::Scalar(), 1, CV_AA, 0);
			cv::circle(img, centers[i], 3, cv::Scalar(), -1, CV_AA, 0);
#else if CV_MAJOR_VERSION == 4
			cv::polylines(img, ifacets, true, cv::Scalar(), 1, cv::LINE_AA, 0);
			cv::circle(img, centers[i], 3, cv::Scalar(), -1, cv::LINE_AA, 0);
#endif
		}
	}


	static void paint_voronoi(cv::Subdiv2D subdiv,
		cv::Size &size, std::vector< cv::Mat > &out)
	{
		std::vector<std::vector<cv::Point2f> > facets;
		std::vector<cv::Point2f> centers;
		subdiv.getVoronoiFacetList(std::vector<int>(), facets, centers);

		std::vector<cv::Point> ifacet;
		std::vector<std::vector<cv::Point> > ifacets(1);

		for (size_t i = 0; i < facets.size(); i++)
		{
			cv::Mat m(size, CV_8U, cv::Scalar::all(0));
			ifacet.resize(facets[i].size());
			for (size_t j = 0; j < facets[i].size(); j++)
				ifacet[j] = facets[i][j];

			cv::Scalar color;
			color[0] = 255;
			color[1] = 255;
			color[2] = 255;
			cv::fillConvexPoly(m, ifacet, color, 8, 0);

			ifacets[0] = ifacet;
#if CV_MAJOR_VERSION == 3
			cv::polylines(m, ifacets, true, cv::Scalar(), 1, CV_AA, 0);
#else if CV_MAJOR_VERSION == 4
			cv::polylines(m, ifacets, true, cv::Scalar(), 1, cv::LINE_AA, 0);
#endif
			out.push_back(m);
		}
	}


	/** IMPORTANT: The index start from 1 not from 0, to be able to separate 
	    the elements
	*/
	static void index_voronoi( cv::Mat& img, cv::Subdiv2D subdiv )
	{
		std::vector<std::vector<cv::Point2f> > facets;
		std::vector<cv::Point2f> centers;
		subdiv.getVoronoiFacetList(std::vector<int>(), facets, centers);

		std::vector<cv::Point> ifacet;
		std::vector<std::vector<cv::Point> > ifacets(1);

		img = cv::Scalar::all(-1);

		for( size_t i = 0; i < facets.size(); i++ )
		{
			ifacet.resize(facets[i].size());
			for( size_t j = 0; j < facets[i].size(); j++ )
				ifacet[j] = facets[i][j];

			cv::Scalar color;
			color[0] = i+1;
			color[1] = i+1;
			color[2] = i+1;
			cv::fillConvexPoly(img, ifacet, color, 8, 0);
		}
	}
};

} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_MESH2D_HPP__ */
