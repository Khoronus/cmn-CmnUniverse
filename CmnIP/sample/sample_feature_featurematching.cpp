/**
* @file sample_feature_detection.cpp
* @brief Sample feature detection in an image.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

//#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include <opencv2/opencv.hpp>

#include "feature/inc/feature/feature_headers.hpp"
#include "transform/inc/transform/transform_headers.hpp"
#include "draw/inc/draw/draw_headers.hpp"


namespace
{

/** @brief Function to test the feature detection with a generic detector.
*/
int test_detection(CmnIP::feature::FeatureMatching *feature_matching,
	cv::Mat &prev, cv::Mat &curr, std::vector< cv::Point2f > &v_points1, 
	std::vector< cv::Point2f > &v_points2,
	cv::Mat &out)
{
	v_points1.clear();
	v_points2.clear();
	//feature_matching.match(img1, img2, v_points1, v_points2);
	feature_matching->detect(0, prev, false);
	feature_matching->detect(1, curr, false);
	//feature_matching->prune(0, cv::Rect(0,0,700,1536));
	//feature_matching->prune(1, cv::Rect(700,0,1000,1536));
	//feature_matching->prune(0, 0);
	feature_matching->describe(0, prev, false);
	feature_matching->describe(1, curr, false);

	//feature_matching->
	if (!feature_matching->match(v_points1, v_points2, false)) {
		std::cout << "Unable to find enough feature points" << std::endl;
		return 0;
	}
	if (v_points1.size() == 0 || v_points2.size() == 0) return 0;

	// combine the images
	cv::Mat m((std::max)(curr.rows, prev.rows), 
		(std::max)(curr.cols * 2, prev.cols * 2), CV_8UC3, cv::Scalar(0));
	prev.copyTo(m(cv::Rect(0, 0, prev.cols, prev.rows)));
	curr.copyTo(m(cv::Rect(prev.cols, 0, curr.cols, curr.rows)));

	// Shift the points on the current image to draw the result 
	int s = v_points1.size();
	std::vector< cv::Point2f > v2shift;
	for (size_t i = 0; i < s; i++)
	{
		v2shift.push_back(v_points2[i] + cv::Point2f(prev.cols, 0));
	}

	// Draw the matching
	cv::Mat mtmp = cv::Mat(m.size(), m.type(), cv::Scalar::all(0));
	//CmnIP::draw::Pairs::line<cv::Point2f>(v_points1, v2shift, 
	//	nullptr, 2, mtmp);
	CmnIP::draw::Pairs::points<cv::Point2f>(v_points1, v2shift,
		m.cols / 2, 3, 5, mtmp);
	//CmnIP::draw::Pairs::points<cv::Point2f>(v_points1, v2shift,
	//	m.cols / 2, 1, 1, mtmp);
	//CmnIP::draw::Pairs::numbers<cv::Point2f>(v_points1, v2shift,
	//	0, 0.5, cv::Scalar(0, 0, 255), mtmp);
	std::vector<float> w;
	for (size_t i = 0; i < v_points1.size(); i++) {
		w.push_back((float)std::rand() / (float)RAND_MAX);
	}
	CmnIP::draw::Pairs::numbers_weight<cv::Point2f>(v_points1, v2shift, w,
		0, 1.0, cv::Scalar(0, 0, 255), mtmp);

	//cv::addWeighted(m, 0.75, mtmp, 0.25, 0, m);
	cv::addWeighted(m, 0.45, mtmp, 0.55, 0, m);

	out = m.clone();
	return 1;
}



