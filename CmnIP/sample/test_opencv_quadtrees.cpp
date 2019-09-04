// http://stackoverflow.com/questions/7050164/image-segmentation-split-and-merge-quadtrees/14730467#14730467

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "tree/inc/tree/tree_headers.hpp"

////using namespace cv;
////using namespace std;
//
//struct QuadTreeRegion {
//	// tree data structure
//	std::vector<QuadTreeRegion> childs;
//	bool validity; // TODO: have a method for clear the data structure and remove regions with false validity
//
//	// tree for split&merge procedure
//	cv::Rect roi;
//	cv::Mat m;
//	cv::Scalar label;
//	cv::Mat mask; // for debug. don't use in real cases because it is computationally too heavy.
//};
//
//class QuadTree
//{
//public:
//
//	//----------------------------------------------------------------------------------------------------------------------- merging
//	static bool mergeTwoRegion(QuadTreeRegion& parent, const cv::Mat& src,
//		QuadTreeRegion& r1, QuadTreeRegion& r2,
//		cv::Size &size, float standard_deviation, int min_size,
//		bool(*predicate)(const cv::Mat&, float, int)) {
//
//		if (r1.childs.size() == 0 && r2.childs.size() == 0) {
//
//			cv::Rect roi1 = r1.roi;
//			cv::Rect roi2 = r2.roi;
//			cv::Rect roi12 = roi1 | roi2;
//			if (predicate(src(roi12), standard_deviation, min_size)) {
//				r1.roi = roi12;
//
//				// recompute mask
//				r1.mask = cv::Mat::zeros(size, CV_8U);
//				rectangle(r1.mask, r1.roi, 1, CV_FILLED);
//
//				r2.validity = false;
//				return true;
//			}
//		}
//		return false;
//	}
//
//	static void merge(const cv::Mat& src, QuadTreeRegion& r,
//		cv::Size &size, float standard_deviation, int min_size,
//		bool(*predicate)(const cv::Mat&, float, int)) {
//		// check for adjiacent regions. if predicate is true, then  merge.
//		// the problem is to check for adjiacent regions.. one way can be:
//		// check merging for rows. if neither rows can be merged.. check for cols.
//
//		bool row1 = false, row2 = false, col1 = false, col2 = false;
//
//		if (r.childs.size() < 1) return;
//
//		// try with the row
//		row1 = mergeTwoRegion(r, src, r.childs[0], r.childs[1],
//			size, standard_deviation, min_size, predicate);
//		row2 = mergeTwoRegion(r, src, r.childs[2], r.childs[3],
//			size, standard_deviation, min_size, predicate);
//
//		if (!(row1 | row2)) {
//			// try with column
//			col1 = mergeTwoRegion(r, src, r.childs[0], r.childs[2],
//				size, standard_deviation, min_size, predicate);
//			col2 = mergeTwoRegion(r, src, r.childs[1], r.childs[3],
//				size, standard_deviation, min_size, predicate);
//		}
//
//		for (size_t i = 0; i < r.childs.size(); i++) {
//			if (r.childs[i].childs.size()>0)
//				merge(src, r.childs[i],
//				size, standard_deviation, min_size, predicate);
//		}
//	}
//
//	//----------------------------------------------------------------------------------------------------------------------- quadtree splitting
//	static QuadTreeRegion split(const cv::Mat& src, cv::Rect roi,
//		cv::Size &size, float standard_deviation, int min_size,
//		bool(*predicate)(const cv::Mat&, float, int)) {
//		std::vector<QuadTreeRegion> childs;
//		QuadTreeRegion r;
//
//		r.roi = roi;
//		r.m = src;
//		r.mask = cv::Mat::zeros(size, CV_8U);
//		cv::rectangle(r.mask, r.roi, 1, CV_FILLED);
//		r.validity = true;
//
//		bool b = predicate(src, standard_deviation, min_size);
//		if (b) {
//			cv::Scalar mean, s;
//			meanStdDev(src, mean, s);
//			r.label = mean;
//		}
//		else {
//			int w = src.cols / 2;
//			int h = src.rows / 2;
//			QuadTreeRegion r1 = split(src(cv::Rect(0, 0, w, h)), cv::Rect(roi.x, roi.y, w, h), size, standard_deviation, min_size, predicate);
//			QuadTreeRegion r2 = split(src(cv::Rect(w, 0, w, h)), cv::Rect(roi.x + w, roi.y, w, h), size, standard_deviation, min_size, predicate);
//			QuadTreeRegion r3 = split(src(cv::Rect(0, h, w, h)), cv::Rect(roi.x, roi.y + h, w, h), size, standard_deviation, min_size, predicate);
//			QuadTreeRegion r4 = split(src(cv::Rect(w, h, w, h)), cv::Rect(roi.x + w, roi.y + h, w, h), size, standard_deviation, min_size, predicate);
//			r.childs.push_back(r1);
//			r.childs.push_back(r2);
//			r.childs.push_back(r3);
//			r.childs.push_back(r4);
//		}
//		//merge(img, r, predicate);
//		return r;
//	}
//
//	//----------------------------------------------------------------------------------------------------------------------- tree traversing utility
//	static void print_region(QuadTreeRegion r) {
//		if (r.validity == true && r.childs.size() == 0) {
//			std::cout << r.mask << " at " << r.roi.x << "-" << r.roi.y << std::endl;
//			std::cout << r.childs.size() << std::endl;
//			std::cout << "---" << std::endl;
//		}
//		for (size_t i = 0; i < r.childs.size(); i++) {
//			print_region(r.childs[i]);
//		}
//	}
//
//	static void draw_rect(cv::Mat& imgRect, QuadTreeRegion r) {
//		if (r.validity == true && r.childs.size() == 0) {
//			cv::rectangle(imgRect, r.roi, 50, 1); //.1 (thickness)
//		}
//		for (size_t i = 0; i < r.childs.size(); i++) {
//			draw_rect(imgRect, r.childs[i]);
//		}
//	}
//
//	static void draw_region(cv::Mat& img, QuadTreeRegion r) {
//		if (r.validity == true && r.childs.size() == 0) {
//			rectangle(img, r.roi, r.label, CV_FILLED);
//		}
//		for (size_t i = 0; i < r.childs.size(); i++) {
//			draw_region(img, r.childs[i]);
//		}
//	}
//
//	//----------------------------------------------------------------------------------------------------------------------- split&merge test predicates
//	static bool predicateStdZero(const cv::Mat& src) {
//		cv::Scalar stddev, mean;
//		cv::meanStdDev(src, mean, stddev);
//		return stddev[0] == 0;
//	}
//	static bool predicateStd5(const cv::Mat& src, float sdev, int minsize) {
//		cv::Scalar stddev, mean;
//		cv::meanStdDev(src, mean, stddev);
//		return (stddev[0] <= sdev) || (src.rows*src.cols <= minsize);
//	}
//
//};



