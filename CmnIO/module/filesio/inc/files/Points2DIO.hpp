#ifndef CMNIO_FILESIO_POINTS2DIO_HPP__
#define CMNIO_FILESIO_POINTS2DIO_HPP__

#include <fstream>
#include <iostream>
#include <map>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save a set of points.
*/
class Points2DIO
{
  public:

	  template <typename _Ty>
	  static bool save_points(const std::string &filename_mesh,
		  int x, int y, int width, int height,
		  std::map<int, _Ty> &m_points)
	  {
		  std::ofstream myfile;
		  myfile.open(filename_mesh);
		  if (!myfile.is_open()) return false;
		  myfile << "Mesh2D Ver 0.1" << std::endl;
		  myfile << "Rectangle " << x << " " << y << " " << width << " " << 
			  height << std::endl;
		  myfile << "NumPoints " << m_points.size() << std::endl;
		  for (auto it = m_points.begin(); it != m_points.end(); it++)
		  {
			  myfile << it->first << " " << it->second.x << " " << 
				  it->second.y << std::endl;
		  }
		  myfile.close();
		  myfile.clear();
		  return true;
	  }
};



} // namespace filesio
} // namespace CmnIO


#endif /* CMNIO_FILESIO_POINTS2DIO_HPP__ */