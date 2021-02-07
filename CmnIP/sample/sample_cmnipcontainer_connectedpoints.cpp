/**
* @file sample_feature2d_connectedpoints.cpp
* @brief Example of how connected points are detected.cpp
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
* @version 1.0.0.0
*
*/

#include <iostream>
#include <queue>

#include "cmnipcontainer/inc/cmnipcontainer/cmnipcontainer_headers.hpp"

namespace
{

/** Test function
*/
void test()
{
	int min_radius = 0;
	int max_radius = 50;
	int height_ = 1024, width_ = 1024;
	cv::Mat image(height_, width_, CV_8UC3, cv::Scalar::all(0));
	cv::Size img_size(height_, width_);
	// Open a mask image
	cv::Mat mask = cv::imread("..\\..\\data\\mask.bmp", 0);
	if (mask.empty()) return;
	if (mask.size() != img_size) cv::resize(mask, mask, img_size);
	cv::imshow("mask", mask);
	// Find the borders of the mask
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
    // Find contours
#if CV_MAJOR_VERSION == 3
	cv::findContours(mask, contours, hierarchy, CV_RETR_TREE,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
#elif CV_MAJOR_VERSION == 4
	cv::findContours(mask, contours, hierarchy, cv::RETR_TREE,
		cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
#endif
	/// Draw contours
	cv::Mat drawing = cv::Mat::zeros( mask.size(), CV_8UC3 );
	for( size_t i = 0; i< contours.size(); i++ )
	{
		cv::Scalar color = cv::Scalar( 255,225 );
		cv::drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, 
			cv::Point() );
	}
	/// Show in a window
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
#elif CV_MAJOR_VERSION == 4
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow( "Contours", drawing );

	std::vector< cv::Point2f > v_vertex;
	std::set< std::pair<float, float> > points_sparse, tmp_container;

	// Add the extremes
	//for (auto it = contours.begin(); it != contours.end(); it++)
	//{
	//	for (auto it2 = it->begin(); it2 != it->end(); it2++)
	//	{
	//		points_sparse.insert( std::make_pair(it2->x, it2->y) );
	//	}
	//}

	// Add the extremes
	cv::Mat mask_cpy;
#if CV_MAJOR_VERSION == 3
	cv::cvtColor(mask, mask_cpy, CV_GRAY2BGR);
#elif CV_MAJOR_VERSION == 4
	cv::cvtColor(mask, mask_cpy, cv::COLOR_GRAY2BGR);
#endif
	int counter_insert_sparse = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = contours.begin(); it != contours.end(); it++)
	{
		for (auto it2 = it->begin(); it2 != it->end(); it2++)
		{
#else
	for (std::vector<std::vector<cv::Point> >::const_iterator it = contours.begin(); it != contours.end(); it++)
	{
		for (std::vector<cv::Point>::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
#endif
			std::cout << "Insert sparse: " << 
				counter_insert_sparse++ << std::endl;
			points_sparse.insert( std::make_pair(it2->x, it2->y) );
			cv::circle(mask_cpy, cv::Point(it2->x, it2->y), 2, cv::Scalar(0,0,255), 3);
		}
	}
	cv::imshow("mask_cpy", mask_cpy);

	// Scan the drawing and get the points
	float epsilon = 2;
	tmp_container.insert( std::make_pair(points_sparse.begin()->first,
		points_sparse.begin()->second) );
	std::queue<std::pair<float, float> > remaining;
	remaining.push( std::make_pair(points_sparse.begin()->first,
		points_sparse.begin()->second) );
	//std::queue<cv::Point2f> remaining;
	//remaining.push( cv::Point2f(points_sparse.begin()->first,
	//	points_sparse.begin()->second) );
	CmnIP::cmnipcontainer::ContourOperations::get_point(remaining, drawing, 
		max_radius - epsilon * 2, max_radius / 2, epsilon, tmp_container);

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = tmp_container.begin(); it != tmp_container.end(); it++)
#else
	for (std::set< std::pair<float, float> >::const_iterator it = tmp_container.begin(); it != tmp_container.end(); it++)
#endif
	{
		points_sparse.insert( std::make_pair( it->first, it->second ) );
	}

	// If use random points
	bool use_random_points = false;
	if (use_random_points) {
		max_radius = 300;
		v_vertex.clear();
		points_sparse.clear();
		for (int i = 0; i < 100; i++)
		{
			int imin = 50, imax = 462;
			int x = std::rand() % width_;
			while (x < imin || x > imax) x = std::rand() % width_;
			int y = std::rand() % height_;
			while (y < imin || y > imax) y = std::rand() % width_;
			points_sparse.insert( std::make_pair(x, y) );
		}
	}

	// Set the vertex
	// Best solution would be to scan the points
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = points_sparse.begin(); it != points_sparse.end(); it++)
#else
	for (std::set< std::pair<float, float> >::const_iterator it = points_sparse.begin(); it != points_sparse.end(); it++)
#endif
	{
		v_vertex.push_back( cv::Point2f( it->first, it->second ) );
	}

	if (use_random_points) {
		std::vector< cv::Point2f > ch;
		// Find the Hull borders
		CmnIP::cmnipcontainer::GeometricalOperations::convexHullArea(v_vertex, ch);
		v_vertex = ch;
	}

	// Display the points
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v_vertex.begin(); it != v_vertex.end(); it++)
#else
	for (std::vector< cv::Point2f >::const_iterator it = v_vertex.begin(); it != v_vertex.end(); it++)
#endif
	{
		cv::circle(image, *it, 1, cv::Scalar::all(255));
	}