void test(const cv::Mat &img)
{
	// Default
	float standard_deviation = 10.8f;
	int min_size = 36;
	//float standard_deviation = 3.8f;
	//int min_size = 10;
	cv::Size size;

	// round (down) to the nearest power of 2 .. quadtree dimension is a pow of 2.
	double exponent = std::log((float)(std::min)(img.cols, img.rows)) / std::log(2.0f);
	int s = static_cast<int>(std::pow(2.0, exponent));
	cv::Rect square = cv::Rect(0, 0, s, s);
	//img = img(square).clone();

#if CV_MAJOR_VERSION == 3
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("original", img);

	std::cout << "now try to split.." << std::endl;
	CmnIP::tree::QuadTreeRegion r = CmnIP::tree::QuadTree::split(
		img, cv::Rect(0, 0, img.cols, img.rows), size, standard_deviation, 
		min_size, CmnIP::tree::QuadTree::predicateStd5);

	std::cout << "splitted" << std::endl;
	cv::Mat imgRect = img.clone();
	CmnIP::tree::QuadTree::draw_rect(imgRect, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("split", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("split", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("split", imgRect);
	//cv::imwrite("split.jpg", imgRect);

	CmnIP::tree::QuadTree::merge(img, r, size, standard_deviation, min_size, 
		&CmnIP::tree::QuadTree::predicateStd5);
	cv::Mat imgMerge = img.clone();
	CmnIP::tree::QuadTree::draw_rect(imgMerge, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("merge", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("merge", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("merge", imgMerge);
	//cv::imwrite("merge.jpg", imgMerge);

	cv::Mat imgSegmented = img.clone();
	CmnIP::tree::QuadTree::draw_region(imgSegmented, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("segmented", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("segmented", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("segmented", imgSegmented);
	//cv::imwrite("segmented.jpg", imgSegmented);

}

//----------------------------------------------------------------------------------------------------------------------- main
int main(int /*argc*/, char** /*argv*/)
{
	if (false) // test a video
	{
		//cv::VideoCapture vc("C:\\moro\\programs\\sample\\bodycomponentdetection\\data\\DSCN1340.MOV");
		cv::VideoCapture vc(0);
		while (true)
		{
			cv::Mat img;
			vc >> img;
			if (img.empty()) continue;
			cv::resize(img, img, cv::Size(img.cols / 2, img.rows / 2));
			// Quablock segmentation
			test(img);
			if (cv::waitKey(1) > 0) break;
		}
		return 0;
	}



	cv::Mat img;
	cv::Size size;
	float standard_deviation;
	int min_size;


	//img = (Mat_<uchar>(4, 4) << 0, 0, 1, 1,
	//	1, 1, 1, 1,
	//	3, 3, 3, 3,
	//	3, 4, 4, 3);

	//cout << img << endl;
	//size = img.size();

	//region r;
	//r = split(img, Rect(0, 0, img.cols, img.rows), &predicateStdZero);
	//merge(img, r, &predicateStdZero);
	//cout << "------- print" << endl;
	//print_region(r);

	//cout << "-----------------------" << endl;

	//img = imread("..\\..\\data\\out_front.jpg");
	img = cv::imread("..\\..\\data\\rgb_frame.png");
	if (img.empty()) return 0;
	cv::resize(img, img, cv::Size(img.cols / 2, img.rows / 2));
	standard_deviation = 5.8f;
	min_size = 25;

	// round (down) to the nearest power of 2 .. quadtree dimension is a pow of 2.
	double exponent = std::log((float)(std::min)(img.cols, img.rows)) / std::log(2.0f);
	int s = static_cast<int>(std::pow(2.0, exponent));
	cv::Rect square = cv::Rect(0, 0, s, s);
	//img = img(square).clone();

#if CV_MAJOR_VERSION == 3
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("original", img);

	std::cout << "now try to split.." << std::endl;
	CmnIP::tree::QuadTreeRegion r = CmnIP::tree::QuadTree::split(img, 
		cv::Rect(0, 0, img.cols, img.rows), size, standard_deviation, min_size, 
		CmnIP::tree::QuadTree::predicateStd5);

	std::cout << "splitted" << std::endl;
	cv::Mat imgRect = img.clone();
	CmnIP::tree::QuadTree::draw_rect(imgRect, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("split", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("split", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("split", imgRect);
	//cv::imwrite("split.jpg", imgRect);

	CmnIP::tree::QuadTree::merge(img, r, size, standard_deviation, min_size, 
		&CmnIP::tree::QuadTree::predicateStd5);
	cv::Mat imgMerge = img.clone();
	CmnIP::tree::QuadTree::draw_rect(imgMerge, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("merge", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("merge", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("merge", imgMerge);
	//cv::imwrite("merge.jpg", imgMerge);

	cv::Mat imgSegmented = img.clone();
	CmnIP::tree::QuadTree::draw_region(imgSegmented, r);
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("segmented", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("segmented", cv::WINDOW_AUTOSIZE);
#endif
	cv::imshow("segmented", imgSegmented);
	//cv::imwrite("segmented.jpg", imgSegmented);

	while (true)
	{
		char c = (char)cv::waitKey(10);
		if (c == 27) { break; }
	}

	return 0;
}