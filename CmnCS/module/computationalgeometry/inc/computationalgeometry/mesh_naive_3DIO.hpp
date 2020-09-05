/**
* @file mehs_naive_3DIO.hpp
* @brief Class to generate a mesh structure.
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.1.0.0
*
*/


#ifndef CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3DIO_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3DIO_HPP__

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace CmnCS
{
namespace computationalgeometry
{


/** @brief Class with mesh useful functions
*/
class MeshNaive3DIO
{
public:

	/** @brief Create the 3D mesh with texture

	Create the 3D mesh with texture
	@param[in] filename Filename to save the mesh and texture mapping.
	@param[in] mesh The 2D mesh structure to memorize.
	@param[in] m_3Dmap 3D point position for each pixel of the image.
	@param[in] size Texture image size.
	@param[in] k_ Maximum distance allowed to construct the triangles.
	@param[out] image Pointer to the image used to draw the connection
	result.
	*/
	static void create_model(
		const std::string &filename,
		const Mesh2D &mesh,
		const cv::Point3f &filter,
		std::map< std::pair<int, int>, cv::Point3f > &m_3Dmap,
		const cv::Size &size)
	{
		// Create the mesh association
		cv::Subdiv2D subdiv = mesh.subdiv();
		std::vector<cv::Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);
		std::vector<cv::Point> pt(3);

		// Save the triangle information
		std::ofstream myfile;

		myfile.open(filename);

		// Map the points of the image
		for (size_t i = 0; i < triangleList.size(); i++)
		{
			cv::Vec6f t, t_aux = triangleList[i];
			std::vector< cv::Point2f > v_src, v_dst;
			for (int j = 0; j < 3; j++)
			{
				v_src.push_back(cv::Point2f(t_aux[j * 2], t_aux[j * 2 + 1]));
			}
			// Reverse from the perspective image to the original coordinate
			v_dst = v_src;
			for (int j = 0; j < 3; j++)
			{
				t[j * 2] = v_dst[j].x;
				t[j * 2 + 1] = v_dst[j].y;
			}

			//std::cout << "Triangle: " << i << " " << t << std::endl;
			if (t[0] > 0 && t[0] < size.width &&
				t[1] > 0 && t[1] < size.width &&
				t[2] > 0 && t[2] < size.width &&
				t[3] > 0 && t[3] < size.width &&
				t[4] > 0 && t[4] < size.width &&
				t[5] > 0 && t[5] < size.width)
			{
				bool normal_direct_ = true;

				cv::Point2f p0(t[0], t[1]);
				cv::Point2f p1(t[2], t[3]);
				cv::Point2f p2(t[4], t[5]);
				cv::Point2f c(static_cast<float>(size.width) / 2, 
					static_cast<float>(size.height) / 2);
				if (CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p0, c) > filter.x ||
					CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p1, c) > filter.y ||
					CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p2, c) > filter.z)
					continue;

				cv::Point3f a = (m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])] - m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);
				cv::Point3f b = (m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])] - m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);
				cv::Point3f N = a.cross(b);
				float w = N.dot(m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);

				if (w > 0) {
					normal_direct_ = true;
				}
				else {
					normal_direct_ = false;
				}

				if (normal_direct_) {
					myfile << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].z << " " <<
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].z << " " <<
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].z << " " <<
						t[0] / size.width << " " << t[1] / size.height << " " <<
						t[2] / size.width << " " << t[3] / size.height << " " <<
						t[4] / size.width << " " << t[5] / size.height << std::endl;
				}
				else {
					myfile << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].z << " " <<
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].z << " " <<
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].x << " " << m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].y << " " << m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].z << " " <<
						t[0] / size.width << " " << t[1] / size.height << " " <<
						t[4] / size.width << " " << t[5] / size.height << " " <<
						t[2] / size.width << " " << t[3] / size.height << std::endl;
				}
			}
		}
		myfile.close();
		myfile.clear();
	}


	/** @brief Create the 3D mesh with texture

	Create the 3D mesh with texture
	@param[in] filename Filename to save the mesh and texture mapping.
	@param[in] mesh The 2D mesh structure to memorize.
	@param[in] m_3Dmap 3D point position for each pixel of the image.
	@param[in] size Texture image size.
	@param[in] k_ Maximum distance allowed to construct the triangles.
	@param[out] image Pointer to the image used to draw the connection
	result.
	*/
	static void create_model(
		const Mesh2D &mesh,
		const cv::Point3f &filter,
		std::map< std::pair<int, int>, cv::Point3f > &m_3Dmap,
		const cv::Size &size,
		std::vector< std::vector< std::pair< cv::Point2f, cv::Point3f> > > &naivemesh)
	{
		// Create the mesh association
		cv::Subdiv2D subdiv = mesh.subdiv();
		std::vector<cv::Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);
		std::vector<cv::Point> pt(3);

		// Map the points of the image
		for (size_t i = 0; i < triangleList.size(); i++)
		{
			cv::Vec6f t, t_aux = triangleList[i];
			std::vector< cv::Point2f > v_src, v_dst;
			for (int j = 0; j < 3; j++)
			{
				v_src.push_back(cv::Point2f(t_aux[j * 2], t_aux[j * 2 + 1]));
			}
			// Reverse from the perspective image to the original coordinate
			v_dst = v_src;
			for (int j = 0; j < 3; j++)
			{
				t[j * 2] = v_dst[j].x;
				t[j * 2 + 1] = v_dst[j].y;
			}

			//std::cout << "Triangle: " << i << " " << t << std::endl;
			if (t[0] > 0 && t[0] < size.width &&
				t[1] > 0 && t[1] < size.width &&
				t[2] > 0 && t[2] < size.width &&
				t[3] > 0 && t[3] < size.width &&
				t[4] > 0 && t[4] < size.width &&
				t[5] > 0 && t[5] < size.width)
			{
				bool normal_direct_ = true;

				cv::Point2f p0(t[0], t[1]);
				cv::Point2f p1(t[2], t[3]);
				cv::Point2f p2(t[4], t[5]);
				cv::Point2f c(size.width / 2, size.height / 2);
				if (CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p0, c) > filter.x ||
					CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p1, c) > filter.y ||
					CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p2, c) > filter.z)
					continue;

				cv::Point3f a = (m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])] - m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);
				cv::Point3f b = (m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])] - m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);
				cv::Point3f N = a.cross(b);
				float w = N.dot(m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])]);

				if (w > 0) {
					normal_direct_ = true;
				}
				else {
					normal_direct_ = false;
				}

				if (normal_direct_) {

					std::vector< std::pair< cv::Point2f, cv::Point3f > > triangles;

					triangles.push_back(
						std::make_pair(cv::Point2f(t[0] / size.width, t[1] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].x,
						m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].y,
						m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].z)));
					triangles.push_back(
						std::make_pair(cv::Point2f(t[2] / size.width, t[3] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].x,
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].y,
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].z)));
					triangles.push_back(
						std::make_pair(cv::Point2f(t[4] / size.width, t[5] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].x,
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].y,
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].z)));

					naivemesh.push_back(triangles);
				}
				else {

					std::vector< std::pair< cv::Point2f, cv::Point3f > > triangles;

					triangles.push_back(
						std::make_pair(cv::Point2f(t[0] / size.width, t[1] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].x,
						m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].y,
						m_3Dmap[std::pair<int, int>(t_aux[0], t_aux[1])].z)));
					triangles.push_back(
						std::make_pair(cv::Point2f(t[2] / size.width, t[3] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].x,
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].y,
						m_3Dmap[std::pair<int, int>(t_aux[2], t_aux[3])].z)));
					triangles.push_back(
						std::make_pair(cv::Point2f(t[4] / size.width, t[5] / size.height),
						cv::Point3f(m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].x,
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].y,
						m_3Dmap[std::pair<int, int>(t_aux[4], t_aux[5])].z)));

					naivemesh.push_back(triangles);

				}
			}
		}
	}

	/** @brief Load all the triangles
	*/
	static int loadTriangles_naive(const std::string &filename,
		std::vector< std::vector< float > > &v_triangles_)
	{
		std::ifstream myfile(filename);
		if (!myfile.is_open()) return 0;
		v_triangles_.clear();
		char buf[1024];
		myfile.getline(buf, 1024);
		myfile.getline(buf, 1024);
		while (!myfile.eof())
		{
			myfile.getline(buf, 1024);
			if (strlen(buf) <= 2) continue;

			float x[3], y[3], z[3], u[3], v[3];
			sscanf(buf, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
				&x[0], &y[0], &z[0],
				&x[1], &y[1], &z[1],
				&x[2], &y[2], &z[2],
				&u[0], &v[0],
				&u[1], &v[1],
				&u[2], &v[2]);
			std::vector<float> v_values;
			v_values.push_back(x[0]);
			v_values.push_back(y[0]);
			v_values.push_back(z[0]);
			v_values.push_back(x[1]);
			v_values.push_back(y[1]);
			v_values.push_back(z[1]);
			v_values.push_back(x[2]);
			v_values.push_back(y[2]);
			v_values.push_back(z[2]);
			v_values.push_back(u[0]);
			v_values.push_back(v[0]);
			v_values.push_back(u[1]);
			v_values.push_back(v[1]);
			v_values.push_back(u[2]);
			v_values.push_back(v[2]);
			v_triangles_.push_back(v_values);
		}
		myfile.close();
		myfile.clear();
		return 1;
	}

	/** @brief Load all the triangles
	*/
	static int loadTriangles_naive_v0(const std::string &filename,
		std::vector< std::vector< float > > &v_triangles_)
	{
		std::ifstream myfile(filename);
		if (!myfile.is_open()) return 0;
		v_triangles_.clear();
		char buf[1024];
		while (!myfile.eof())
		{
			myfile.getline(buf, 1024);
			if (strlen(buf) <= 2) continue;

			float x[3], y[3], z[3], u[3], v[3];
			sscanf(buf, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
				&x[0], &y[0], &z[0],
				&x[1], &y[1], &z[1],
				&x[2], &y[2], &z[2],
				&u[0], &v[0],
				&u[1], &v[1],
				&u[2], &v[2]);
			std::vector<float> v_values;
			v_values.push_back(x[0]);
			v_values.push_back(y[0]);
			v_values.push_back(z[0]);
			v_values.push_back(x[1]);
			v_values.push_back(y[1]);
			v_values.push_back(z[1]);
			v_values.push_back(x[2]);
			v_values.push_back(y[2]);
			v_values.push_back(z[2]);
			v_values.push_back(u[0]);
			v_values.push_back(v[0]);
			v_values.push_back(u[1]);
			v_values.push_back(v[1]);
			v_values.push_back(u[2]);
			v_values.push_back(v[2]);
			v_triangles_.push_back(v_values);
		}
		myfile.close();
		myfile.clear();
		return 1;
	}

};



} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3D_HPP__ */

