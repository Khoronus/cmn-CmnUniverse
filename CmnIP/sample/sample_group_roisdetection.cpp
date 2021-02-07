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

#include <iostream>
#include <string>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#if CV_MAJOR_VERSION == 2
#include <opencv2/nonfree/nonfree.hpp>
#endif
#include <opencv2/features2d/features2d.hpp>

#include "group/inc/group/group_headers.hpp"
#include "cmnipcontainer/inc/cmnipcontainer/cmnipcontainer_headers.hpp"
#include "feature/inc/feature/feature_headers.hpp"
#include "measure/inc/measure/measure_headers.hpp"

namespace
{

/** @brief Global container for all the images found (temporary)
*/
std::vector< cv::Mat > container;

/** @brief Information about an image
*/
typedef struct ImageInfo_
{
	cv::Mat src;
	cv::Point2f position;
} ImageInfo;

/** @brief Function to test the feature detection with a generic detector.
*/
void detection_features(CmnIP::feature::FeatureMatching *feature_matching,
	cv::Mat &prev, cv::Mat &curr, std::vector< cv::Point2f > &v_points1, 
	std::vector< cv::Point2f > &v_points2)
{
	// Container with the detected points
	v_points1.clear();
	v_points2.clear();
	// Detect the features and set the descriptors
	feature_matching->detect(0, prev, false);
	feature_matching->detect(1, curr, false);
	feature_matching->describe(0, prev, true);
	feature_matching->describe(1, curr, true);
	// Perform the matching
	if (!feature_matching->match(v_points1, v_points2, false)) return;
}

/** @brief Function to test the feature detection with a generic detector.
*/
void detect_clusters(
	std::vector< cv::Point2f > &v_points1,
	std::vector< cv::Point2f > &v_points2,
	cv::Mat &prev, cv::Mat &curr, cv::Mat &out)
{
	// combine the images
	cv::Mat m(curr.rows, curr.cols * 2, CV_8UC3);
	curr.copyTo(m(cv::Rect(0, 0, curr.cols, curr.rows)));
	prev.copyTo(m(cv::Rect(curr.cols, 0, prev.cols, prev.rows)));
	int s = v_points1.size();
	cv::RNG r;
	cv::Mat mclone = m.clone();
	// Draw the detected features
	for (int i = 0; i < s; i++)
	{
		cv::line(mclone, v_points1[i],
			v_points2[i] + cv::Point2f(curr.cols, 0), cv::Scalar(r.uniform(0, 255),
			r.uniform(0, 255), r.uniform(0, 255)));
	}

	// Detect the candidate clusters
	// It affects the number of clusters (bigger is the number small is the
	// number of clusters).
	float max_cluster_radius = 50;
	std::map<int, std::vector<int> > cluster;
	// Approximatively estimate the number of clusters
	CmnIP::group::Clustering::set2cluster(v_points1, max_cluster_radius, cluster);
	// Empty the cluster and recalculate the number of clusters
	int num_expected_clusters = cluster.size();
	cluster.clear();
	CmnIP::group::Clustering::kmean(v_points1, num_expected_clusters, cluster);

	// Generate the container for the cluster in the previous image
	std::map<int, std::map<int, float>> radius;
	std::map<int, CmnIP::cmnipcontainer::BoundContainer> bc;
	CmnIP::cmnipcontainer::BoundContainerManager::cluster2bound_container(
		v_points1, cluster, cv::Point2f(0, 0), radius[0], bc[0]);

	// Scan the points in the previous image cluster and check where they head 
	// in the current image.
	// If the points are too far from the mean center (out of max_radius + 
	// epsilon), remove the points from the cluster. 
	int max_delta_radius = 10;
	for (auto it = cluster.begin(); it != cluster.end(); it++)
	{
		// Create a container of points from the cluster association.
		// Only valid index (>=0) is taken in account.
		std::vector<cv::Point2f> vct;
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (*it2 >= 0) vct.push_back(v_points2[*it2]);
		}
		// Calculate the mean position
		cv::Point2f c = CmnIP::measure::CentralTendency<cv::Point2f>::points_mean(vct);
		// Draw it (only for debug)
		cv::circle(mclone, c + cv::Point2f(curr.cols, 0), 5, 
			cv::Scalar(0, 0, 255), -1);
		// Remove the index of the points which are too far from the center and
		// the radius is not compatible
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			float d = CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(
				c, v_points2[*it2]);
			if (d > radius[0][it->first] + max_delta_radius) {
				*it2 = -1;
			}
		}
	}

	// From the cluster in the current image, create the containers
	CmnIP::cmnipcontainer::BoundContainerManager::cluster2bound_container(
		v_points2, cluster,	cv::Point2f(0, 0), radius[1], bc[1]);
	// From the cluster in the current image, create the containers
	// used for the visualization
	CmnIP::cmnipcontainer::BoundContainerManager::cluster2bound_container(
		v_points2, cluster,	cv::Point2f(curr.cols, 0), radius[2], bc[2]);
	// Draw the clusters over the copy image (debug)
	CmnIP::cmnipcontainer::BoundContainerManager::draw(bc.at(0), mclone);
	CmnIP::cmnipcontainer::BoundContainerManager::draw(bc.at(2), mclone);
	cv::imshow("mclone", mclone);

	CmnIP::cmnipcontainer::BoundContainerManager::draw(bc.at(0), m);
	CmnIP::cmnipcontainer::BoundContainerManager::draw(bc.at(2), m);

	// Container with the pairs of images
	std::vector< std::pair< ImageInfo, ImageInfo > > img_pairs;
	// Container with the associated images (to show)
	cv::Mat tmp_out(700, 110, CV_8UC3, cv::Scalar::all(0));
	// Number of clusters
	int nclusters = bc[0].boundRect.size();
	// Estimate the image size 
	int wsize = (std::min)(tmp_out.rows / nclusters, tmp_out.cols / 2 - 2);

	// It scans the clusters from the previous and current image.
	// If they are compatible, they are add to the pairs container.
	// These pictures should be memorized as associable images.
	for (int i = 0; i < nclusters; i++)
	{
		// The poly boundler has at least a point and the rectangle is inside
		// the source image.
		if (bc[0].contours_poly[i].size() > 1 && bc[1].contours_poly[i].size() > 1 &&
			CmnIP::measure::CheckImageData::is_valid(curr, bc[0].boundRect[i]) && 
			CmnIP::measure::CheckImageData::is_valid(prev, bc[1].boundRect[i])) {
			// Extract the ROIs
			cv::Mat tmp0 = curr(bc[0].boundRect[i]);
			cv::Mat tmp1 = prev(bc[1].boundRect[i]);

			// Add the original rois in the container.
			ImageInfo ii0, ii1;
			ii0.position = bc[0].boundRect[i].tl();
			ii0.src = tmp0.clone();
			ii1.position = bc[1].boundRect[i].tl();
			ii1.src = tmp1.clone();
			img_pairs.push_back(std::make_pair(ii0, ii1));
		}
	}

	// Scan the container of points and verify the likelihood that the pair
	// match (debug)
	float max_match_pair_likelihood = 0.5;
	int image_idx = 0;
	for (auto it = img_pairs.begin(); it != img_pairs.end(); it++)
	{
		cv::Mat tmp0, tmp1;
		cv::resize(it->first.src, tmp0, cv::Size(wsize, wsize));
		cv::resize(it->second.src, tmp1, cv::Size(wsize, wsize));

		// Calculate the likelihood the images match
		// It colors the images which likelihood is over a threshold in green
		// red othewise.
		cv::Rect region_out;
		double likelihood;
		CmnIP::measure::TemplateMatching::region(tmp0, tmp1, 5, false,
			region_out,
			likelihood);
		if (likelihood > max_match_pair_likelihood) {
			cv::rectangle(tmp0, cv::Rect(0, 0, tmp0.cols, tmp0.rows),
				cv::Scalar(0, 255), 3);
			cv::rectangle(tmp1, cv::Rect(0, 0, tmp1.cols, tmp1.rows),
				cv::Scalar(0, 255), 3);
		}
		else {
			cv::rectangle(tmp0, cv::Rect(0, 0, tmp0.cols, tmp0.rows),
				cv::Scalar(0, 0, 255), 3);
			cv::rectangle(tmp1, cv::Rect(0, 0, tmp1.cols, tmp1.rows),
				cv::Scalar(0, 0, 255), 3);
		}
		tmp0.copyTo(tmp_out(cv::Rect(0, wsize * image_idx, tmp0.cols, tmp0.rows)));
		tmp1.copyTo(tmp_out(cv::Rect(wsize, wsize * image_idx, tmp1.cols, tmp1.rows)));
		++image_idx;
	}
	cv::imshow("tmp_out", tmp_out);

	if (false)
	{
		// It compares the ROIs from the previous image and the memorized clusters
		// to find a match. If no match has been found, it add the image to the
		// container.
		// [TODO] Do it in a separate process/thread.
		float max_match_container_likelihood = 0.8;
		for (auto it = img_pairs.begin(); it != img_pairs.end(); it++)
		{
			cv::Mat tmp0;
			cv::resize(it->first.src, tmp0, cv::Size(32, 32));
			bool bAdd = true;
			int k = container.size();
			for (int j = 0; j < k; j++)
			{
				cv::Rect region_out;
				double likelihood;
				// If it is not possible to match, do not add!!!
				if (!CmnIP::measure::TemplateMatching::region(tmp0, container[j], 5,
					false, region_out, likelihood)) bAdd = false;
				if (likelihood > max_match_container_likelihood) {
					bAdd = false;
				}
			}
			if (bAdd) {
				container.push_back(tmp0.clone());
			}
		}

		// Create a panel with all the images in the container
		// [TODO] Copy in a drawing class.
		cv::Mat tmp_container(700, 700, CV_8UC3, cv::Scalar::all(0));
		int elements = container.size();
		if (elements > 0)
		{
			int w = std::sqrt((float)elements) + 1;
			int h = w;
			int wsize = tmp_container.cols / w - 2;
			for (int i = 0; i < elements; i++)
			{
				int x = i % w; int y = i / w;
				cv::Mat tmp;
				cv::resize(container[i], tmp, cv::Size(wsize, wsize));
				tmp.copyTo(tmp_container(cv::Rect(wsize * x, wsize * y, wsize, wsize)));
			}
			cv::imshow("img_container", tmp_container);
		}
	}

	out = m.clone();
}