/** @brief Function to show the feature detection.
*/
int test()
{
#if CV_MAJOR_VERSION == 2 
	cv::initModule_nonfree();
#endif

	//cv::VideoCapture vc("..\\..\\data\\test_video0.avi");
	cv::VideoCapture vc(0);
	//cv::VideoCapture vc("C:\\workspace\\Database\\CameraCalibration\\DSCN7772.MOV");

	if (!vc.isOpened()) {
		std::cout << "Unable to open the video" << std::endl;
	}
	// Feature detection collectors
	CmnIP::feature::FeatureMatching *feature_matching = 
		new CmnIP::feature::FeatureMatching();

	// Feature matching (generic)
	std::string _detector = "FAST"; // FAST
	std::string _descriptorExtractor = "BRISK"; // BRISK ORB
	std::string _descriptorMatcher = "BruteForce";
	std::string  _mactherFilterType = "CrossCheckFilter"; //"NoneFilter"; // CrossCheckFilter
	double _ransacReprojThreshold = 0.01;
	bool _eval = true;
	feature_matching->set(_detector, _descriptorExtractor, _descriptorMatcher,
		_mactherFilterType, _ransacReprojThreshold, _eval);
	//feature_matching->set_detector_params("threshold", 1);
	feature_matching->set_detector_params("threshold", 30);
	//feature_matching.set_detector_params("nFeatures", 300);


	cv::Mat prev, curr, out;
	bool bContinue = true;
	while (bContinue)
	{
		vc >> curr;

		if (curr.empty()) {
			//bContinue = false;
			continue;
		}
		//cv::resize(curr, curr, cv::Size(curr.cols / 5, curr.rows / 5));
		//curr = curr(cv::Rect(0,0,curr.cols / 2, curr.rows));

		if (prev.empty()) {
			prev = curr.clone();
			continue;
		}

		std::vector< cv::Point2f > v_points1, v_points2;
		test_detection(feature_matching, prev, curr, v_points1, v_points2, out);
		if (!curr.empty()) cv::imshow("curr", curr);
		if (!out.empty()) cv::imshow("out", out);

		if (cv::waitKey(10) == 27) bContinue = false;
		cv::swap(curr, prev);
	}

	cv::destroyAllWindows();
	return 1;
}


template <typename _Ty>
int mean(std::vector<_Ty> &values, _Ty &value)
{
	if (values.size() == 0) return 0;
	std::sort(values.begin(), values.end());
	int s = values.size();
	value = s % 2 == 1 ? s > 1 ? values[s / 2] : values[0] : 
		(values[s / 2 - 1] + values[s / 2]) / 2;
	return 1;
}

