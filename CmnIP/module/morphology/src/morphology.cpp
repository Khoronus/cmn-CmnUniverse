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

#include "morphology\inc\morphology\morphology.hpp"


namespace CmnIP
{
namespace morphology
{

/* ############################################################################
   [class] Morphology
   ######################################################################### */
//-----------------------------------------------------------------------------
void Morphology::Erosion( const cv::Mat &src, cv::Mat &dst, int type, int size)
{
  int erosion_elem = type;
  int erosion_size = size;//2
  int const max_elem = 2;
  int const max_kernel_size = 21;

  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = cv::MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = cv::MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

  cv::Mat element = cv::getStructuringElement( erosion_type,
									   cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
									   cv::Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  cv::erode( src, dst, element );
}
//-----------------------------------------------------------------------------
void Morphology::Dilation( const cv::Mat &src, cv::Mat &dst, 
	int type, int size )
{
  int dilation_elem = type;
  int dilation_size = size;
  int const max_elem = 2;
  int const max_kernel_size = 21;
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = cv::MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = cv::MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

  cv::Mat element = cv::getStructuringElement( dilation_type,
									   cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
									   cv::Point( dilation_size, dilation_size ) );
  /// Apply the dilation operation
  cv::dilate( src, dst, element );
}


} // namespace morphology
} // namespace CmnIP
