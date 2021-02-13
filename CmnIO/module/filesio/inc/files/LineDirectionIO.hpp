/**
* @file filesio_headers.hpp
* @brief Header of all the files related to the line direction IO
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
#ifndef CMNIO_FILESIO_LINEDIRECTIONIO_HPP__
#define CMNIO_FILESIO_LINEDIRECTIONIO_HPP__

#include <fstream>
#include <iostream>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save the remap data information
*/
class LineDirectionIO
{
  public:

	  template <typename _Ty2, typename _Ty3>
	  static bool save_dir(const std::string &filename,
		  std::map<int, std::vector< std::pair<_Ty3, _Ty2> > > &dir)
	  {
		  std::ofstream f(filename);
		  if (!f.is_open()) return false;
		  f << "LineDirectionXYZXYIO v0.0.1" << std::endl;
		  f << "#desc id XYZ.X XYZ.Y XYZ.Z XY.X XY.Y" << std::endl;
		  for (auto it : dir)
		  {
			  for (auto it2 : it.second)
			  {
				  f << it.first << " " << it2.first.x << " " << it2.first.y << " " <<
					  it2.first.z << " " << it2.second.x << " " << it2.second.y <<
					  std::endl;
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  template <typename _Ty2, typename _Ty3>
	  static  bool load_dir(const std::string &filename,
		  std::map<int, std::vector< std::pair<cv::Point3f, cv::Point2f> > > &dir)
	  {
		  std::ifstream f(filename);
		  if (!f.is_open()) return false;
		  char buf[512];
		  f.getline(buf, 512); // header
		  f.getline(buf, 512); // descriptor
		  // content
		  while (!f.eof())
		  {
			  f.getline(buf, 512);
			  if (strlen(buf) > 3) {
				  int id = 0;
				  _Ty3 xyz;
				  _Ty2 xy;
				  sscanf(buf, "%i %f %f %f %f %f", &id,
					  &xyz.x, &xyz.y, &xyz.z, &xy.x, &xy.y);
				  dir[id].push_back(std::make_pair(xyz, xy));
			  }
		  }
		  f.close();
		  f.clear();
	  }


	  template <typename _Ty3>
	  static bool save_dir(const std::string &filename,
		  std::map<int, std::vector< _Ty3 > > &dir)
	  {
		  std::ofstream f(filename);
		  if (!f.is_open()) return false;
		  f << "LineDirectionXYZIO v0.0.1" << std::endl;
		  f << "#desc id XYZ.X XYZ.Y XYZ.Z" << std::endl;
		  for (auto it : dir)
		  {
			  for (auto it2 : it.second)
			  {
				  f << it.first << " " << it2.x << " " << it2.y << " " << 
					  it2.z << std::endl;
			  }
		  }
		  f.close();
		  f.clear();
		  return true;
	  }

	  template <typename _Ty3>
	  static  bool load_dir(const std::string &filename,
		  std::map<int, std::vector< cv::Point3f > > &dir)
	  {
		  std::ifstream f(filename);
		  if (!f.is_open()) return false;
		  char buf[512];
		  f.getline(buf, 512); // header
		  f.getline(buf, 512); // descriptor
		  // content
		  while (!f.eof())
		  {
			  f.getline(buf, 512);
			  if (strlen(buf) > 3) {
				  int id = 0;
				  _Ty3 xyz;
				  sscanf(buf, "%i %f %f %f", &id,
					  &xyz.x, &xyz.y, &xyz.z);
				  dir[id].push_back(xyz);
			  }
		  }
		  f.close();
		  f.clear();
	  }


};

} // namespace filesio
} // namespace CmnIO


#endif // CMNIO_FILESIO_LINEDIRECTIONIO_HPP__