/** @brief Function to test the feature detection with a generic detector.
*/
void test_detection2(
        CmnIP::feature::FeatureMatching *feature_matching,
	cv::Mat &prev, cv::Mat &curr, 
	const cv::Point2f &a, 
	const cv::Point2f &b, cv::Mat &out)
{
	std::vector< cv::Point2f > v_points1, v_points2;

	//feature_matching.match(img1, img2, v_points1, v_points2);
	//feature_matching->detect(0, prev, false);
	//feature_matching->detect(1, curr, false);
	feature_matching->set_keypoint1(a);
	feature_matching->set_keypoint2(b);
	//feature_matching->add_keypoint1(cv::Point2f(600, 500));
	//feature_matching->add_keypoint2(cv::Point2f(600, 500));
	//feature_matching->add_keypoint1(cv::Point2f(700, 500));
	//feature_matching->add_keypoint2(cv::Point2f(700, 500));
	//feature_matching->add_keypoint1(cv::Point2f(800, 500));
	//feature_matching->add_keypoint2(cv::Point2f(800, 500));
	//feature_matching.prune(0, cv::Rect(0,0,500,1536));
	//feature_matching.prune(1, cv::Rect(700,0,1000,1536));
	//feature_matching->prune(0, 0);
	feature_matching->describe(0, prev, true);
	feature_matching->describe(1, curr, true);

	// Chart radar
	CmnIP::draw::ChartRadar cr1(512, 0, 300);
	cr1.clear();
	CmnIP::draw::ChartRadar cr2(512, 0, 300);
	cr2.clear();
	CmnIP::draw::ChartRadar cr(512, 0, 300);
	cr.clear();
	//if (feature_matching->filteredMatches_.size() > 0)
	std::vector<float> values0, values1;
	{
		{
			cv::Mat m = feature_matching->get_descriptors1();
			if (!m.empty())
			{
				std::vector< std::pair<float, float> > features_mM;
				{
					int c = m.cols;
					int r = m.rows;
					for (int i = 0; i < c; i++) {
						//std::cout << (int)m.at<uchar>(0, i) << " ";
						values0.push_back(m.at<uchar>(0, i));
					}
					//std::cout << std::endl;// << m << std::endl;
					cr.draw(values0, cv::Scalar(std::rand() % 255,
						std::rand() % 255, std::rand() % 255));
					//cv::waitKey();
				}
			}
		}
		{
			cv::Mat m = feature_matching->get_descriptors2();
			if (!m.empty())
			{
				std::vector< std::pair<float, float> > features_mM;
				{
					int c = m.cols;
					int r = m.rows;
					for (int i = 0; i < c; i++) {
						//std::cout << (int)m.at<uchar>(0, i) << " ";
						values1.push_back(m.at<uchar>(0, i));
					}
					//std::cout << std::endl;// << m << std::endl;
					cr.draw(values1, cv::Scalar(std::rand() % 255,
						std::rand() % 255, std::rand() % 255));
				}
			}
		}
		std::vector<float> values;
		if (values0.size() == values1.size())
		{
			cr.clear();
			int c = values0.size();
			for (int i = 0; i < c; i++) {
				values.push_back(std::abs(values0[i] - values1[i]));
			}
			cr.draw(values, cv::Scalar(std::rand() % 255,
				std::rand() % 255, std::rand() % 255));

			cr1.clear();
			values.clear();
			for (int i = 0; i < c; i++) {
				values.push_back(std::abs(values0[i]));
			}
			cr1.draw(values, cv::Scalar(std::rand() % 255,
				std::rand() % 255, std::rand() % 255));

			cr2.clear();
			values.clear();
			for (int i = 0; i < c; i++) {
				values.push_back(std::abs(values1[i]));
			}
			cr2.draw(values, cv::Scalar(std::rand() % 255,
				std::rand() % 255, std::rand() % 255));
		}
		float v = 0;
		if (mean<float>(values, v)) std::cout << "mean: " << v << std::endl;
	}
	cv::imshow("chart", cr.chart());
	//cv::imwrite("feature_charA.png", cr1.chart());
	//cv::imwrite("feature_charB.png", cr2.chart());
	//cv::imwrite("feature_char.png", cr.chart());

	//feature_matching->
	if (!feature_matching->match(v_points1, v_points2, false)) return;

	//std::vector< uchar > status(v_points1.size());
	//for (int i = 0; i < status.size(); i++)
	//{
	//	//std::cout << v_points1[i] << " -> " << v_points2[i] << std::endl;
	//	status[i] = 1;
	//}
	//Featurecmn::drawArrows(prev, v_points1, v_points2, status, 1, cv::Scalar(0,255));

	// combine the images
	cv::Mat m(curr.rows, curr.cols * 2, CV_8UC3);
	curr.copyTo(m(cv::Rect(0, 0, curr.cols, curr.rows)));
	prev.copyTo(m(cv::Rect(curr.cols, 0, prev.cols, prev.rows)));
	int s = v_points1.size();
	cv::RNG r;
	//std::vector< cv::KeyPoint > v_k = feature_matching.keypoints1_out();
	//s = v_k.size();
	for (int i = 0; i < s; i++)
	{
		//cv::circle(m, v_k[i].pt, 2, cv::Scalar(0,0,255), 1);
		cv::line(m, v_points1[i] + cv::Point2f(curr.cols, 0),
			v_points2[i], cv::Scalar(r.uniform(0, 255),
			r.uniform(0, 255), r.uniform(0, 255)), 5);
	}
	//cv::resize(m,m,cv::Size(1926,1024));
	out = m.clone();
}


