/**
* @file structure_texture.hpp
* @brief Contains classes to manage the 3D structure and textures, merge and
* split.
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
* @version 1.1.1.0
*
*/


#ifndef CMNCS_COMPUTATIONALGEOMETRY_MESH3D_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_MESH3D_HPP__

#include <limits>       // std::numeric_limits
#include <vector>
#include <map>

#include "mesh_naive_3DIO.hpp"
#include "triangle3D.hpp"

namespace CmnCS
{
namespace computationalgeometry
{


/** @brief Class used to define 2D-3D triangles structures.

	Class used to define 2D-3D triangles structures.
*/
template <typename _Ty2, typename _Ty3>
class Mesh3D
{
 public:

  Mesh3D() {
	  clear();
  }

  void clear() {
	  index_last_valid_ = 0;
	  m_triangle_.clear();
  }

  /** @brief Add a new triangle to the list.

      Add a new triangle to the list. It does not check if it is univoque.
	  @param[in] v_values Vector with the triangles 3D and texture points 
	                      information.
  */
  void add(const std::vector< float > &v_values) {
	  if (m_triangle_[index_last_valid_].set(v_values)) {
		++index_last_valid_;
	  }
  }

  /** @brief Add a new triangle to the list.

      Add a new triangle to the list. It does not check if it is univoque.
	  @param[in] v_structure Vector with the triangles 3D structure.
	  @param[in] v_texture Vector with the texture points information.
  */
  void add(std::vector< _Ty3 > &v_structure,
	  std::vector< _Ty2 > &v_texture) {
	  if (m_triangle_[index_last_valid_].set(v_structure, v_texture)) {
		++index_last_valid_;
	  }
  }

  /** @brief Add a new triangle to the list.

	  Add a new triangle to the list.
  */
  void add(Triangle3D<_Ty2, _Ty3> &triangle) {
	  if (m_triangle_[index_last_valid_].set(triangle)) {
		++index_last_valid_;
	  }
  }

