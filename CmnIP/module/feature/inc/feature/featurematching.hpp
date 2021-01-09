/**
* @file feature_matching.hpp
* @brief Abstract camera structure.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNIP_FEATURE_FEATUREMATCHING_HPP__
#define CMNIP_FEATURE_FEATUREMATCHING_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

//#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#if CV_MAJOR_VERSION == 2
#include <opencv2/nonfree/nonfree.hpp>
#endif
//#include "opencv2/contrib/contrib.hpp"

//#include "opencv2/core/opengl_interop.hpp"
//*****************************************
//	FEATURE MATCHING
//*****************************************



#define DRAW_RICH_KEYPOINTS_MODE     0
#define DRAW_OUTLIERS_MODE           0

namespace CmnIP
{
namespace feature
{

class FeatureMatching
{
public:

	FeatureMatching()	{
		winName = "correspondences";
	}

	/** Setup the feature detectors
		@example
		"STAR", "BRIEF", "BruteForce-L1", "CrossCheckFilter"
	*/
	int set(std::string &_detector, std::string &_descriptorExtractor, std::string &_descriptorMatcher, std::string &_mactherFilterType, double _ransacReprojThreshold, bool _eval)	{
		ransacReprojThreshold = _ransacReprojThreshold;
		eval = _eval;

#if CV_MAJOR_VERSION == 2
		std::cout << "< Creating detector, descriptor extractor and descriptor matcher ..." << std::endl;
		detector = cv::FeatureDetector::create(_detector);	// Grid - Pyramid - HARRIS - Dynamic
		descriptorExtractor = cv::DescriptorExtractor::create( _descriptorExtractor );
		descriptorMatcher = cv::DescriptorMatcher::create(_descriptorMatcher);
		mactherFilterType = getMatcherFilterType( _mactherFilterType );

		std::cout << ">" << std::endl;
		if( detector.empty()  )
		{
			std::cout << "Can not create detector of given types" << std::endl;
			return -1;
		}
		if( descriptorExtractor.empty()  )
		{
			std::cout << "Can not create descriptor extractor of given types" << std::endl;
			return -1;
		}
		if( descriptorMatcher.empty()  )
		{
			std::cout << "Can not create descriptor matcher of given types" << std::endl;
			return -1;
		}

		std::cout << "Detector params" << std::endl;
		printParams(detector);
		std::cout << "Descriptor params" << std::endl;
		printParams(descriptorExtractor);
#else
		std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;

		std::cout << "< Creating detector, descriptor extractor and descriptor matcher ..." << std::endl;
		detector = cv::BRISK::create();	// Grid - Pyramid - HARRIS - Dynamic
		descriptorExtractor = cv::BRISK::create();
		descriptorMatcher = cv::DescriptorMatcher::create(_descriptorMatcher);
		mactherFilterType = getMatcherFilterType(_mactherFilterType);

		std::cout << ">" << std::endl;
		if (detector.empty())
		{
			std::cout << "Can not create detector of given types" << std::endl;
			return -1;
		}
		if (descriptorExtractor.empty())
		{
			std::cout << "Can not create descriptor extractor of given types" << std::endl;
			return -1;
		}
		if (descriptorMatcher.empty())
		{
			std::cout << "Can not create descriptor matcher of given types" << std::endl;
			return -1;
		}

		std::cout << "Detector params" << std::endl;
		printParams(detector);
		std::cout << "Descriptor params" << std::endl;
		printParams(descriptorExtractor);


#endif
		return 0;
	}

	/** @brief Wrapper to the function to set the detector parameters.

		Set the detector parameters.
		@param[in] param Parameter to set.
		@param[in] value Value to assign.
	*/
	void set_detector_params(const std::string &param, double value) {
#if CV_MAJOR_VERSION == 2
		detector->set(param, value);
#else
		std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;
#endif
	}

	/** @brief Print the parameters of the algorithm
	*/
	void printParams( cv::Algorithm* algorithm ) {
		std::vector<std::string> parameters;

#if CV_MAJOR_VERSION == 2
		algorithm->getParams(parameters);

		for (int i = 0; i < (int) parameters.size(); i++) {
			std::string param = parameters[i];
			int type = algorithm->paramType(param);
			std::string helpText = algorithm->paramHelp(param);
			std::string typeText;

			switch (type) {
			case cv::Param::BOOLEAN:
				typeText = "bool";
				break;
			case cv::Param::INT:
				typeText = "int";
				break;
			case cv::Param::REAL:
				typeText = "real (double)";
				break;
			case cv::Param::STRING:
				typeText = "string";
				break;
			case cv::Param::MAT:
				typeText = "Mat";
				break;
			case cv::Param::ALGORITHM:
				typeText = "Algorithm";
				break;
			case cv::Param::MAT_VECTOR:
				typeText = "Mat vector";
				break;
			}
			std::cout << "Parameter '" << param << "' type=" << typeText << " help=" << helpText << std::endl;
		}
#else
		std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;
#endif
	}

	bool match(cv::Mat &img1, cv::Mat &img2, std::vector<cv::Point2f> &point1, std::vector<cv::Point2f> &point2, bool verbose)	{

		// Feature matching
		if (verbose) std::cout << std::endl << "< Extracting keypoints from first image..." << std::endl;
		detector->detect( img1, keypoints1 );
		if (verbose) std::cout << keypoints1.size() << " points" << std::endl << ">" << std::endl;

		if (verbose) std::cout << "< Computing descriptors for keypoints from first image..." << std::endl;
		descriptorExtractor->compute( img1, keypoints1, descriptors1 );
		if (verbose) std::cout << ">" << std::endl;

		bool isWarpPerspective = false;
		cv::RNG rng = cv::theRNG();
		return doIteration( img1, img2, isWarpPerspective, keypoints1, descriptors1,
						detector, descriptorExtractor, descriptorMatcher, mactherFilterType, eval,
						ransacReprojThreshold, rng, point1, point2 );
	}


	void detect(int id, cv::Mat &source, bool verbose) 
	{
		if (id == 0) {
			if (verbose) std::cout << std::endl << "< Extracting keypoints from first image..." << std::endl;
			detector->detect( source, keypoints1 );
			if (verbose) std::cout << keypoints1.size() << " points" << std::endl << ">" << std::endl;
		} else {
			if (verbose) std::cout << std::endl << "< Extracting keypoints from first image..." << std::endl;
			detector->detect( source, keypoints2 );
			if (verbose) std::cout << keypoints2.size() << " points" << std::endl << ">" << std::endl;
		}
	}


	void set_keypoint1(const cv::Point2f &p) {
		keypoints1.clear();
		keypoints1.push_back(cv::KeyPoint(p.x, p.y, 1));
	}
	void set_keypoint2(const cv::Point2f &p) {
		keypoints2.clear();
		keypoints2.push_back(cv::KeyPoint(p.x, p.y, 1));
	}


	void prune(int id, cv::Rect &r)
	{
		std::vector<cv::KeyPoint> tmp;
		std::vector<cv::KeyPoint> use;
		if (id == 0) {
			tmp = keypoints1;
		} else {
			tmp = keypoints2;
		}
		for (auto it = tmp.begin(); it != tmp.end(); it++)
		{
			if (it->pt.inside(r)) {
				use.push_back( *it );
			}
		}
		if (id == 0) {
			keypoints1 = use;
		} else {
			keypoints2 = use;
		}
	}

	void prune(int id, int index)
	{
		std::vector<cv::KeyPoint> tmp;
		std::vector<cv::KeyPoint> use;
		if (id == 0) {
			tmp = keypoints1;
		}
		else {
			tmp = keypoints2;
		}
		int idx = 0;
		for (auto it = tmp.begin(); it != tmp.end(); it++)
		{
			if (idx == index) {
				use.push_back(*it);
				break;
			}
			++idx;
		}
		if (id == 0) {
			keypoints1 = use;
		}
		else {
			keypoints2 = use;
		}
	}


	void describe(int id, cv::Mat &source, bool verbose)
	{
		if (id == 0) {
			if (verbose) std::cout << "< Computing descriptors for " << keypoints1.size() << " keypoints from first image..." << std::endl;
			descriptorExtractor->compute( source, keypoints1, descriptors1 );
			if (verbose) std::cout << "> descriptors: " << descriptors1.rows << std::endl;
		} else {
			if (verbose) std::cout << "< Computing descriptors for " << keypoints2.size() << " keypoints from second image..." << std::endl;
			descriptorExtractor->compute(source, keypoints2, descriptors2);
			if (verbose) std::cout << "> descriptors: " << descriptors1.rows << std::endl;
		}
	}

	std::vector<cv::DMatch> filteredMatches_;

	bool match(std::vector<cv::Point2f> &points1, std::vector<cv::Point2f> &points2, bool verbose)	{

		bool bMatchFound = true;
		if (descriptors1.rows == 0 || descriptors2.rows == 0) return false;
		if (verbose) std::cout << "Descriptors1: " << descriptors1.cols << " " << descriptors1.rows << std::endl;
		if (verbose) std::cout << "Descriptors2: " << descriptors2.cols << " " << descriptors2.rows << std::endl;
		if (verbose) std::cout << "< Matching descriptors..." << std::endl;

		std::vector<cv::DMatch> filteredMatches;
		switch( mactherFilterType )
		{
		case CROSS_CHECK_FILTER :
			crossCheckMatching( descriptorMatcher, descriptors1, descriptors2, filteredMatches, 1 );
			break;
		default :
			simpleMatching( descriptorMatcher, descriptors1, descriptors2, filteredMatches );
		}
		if (verbose) std::cout << ">" << std::endl;

		std::vector<int> queryIdxs(filteredMatches.size()), trainIdxs(filteredMatches.size());
		for( size_t i = 0; i < filteredMatches.size(); i++ )
		{
			//std::cout << filteredMatches[i].queryIdx << " " << filteredMatches[i].trainIdx << std::endl;
			queryIdxs[i] = filteredMatches[i].queryIdx;
			trainIdxs[i] = filteredMatches[i].trainIdx;
		}

		points1.clear(); cv::KeyPoint::convert(keypoints1, points1, queryIdxs);
		points2.clear(); cv::KeyPoint::convert(keypoints2, points2, trainIdxs);
		filteredMatches_ = filteredMatches;

		return bMatchFound;
	}


	/** @brief Return the keypoints detected in the image1 (usually source)
	*/
	std::vector<cv::KeyPoint>& keypoints1_out() {
		return keypoints1;
	}


	/** @brief Return the keypoints detected in the image2 (usually source)
	*/
	std::vector<cv::KeyPoint>& keypoints2_out() {
		return keypoints2;
	}

	cv::Mat& get_descriptors1() {
		return descriptors1;
	}

	cv::Mat& get_descriptors2() {
		return descriptors2;
	}