/** @brief Function to show the feature detection.
*/
int test_2pic()
{
#if CV_MAJOR_VERSION == 2 
	cv::initModule_nonfree();
#endif

	// Feature detection collectors
	CmnIP::feature::FeatureMatching *feature_matching = 
		new CmnIP::feature::FeatureMatching();

	// Feature matching (generic)
	std::string _detector = "SIFT"; // FAST
	std::string _descriptorExtractor = "SIFT"; // BRISK ORB
	std::string _descriptorMatcher = "BruteForce";
	std::string  _mactherFilterType = "CrossCheckFilter"; //"NoneFilter"; // CrossCheckFilter
	double _ransacReprojThreshold = 0.01;
	bool _eval = true;
	feature_matching->set(_detector, _descriptorExtractor, _descriptorMatcher,
		_mactherFilterType, _ransacReprojThreshold, _eval);
	//feature_matching->set_detector_params("threshold", 30);


	//cv::Mat m0 = cv::imread("..\\..\\data\\fish_frontA.jpg");
	//cv::Mat m1 = cv::imread("..\\..\\data\\fish_leftA.jpg");
	cv::Mat m0 = cv::imread("..\\..\\data\\out_front.jpg");
	cv::Mat m1 = cv::imread("..\\..\\data\\out_left.jpg");
	cv::Mat out;

	cv::Point2f a(50, 170);
	cv::Point2f b(50, 200);
	//cv::Point2f b(1005, 937);
	for (int y = -3; y <= 3; y++)
	{
		for (int x = -3; x <= 3; x++)
		{
			std::vector< cv::Point2f > v_points1, v_points2;
			test_detection(feature_matching, m0, m1, v_points1, v_points2, out);
			cv::Mat tmp;
			cv::resize(m0, tmp, cv::Size(512, 512));
			if (!m0.empty()) cv::imshow("m0", tmp);
			cv::resize(m1, tmp, cv::Size(512, 512));
			if (!m1.empty()) cv::imshow("m1", tmp);
			cv::resize(out, tmp, cv::Size(1024, 512));
			if (!out.empty()) cv::imshow("out", tmp);
			//cv::imwrite("feature_detection_result.png", out);
			if (cv::waitKey() == 27) return 0;

			test_detection2(feature_matching, m0, m1, a, b + cv::Point2f(x, y), out);
			cv::resize(m0, tmp, cv::Size(512, 512));
			if (!m0.empty()) cv::imshow("m0", tmp);
			cv::resize(m1, tmp, cv::Size(512, 512));
			if (!m1.empty()) cv::imshow("m1", tmp);
			cv::resize(out, tmp, cv::Size(1024, 512));
			if (!out.empty()) cv::imshow("out", tmp);
			//cv::imwrite("feature_detection_result_single.png", out);
			if (cv::waitKey() == 27) return 0;

		}
	}
	cv::destroyAllWindows();
	return 1;
}


