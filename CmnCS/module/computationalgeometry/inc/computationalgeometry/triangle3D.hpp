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


#ifndef CMNCS_COMPUTATIONALGEOMETRY_TRIANGLE3D_HPP__ 
#define CMNCS_COMPUTATIONALGEOMETRY_TRIANGLE3D_HPP__

#include <limits>       // std::numeric_limits
#include <vector>
#include <map>

#include "vertexN.hpp"

namespace CmnCS
{
namespace computationalgeometry
{


/** @brief Class used to define 2D-3D triangles structures.

	Class used to define 2D-3D triangles structures.
*/
template <typename _Ty2, typename _Ty3>
class Triangle3D
{
 public:

  Triangle3D() {}

  ~Triangle3D() {
	  clear();
  }

  /** @brief Clear the data.

	   Clear the data.
  */
  void clear() {
	  structure_.clear();
	  texture_.clear();
  }

  /** @brief Return if the triangle is valid.

	  Return if the triangle is valid.
	  @return Return TRUE if the triangle is valid. FALSE otherwise.
  */
  bool is_valid() {
	  if (structure_.size() >= 3 && texture_.size() >= 3) return true;
	  return false;
  }

  /** @brief Set the points.

	  Set the points.
	  @param[in] data The points information used for the setting. The data
	                  is in the format 
					  x0,y0,z0,x1,y1,z1,x2,y2,z2,u0,v0,u1,v1,u2,v2
	  @return Return 1 in case of success. 0 otherwise.
  */
  int set(const std::vector< float > &data) {
	  if (data.size() < 15) return 0;
	  clear();
	  for (int i = 0; i < 3; i++)
	  {
		  structure_.set(i, _Ty3(data[0 + i * 3], data[1 + i * 3],
		                                data[2 + i*3]));
	  }
	  for (int i = 0; i < 3; i++)
	  {
		  texture_.set(i, _Ty2(data[9 + i * 2], data[10 + i * 2]));
	  }
	  return 1;
  }

  /** @brief Set the points.

	  Set the points.
	  @param[in] v_structure Container with the 3D points.
	  @param[in] v_texture Container with the 2D texture points.
	  @return Return 1 in case of success. 0 otherwise.
  */
  int set(std::vector< _Ty3 > &v_structure,
	  std::vector< _Ty2 > &v_texture) {
	  if (v_structure.size() < 3 ||
		  v_texture.size() < 3) return 0;
	  clear();
	  for (int i = 0; i < 3; i++)
	  {
		  structure_.set(i, v_structure[i]);
	  }
	  for (int i = 0; i < 3; i++)
	  {
		  texture_.set(i, v_texture[i]);
	  }
	  return 1;
  }

  /** @brief Set the structure and texture information.

	  Set the structure and texture information.
	  @param[in] triangle Set the 
	  @return Return 1 in case of success. 0 otherwise.
  */
  int set(Triangle3D &triangle) {
	  if (!triangle.is_valid()) return 0;
	  structure_.clear();
	  texture_.clear();
	  std::vector< _Ty3 > v_structure;
	  std::vector< _Ty2 > v_texture;
	  triangle.get(v_structure, v_texture);
	  set(v_structure, v_texture);
	  return 1;
  }

  /** @brief Move a point on the structure.

	  Move a point on the structure.
  */
  int move(const _Ty3 &src, _Ty3 &dst) {
	  INDEX key;
	  if (!structure_.find(src, key)) return 0;
	  structure_.set(key, dst);
	  return 1;
  }

  /** @brief Move the nearest point on a structure.

	  Move the nearest point on a structure.
  */
  int move_nearest(const _Ty3 &src, _Ty3 &dst) {
	  INDEX key;
	  float distance = 0;
	  structure_.find_nearest(src, key, distance);
	  structure_.set(key, dst);
	  return 1;
  }

