/**
* @file algorithm_headers.hpp
* @brief Header of all the files related to the algorithm
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
* @version 0.1.0.0
*
*/

#ifndef CMNIP_TREE_QUADTREE_HPP__
#define CMNIP_TREE_QUADTREE_HPP__

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

namespace CmnIP
{
namespace tree
{

struct QuadTreeRegion {
	// tree data structure
	std::vector<QuadTreeRegion> childs;
	bool validity; // TODO: have a method for clear the data structure and remove regions with false validity

	// tree for split&merge procedure
	cv::Rect roi;
	cv::Mat m;
	cv::Scalar label;
	cv::Mat mask; // for debug. don't use in real cases because it is computationally too heavy.
};

/** @brief QuadTree

	@link http://stackoverflow.com/questions/7050164/image-segmentation-split-and-merge-quadtrees/14730467#14730467
*/
class QuadTree
{
public:

	//----------------------------------------------------------------------------------------------------------------------- merging
	static bool mergeTwoRegion(QuadTreeRegion& parent, const cv::Mat& src,
		QuadTreeRegion& r1, QuadTreeRegion& r2,
		cv::Size &size, float standard_deviation, int min_size,
		bool(*predicate)(const cv::Mat&, float, int)) {

		if (r1.childs.size() == 0 && r2.childs.size() == 0) {

			cv::Rect roi1 = r1.roi;
			cv::Rect roi2 = r2.roi;
			cv::Rect roi12 = roi1 | roi2;
			if (predicate(src(roi12), standard_deviation, min_size)) {
				r1.roi = roi12;

				// recompute mask
				r1.mask = cv::Mat::zeros(size, CV_8U);
#if CV_MAJOR_VERSION == 3
				cv::rectangle(r1.mask, r1.roi, 1, CV_FILLED);
#elif CV_MAJOR_VERSION == 4
				cv::rectangle(r1.mask, r1.roi, 1, cv::FILLED);
#endif

				r2.validity = false;
				return true;
			}
		}
		return false;
	}

	static void merge(const cv::Mat& src, QuadTreeRegion& r,
		cv::Size &size, float standard_deviation, int min_size,
		bool(*predicate)(const cv::Mat&, float, int)) {
		// check for adjiacent regions. if predicate is true, then  merge.
		// the problem is to check for adjiacent regions.. one way can be:
		// check merging for rows. if neither rows can be merged.. check for cols.

		bool row1 = false, row2 = false, col1 = false, col2 = false;

		if (r.childs.size() < 1) return;

		// try with the row
		row1 = mergeTwoRegion(r, src, r.childs[0], r.childs[1],
			size, standard_deviation, min_size, predicate);
		row2 = mergeTwoRegion(r, src, r.childs[2], r.childs[3],
			size, standard_deviation, min_size, predicate);

		if (!(row1 | row2)) {
			// try with column
			col1 = mergeTwoRegion(r, src, r.childs[0], r.childs[2],
				size, standard_deviation, min_size, predicate);
			col2 = mergeTwoRegion(r, src, r.childs[1], r.childs[3],
				size, standard_deviation, min_size, predicate);
		}

		for (size_t i = 0; i < r.childs.size(); i++) {
			if (r.childs[i].childs.size()>0)
				merge(src, r.childs[i],
				size, standard_deviation, min_size, predicate);
		}
	}

	//----------------------------------------------------------------------------------------------------------------------- quadtree splitting
	static QuadTreeRegion split(const cv::Mat& src, cv::Rect roi,
		cv::Size &size, float standard_deviation, int min_size,
		bool(*predicate)(const cv::Mat&, float, int)) {
		std::vector<QuadTreeRegion> childs;
		QuadTreeRegion r;

		r.roi = roi;
		r.m = src;
		r.mask = cv::Mat::zeros(size, CV_8U);
#if CV_MAJOR_VERSION == 3
		cv::rectangle(r.mask, r.roi, 1, CV_FILLED);
#elif CV_MAJOR_VERSION == 4
		cv::rectangle(r.mask, r.roi, 1, cv::FILLED);
#endif
		r.validity = true;

		bool b = predicate(src, standard_deviation, min_size);
		if (b) {
			cv::Scalar mean, s;
			meanStdDev(src, mean, s);
			r.label = mean;
		}
		else {
			int w = src.cols / 2;
			int h = src.rows / 2;
			QuadTreeRegion r1 = split(src(cv::Rect(0, 0, w, h)), cv::Rect(roi.x, roi.y, w, h), size, standard_deviation, min_size, predicate);
			QuadTreeRegion r2 = split(src(cv::Rect(w, 0, w, h)), cv::Rect(roi.x + w, roi.y, w, h), size, standard_deviation, min_size, predicate);
			QuadTreeRegion r3 = split(src(cv::Rect(0, h, w, h)), cv::Rect(roi.x, roi.y + h, w, h), size, standard_deviation, min_size, predicate);
			QuadTreeRegion r4 = split(src(cv::Rect(w, h, w, h)), cv::Rect(roi.x + w, roi.y + h, w, h), size, standard_deviation, min_size, predicate);
			r.childs.push_back(r1);
			r.childs.push_back(r2);
			r.childs.push_back(r3);
			r.childs.push_back(r4);
		}
		//merge(img, r, predicate);
		return r;
	}

	//----------------------------------------------------------------------------------------------------------------------- tree traversing utility
	static void print_region(QuadTreeRegion r) {
		if (r.validity == true && r.childs.size() == 0) {
			std::cout << r.mask << " at " << r.roi.x << "-" << r.roi.y << std::endl;
			std::cout << r.childs.size() << std::endl;
			std::cout << "---" << std::endl;
		}
		for (size_t i = 0; i < r.childs.size(); i++) {
			print_region(r.childs[i]);
		}
	}

	static void draw_rect(cv::Mat& imgRect, QuadTreeRegion r) {
		if (r.validity == true && r.childs.size() == 0) {
			cv::rectangle(imgRect, r.roi, 50, 1); //.1 (thickness)
		}
		for (size_t i = 0; i < r.childs.size(); i++) {
			draw_rect(imgRect, r.childs[i]);
		}
	}

	static void draw_region(cv::Mat& img, QuadTreeRegion r) {
		if (r.validity == true && r.childs.size() == 0) {
#if CV_MAJOR_VERSION == 3
			cv::rectangle(img, r.roi, r.label, CV_FILLED);
#elif CV_MAJOR_VERSION == 4
			cv::rectangle(img, r.roi, r.label, cv::FILLED);
#endif
		}
		for (size_t i = 0; i < r.childs.size(); i++) {
			draw_region(img, r.childs[i]);
		}
	}

	//----------------------------------------------------------------------------------------------------------------------- split&merge test predicates
	static bool predicateStdZero(const cv::Mat& src) {
		cv::Scalar stddev, mean;
		cv::meanStdDev(src, mean, stddev);
		return stddev[0] == 0;
	}
	static bool predicateStd5(const cv::Mat& src, float sdev, int minsize) {
		cv::Scalar stddev, mean;
		cv::meanStdDev(src, mean, stddev);
		return (stddev[0] <= sdev) || (src.rows*src.cols <= minsize);
	}

};

} // namespace tree
} // namespace CmnIP

#endif /* CMNIP_TREE_QUADTREE_HPP__ */
