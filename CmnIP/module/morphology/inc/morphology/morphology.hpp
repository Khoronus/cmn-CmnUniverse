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

#ifndef CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__
#define CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "opencv2/legacy/legacy.hpp"

namespace CmnIP
{
namespace morphology
{

/** Simple morphology operations
*/
class Morphology
{
public:

  /**  @function Erosion  */
  static void Erosion( const cv::Mat &src, cv::Mat &dst,
	  int type = 2, int size = 2);

  /** @function Dilation */
  static void Dilation( const cv::Mat &src, cv::Mat &dst,
	  int type = 2, int size = 2 );

};


} // namespace morphology
} // namespace CmnIP

#endif /* CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__ */
