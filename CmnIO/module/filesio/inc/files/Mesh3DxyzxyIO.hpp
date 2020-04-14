#ifndef CMNIO_FILESIO_MESH3DXYZXYIO_HPP__
#define CMNIO_FILESIO_MESH3DXYZXYIO_HPP__

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "cmnlibworld\inc\cmnlibworld\cmnlibworld_headers.hpp"

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save the remap data information
*/
class Mesh3DXYZXY
{
  public:

	  /** @brief Function to load a set of XYZXY points for further purposes.

	  Function to load a set of XYZXY points for further purposes.

	  @param[in] filename Source file.
	  @param[out] containerxyzxy Container with the 3D2D information.
	  @return Return TRUE if the file has been found. False otherwise.

	  @note The file structure data expected is:
	  id X(3d) Y(3d) Z(3d) X(2d i.e. image) Y(2d i.e. image)
	  */
	  template <typename _Ty2, typename _Ty3>
	  static bool SaveSourceXYZXY_naive(
		  const std::string &filename,
		  std::vector< std::pair<_Ty3, _Ty2> > &containerxyzxy) {
		  // Container with the 3D points in the space and 2D points in the source data.
		  // XYZ point, XY image coordinate

		  std::ofstream f(filename);
		  if (!f.is_open()) return false;
		  f << "SourceXYZXY_naive_v001" << std::endl;
		  f << "id x y z x(u) y(v)" << std::endl;
		  size_t s = containerxyzxy.size();
		  for (size_t i = 0; i < s; ++i)
		  {
			  f << i << " " <<
				  containerxyzxy[i].first.x << " " <<
				  containerxyzxy[i].first.y << " " <<
				  containerxyzxy[i].first.z << " " <<
				  containerxyzxy[i].second.x << " " <<
				  containerxyzxy[i].second.y << std::endl;
		  }
		  f.close();
		  f.clear();

		  return true;
	  }

	  /** @brief Function to load a set of XYZXY points for further purposes.

	  Function to load a set of XYZXY points for further purposes.

	  @param[in] filename Source file.
	  @param[out] containerxyzxy Container with the 3D2D information.
	  @return Return TRUE if the file has been found. False otherwise.

	  @note The file structure data expected is:
	  id X(3d) Y(3d) Z(3d) X(2d i.e. image) Y(2d i.e. image)
	  */
	  template <typename _Ty2, typename _Ty3>
	  static bool LoadSourceXYZXY_naive(
		  const std::string &filename,
		  std::vector< std::pair<_Ty3, _Ty2> > &containerxyzxy) {
		  // Container with the 3D points in the space and 2D points in the source data.
		  // XYZ point, XY image coordinate

		  std::ifstream f(filename);
		  if (!f.is_open()) return false;
		  char buf[1024];
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  while (!f.eof())
		  {
			  f.getline(buf, 1024);
			  _Ty3 xyz;
			  _Ty2 xy;
			  int id;
			  if (strlen(buf) > 3)
			  {
				  sscanf(buf, "%i %f %f %f %f %f", &id, &xyz.x, &xyz.y, &xyz.z, &xy.x, &xy.y);
				  containerxyzxy.push_back(std::make_pair(xyz, xy));
			  }
		  }
		  f.close();
		  f.clear();

		  return true;
	  }


	  /** @brief Function to load a set of XYZXY points for further purposes.

	  Function to load a set of XYZXY points for further purposes.

	  @param[in] filename Source file.
	  @param[out] containerxyzxy Container with the 3D2D information.
	  @return Return TRUE if the file has been found. False otherwise.

	  @note The file structure data expected is:
	  id X(3d) Y(3d) Z(3d) X(2d i.e. image) Y(2d i.e. image)
	  */
	  template <typename _Ty2, typename _Ty3>
	  static bool SaveSourceXYZXY_naive(
		  const std::string &filename,
		  std::map<int, std::vector< std::pair<_Ty2, _Ty3> > > &containerxyxyz) {
		  // Container with the 3D points in the space and 2D points in the source data.
		  // XYZ point, XY image coordinate

		  std::ofstream f(filename);
		  if (!f.is_open()) return false;
		  f << "SourceXYZXY_naive_v002" << std::endl;
		  f << "id x(u) y(v) x y z " << std::endl;
		  for (auto it : containerxyxyz)
		  {
			  for (auto it2 : it.second)
			  {
				  f << it.first << " " <<
					  it2.first.x << " " << it2.first.y << " " <<
					  it2.second.x << " " << it2.second.y << " " << 
					  it2.second.z << std::endl;
			  }
		  }
		  f.close();
		  f.clear();

		  return true;
	  }

	  /** @brief Function to load a set of XYZXY points for further purposes.

	  Function to load a set of XYZXY points for further purposes.

	  @param[in] filename Source file.
	  @param[out] containerxyzxy Container with the 3D2D information.
	  @return Return TRUE if the file has been found. False otherwise.

	  @note The file structure data expected is:
	  id X(3d) Y(3d) Z(3d) X(2d i.e. image) Y(2d i.e. image)
	  */
	  template <typename _Ty2, typename _Ty3>
	  static bool LoadSourceXYZXY_naive(
		  const std::string &filename,
		  std::map<int, std::vector< std::pair<_Ty2, _Ty3> > > &containerxyxyz) {
		  // Container with the 3D points in the space and 2D points in the source data.
		  // XYZ point, XY image coordinate

		  std::ifstream f(filename);
		  if (!f.is_open()) return false;
		  char buf[1024];
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  while (!f.eof())
		  {
			  f.getline(buf, 1024);
			  _Ty3 xyz;
			  _Ty2 xy;
			  int id;
			  if (strlen(buf) > 3)
			  {
				  sscanf(buf, "%i %f %f %f %f %f", &id, &xy.x, &xy.y, &xyz.x, &xyz.y, &xyz.z);
				  containerxyxyz[id].push_back(std::make_pair(xy, xyz));
			  }
		  }
		  f.close();
		  f.clear();

		  return true;
	  }


};

} // namespace filesio
} // namespace CmnIO


#endif /* CMNIO_FILESIO_MESH3DXYZXYIO_HPP__ */