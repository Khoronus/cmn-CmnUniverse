/**
* @file Points3DIO.hpp
* @brief Header of all the files related to the IO for points 3D.
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.2.0.0
*
*/

#ifndef CMNIO_FILESIO_POINTS3DIO_HPP__
#define CMNIO_FILESIO_POINTS3DIO_HPP__

#include <fstream>
#include <iostream>
#include <map>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save a set of points.
*/
class Points3DIO
{
  public:

	  /** @brief It saves a collection of points in a raw form.

	      It saves a collection of points in a raw form.
		  Header
		  NumPoints #
		  id x y z
		  ...
	  */
	  template <typename _Ty3>
	  static bool save_collection(const std::string &filename,
		  std::map<int, _Ty3> &m_points)
	  {
		  std::ofstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  f << "Points3D Ver 0.1" << std::endl;
		  f << "#NumPoints #" << std::endl;
		  f << "#id x y z" << std::endl;
		  f << "NumPoints " << m_points.size() << std::endl;
		  for (auto it = m_points.begin(); it != m_points.end(); it++)
		  {
			  f << it->first << " " << it->second.x << " " << 
				  it->second.y << " " << it->second.z << std::endl;
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  template <typename _Ty3>
	  static bool load_collection(const std::string &filename,
		  std::map<int, _Ty3> &m_points)
	  {
		  std::ifstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  char buf[1024];
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  while (!f.eof())
		  {
			  f.getline(buf, 1024);
			  if (strlen(buf) > 3) {
				  int id = 0;
				  float x = 0, y = 0, z = 0;
				  sscanf(buf, "%i %f %f %f", &id, &x, &y, &z);
				  m_points[id] = _Ty3(x, y, z);
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  /** @brief It saves a collection of points in a raw form.

	  It saves a collection of points in a raw form.
	  Header
	  NumPoints #
	  id x y z
	  ...
	  */
	  template <typename _Txyz, typename _Trgb>
	  static bool save_collection(const std::string &filename,
		  std::vector<std::pair<_Txyz, _Trgb> > &v_points)
	  {
		  std::ofstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  f << "PointsXYZRGB Ver 0.1" << std::endl;
		  f << "x y z r g b" << std::endl;
		  for (auto it : v_points)
		  {
			  f << it.first.x << " " << it.first.y << " " << it.first.z << " " <<
				   it.second.x << " " << it.second.y << " " << it.second.z << 
				   std::endl;
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  template <typename _Txyz, typename _Trgb>
	  static bool load_collection(const std::string &filename,
		  std::vector<std::pair<_Txyz, _Trgb> > &v_points)
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
				  float x = 0, y = 0, z = 0;
				  float r = 0, g = 0, b = 0;
				  sscanf(buf, "%f %f %f", &x, &y, &z, &r, &g, &b);
				  v_points.push_back(std::make_pair(_Txyz(x, y, z), _Trgb(r, g, b)));
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }


};



} // namespace filesio
} // namespace CmnIO


#endif // CMNIO_FILESIO_POINTS3DIO_HPP__ 