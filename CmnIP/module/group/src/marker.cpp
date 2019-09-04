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

#include "group\inc\group\marker.hpp"


namespace CmnIP
{
namespace group
{

/* ############################################################################
   [class] Marker
   ######################################################################### */
//-----------------------------------------------------------------------------
void Marker::clear()
{
  contours_.clear();
  hierarchy_.clear();
  mu_.clear();
  mc_.clear();
}
//-----------------------------------------------------------------------------
void Marker::estimate(const cv::Mat &src )
{
  // check source
  if (src.empty()) return;

#if CV_MAJOR_VERSION == 3
  cv::findContours(src, contours_, hierarchy_, CV_RETR_EXTERNAL,
	  CV_CHAIN_APPROX_SIMPLE);
#else if CV_MAJOR_VERSION == 4
  cv::findContours(src, contours_, hierarchy_, cv::RETR_EXTERNAL,
	  cv::CHAIN_APPROX_SIMPLE);
#endif
  int ncomp = contours_.size();
  mu_ = std::vector<cv::Moments>(ncomp);
  mc_ = std::vector<cv::Point2f>(ncomp);

  // Calculate the moment
  /// Get the moments
  for( int i = 0; i < ncomp; i++ )
  { mu_[i] = cv::moments( contours_[i], false ); }

  ///  Get the mass centers:
  for( int i = 0; i < ncomp; i++ )
  { mc_[i] = cv::Point2f( mu_[i].m10/mu_[i].m00 , mu_[i].m01/mu_[i].m00 ); }
}
//-----------------------------------------------------------------------------
void Marker::draw(double min_area, cv::Mat &dst)
{
  if (dst.empty()) return;
  for( int i = 0; i< static_cast<int>(contours_.size()); i++ )
  {
    cv::Scalar color = cv::Scalar( cv::theRNG().uniform(0, 255), 
      cv::theRNG().uniform(0,255), cv::theRNG().uniform(0,255) );
    if (cv::contourArea(contours_[i]) > min_area)
    {
      cv::drawContours( dst, contours_, i, color, 2, 8, hierarchy_, 0, 
        cv::Point() );
      cv::circle( dst, mc_[i], 4, color, -1, 8, 0 );
    }
  }
}
//-----------------------------------------------------------------------------
void Marker::draw(cv::Size &size, double min_area, 
				  std::vector< cv::Mat > &v_dst)
{
	v_dst.clear();
	int ncomp = contours_.size();

	// Create the marker image for the watershed algorithm
	cv::Mat markers = cv::Mat::zeros(size, CV_32SC1);

	// Draw the foreground markers
	for (int i = 0; i < ncomp; i++)
	{
		// Write only if the area is big enough
		if (cv::contourArea(contours_[i]) > min_area)
			cv::drawContours(markers, contours_, i, cv::Scalar::all(i+1), -1);
	}

	// Draw the background marker
	cv::circle(markers, cv::Point(5,5), 3, CV_RGB(255,255,255), -1);
	v_dst.push_back(markers*10000);

	// Generate random colors
	std::vector<cv::Vec3b> colors;
	for (int i = 0; i < ncomp; i++)
	{
	int b = cv::theRNG().uniform(0, 255);
	int g = cv::theRNG().uniform(0, 255);
	int r = cv::theRNG().uniform(0, 255);

	colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

  // Create the result image
  cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);

  // Fill labeled objects with random colors
  for (int i = 0; i < markers.rows; i++)
  {
    for (int j = 0; j < markers.cols; j++)
    {
      int index = markers.at<int>(i,j);
      if (index > 0 && index <= ncomp)
      {
        dst.at<cv::Vec3b>(i,j) = colors[index-1];
	  } else {
        dst.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
      }
    }
  }
  v_dst.push_back(dst);
}
//-----------------------------------------------------------------------------
std::vector<cv::Point2f> Marker::get_centers(double min_area)
{
  std::vector< cv::Point2f > v_pt;
  for( int i = 0; i< static_cast<int>(contours_.size()); i++ )
  {
    if (cv::contourArea(contours_[i]) > min_area)
    {
	  v_pt.push_back(mc_[i]);
    }
  }
  return v_pt;
}
//-----------------------------------------------------------------------------
std::vector<std::pair<int, cv::Point2f> > 
	Marker::get_centers_and_index(double min_area)
{
  std::vector< std::pair<int, cv::Point2f> > v_pt;
  for( int i = 0; i< static_cast<int>(contours_.size()); i++ )
  {
    if (cv::contourArea(contours_[i]) > min_area)
    {
	  v_pt.push_back(std::pair<int, cv::Point2f>(i, mc_[i]) );
    }
  }
  return v_pt;
}

} // namespace group
} // namespace CmnIP