  /** @brief Move a point on the texture.

	  Move a point on the texture.
  */
  int move(const _Ty2 &src, _Ty2 &dst) {
	  INDEX key;
	  if (!texture_.find(src, key)) return 0;
	  texture_.set(key, dst);
	  return 1;
  }

  /** @brief Move a point on the texture by its key.

	  Move a point on the texture.
	  @param[in] key The key of research.
	  @param[in] dst The new point position.
	  @return Return 1 in case of success. 0 otherwise.
  */
  int move(INDEX key, _Ty2 &dst) {
	  if (!texture_.exist(key)) return 0;
	  texture_.set(key, dst);
	  return 1;
  }

  /** @brief Move a point on the structure by its key.

	  Move a point on the structure.
	  @param[in] key The key of research.
	  @param[in] dst The new point position.
	  @return Return 1 in case of success. 0 otherwise.
  */
  int move(INDEX key, _Ty3 &dst) {
	  if (!structure_.exist(key)) return 0;
	  structure_.set(key, dst);
	  return 1;
  }

  /** @brief Move the nearest point on the texture.

	  Move the nearest point on the texture.
  */
  int move_nearest(const _Ty2 &src, _Ty2 &dst) {
	  INDEX key;
	  float distance = 0;
	  texture_.find_nearest(src, key, distance);
	  texture_.set(key, dst);
	  return 1;
  }

  /** @brief Find the point.

	  Find the point.
	  @param[in] point The point to find.
	  @param[out] index The index of the detected point in the structure. It is
	                    equal to max numeric limit in case of failure.
	  @param[in] distance If >= 0 search the nearest point. Otherwise search
	                      exaclty the requested point.
	  @return Return TRUE in case of success.
  */
  bool find(const _Ty3 &point, INDEX &index, double distance = -1) {
	  INDEX key;
	  if (distance < 0 && structure_.find(point, key)) {
		  index = key;
		  return true;
	  } else if (distance >= 0 && structure_.find_nearest(point, distance, 
		  key)) {
		  index = key;
		  return true;
	  }
	  index = std::numeric_limits<INDEX>::max();
	  return false;
  }

  /** @brief Find the nearest point.

	  Find the nearest point.
	  @param[in] point The point to find.
	  @param[out] index The index of the detected point in the structure. It is
	                    equal to max numeric limit in case of failure.
	  @param[in] distance If >= 0 search the nearest point. Otherwise search
	                      the nearest point.
	  @return Return TRUE in case of success.
  */
  bool find_nearest(const _Ty3 &point, double min_distance, INDEX &index,
	  float &distance_out) {
	  INDEX key;
	  if (min_distance < 0 && structure_.find_nearest(point, key, distance_out)) {
		  index = key;
		  return true;
	  } else if (min_distance >= 0 && structure_.find_nearest(point, min_distance, 
		  key)) {
		  index = key;
		  return true;
	  }
	  index = std::numeric_limits<INDEX>::max();
	  return false;
  }


  /** @brief Find the nearest point.

	  Find the nearest point.
	  @param[in] point The point to find.
	  @param[out] index The index of the detected point in the structure. It is
	                    equal to max numeric limit in case of failure.
	  @param[in] distance If >= 0 search the nearest point. Otherwise search
	                      exaclty the requested point.
	  @return Return TRUE in case of success.
  */
  bool find(const _Ty2 &point, INDEX &index, double distance = -1) {
	  INDEX key;
	  if (distance < 0 && texture_.find(point, key)) {
		  index = key;
		  return true;
	  } else if (distance >= 0 && texture_.find_nearest(point, distance, 
		  key)) {
		  index = key;
		  return true;
	  }
	  index = std::numeric_limits<INDEX>::max();
	  return false;
  }

