/**
* @file sample_numericsystem_numericsystem.cpp
* @brief Sample dynamic.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include "computationalgeometry\inc\computationalgeometry\computationalgeometry_headers.hpp"

namespace
{

void test()
{
	CmnCS::computationalgeometry::Mesh2D mesh2d;
	mesh2d.setup(cv::Rect(0, 0, 2048, 2048));
	//mesh2d.add(cv::Point2f(100, 100));
	//mesh2d.add(cv::Point2f(100, 1948));
	//mesh2d.add(cv::Point2f(1948, 1948));
	//mesh2d.add(cv::Point2f(1948, 100));
	mesh2d.add(cv::Point2f(1000, 100));
	mesh2d.add(cv::Point2f(1000, 2000));
	mesh2d.add(cv::Point2f(100, 1000));
	mesh2d.add(cv::Point2f(2000, 1000));


	cv::Mat img(cv::Size(2048, 2048), CV_8UC3, cv::Scalar::all(0));
	CmnCS::computationalgeometry::Draw::mesh_voronoi(mesh2d, img);
	CmnCS::computationalgeometry::Draw::mesh(mesh2d, img);
	cv::resize(img, img, cv::Size(img.cols / 2, img.rows / 2));
	cv::imshow("img", img);

	//CmnCS::computationalgeometry::Mesh3D<cv::Point2f, cv::Point3f> mesh3d;
	//std::vector<cv::Point3f> v_structure;
	//v_structure.push_back(cv::Point3f(-0.5, 0.3, -1));
	//v_structure.push_back(cv::Point3f(0.5, 0.3, -1));
	//v_structure.push_back(cv::Point3f(0.5, -0.3, -0.7));
	//v_structure.push_back(cv::Point3f(0.5, -0.3, -1));
	//v_structure.push_back(cv::Point3f(0.0, 1.2, -1.5));
	//mesh3d.add(v_structure, mesh2d.vector_points());
	//mesh3d.save("mesh3d.txt");

	std::map< std::pair< int, int >, cv::Point3f > m_3dmap;
	m_3dmap[std::make_pair(100, 100)] = cv::Point3f(-0.5, -0.5, -1);
	m_3dmap[std::make_pair(100, 1948)] = cv::Point3f(-0.5, 0.5, -1);
	m_3dmap[std::make_pair(1948, 1948)] = cv::Point3f(0.5, 0.5, -1);
	m_3dmap[std::make_pair(1948, 100)] = cv::Point3f(0.5, -0.5, -1);
	CmnCS::computationalgeometry::MeshNaive3DIO::create_model("testmesh.txt", mesh2d,
		cv::Point3f(100, 100, 100), m_3dmap, cv::Size(2048, 2048));

	//CmnCS::computationalgeometry::MeshGenerator::create_model("testmesh.txt", mesh2d, )
	cv::waitKey();

	CmnCS::computationalgeometry::ConvertPlane2D3D convert_plane_2d3d;
	cv::Point2f xy(10, 20), uv;
	cv::Point3f xyz;
	convert_plane_2d3d.map_xy_uv<cv::Point2f>(xy, 0, 0, 256, 256, 
		uv);
	convert_plane_2d3d.map_uv_xyz<cv::Point2f, cv::Point3f>(uv, 2, -1, xyz);
	std::cout << "CmnCS::computationalgeometry::ConvertPlane2D3D" << std::endl;
	std::cout << "Convert: " << xy << " -> " << uv << " -> " << xyz << 
		std::endl;

}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample ComputationalGeometry" << std::endl;
	test();
}


