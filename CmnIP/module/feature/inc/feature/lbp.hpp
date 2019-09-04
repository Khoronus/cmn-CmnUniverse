#ifndef CMNIP_FEATURE_LBP_HPP__
#define CMNIP_FEATURE_LBP_HPP__

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

//! \author philipp <bytefish[at]gmx[dot]de>
//! \copyright BSD, see LICENSE.

#include <opencv2/opencv.hpp>
#include <limits>

namespace CmnIP{
namespace feature {

class LBP
{
public:
	// templated functions
	template <typename _Tp>
	static void OLBP_(const cv::Mat& src, cv::Mat& dst);
	template <typename _Tp>
	static void ELBP_(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);
	template <typename _Tp>
	static void VARLBP_(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

	// wrapper functions
	static void OLBP(const cv::Mat& src, cv::Mat& dst);
	static void ELBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);
	static void VARLBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

	// Mat return type functions
	static cv::Mat OLBP(const cv::Mat& src);
	static cv::Mat ELBP(const cv::Mat& src, int radius = 1, int neighbors = 8);
	static cv::Mat VARLBP(const cv::Mat& src, int radius = 1, int neighbors = 8);
};

} // namespace feature
} // namespace CmnIP

#endif /* CMNIP_FEATURE_LBP_HPP__ */