/** @brief Show a set of plot over the image.
*/
void test_multiple_areas()
{
#if CV_MAJOR_VERSION == 2 
	cv::initModule_nonfree();
#endif

	// Feature detection collectors
	CmnIP::feature::FeatureMatching *feature_matching =
		new CmnIP::feature::FeatureMatching();

	// Feature matching (generic)
	std::string _detector = "SIFT"; // FAST
	std::string _descriptorExtractor = "SIFT"; // BRISK ORB
	std::string _descriptorMatcher = "BruteForce";
	std::string  _mactherFilterType = "CrossCheckFilter"; //"NoneFilter"; // CrossCheckFilter
	double _ransacReprojThreshold = 0.01;
	bool _eval = true;
	feature_matching->set(_detector, _descriptorExtractor, _descriptorMatcher,
		_mactherFilterType, _ransacReprojThreshold, _eval);
	//feature_matching->set_detector_params("threshold", 30);

	//cv::Mat src = cv::imread("../../data/scene_000.png");
	//cv::Mat model = src(cv::Rect(150,200,200,250));
	cv::Mat src_in = cv::imread("..\\..\\data\\fish_left.jpg");
	cv::Mat src_ = src_in(cv::Rect(src_in.cols / 2, 0, src_in.cols / 2, src_in.rows));// src_;//
	//cv::Mat model = cv::imread("../../data/1_patch.jpg");
	cv::Mat model_in = cv::imread("..\\..\\data\\fish_front.jpg");
	cv::Mat model_ = model_in(cv::Rect(0, 0, model_in.cols / 2, src_.rows));// model_in;//

	cv::Mat m(src_in.size(), CV_32FC1, cv::Scalar::all(0));
	int kW = 150, kH = 150;
	cv::Mat a(kH, kW, CV_32FC1, cv::Scalar::all(1));

	for (int y_ = 600; y_ <= src_.rows - a.rows; y_ += a.rows)
	{
		for (int x_ = 400; x_ <= src_.cols - a.cols - 200; x_ += a.cols)
		{
			cv::Mat src = src_(cv::Rect(x_, y_, kW, kH));
			cv::Mat src_clone = src_.clone();
			cv::rectangle(src_clone, cv::Rect(x_, y_, kW, kH), cv::Scalar(0, 0, 255), 3);
			cv::resize(src_clone, src_clone, cv::Size(512, 512));
			cv::imshow("src_clone", src_clone);
			for (int y = 0; y <= model_.rows - a.rows; y += a.rows)
			{
				for (int x = 0; x <= model_.cols - a.cols; x += a.cols)
				{
					cv::Mat model_clone = model_.clone();
					cv::rectangle(model_clone, cv::Rect(x, y, kW, kH), cv::Scalar(0, 0, 255), 3);
					cv::resize(model_clone, model_clone, cv::Size(512, 512));
					cv::imshow("model_clone", model_clone);
					//cv::Mat src = src_(cv::Rect(src_.cols / 2, y, src_.cols / 2, a.rows + 1));
					cv::Mat model = model_(cv::Rect(x, y, kW, kH));
					cv::Mat out;
					std::vector< cv::Point2f > v_points1, v_points2;
					test_detection(feature_matching, src, model, v_points1, v_points2, out);
					if (!out.empty()) {
						cv::Mat tmp;
						cv::resize(out, tmp, cv::Size(1024, 512));
						if (!out.empty()) cv::imshow("out", tmp);
						if (cv::waitKey() == 27) return;
					}
				}
			}
		}
	}
	cv::destroyAllWindows();
}



