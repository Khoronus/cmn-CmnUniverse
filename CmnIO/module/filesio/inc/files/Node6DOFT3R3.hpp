#ifndef CMNIO_FILESIO_NODE6DOFT3R3_HPP__
#define CMNIO_FILESIO_NODE6DOFT3R3_HPP__

#include <fstream>
#include <iostream>
#include <map>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save the information about 6 degrees of freedom.
*/
class Node6DOFT3R3
{
  public:

	  /** @brief It saves a collection of points in a raw form.

	      It saves a collection of points in a raw form.
		  Header
		  NumPoints #
		  id x y z r_x, r_y, r_z
		  ...
	  */
	  template <typename _Ty3>
	  static bool save(const std::string &filename,
		  std::map<int, _Ty3> &m_origin, std::map<int, _Ty3> &m_angle)
	  {
		  std::ofstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  f << "Node6DOFXYZPTR Ver 0.1" << std::endl;
		  f << "#id x y z p t r" << std::endl;
		  for (auto it : m_origin)
		  {
			  int idx = it.first;
			  if (m_angle.find(idx) != m_angle.end())
			  {
				  f << it.first << " " << it.second.x << " " << it.second.y << " " << it.second.z << " " <<
					  m_angle[idx].x << " " << m_angle[idx].y << " " << m_angle[idx].z << std::endl;
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  template <typename _Ty3>
	  static bool load(const std::string &filename,
		  std::map<int, _Ty3> &m_origin, std::map<int, _Ty3> &m_angle)
	  {
		  std::ifstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  char buf[1024];
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  while (!f.eof())
		  {
			  f.getline(buf, 1024);
			  if (strlen(buf) > 3) {
				  int id = 0;
				  float x = 0, y = 0, z = 0;
				  float r_x = 0, r_y = 0, r_z = 0;
				  sscanf(buf, "%i %f %f %f %f %f %f", &id, &x, &y, &z, 
					  &r_x, &r_y, &r_z);
				  m_origin[id] = _Ty3(x, y, z);
				  m_angle[id] = _Ty3(r_x, r_y, r_z);
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

};



} // namespace filesio
} // namespace CmnIO


#endif /* CMNIO_FILESIO_NODE6DOFT3R3_HPP__ */