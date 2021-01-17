#include "feature/inc/feature/lbphistogram.hpp"
namespace CmnIP{
namespace feature {


template <typename _Tp>
void LBPHistogram::histogram_(const cv::Mat& src, cv::Mat& hist, int numPatterns, int divisions) {
	int _divisions = (std::max)(divisions, 1);
	hist = cv::Mat::zeros(1, numPatterns, CV_32SC1);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int bin = (src.at<_Tp>(i, j)) / _divisions;
			hist.at<int>(0, bin) += 1;
		}
	}
}

template <typename _Tp>
double LBPHistogram::chi_square_(const cv::Mat& histogram0, const cv::Mat& histogram1) {
#if CV_MAJOR_VERSION == 3
	if (histogram0.type() != histogram1.type())
		CV_Error(CV_StsBadArg, "Histograms must be of equal type.");
	if (histogram0.rows != 1 || histogram0.rows != histogram1.rows || histogram0.cols != histogram1.cols)
		CV_Error(CV_StsBadArg, "Histograms must be of equal dimension.");
#elif CV_MAJOR_VERSION == 4
	if (histogram0.type() != histogram1.type())
		CV_Error(-1, "Histograms must be of equal type.");
	if (histogram0.rows != 1 || histogram0.rows != histogram1.rows || histogram0.cols != histogram1.cols)
		CV_Error(-1, "Histograms must be of equal dimension.");
#endif
	double result = 0.0;
	for (int i = 0; i < histogram0.cols; i++) {
		double a = histogram0.at<_Tp>(0, i) - histogram1.at<_Tp>(0, i);
		double b = histogram0.at<_Tp>(0, i) + histogram1.at<_Tp>(0, i);
		if (abs(b) > std::numeric_limits<double>::epsilon()) {
			result += (a*a) / b;
		}
	}
	return result;
}


void LBPHistogram::spatial_histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns, const cv::Size& window, int overlap) {
	int width = src.cols;
	int height = src.rows;
	std::vector<cv::Mat> histograms;
	for (int x = 0; x < width - window.width; x += (window.width - overlap)) {
		for (int y = 0; y < height - window.height; y += (window.height - overlap)) {
			cv::Mat cell = cv::Mat(src, cv::Rect(x, y, window.width, window.height));
			histograms.push_back(histogram(cell, numPatterns, 1));
		}
	}
	hist.create(1, histograms.size()*numPatterns, CV_32SC1);
	// i know this is a bit lame now... feel free to make this a bit more efficient...
	for (int histIdx = 0; histIdx < histograms.size(); histIdx++) {
		for (int valIdx = 0; valIdx < numPatterns; valIdx++) {
			int y = histIdx*numPatterns + valIdx;
			hist.at<int>(0, y) = histograms[histIdx].at<int>(valIdx);
		}
	}
}

// wrappers
void LBPHistogram::histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns, int divisions) {
	switch (src.type()) {
	case CV_8SC1: histogram_<char>(src, hist, numPatterns, divisions); break;
	case CV_8UC1: histogram_<unsigned char>(src, hist, numPatterns, divisions); break;
	case CV_16SC1: histogram_<short>(src, hist, numPatterns, divisions); break;
	case CV_16UC1: histogram_<unsigned short>(src, hist, numPatterns, divisions); break;
	case CV_32SC1: histogram_<int>(src, hist, numPatterns, divisions); break;
	}
}

double LBPHistogram::chi_square(const cv::Mat& histogram0, const cv::Mat& histogram1) {
	switch (histogram0.type()) {
	case CV_8SC1: return chi_square_<char>(histogram0, histogram1); break;
	case CV_8UC1: return chi_square_<unsigned char>(histogram0, histogram1); break;
	case CV_16SC1: return chi_square_<short>(histogram0, histogram1); break;
	case CV_16UC1: return chi_square_<unsigned short>(histogram0, histogram1); break;
	case CV_32SC1: return chi_square_<int>(histogram0, histogram1); break;
	}
	return 0;
}

void LBPHistogram::spatial_histogram(const cv::Mat& src, cv::Mat& dst, int numPatterns, int gridx, int gridy, int overlap) {
	int width = static_cast<int>(std::floor((float)src.cols / (float)gridx));
	int height = static_cast<int>(std::floor((float)src.rows / (float)gridy));
	spatial_histogram(src, dst, numPatterns, cv::Size_<int>(width, height), overlap);
}

// Mat return type functions
cv::Mat LBPHistogram::histogram(const cv::Mat& src, int numPatterns, int divisions) {
	cv::Mat hist;
	histogram(src, hist, numPatterns, divisions);
	return hist;
}


cv::Mat LBPHistogram::spatial_histogram(const cv::Mat& src, int numPatterns, const cv::Size& window, int overlap) {
	cv::Mat hist;
	spatial_histogram(src, hist, numPatterns, window, overlap);
	return hist;
}


cv::Mat LBPHistogram::spatial_histogram(const cv::Mat& src, int numPatterns, int gridx, int gridy, int overlap) {
	cv::Mat hist;
	spatial_histogram(src, hist, numPatterns, gridx, gridy);
	return hist;
}



} // namespace feature
} // namespace CmnIP