private:

	std::string winName;

	enum { NONE_FILTER = 0, CROSS_CHECK_FILTER = 1 };

	// OpenCV feature detectors
	cv::Ptr<cv::FeatureDetector> detector;
	cv::Ptr<cv::DescriptorExtractor> descriptorExtractor;
	cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;
	int mactherFilterType;

	// These variables are used to detect the features from image 1 (source)
	// see "match" function
	std::vector<cv::KeyPoint> keypoints1;
	cv::Mat descriptors1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptors2;
	bool eval;

	double ransacReprojThreshold;

	int getMatcherFilterType(const std::string& str)
	{
		if (str == "NoneFilter")
			return NONE_FILTER;
		if (str == "CrossCheckFilter")
			return CROSS_CHECK_FILTER;
#if CV_MAJOR_VERSION == 3
		CV_Error(CV_StsBadArg, "Invalid filter name");
#elif CV_MAJOR_VERSION == 4
		CV_Error(-1, "Invalid filter name");
#endif
		return -1;
	}

	void simpleMatching(cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher,
		const cv::Mat& descriptors1, const cv::Mat& descriptors2,
		std::vector<cv::DMatch>& matches12)
	{
		std::vector<cv::DMatch> matches;
		descriptorMatcher->match(descriptors1, descriptors2, matches12);
	}

	void crossCheckMatching(cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher,
		const cv::Mat& descriptors1, const cv::Mat& descriptors2,
		std::vector<cv::DMatch>& filteredMatches12, int knn = 1)
	{
		filteredMatches12.clear();
		std::vector<std::vector<cv::DMatch> > matches12, matches21;
		descriptorMatcher->knnMatch(descriptors1, descriptors2, matches12, knn);
		descriptorMatcher->knnMatch(descriptors2, descriptors1, matches21, knn);
		for (size_t m = 0; m < matches12.size(); m++)
		{
			bool findCrossCheck = false;
			for (size_t fk = 0; fk < matches12[m].size(); fk++)
			{
				cv::DMatch forward = matches12[m][fk];

				for (size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++)
				{
					cv::DMatch backward = matches21[forward.trainIdx][bk];
					if (backward.trainIdx == forward.queryIdx)
					{
						filteredMatches12.push_back(forward);
						findCrossCheck = true;
						break;
					}
				}
				if (findCrossCheck) break;
			}
		}
	}

	void warpPerspectiveRand(const cv::Mat& src, cv::Mat& dst, cv::Mat& H, cv::RNG& rng)
	{
		H.create(3, 3, CV_32FC1);
		H.at<float>(0, 0) = rng.uniform(0.8f, 1.2f);
		H.at<float>(0, 1) = rng.uniform(-0.1f, 0.1f);
		H.at<float>(0, 2) = rng.uniform(-0.1f, 0.1f)*src.cols;
		H.at<float>(1, 0) = rng.uniform(-0.1f, 0.1f);
		H.at<float>(1, 1) = rng.uniform(0.8f, 1.2f);
		H.at<float>(1, 2) = rng.uniform(-0.1f, 0.1f)*src.rows;
		H.at<float>(2, 0) = rng.uniform(-1e-4f, 1e-4f);
		H.at<float>(2, 1) = rng.uniform(-1e-4f, 1e-4f);
		H.at<float>(2, 2) = rng.uniform(0.8f, 1.2f);

		warpPerspective(src, dst, H, src.size());
	}


	bool doIteration(const cv::Mat& img1, cv::Mat& img2, bool isWarpPerspective,
		std::vector<cv::KeyPoint>& keypoints1, const cv::Mat& descriptors1,
		cv::Ptr<cv::FeatureDetector>& detector, cv::Ptr<cv::DescriptorExtractor>& descriptorExtractor,
		cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher, int matcherFilter, bool eval,
		double ransacReprojThreshold, cv::RNG& rng,
		std::vector<cv::Point2f> &points1,
		std::vector<cv::Point2f> &points2)
	{
		bool bMatchFound = false;
		assert(!img1.empty());
		cv::Mat H12;
		if (isWarpPerspective)
			warpPerspectiveRand(img1, img2, H12, rng);
		else
			assert(!img2.empty()/* && img2.cols==img1.cols && img2.rows==img1.rows*/);

		std::cout << std::endl << "< Extracting keypoints from second image..." << std::endl;
		std::vector<cv::KeyPoint> keypoints2;
		detector->detect(img2, keypoints2);
		std::cout << keypoints2.size() << " points" << std::endl << ">" << std::endl;

		if (!H12.empty() && eval)
		{
			std::cout << "< Evaluate feature detector..." << std::endl;
			float repeatability;
			int correspCount;
			evaluateFeatureDetector(img1, img2, H12, &keypoints1, &keypoints2, repeatability, correspCount);
			std::cout << "repeatability = " << repeatability << std::endl;
			std::cout << "correspCount = " << correspCount << std::endl;
			std::cout << ">" << std::endl;
		}

		std::cout << "< Computing descriptors for keypoints from second image..." << std::endl;
		cv::Mat descriptors2;
		descriptorExtractor->compute(img2, keypoints2, descriptors2);
		std::cout << ">" << std::endl;

		std::cout << "Descriptors1: " << descriptors1.cols << " " << descriptors1.rows << std::endl;
		std::cout << "Descriptors2: " << descriptors2.cols << " " << descriptors2.rows << std::endl;
		std::vector<cv::DMatch> filteredMatches;
		cv::Mat drawImg;
		if (descriptors1.cols > 4 && descriptors1.rows > 4 && descriptors2.cols > 4 && descriptors2.rows > 4)
		{
			std::cout << "< Matching descriptors..." << std::endl;

			switch (matcherFilter)
			{
			case CROSS_CHECK_FILTER:
				crossCheckMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches, 1);
				break;
			default:
				simpleMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches);
			}
			std::cout << ">" << std::endl;


			if (!H12.empty() && eval)
			{
				std::cout << "< Evaluate descriptor matcher..." << std::endl;
				std::vector<cv::Point2f> curve;
#if CV_MAJOR_VERSION == 2
				cv::Ptr<cv::GenericDescriptorMatcher> gdm = new cv::VectorDescriptorMatcher(descriptorExtractor, descriptorMatcher);
				evaluateGenericDescriptorMatcher(img1, img2, H12, keypoints1, keypoints2, 0, 0, curve, gdm);
#else
				std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;
#endif

				cv::Point2f firstPoint = *curve.begin();
				cv::Point2f lastPoint = *curve.rbegin();
				int prevPointIndex = -1;
				std::cout << "1-precision = " << firstPoint.x << "; recall = " << firstPoint.y << std::endl;
				for (float l_p = 0; l_p <= 1 + FLT_EPSILON; l_p += 0.05f)
				{
					int nearest = getNearestPoint(curve, l_p);
					if (nearest >= 0)
					{
						cv::Point2f curPoint = curve[nearest];
						if (curPoint.x > firstPoint.x && curPoint.x < lastPoint.x && nearest != prevPointIndex)
						{
							std::cout << "1-precision = " << curPoint.x << "; recall = " << curPoint.y << std::endl;
							prevPointIndex = nearest;
						}
					}
				}
				std::cout << "1-precision = " << lastPoint.x << "; recall = " << lastPoint.y << std::endl;
				std::cout << ">" << std::endl;
			}

			std::vector<int> queryIdxs(filteredMatches.size()), trainIdxs(filteredMatches.size());
			for (size_t i = 0; i < filteredMatches.size(); i++)
			{
				queryIdxs[i] = filteredMatches[i].queryIdx;
				trainIdxs[i] = filteredMatches[i].trainIdx;
			}

			if (!isWarpPerspective && ransacReprojThreshold >= 0)
			{
				std::cout << "< Computing homography (RANSAC)..." << std::endl;
				//vector<Point2f> points1; KeyPoint::convert(keypoints1, points1, queryIdxs);
				//vector<Point2f> points2; KeyPoint::convert(keypoints2, points2, trainIdxs);
				points1.clear(); cv::KeyPoint::convert(keypoints1, points1, queryIdxs);
				points2.clear(); cv::KeyPoint::convert(keypoints2, points2, trainIdxs);
#if CV_MAJOR_VERSION == 3
				H12 = cv::findHomography(cv::Mat(points1), cv::Mat(points2), 
					CV_RANSAC, ransacReprojThreshold);
#elif CV_MAJOR_VERSION == 4
				H12 = cv::findHomography(cv::Mat(points1), cv::Mat(points2), 
					cv::RANSAC, ransacReprojThreshold);
#endif

				//ImageTransformation image_transformation;
				//image_transformation.homography(points1, points2, CV_RANSAC, ransacReprojThreshold );
				//Mat dst;
				//image_transformation.transform(img1, dst, Size(640, 480));
				//imshow("warp", dst);
				//cout << ">" << endl;
			}

			if (!H12.empty()) // filter outliers
			{
				bMatchFound = true;
				std::vector<char> matchesMask(filteredMatches.size(), 0);
				std::vector<cv::Point2f> points1; cv::KeyPoint::convert(keypoints1, points1, queryIdxs);
				std::vector<cv::Point2f> points2; cv::KeyPoint::convert(keypoints2, points2, trainIdxs);
				cv::Mat points1t; perspectiveTransform(cv::Mat(points1), points1t, H12);

				double maxInlierDist = ransacReprojThreshold < 0 ? 3 : ransacReprojThreshold;
				for (size_t i1 = 0; i1 < points1.size(); i1++)
				{
					if (norm(points2[i1] - points1t.at<cv::Point2f>((int)i1, 0)) <= maxInlierDist) // inlier
						matchesMask[i1] = 1;
				}
				// draw inliers
				drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, CV_RGB(0, 255, 0), CV_RGB(0, 0, 255), matchesMask
#if DRAW_RICH_KEYPOINTS_MODE
					, DrawMatchesFlags::DRAW_RICH_KEYPOINTS
#endif
					);