  /** @brief Check if a vertex of a triangle were found, and the index.

	  Check if a vertex of a triangle were found, and the index. If the
	  distance is too big, it can match with other triangle points.
	  The distance should be used only for minimal errors. Otherwise use a
	  function can get the minimum distance.

	  @param[in] point The point to check.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find(const _Ty2 &point, std::pair<int, INDEX> &index,
	  double distance = 10e-5) {
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  if (it->second.find(point, index.second, distance)) {
			  index.first = it->first;
			  return true;
		  }
	  }
	  return false;
  }

  /** @brief Check if a vertex of a triangle were found, and the index.

	  Check if a vertex of a triangle were found, and the index. If the
	  distance is too big, it can match with other triangle points.
	  The distance should be used only for minimal errors. Otherwise use a
	  function can get the minimum distance.
	  Multiple triangles vertexes can be detected.

	  @param[in] point The point to check.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find(const _Ty2 &point,
	  std::vector< std::pair<int,INDEX> > &index, double distance = 10e-5) {
	  index.clear();
	  bool bFound = false;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  INDEX idx = 0;
		  if (it->second.find(point, idx, distance)) {
			  index.push_back( std::make_pair(it->first, idx) );
			  bFound = true;
		  }
	  }
	  return bFound;
  }

  /** @brief Check if a vertex of a triangle were found, and the index.

	  Check if a vertex of a triangle were found, and the index. If the
	  distance is too big, it can match with other triangle points.
	  The distance should be used only for minimal errors. Otherwise use a
	  function can get the minimum distance.

	  @param[in] point The point to check.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find_nearest(const _Ty2 &point, std::pair<int, INDEX> &index,
	  double distance = 10e-5) {

	  float min_distance_internal = std::numeric_limits<float>::max();
	  bool bFound = false;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  float dmin = std::numeric_limits<float>::max();
		  INDEX idx = 0;
		  if (it->second.find_nearest(point, distance, idx, dmin)) {
			  if (dmin < min_distance_internal) {
				  min_distance_internal = dmin;
				  index.first = it->first;
				  index.second = idx;
				  bFound = true;
			  }
		  }
	  }
	  return bFound;
  }


  /** @brief Check if a vertex of a triangle were found, and the index.

	  Check if a vertex of a triangle were found, and the index. If the
	  distance is too big, it can match with other triangle points.
	  The distance should be used only for minimal errors. Otherwise use a
	  function can get the minimum distance.

	  @param[in] point The point to check.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find(const _Ty3 &point, std::pair<int, INDEX> &index,
	  double distance = 10e-5) {
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  if (it->second.find(point, index.second, distance)) {
			  index.first = it->first;
			  return true;
		  }
	  }
	  return false;
  }

  /** @brief Check if a vertex of a triangle were found, and the index.

	  Check if a vertex of a triangle were found, and the index. If the
	  distance is too big, it can match with other triangle points.
	  The distance should be used only for minimal errors. Otherwise use a
	  function can get the minimum distance.
	  Multiple triangles vertexes can be detected.

	  @param[in] point The point to check.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find(const _Ty3 &point,
	  std::vector< std::pair<int,INDEX> > &index, double distance = 10e-5) {
	  index.clear();
	  bool bFound = false;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  INDEX idx = 0;
		  if (it->second.find(point, idx, distance)) {
			  index.push_back( std::make_pair(it->first, idx) );
			  bFound = true;
		  }
	  }
	  return bFound;
  }


  /** @brief Check if a triangle is memorized.

	  Check if a triangle is memorized.

	  @param[in] point The vector extremes of the triangle to find.
	  @param[out] index A pair of index (index triangle, index vertex).
	  @param[in] distance The minimum distance allowed. 
	                      If negative it is searched a perfect match.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool find(const std::vector<_Ty3> &v_points,
	  int &index, double distance = 10e-5) {
	  if (v_points.size() != 3) return false;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		INDEX idx;
		if (it->second.find( v_points[0], idx, distance)) {
			if (it->second.find( v_points[1], idx, distance)) {
				if (it->second.find( v_points[2], idx, distance)) {
					index = it->first;
					return true;
				}
			}
		}
	  }
	  return false;
  }


  /** @brief Return if a vertex of a triangle were found, and the index.
  */
  bool get(std::pair<int, INDEX> &index, _Ty3 &space_position,
	  _Ty2 &texture_position) {
	  if (m_triangle_.find(index.first) != m_triangle_.end())
	  {
		  m_triangle_[index.first].get(index.second, space_position, 
			  texture_position);
		  return true;
	  }
	  return false;
  }


  /** @brief Get a triangle data.
	  
	  Get a triangle data.
	  @param[in] index The index of the triangle.
	  @param[out] triangle The triangle object.
	  @return Return 1 in case of success.
  */
  int get(int index, Triangle3D<_Ty2, _Ty3> &triangle) {
	  if (m_triangle_.find(index) != m_triangle_.end()) {
		  triangle = m_triangle_[index];
		  return 1;
	  }
	  return 0;
  }

  /** @brief Get all the mesh texture vertexes.
	  
	  Get all the mesh texture vertexes.
	  @param[in] kWidth The texture u position is multiplied by the constant.
	  @param[in] kHeight The texture v position is multiplied by the constant.
	  @param[out] v_points The total number of vertex found.
	  @return Return 1 in case of success.
  */
  int get(const int kWidth, const int kHeight,
	  std::vector< _Ty2 > &v_points) {
	  v_points.clear();
	  if (m_triangle_.size() == 0) return 0;
	  std::map< std::pair< float, float >, int > m_vertex;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++) {
		  std::vector< _Ty3 > point_structure;
		  std::vector< _Ty2 > point_texture;
		  it->second.get(point_structure, point_texture);
		  for (auto it2 = point_texture.begin(); 
			   it2 != point_texture.end(); it2++) {
			m_vertex[ std::make_pair( it2->x * kWidth, it2->y * kHeight) ] = 1;
		  }
	  }
	  // Minimize the points
	  for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	  {
		  _Ty2 p(it->first.first, it->first.second);
		  int s = v_points.size();
		  bool bFound = false;
		  //for (int i = 0; i < s; i++)
		  //{
			 // float distance = std::sqrt(
				//  std::pow((float)(v_points[i].x / kWidth) - (float)(p.x / kWidth), 2) + 
				//  std::pow((float)(v_points[i].y / kHeight) - (float)(p.y / kHeight), 2) );
			 // if (distance < 0.1) bFound = true;
		  //}
		  if (!bFound) v_points.push_back( p );
	  }
	  return 1;
  }


