#ifndef CMNIO_FILESIO_PAIRS2DIO_HPP__
#define CMNIO_FILESIO_PAIRS2DIO_HPP__

#include <fstream>
#include <iostream>
#include <map>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to save a set of points.
*/
class Pairs2DIO
{
  public:


	  /** @brief Save a collection of pairs.

	  @note The second point in the pair is adjusted with the offset_dest position
	  to give the origin to the 0,0 point.
	  */
	  template <typename _Ty>
	  static bool save_pairs(const std::string &filename,
		  std::map< std::pair<int, int>, std::map<int, std::pair<_Ty, _Ty> > > &m_m_points)
	  {
		  std::ofstream myfile;
		  myfile.open(filename);
		  if (!myfile.is_open()) return false;

		  myfile << "SelectPair_v002" << std::endl;
		  myfile << "#idA idB xA yA xB yB" << std::endl;
		  for (auto it = m_m_points.begin(); it != m_m_points.end(); it++)
		  {
			  for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			  {
				  myfile << it->first.first << " " << it->first.second << " " <<
					  it2->first << " " <<
					  it2->second.first.x << " " <<
					  it2->second.first.y << " " <<
					  it2->second.second.x << " " <<
					  it2->second.second.y << std::endl;
			  }
		  }
		  myfile.close();
		  myfile.clear();

		  return true;
	  }


	  /** @brief Save a collection of pairs.

	      @note The second point in the pair is adjusted with the offset_dest position
	        to give the origin to the 0,0 point.
	  */
	  template <typename _Ty>
	  static bool save_pairs(const std::string &filename,
		  _Ty &offset_dest, float xscale0, float yscale0, 
		  float xscale1, float yscale1,
		  std::map< std::pair<int, int>, std::map<int, std::pair<_Ty, _Ty> > > &m_m_points)
	  {
		  std::ofstream myfile;
		  myfile.open(filename);
		  if (!myfile.is_open()) return false;

		  myfile << "SelectPair_v002" << std::endl;
		  myfile << "#idA idB xA yA xB yB" << std::endl;
		  for (auto it = m_m_points.begin(); it != m_m_points.end(); it++)
		  {
			  for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			  {
				  myfile << it->first.first << " " << it->first.second << " " <<
					  it2->first << " " <<
					  it2->second.first.x / xscale0 << " " <<
					  it2->second.first.y / yscale0 << " " <<
					  (it2->second.second.x - offset_dest.x) / xscale1 << " " <<
					  (it2->second.second.y - offset_dest.y) / yscale1 << std::endl;
			  }
		  }
		  myfile.close();
		  myfile.clear();

		  return true;
	  }


	  /** @brief Load a collection of pairs.

	  */
	  template <typename _Ty>
	  static bool load_pairs(const std::string &filename,
		  std::map< std::pair<int, int>, std::map<int, std::pair<_Ty, _Ty> > > &m_m_points)
	  {
		  std::ifstream f;
		  f.open(filename);
		  if (!f.is_open()) return false;
		  char buf[1024];
		  f.getline(buf, 1024);
		  f.getline(buf, 1024);
		  // Information
		  while (!f.eof())
		  {
			  f.getline(buf, 1024);
			  if (std::strlen(buf) > 3) {
				  int idx[2];
				  float val[4];
				  int s = 0;
				  sscanf(buf, "%i %i %i %f %f %f %f", &idx[0], &idx[1], &s,
					  &val[0], &val[1], &val[2], &val[3]);
				  //if (m_m_points.find(std::make_pair(idx[0], idx[1])) !=
					 // m_m_points.end()) {
					 // s = m_m_points[std::make_pair(idx[0], idx[1])].size();
				  //}
				  m_m_points[std::make_pair(idx[0], idx[1])][s].first =
					  cv::Point2f(val[0], val[1]);
				  m_m_points[std::make_pair(idx[0], idx[1])][s].second =
					  cv::Point2f(val[2], val[3]);
			  }
		  }
		  f.close();
		  f.clear();

		  return true;
	  }

};



} // namespace filesio
} // namespace CmnIO


#endif /* CMNIO_FILESIO_PAIRS2DIO_HPP__ */