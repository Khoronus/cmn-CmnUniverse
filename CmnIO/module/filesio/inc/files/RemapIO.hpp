#ifndef CMNIO_FILESIO_REMAPIO_HPP__
#define CMNIO_FILESIO_REMAPIO_HPP__

#include <iostream>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace CmnIO
{
namespace filesio
{


/** @brief Class to save the remap data information
*/
class RemapIO
{
  public:

	  static int save(const std::string &filename, cv::Mat &src)
	  {
		  std::ofstream f(filename);
		  f << src.cols << " " << src.rows << std::endl;
		  for (int y = 0; y < src.rows; ++y)
		  {
			  for (int x = 0; x < src.cols; ++x)
			  {
				  f << src.at<float>(y, x) << std::endl;
			  }
		  }
		  f.close();
		  f.clear();
		  return 1;
	  }

	  static int load(const std::string &filename, cv::Mat &src)
	  {
		  std::ifstream f(filename);
		  char buf[256];
		  f.getline(buf, 256);
		  int w = 0, h = 0;
		  sscanf(buf, "%i %i", &w, &h);
		  src = cv::Mat(h, w, CV_32FC1);
		  for (int y = 0; y < src.rows; ++y)
		  {
			  for (int x = 0; x < src.cols; ++x)
			  {
				  f >> src.at<float>(y, x);
			  }
		  }
		  f.close();
		  f.clear();
		  return 1;
	  }

	  /** @brief Save two map remap
	  */
	  static int save(const std::string &filename, const std::string &keyword, cv::Mat &map)
	  {
		  cv::FileStorage fs(filename, cv::FileStorage::WRITE);

		  fs << keyword << map;
		  fs.release();
		  return 1;
	  }

	  /** @brief Load two map remap
	  */
	  static int load(const std::string &filename, const std::string &keyword, cv::Mat &map)
	  {
		  cv::FileStorage fs2(filename, cv::FileStorage::READ);

		  fs2[keyword] >> map;

		  fs2.release();
		  return 1;
	  }


	  /** @brief Save two map remap
	  */
	  static int save(const std::string &filename, cv::Mat &mapx, cv::Mat &mapy)
	  {
		  cv::FileStorage fs(filename, cv::FileStorage::WRITE);

		  fs << "mapx" << mapx;
		  fs << "mapy" << mapy;
		  fs.release();
		  return 1;
	  }

	  /** @brief Load two map remap
	  */
	  static int load(const std::string &filename, cv::Mat &mapx, cv::Mat &mapy)
	  {
		  cv::FileStorage fs2(filename, cv::FileStorage::READ);

		  fs2["mapx"] >> mapx;
		  fs2["mapy"] >> mapy;

		  fs2.release();
		  return 1;
	  }

	  /** @brief Save two map remap
	  */
	  static int save(const std::string &filename, cv::Mat &mapx, cv::Mat &mapy, cv::Mat &mapz)
	  {
		  cv::FileStorage fs(filename, cv::FileStorage::WRITE);

		  fs << "mapx" << mapx << "mapy" << mapy << "mapz" << mapz;
		  fs.release();
		  return 1;
	  }

	  /** @brief Load two map remap
	  */
	  static int load(const std::string &filename, cv::Mat &mapx, cv::Mat &mapy, cv::Mat &mapz)
	  {
		  cv::FileStorage fs2(filename, cv::FileStorage::READ);

		  fs2["mapx"] >> mapx;
		  fs2["mapy"] >> mapy;
		  fs2["mapz"] >> mapz;

		  fs2.release();
		  return 1;
	  }
};

} // namespace filesio
} // namespace CmnIO



#endif /* CMNIO_FILESIO_REMAPIO_HPP__ */