/** @brief Show a set of plot over the image.
*/
void test_regions()
{
#if CV_MAJOR_VERSION == 2 
	cv::initModule_nonfree();
#endif

	// Feature detection collectors
	CmnIP::feature::FeatureMatching *feature_matching =
		new CmnIP::feature::FeatureMatching();

	// Feature matching (generic)
	std::string _detector = "SIFT"; // FAST
	std::string _descriptorExtractor = "SIFT"; // BRISK ORB
	std::string _descriptorMatcher = "BruteForce";
	std::string  _mactherFilterType = "CrossCheckFilter"; //"NoneFilter"; // CrossCheckFilter
	double _ransacReprojThreshold = 0.01;
	bool _eval = true;
	feature_matching->set(_detector, _descriptorExtractor, _descriptorMatcher,
		_mactherFilterType, _ransacReprojThreshold, _eval);

	cv::Mat src = cv::imread("..\\..\\data\\fish_left.jpg");
	//cv::Mat src = src_(cv::Rect(src_.cols / 2, 0, src_.cols / 2, src_.rows));// src_;//
	cv::Mat model_ = cv::imread("..\\..\\data\\fish_front.jpg");

	// Points organized as top left, width height
	//std::ifstream myfile("regions_sd.txt");
	//std::vector<std::pair<cv::Rect, cv::Rect> > vrect;
	//while (!myfile.eof())
	//{
	//	char buf[512];
	//	int x, y, w, h;
	//	int x2, y2, w2, h2;
	//	myfile.getline(buf, 512);
	//	if (std::strlen(buf) > 2) {
	//		sscanf(buf, "%i %i %i %i %i %i %i %i", &x, &y, &w, &h, &x2, &y2, &w2, &h2);
	//		if (x >= 0 && y >= 0 && (x + w) < src.cols &&
	//			(y + h) < src.rows) {
	//			if (x2 >= 0 && y2 >= 0 && (x2 + w2) < src.cols &&
	//				(y2 + h2) < src.rows) {
	//				vrect.push_back(std::make_pair(cv::Rect(x, y, w, h), cv::Rect(x2, y2, w2, h2)));
	//			}
	//		}
	//	}
	//}

	// Points organized as top left, bottom right
	std::ifstream myfile("..\\..\\data\\regions_good.txt");
	if (!myfile.is_open()) {
		std::cout << "Unable to find the file regions_good.txt" << std::endl;
		std::cout << "The file contains the coordinate of rectangular areas" \
			" that match between two images" << std::endl;
		std::cout << "File format " << std::endl;
		std::cout << "TL_IMG0_X TL_IMG0_Y BR_IMG0_X BR_IMG0_Y TL_IMG1_X TL_IMG1_Y BR_IMG1_X BR_IMG1_Y" << std::endl;
		return;
	}
	std::vector<std::pair<cv::Rect, cv::Rect> > vrect;
	while (!myfile.eof())
	{
		char buf[512];
		int x, y, w, h;
		int x2, y2, w2, h2;
		myfile.getline(buf, 512);
		if (std::strlen(buf) > 2) {
			sscanf(buf, "%i %i %i %i %i %i %i %i", &x, &y, &w, &h, &x2, &y2, &w2, &h2);
			vrect.push_back(std::make_pair(cv::Rect(cv::Point(x, y), cv::Point(w, h)), cv::Rect(cv::Point(x2, y2), cv::Point(w2, h2))));
		}
	}

	cv::Mat combo((std::max)(model_.rows, src.rows), model_.cols + src.cols,
		src.type(), cv::Scalar::all(0));
	model_.copyTo(combo(cv::Rect(0, 0, model_.cols, model_.rows)));
	src.copyTo(combo(cv::Rect(model_.cols, 0, src.cols, src.rows)));

	cv::RNG rng(12345);
	for (auto it = vrect.begin(); it != vrect.end(); it++)
	{
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::Mat model_clone = model_.clone();
		cv::rectangle(model_clone, it->first, color, 3);
		cv::rectangle(combo, it->first, color, 5);
		cv::resize(model_clone, model_clone, cv::Size(512, 512));
		cv::imshow("model_clone", model_clone);
		cv::Mat model = model_(it->first);
		cv::Mat src_ = src(it->second);
		cv::imshow("model", model);
		cv::Rect region_out;

		cv::Mat out;
		std::vector< cv::Point2f > v_points1, v_points2;
		test_detection(feature_matching, model, src_, v_points1, 
			v_points2, out);
		if (!out.empty()) {
			cv::Mat tmp;
			cv::resize(out, tmp, cv::Size(1024, 512));
			if (!out.empty()) {
				cv::imshow("out", tmp);
				//cv::imwrite("out.png", tmp);
			}

			std::vector<cv::Point2f> v1, v2;
			int s = v_points1.size();
			for (int i = 0; i < s; i++)
			{
				v1.push_back(v_points1[i] + cv::Point2f(it->first.x, it->first.y));
				v2.push_back(v_points2[i] + cv::Point2f(it->second.x, it->second.y) + cv::Point2f(model_.cols, 0));
			}
			//CmnIP::draw::Pairs::line<cv::Point2f>(v1, v2, &cv::Scalar(rand() % 255, rand() % 128 + 127, 255 - rand() % 255), 2, combo);
			CmnIP::draw::Pairs::points<cv::Point2f>(v1, v2, model_.cols, 5, 7, combo);
			cv::resize(combo, tmp, cv::Size(1024, 512));
			cv::imshow("combo", tmp);
			//cv::imwrite("combo.png", combo);


			if (cv::waitKey() == 27) return;
		}
	}
	cv::destroyAllWindows();
}



} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample Feature Detection" << std::endl;

	test();
	test_2pic();
	test_multiple_areas();
	test_regions();
	
	return 0;
}
