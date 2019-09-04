/**
* @file contour_operations.hpp
* @brief Body of the classes to perform some operations with a contour image.
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

#include "cmnipcontainer/inc/cmnipcontainer/contouroperations.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

//-----------------------------------------------------------------------------
void ContourOperations::get_point(
	std::queue< std::pair<float, float> > &remaining, cv::Mat &src, 
	float radius, float radius2, float epsilon, 
	std::set< std::pair<float, float> > &container) {

	if (remaining.empty()) return;
	std::pair<float, float> p = remaining.front();
	remaining.pop();
	// Check if there are points that are in the container within the radius
	bool found = false;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = container.begin(); it != container.end(); it++) {
#else
	for (std::set< std::pair<float, float> >::const_iterator it = container.begin(); it != container.end(); it++) {
#endif
		if (*it != p) {
			if (CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<float>(
				p, *it) < radius2) {
				found = true;
				break;
			}
		}
	}
	if (found) return;

	// Search the matching within a subregion
	for (int y = p.second - radius; y <= p.second + radius; y++)
	{
		for (int x = p.first - radius; x <= p.first + radius; x++)
		{
			if (x >= 0 && y >= 0 && x < src.cols && y < src.rows &&
				src.at<cv::Vec3b>(y,x)[0] != 0) {
				float d = CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<float>(
					p, std::make_pair(x,y));
				if (std::abs(d - radius) < epsilon) {
					// check if there are already points in the similar area
					bool found = false;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
					for (auto it = container.begin(); it != container.end(); it++) 
#else
					for (std::set< std::pair<float, float> >::const_iterator it = container.begin(); it != container.end(); it++) 
#endif
					{
						if (CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<float>(
							std::make_pair(x,y), 
							std::make_pair(it->first, it->second)) < radius2) {
							found = true;
							break;
						}
					}
					if (!found) {
						container.insert( std::make_pair((float)x, (float)y) );
						remaining.push( std::make_pair(x, y) );
					}
				}
			}
		}
	}
	// Scan for the remaining points
	while (!remaining.empty()) {
		get_point(remaining, src, radius, radius2, epsilon, container);
	}
}

}	// namespace cmnipcontainer
}	// namespace CmnIP
