/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#include "measure\inc\measure\moment.hpp"


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
#else if CV_MAJOR_VERSION == 4
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
#else if CV_MAJOR_VERSION == 4
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