  /** @brief Get all the mesh vertexes.
	  
	  Get all the mesh vertexes.
	  @param[in] kWidth The texture u position is multiplied by the constant.
	  @param[in] kHeight The texture v position is multiplied by the constant.
	  @param[out] v_points The total number of vertex found.
	  @return Return 1 in case of success.
  */
  int get(std::vector< _Ty3 > &v_points) {
	  v_points.clear();
	  if (m_triangle_.size() == 0) return 0;
	  std::map< std::pair< float, std::pair< float, float > >, int > m_vertex;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++) {
		  std::vector< _Ty3 > point_structure;
		  std::vector< _Ty2 > point_texture;
		  it->second.get(point_structure, point_texture);
		  for (auto it2 = point_structure.begin(); 
			   it2 != point_structure.end(); it2++) {
			m_vertex[ std::make_pair(it2->x, 
				std::make_pair( it2->y, it2->z)) ] = 1;
		  }
	  }
	  // Minimize the points
	  for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	  {
		  _Ty3 p(it->first.first, it->first.second.first,
			  it->first.second.second);
		  int s = v_points.size();
		  v_points.push_back( p );
	  }
	  return 1;
  }


  /** @brief Move a point to a new position based on its index value.

	  Move a point to a new position based on its index value.
	  @param[in] index The index of the triangle and vertex.
	  @param[in] position The new vertex position.
	  @return Return 1 in case of success.
  */
  int move(std::pair<int, INDEX> &index, _Ty2 &position) {
	  if (m_triangle_.find(index.first) != m_triangle_.end())
	  {
		  m_triangle_[index.first].move(index.second, position);
		  return 1;
	  }
	  return 0;
  }

  /** @brief Move all the points within an area to a new position.

	  Move all the points within an area to a new position.
	  @param[in] origin The original position where the points are expected
	                    to be.
	  @param[in] position The new vertex position.
	  @param[in] distance The maximum distance from the origin.
	  @return Return 1 in case of success.
  */
  void move(_Ty2 &origin, _Ty2 &position,
	  double distance = 10e-5) {

	  std::vector< std::pair<int, INDEX > > v_index;
	  if (find(origin, v_index, distance))
	  {
		  for (auto it = v_index.begin(); it != v_index.end(); it++)
		  {
			  move(*it, position);
		  }
	  }
  }


  /** @brief Return the last valid index.

	  Return the last valid index.
	  @return Return the last valid index.
  */
  int index_last_valid() {
	  return index_last_valid_;
  }

  /** @brief Save the triangles file information in a mesh form.

	  Save the triangles file information in a mesh form.
	  @param[in] filename Name of the file to save the data.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool save(const std::string &filename)
  {
	  std::ofstream myfile(filename);
	  if (!myfile.is_open()) return false;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  // correct the normals
		  it->second.correct_normal();

		  std::vector< _Ty3 > v_p3d;
		  std::vector< _Ty2 > v_p2d;

		  it->second.get(v_p3d, v_p2d);
		  for (auto it2 = v_p3d.begin(); it2 != v_p3d.end(); it2++)
		  {
			  myfile << it2->x << " " << it2->y << " " << it2->z << " ";
		  }
		  for (auto it2 = v_p2d.begin(); it2 != v_p2d.end(); it2++)
		  {
			  myfile << it2->x << " " << it2->y << " ";
		  }
		  myfile << std::endl;
	  }
	  myfile.close(); 
	  myfile.clear();
	  return true;
  }

  /** @brief Save in ply format
  */
  bool save_ply(const std::string &filename)
  {
	  std::vector< _Ty3 > v_points;
	  if (!get(v_points)) return false;

	  std::ofstream myfile(filename);
	  if (!myfile.is_open()) return false;
	  myfile << "ply" << std::endl;
	  myfile << "format ascii 1.0" << std::endl;
	  myfile << "element vertex " << v_points.size() << std::endl;
	  myfile << "property float32 x" << std::endl;
	  myfile << "property float32 y" << std::endl;
	  myfile << "property float32 z" << std::endl;
	  myfile << "element face " << size() << std::endl;
	  myfile << "property list uint8 int32 vertex_indices" << std::endl;
	  myfile << "end_header" << std::endl;

	  // copy the vertex
	  std::map< std::pair<float, std::pair< float, float > >, int > m_vertex;
	  int index = 0;
	  for (auto it = v_points.begin(); it != v_points.end(); it++)
	  {
		  myfile << it->x << " " << it->y << " " << it->z << std::endl;
		  m_vertex[ std::make_pair(it->x, std::make_pair(it->y, it->z) ) ] = index;
		  ++index;
	  }
	  // copy the faces
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  // scan the vertex and find the index
		  std::vector< _Ty3 > point_structure;
		  std::vector< _Ty2 > point_texture;
		  it->second.get(point_structure, point_texture);
		  // search for the vertex
		  myfile << "3 ";
		  if (point_structure.size() != 3) system("pause");
		  for (auto it2 = point_structure.begin(); it2 != point_structure.end(); it2++)
		  {
			  myfile << m_vertex[ std::make_pair(it2->x, std::make_pair(it2->y, it2->z) ) ] << " ";
		  }
		  myfile << std::endl;
	  }

