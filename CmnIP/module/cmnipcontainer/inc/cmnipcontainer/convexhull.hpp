/**
* @file convexhull.hpp
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
* @version 1.0.0.0
*
*/

#ifndef CMNIP_CMNIPCONTAINER_CONVEXHULL_HPP__
#define CMNIP_CMNIPCONTAINER_CONVEXHULL_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctime>

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

/** Some geometrical operation
*/
class GeometricalOperations
{
public:

	/**
		// draw the border
		for (int i = 0; i < ch.size() - 1; i++)
			cv::line(image, Point(ch[i].x, ch[i].y), Point(ch[i+1].x, ch[i+1].y), Scalar(1,1,0,0), 2);
		if (ch.size() > 2)
			cv::line(image, Point(ch[0].x, ch[0].y), Point(ch[ ch.size() - 1 ].x, ch[ ch.size() - 1 ].y), Scalar(1,1,0,0), 2);
	*/
	static float convexHullArea(std::vector<cv::Point2f> &originalPoints,	// original points
								std::vector<cv::Point2f> &ch				// convex hull points
								);

	static float convexHullArea(std::vector<cv::Point2f> &originalPoints,	// original points
								std::vector<cv::Point2f> &ch,				// convex hull points
								cv::Mat &image
								);

};

} // namespace cmnipcontainer
} // namespace CmnIP


#endif // CMNIP_CMNIPCONTAINER_CONVEXHULL_HPP__
