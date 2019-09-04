#ifndef CMNIP_FEATURE_LBPHISTOGRAM_HPP__
#define CMNIP_FEATURE_LBPHISTOGRAM_HPP__

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

//! \author philipp <bytefish[at]gmx[dot]de>
//! \copyright BSD, see LICENSE.

#include <opencv2/opencv.hpp>
#include <limits>

namespace CmnIP{
namespace feature {

class LBPHistogram
{
  public:

	// templated functions
	template <typename _Tp>
	static void histogram_(const cv::Mat& src, cv::Mat& hist, int numPatterns, int divisions);

	template <typename _Tp>
	static double chi_square_(const cv::Mat& histogram0, const cv::Mat& histogram1);

	// non-templated functions
	static void spatial_histogram(const cv::Mat& src, cv::Mat& spatialhist, int numPatterns, const cv::Size& window, int overlap = 0);

	// wrapper functions
	static void spatial_histogram(const cv::Mat& src, cv::Mat& spatialhist, int numPatterns, int gridx = 8, int gridy = 8, int overlap = 0);
	static void histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns, int divisions);
	static double chi_square(const cv::Mat& histogram0, const cv::Mat& histogram1);

	// Mat return type functions
	static cv::Mat histogram(const cv::Mat& src, int numPatterns, int divisions);
	static cv::Mat spatial_histogram(const cv::Mat& src, int numPatterns, const cv::Size& window, int overlap = 0);
	static cv::Mat spatial_histogram(const cv::Mat& src, int numPatterns, int gridx = 8, int gridy = 8, int overlap = 0);

};

} // namespace feature
} // namespace CmnIP

#endif /* CMNIP_FEATURE_LBPHISTOGRAM_HPP__ */