	  myfile.close(); 
	  myfile.clear();
	  return true;
  }


  /** @brief Load the triangles file information in a mesh form.

	  Load the triangles file information in a mesh form.
	  @param[in] filename Name of the file to save the data.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool load(const std::string &filename)
  {
	  std::vector< std::vector< float > > v_triangles_;
	  if (!MeshNaive3DIO::loadTriangles_naive(filename, v_triangles_)) return false;
	  m_triangle_.clear();
	  index_last_valid_ = 0;

	  // Get only the triangles that have vertex over a certain height
	  for (auto it = v_triangles_.begin(); it != v_triangles_.end(); it++)
	  {
		  add(*it);
	  }
	  return true;
  }


  /** @brief Return the triangle information in a vector form.

	  Return the triangle information in a vector form.
	  @param[out] values It contains all the triangles vertex information.
	  @param[out] num_triangles The total number of triangles.
	  @param[out] triangles_elems The total number of floats.
  */
  void toVector(float *p_out, int &num_triangles, int &triangles_elems)
  {
	  num_triangles = 0;
	  triangles_elems = 0;
	  for (auto it = m_triangle_.begin(); it != m_triangle_.end(); it++)
	  {
		  // correct the normals
		  it->second.correct_normal();

		  std::vector< cv::Point3f > v_p3d;
		  std::vector< cv::Point2f > v_p2d;

		  it->second.get(v_p3d, v_p2d);
		  for (auto it2 = v_p3d.begin(); it2 != v_p3d.end(); it2++)
		  {
			  p_out[triangles_elems++] = it2->x;
			  p_out[triangles_elems++] = it2->y;
			  p_out[triangles_elems++] = it2->z;
		  }
		  for (auto it2 = v_p2d.begin(); it2 != v_p2d.end(); it2++)
		  {
			  p_out[triangles_elems++] = it2->x;
			  p_out[triangles_elems++] = it2->y;
		  }
		  ++num_triangles;
	  }
  }

  /** @brief Return the number of items memorized.

	  Return the number of items memorized.
	  @return Return the number of items memorized.
  */
  int size() {
	  return m_triangle_.size();
  }

  /** @brief Return the container with all the triangles.

	  Return the container with all the triangles.
	  @return Return the container with all the triangles.
  */
  std::map<int, Triangle3D<_Ty2, _Ty3>> &m_triangle() {
	  return m_triangle_;
  }

 private:

  /** @brief It contains the set of triangles that defines the mesh.
			 A better container can be a multimap with the std::pair<int,int>
			 as key, where the points are 2D bin position.
  */
  std::map<int, Triangle3D<_Ty2, _Ty3>> m_triangle_;

  /** @brief It contains the last valid index. Incrementally increased. It is
      necessary to reprocess the triangle container in order to change the
	  value.
  */
  int index_last_valid_;
};


} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_MESH3D_HPP__ */