#if DRAW_OUTLIERS_MODE
				// draw outliers
				for (size_t i1 = 0; i1 < matchesMask.size(); i1++)
					matchesMask[i1] = !matchesMask[i1];
				drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, CV_RGB(0, 0, 255), CV_RGB(255, 0, 0), matchesMask,
					DrawMatchesFlags::DRAW_OVER_OUTIMG | DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
#endif
			}
			else
				drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg);
		}
		else
			drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg);

		//// Detect chessboard left image
		//int nx = 10, ny = 7; // paper
		////int nx = 8, ny = 6;	// wood
		////int nx = 9, ny = 6; //opencv
		//if (DetectChessboard(img1, nx, ny))
		//{
		//	for (vector<Point2f>::iterator it = points_use.begin(); it != points_use.end(); it++)
		//	{
		//		it->x += img1.cols;
		//	}
		//	drawChessboardCorners(drawImg, Size(nx, ny), points_use, true);

		//	// Detect chessboard right image
		//	if (DetectChessboard(img2, nx, ny))
		//	{
		//		for (vector<Point2f>::iterator it = points_use.begin(); it != points_use.end(); it++)
		//		{
		//			it->x += img1.cols;
		//		}
		//		drawChessboardCorners(drawImg, Size(nx, ny), points_use, true);

		//		if (bStartCalibration)
		//		{
		//			iFrameCalib++;
		//			if (iFrameCalib % iFrameCalibStep == 0)
		//			{
		//				Mat mgray;
		//				cvtColor(img1, mgray, CV_BGR2GRAY);
		//				v_image_list.push_back(mgray.clone());
		//				cvtColor(img2, mgray, CV_BGR2GRAY);
		//				v_image_list.push_back(mgray.clone());

		//				char buf[256];
		//				//sprintf(buf, "xleft%02d.jpg", v_image_list.size() / 2);
		//				//imwrite(buf, img1);
		//				//sprintf(buf, "xright%02d.jpg", v_image_list.size() / 2);
		//				//imwrite(buf, img2);
		//			}

		//			imwrite("drawImg.jpg", drawImg);

		//			if (v_image_list.size() == 22)
		//			{
		//				StereoCalib2(v_image_list, Size(nx, ny));
		//				bStartCalibration = false;
		//			}
		//		}
		//	}
		//}
		//rectangle(drawImg, Point(img1.cols + 50, 50), Point(img1.cols + 100, 150), Scalar(255, 0, 0), 2);

		cv::resize(drawImg, drawImg,
			cv::Size(drawImg.cols / 4, drawImg.rows / 4));
		imshow(winName, drawImg);

		return bMatchFound;
	}


};

} // namespace feature
} // namespace CmnIP

#endif // CMNIP_FEATURE_FEATUREMATCHING_HPP__
