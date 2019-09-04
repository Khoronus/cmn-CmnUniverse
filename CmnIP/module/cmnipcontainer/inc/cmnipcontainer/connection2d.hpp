/**
* @file connection2d.hpp
* @brief Body of the classes to measure various forms of distance.
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


#ifndef CMNIP_CMNIPCONTAINER_CONNECTION2D_HPP__
#define CMNIP_CMNIPCONTAINER_CONNECTION2D_HPP__

#include <iostream>
#include <fstream>
#include <set>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"
#include "matchpositionpointsmanager.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{


/** @brief Class to find information about points and features in a 2D space.
*/
class Connection2D
{
  public:

	/** @brief Find the valid index

		Add explanation
	*/
	static int find_index(float angle, cv::Point2f &p, 
		std::vector< cv::Point2f > &v_values, 
		cv::Point2f &norm_out,
		int &index);

	/** @brief Function to find the next candidate connection point.

		Function to find the next candidate connection point. It search in 
		clockwise direction. The point must be inside a certain range.
	*/
	static int get_next_connected(cv::Point2f &norm,
		cv::Point2f &p,
		std::set< std::pair< float, float > > &vertex_sparse,
		float min_distance, float max_distance,
		cv::Point2f &norm_out,
		cv::Point2f &point_out);
};


} // namespace cmnipcontainer
} // namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_CONNECTION2D_HPP__ */
