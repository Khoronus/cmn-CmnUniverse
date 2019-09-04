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

#ifndef CMNIP_GROUP_MARKER_HPP__
#define CMNIP_GROUP_MARKER_HPP__

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "opencv2/legacy/legacy.hpp"

namespace CmnIP
{
namespace group
{

/** Detect candidate markers from a source
*/
class Marker
{
public:

  Marker() {}

  /** Clear the contents
  */
  void clear();

  /** Estimate the image markers 
  */
  void estimate( const cv::Mat &src );

  /** Draw the detected countour
  */
  void draw( double min_area, cv::Mat &dst );

  /** Draw the marker and regions filled.
      Return a vector of images.
	  First: Grayscale filled regions
	  Second: Colored filled regions
  */
  void draw( cv::Size &size, double min_area, 
	  std::vector< cv::Mat > &v_dst );

  /** Get the contours
  */
  std::vector<std::vector<cv::Point> > contours() const {
	  return contours_;
  }
  std::vector<std::vector<cv::Point> > contours() {
	  return contours_;
  }

  /** Get the hierarchy
  */
  std::vector<cv::Vec4i> hierarchy() const {
	  return hierarchy_;
  }
  std::vector<cv::Vec4i> hierarchy() {
	  return hierarchy_;
  }
  /** Get the moment
  */
  std::vector<cv::Moments> mu() const {
	  return mu_;
  }
  std::vector<cv::Moments> mu() {
	  return mu_;
  }  
  /** Get the center of mass
  */
  std::vector<cv::Point2f> mc() const {
	  return mc_;
  }
  std::vector<cv::Point2f> mc() {
	  return mc_;
  }

  /** Debug get interesting point
  */
  std::vector<cv::Point2f> get_centers(double min_area);
   /** Debug get interesting point
  */
  std::vector<std::pair<int, cv::Point2f> > get_centers_and_index(
	  double min_area);
 
 private:

  /** @Container with the candidate points of an observed roi which are used
      to describe a contours
  */
  std::vector<std::vector<cv::Point> > contours_;
  /** @Hiearchy of observed roi
  */
  std::vector<cv::Vec4i> hierarchy_;
  /** @ROI moment
  */
  std::vector<cv::Moments> mu_;
  /** @Center of mass
  */
  std::vector<cv::Point2f> mc_;

};


} // namespace group
} // namespace CmnIP

#endif /* CMNIP_GROUP_MARKER_HPP__ */
