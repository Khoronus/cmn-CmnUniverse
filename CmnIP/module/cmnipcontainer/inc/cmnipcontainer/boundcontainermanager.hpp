/**
* @file boundcontainermanager.hpp
* @brief Wrapper for the bounding class.
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
* @version 1.1.0.0
*
*/

#ifndef CMNIP_CMNIPCONTAINER_BOUNDCONTAINERMANAGER_HPP__
#define CMNIP_CMNIPCONTAINER_BOUNDCONTAINERMANAGER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ctime>
#include <map>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/video/tracking.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

/** @brief Structure with the possible bound container
*/
typedef struct BoundContainer_
{
	std::vector<std::vector<cv::Point> > contours_poly;
	std::vector<cv::Rect> boundRect;
	std::vector<cv::Point2f>center;
	std::vector<float>radius;
} BoundContainer;

class BoundContainerManager
{
public:

	/** @brief Draw bound containers
	*/
	static void draw(const BoundContainer &bc,
		cv::Mat &m)
	{
		//cv::RNG rng(12345);
		/// Draw polygonal contour + bonding rects + circles
		for (size_t i = 0; i < bc.boundRect.size(); i++)
		{
			if (bc.contours_poly.size() > 4) {
				//cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				cv::Scalar color = cv::Scalar(i * 37 % 255, (127 + i * 19) % 255, (255 - i * 43) % 255);
				cv::drawContours(m, bc.contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
				cv::rectangle(m, bc.boundRect[i].tl(), bc.boundRect[i].br(), color, 2, 8, 0);
				cv::circle(m, bc.center[i], (int)bc.radius[i], color, 2, 8, 0);
			}
		}
	}

	static void draw(const BoundContainer &bc,
		std::vector< bool > &show, cv::Mat &m)
	{
		//cv::RNG rng(12345);
		/// Draw polygonal contour + bonding rects + circles
		for (size_t i = 0; i < bc.boundRect.size(); i++)
		{
			if (!show[i]) continue;
			//cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			cv::Scalar color = cv::Scalar(i * 37 % 255, (127 + i * 19) % 255, (255 - i * 43) % 255);
			cv::drawContours(m, bc.contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
			cv::rectangle(m, bc.boundRect[i].tl(), bc.boundRect[i].br(), color, 2, 8, 0);
			cv::circle(m, bc.center[i], (int)bc.radius[i], color, 2, 8, 0);
		}
	}

	/** @brief Function to convert a cluster in a bound container.

	Function to convert a cluster in a bound container.
	@param[in] points The original set of points.
	@param[in] cluster The cluster which describe how the points are
	organized.
	@param[in] offset An offset value to add to the set of points to group.
	@param[out] radius_out The radius each cluster occupy.
	@param[out] bc The collection of the bound containers.
	*/
	static void cluster2bound_container(
		const std::vector<cv::Point2f> &points,
		const std::map<int, std::vector<int> > &cluster,
		const cv::Point2f &offset,
		std::map<int, float> &radius_out,
		BoundContainer &bc)
	{
		/// Approximate contours to polygons + get bounding rects and circles
		bc.contours_poly =
			std::vector<std::vector<cv::Point> >(cluster.size());
		bc.boundRect = std::vector<cv::Rect>(cluster.size());
		bc.center = std::vector<cv::Point2f>(cluster.size());
		bc.radius = std::vector<float>(cluster.size());
		int idx = 0;
		for (auto it = cluster.begin(); it != cluster.end(); it++)
		{
			std::vector<cv::Point> vct;
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			{
				if (*it2 >= 0) vct.push_back(points[*it2] + offset);
			}
			if (vct.size() > 4) {
				cv::approxPolyDP(cv::Mat(vct), bc.contours_poly[idx], 3, true);
				bc.boundRect[idx] =
					cv::boundingRect(cv::Mat(bc.contours_poly[idx]));
				cv::minEnclosingCircle((cv::Mat)bc.contours_poly[idx],
					bc.center[idx], bc.radius[idx]);
				radius_out[it->first] = bc.radius[idx];
				++idx;
			}
		}
	}
};


} // namespace cmnipcontainer
} // namespace CmnIP


#endif // CMNIP_CMNIPCONTAINER_BOUNDCONTAINERMANAGER_HPP__