	//cv::imshow("image", image);
	//cv::waitKey();


	// Use the border information to create the mesh
	// The total number of points outnumber the hull numbers.
	// Calculate the normals of the vertex hull
	int size = v_vertex.size();
	// Put the normals on the vertex
	std::vector< cv::Point2f > v_norm;
	for (int i = 0; i < size; i++)
	{
		int j = (i + 1) % size;
		float dx = v_vertex[j].x - v_vertex[i].x;
		float dy = v_vertex[j].y - v_vertex[i].y;
		//cv::Point2f norm(-dy, dx);
		cv::Point2f norm(dy, -dx);
		v_norm.push_back( norm );
		//cv::line(image, 
		//	cv::Point( v_vertex[i].x * width_, 
		//				v_vertex[i].y * height_ ),
		//	cv::Point( (v_vertex[i].x + norm.x) * width_, 
		//				(v_vertex[i].y + norm.y) * height_ ),
		//	cv::Scalar(0,255));
	}

	// Estimate all the connecting points which belong to the border.
	cv::Point2f norm = v_norm[0];
	cv::Point2f point = v_vertex[0];
	cv::Point2f spoint = v_vertex[0];
	// Clear the points and re-assign the first
	std::set< std::pair<float, float> > vertex_used;
	vertex_used.insert( std::make_pair(point.x, point.y) );
	cv::circle(image, point, 3, cv::Scalar(0,255));
	// Scan for the extremes
	bool bContinue = true;
	int iMaxIterations = 100;
	int iIteration = 0;
	while (bContinue && iIteration < iMaxIterations)
	{
		cv::Mat display(height_,width_,CV_8UC3,cv::Scalar::all(0));
		// Get the next point
		cv::Point2f point_out;
		cv::Point2f norm_out;
		if (!CmnIP::cmnipcontainer::Connection2D::get_next_connected(
			norm, point, points_sparse, min_radius, max_radius,
			norm_out, point_out)) {
			bContinue = false;
		}
		if (spoint !=  point_out) {
			norm = norm_out;
			point = point_out;
			if (vertex_used.find(std::make_pair(point.x, point.y)) != 
				vertex_used.end()) {
				vertex_used.insert( std::make_pair(point.x, point.y) );
				iIteration = 0;
			}
			cv::circle(image, point, 3, cv::Scalar(0,255,255));
			cv::imshow("image", image);
			cv::waitKey(500);
		} else {
			bContinue = false;
		}
		++iIteration;
	}

	// Display the points
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = vertex_used.begin(); it != vertex_used.end(); it++)
#else
	for (std::set< std::pair<float, float> >::const_iterator it = vertex_used.begin(); it != vertex_used.end(); it++)
#endif
	{
		cv::circle(image, cv::Point(it->first, it->second), 1, cv::Scalar(0,0,255));
	}

	cv::imshow("image", image);
	cv::waitKey();
}

}	// namespace

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test connected points" << std::endl;
	test();
	return 0;
}

#endif