  /** @brief Find the nearest point.

	  Find the nearest point.
	  @param[in] point The point to find.
	  @param[out] index The index of the detected point in the structure. It is
	                    equal to max numeric limit in case of failure.
	  @param[in] distance If >= 0 search the nearest point. Otherwise search
	                      the nearest point.
	  @return Return TRUE in case of success.
  */
  bool find_nearest(const _Ty2 &point, double min_distance, INDEX &index,
	  float &distance_out) {
	  INDEX key;
	  if (min_distance < 0 && texture_.find_nearest(point, key, distance_out)) {
		  index = key;
		  return true;
	  } else if (min_distance >= 0 && texture_.find_nearest(point, min_distance, 
		  key)) {
		  index = key;
		  return true;
	  }
	  index = std::numeric_limits<INDEX>::max();
	  return false;
  }


  /** @brief Get the point of the structure and texture if it exist.

      Get the point of the structure and texture if it exist.
	  @param[in] index The index of the vertex to get.
	  @param[out] point_structure The 3D vertex position of the structure.
	  @param[out] point_texture The 2D vertex position of the texture.
	  @return Return TRUE in case of success. FALSE otherwise.
  */
  bool get(INDEX index, _Ty3 &point_structure, _Ty2 &point_texture)
  {
	  if (structure_.exist(index) && texture_.exist(index)) {
		  structure_.find(index, point_structure);
		  texture_.find(index, point_texture);
		  return true;
	  }
	  return false;
  }

  /** @brief Get all the points of the structure and texture if it exist.

      Get the points of the structure and texture if it exist.
	  @param[out] point_structure The 3D vertex position of the structure.
	  @param[out] point_texture The 2D vertex position of the texture.
	  @return Return 1 if there is at least 1 point. 0 otherwise.
  */
  int get(std::vector< _Ty3 > &point_structure,
	  std::vector< _Ty2 > &point_texture)
  {
	  point_structure.clear();
	  point_texture.clear();
	  if (structure_.size() == 0) return 0;
	  std::map< INDEX, _Ty3 > *pstructure = structure_.pt_data();
	  for (auto it = pstructure->begin(); it != pstructure->end(); it++)
	  {
		  if (!texture_.exist(it->first)) return 0;
		  point_structure.push_back( it->second );
		  _Ty2 p;
		  texture_.find(it->first, p);
		  point_texture.push_back( p );
	  }
	  return 1;
  }

  /** @brief Function to correct the normal of the triangle.

	  Function to correct the normal of the triangle for a correct 
	  representation.
	  @return Return 1 in case of success. 0 otherwise.
  */
  int correct_normal() {

	bool normal_direct_ = true;
	if (structure_.size() < 3) return 0;
	if (!structure_.exist(0) || !structure_.exist(1) || 
		!structure_.exist(2)) return 0;
	if (!texture_.exist(0) || !texture_.exist(1) || 
		!texture_.exist(2)) return 0;
	std::vector< _Ty3 > p3d(3);
	std::vector< _Ty2 > p2d(3);
	structure_.find(0, p3d[0]);
	structure_.find(1, p3d[1]);
	structure_.find(2, p3d[2]);
	//texture_.find(0, p2d[0]);
	texture_.find(1, p2d[1]);
	texture_.find(2, p2d[2]);
	_Ty3 a = p3d[2] - p3d[0];
	_Ty3 b = p3d[1] - p3d[0];
	_Ty3 N = a.cross(b);
	float w = N.dot(p3d[0]);

	if (w > 0) {
		// keep the same points
	} else {
		// reverse 1 and 2
		structure_.set(1, p3d[2]);
		structure_.set(2, p3d[1]);
		// texture need to be reversed too
		texture_.set(1, p2d[2]);
		texture_.set(2, p2d[1]);
	}
	return 1;
  }

 private:

  /** @brief Container with the 3D points structure
  */
  VertexN<_Ty3> structure_;

  /** @brief Container with the 2D points structure (for the texture mapping)
  */
  VertexN<_Ty2> texture_;
};


} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_TRIANGLE3D_HPP__ */