/** @brief Function to show the feature detection.
*/
int test(std::string &settingfilename_in)
{
	//cv::initModule_nonfree();

	cv::VideoCapture vc(0);
	//cv::VideoCapture vc("C:\\Moro\\Programs\\ThirdParty Lib\\ffmpeg-20130809-git-3b2e99f-win32-static\\bin\\20141025\\20141025_001.mp4");

	if (!vc.isOpened()) {
		std::cout << "Unable to open the video" << std::endl;
	}

	// Open the setting file
	//load the settings file
	std::string settfilename;
	if (settingfilename_in.length() < 2) {
		//assume settings in working directory
		settfilename = "..\\..\\data\\settings.yml";
	} else {
		//settings provided as argument
		settfilename = settingfilename_in;
	}

	//cv::FileStorage fs;
	//fs.open(settfilename, cv::FileStorage::READ);
	//if (!fs.isOpened()) {
	//	std::cerr << "Could not open settings file: " << settfilename <<
	//		std::endl;
	//	return 0;
	//}

	// Feature detection collectors
	CmnIP::feature::FeatureMatching *feature_matching =
		new CmnIP::feature::FeatureMatching();

	// Feature matching (generic)
	std::string _detector = "FAST"; // FAST
	std::string _descriptorExtractor = "BRISK"; // BRISK ORB
	//std::string _detector = "SIFT"; // FAST
	//std::string _descriptorExtractor = "SIFT"; // BRISK ORB

	std::string _descriptorMatcher = "BruteForce";
	std::string  _mactherFilterType = "CrossCheckFilter"; //"NoneFilter"; // CrossCheckFilter
	double _ransacReprojThreshold = 0.01;
	bool _eval = true;
	feature_matching->set(_detector, _descriptorExtractor, _descriptorMatcher,
		_mactherFilterType, _ransacReprojThreshold, _eval);
	//feature_matching->set_detector_params("threshold", 30);
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

		if (prev.empty()) {
			prev = curr.clone();
			continue;
		}

		std::vector< cv::Point2f > v_prev, v_curr;
		detection_features(feature_matching, prev, curr, v_prev, v_curr);
		detect_clusters(v_prev, v_curr, prev, curr, out);

		if (!curr.empty()) cv::imshow("curr", curr);
		if (!out.empty()) cv::imshow("out", out);

		if (cv::waitKey(10) == 27) bContinue = false;
		cv::swap(curr, prev);
	}

	return 1;
}


} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample Feature Detection" << std::endl;

	std::string settingfilename = "";
	test(settingfilename);
	
	return 0;
}


