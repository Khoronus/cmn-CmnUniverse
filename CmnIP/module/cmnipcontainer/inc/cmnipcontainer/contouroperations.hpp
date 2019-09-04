/**
* @file contour_operations.hpp
* @brief Header of the classes to perform some operations with a contour image.
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


#ifndef CMNIP_CMNIPCONTAINER_CONTOUROPERATIONS_HPP__
#define CMNIP_CMNIPCONTAINER_CONTOUROPERATIONS_HPP__

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

/** @brief Class to perform some operations with contour image.

	Class to perform some operations with contour image.
*/
class ContourOperations
{
  public:

	/** @brief Function to get a set of points which belong to a contour at a 
		 defined distance.

		Recorsive function.
		Function to get a set of points which belong to a contour at a defined 
		distance.
		@param[inout] remaining The points that remain to be analyzed.
		@param[in] src The image with contour to scan.
		@param[in] radius The distance expected to find a point which belong to the
						  contour. The research is made in a subregion size radius.
		@param[in] radius2 Miminum distance expected to find a unique point.
		@param[in] epsilon Maximum tolerance to accept a point in the expected 
						   radius.
		@param[out] container Container with the found points.
	*/
	static void get_point(std::queue< std::pair<float, float> > &remaining, 
		cv::Mat &src, float radius, float radius2, float epsilon, 
		std::set< std::pair<float, float> > &container);
};

}	// namespace cmnipcontainer
}	// namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_CONTOUROPERATIONS_HPP__ */
