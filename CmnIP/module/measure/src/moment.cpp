/**
* @file moment.cpp
* @brief Body of the relative class
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
* @author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#include "measure/inc/measure/moment.hpp"


namespace CmnIP
{
namespace measure
{

/* ############################################################################
   [class] Moment
   ######################################################################### */
//-----------------------------------------------------------------------------
void Moment::distance(const cv::Mat &src, cv::Mat &dst,
	double normalize_alpha, double normalize_beta, 
	double threshold_thresh, double threshold_maxval,
	std::map<std::string, cv::Mat > *m_images)
{
  // check if the source is empty
  if (src.empty()) return;

  // Perform the distance transform algorithm
  cv::Mat dist;
#if CV_MAJOR_VERSION == 3
  cv::distanceTransform(src, dist, CV_DIST_L2, 3);
#elif CV_MAJOR_VERSION == 4
  cv::distanceTransform(src, dist, cv::DIST_L2, 3);
#endif
  // Normalize the distance image for range = {0.0, 1.0}
  // so we can visualize and threshold it
  cv::normalize(dist, dist, normalize_alpha, normalize_beta, cv::NORM_MINMAX);
  //if (!dist.empty()) cv::imshow("dist", dist);
  if (m_images && !dist.empty()) {
	  cv::Mat tmp;
	  if (dist.channels() == 1)
	  {
		  tmp = dist.clone();
		  tmp *= 255;
		  tmp.convertTo(tmp, CV_8U);
	  }
	(*m_images)[std::string("momentum_norm")] = tmp;
  }

  // Threshold to obtain the peaks
  // This will be the markers for the foreground objects
#if CV_MAJOR_VERSION == 3
  cv::threshold(dist, dist, threshold_thresh, threshold_maxval, 
	  CV_THRESH_BINARY);//.3
#elif CV_MAJOR_VERSION == 4
  cv::threshold(dist, dist, threshold_thresh, threshold_maxval, 
	  cv::THRESH_BINARY);
#endif
  //if (!dist.empty()) cv::imshow("dist2", dist);
  // Create the CV_8U version of the distance image
  // It is needed for cv::findContours()
  //cv::Mat dist_8u;
  dist.convertTo(dst, CV_8U);
  if (m_images && !dist.empty()) {
	  cv::Mat tmp;
	  if (dist.channels() == 1)
	  {
		  tmp = dst.clone();
		  tmp *= 255;
		  tmp.convertTo(tmp, CV_8U);
	  }
	(*m_images)[std::string("momentum_foregroud")] = tmp;
  }
}


} // namespace measure
} // namespace CmnIP
