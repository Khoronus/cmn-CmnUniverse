/**
* @file moment.hpp
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


#ifndef CMNIP_MEASURE_MOMENT_HPP__
#define CMNIP_MEASURE_MOMENT_HPP__

#include <map>

#include <opencv2/opencv.hpp>

namespace CmnIP
{
namespace measure
{

/** Perform some instant image measures
*/
class Moment
{
public:

  /**  Calculate the image distance
  */
  static void distance( const cv::Mat &src, cv::Mat &dst, 
	  	double normalize_alpha, double normalize_beta, 
		double threshold_thresh, double threshold_maxval,
		std::map<std::string, cv::Mat > *m_images);
};


} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_MOMENT_HPP__
