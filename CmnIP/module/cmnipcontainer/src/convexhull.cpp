/**
* @file convexhull.cpp
* @brief Body of the wrapper of the bounding functions.
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

#include "cmnipcontainer/inc/cmnipcontainer/convexhull.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{


//-----------------------------------------------------------------------------
float GeometricalOperations::convexHullArea(
	std::vector<cv::Point2f> &originalPoints,	// original points
	std::vector<cv::Point2f> &ch				// convex hull points
	)
{
	// false parameter is used to organize the points in clockwise direction
	cv::convexHull( cv::Mat(originalPoints), ch, false);	
	// calculate the area of convex hull
	double area = 0;
	for (int i = 0; i < (int)ch.size(); i++)
	{
		int next_i = (i+1)%(ch.size());
		double dX = ch[next_i].x - ch[i].x;
		double avgY = (ch[next_i].y + ch[i].y) / 2;
		area += dX* avgY;	// this is the integration step
	}
	return (float)abs(area);
}
//-----------------------------------------------------------------------------
float GeometricalOperations::convexHullArea(
	std::vector<cv::Point2f> &originalPoints,	// original points
	std::vector<cv::Point2f> &ch,				// convex hull points
	cv::Mat &image
    )
{
	// false parameter is used to organize the points in clockwise direction
	cv::convexHull( cv::Mat(originalPoints), ch, false);	
	// calculate the area of convex hull
	double area = 0;
	for (int i = 0; i < (int)ch.size(); i++)
	{
		int next_i = (i+1)%(ch.size());
		double dX = ch[next_i].x - ch[i].x;
		double avgY = (ch[next_i].y + ch[i].y) / 2;
		area += dX* avgY;	// this is the integration step
	}

	// draw the border
	for (int i = 0; i < (int)ch.size() - 1; i++) {
		cv::line(image, cv::Point((int)ch[i].x, (int)ch[i].y), 
		cv::Point((int)ch[i+1].x, (int)ch[i+1].y), cv::Scalar(0,255,0), 1);
	}
	if (ch.size() > 2) {
		cv::line(image, cv::Point((int)ch[0].x, (int)ch[0].y), 
		cv::Point((int)ch[ ch.size() - 1 ].x, (int)ch[ ch.size() - 1 ].y), 
		cv::Scalar(0,255,0), 1);
	}

	return (float)abs(area);
}


} // namespace cmnipcontainer
} // namespace CmnIP
