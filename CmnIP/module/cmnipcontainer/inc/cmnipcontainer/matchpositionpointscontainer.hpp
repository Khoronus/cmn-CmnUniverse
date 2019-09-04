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

#ifndef CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSCONTAINER_HPP__
#define CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSCONTAINER_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

/** @brief Container of the image of points. It contains all the possible 
           formats of points in the ImagePointMatchPositionContainer.
*/
struct MatchPositionPointsContainer
{
	int image_id_;

	/** v_p_v_points Vector of pairs which associate the associated image id and points
					first: image associated id
					second: points vector
	*/
	std::vector< std::pair< int, std::vector<cv::Point2f> > > v_p_v_points_;

	/** v_p_p_v_points Vector of pairs which associate the associated image id and points from both the images (iImageID, associated image id)
					first: image associated id
					second: pair of vector of points
						first: iImageID points vector
						second: associated image id points vector
	*/
	std::vector< std::pair< int, std::pair< std::vector<cv::Point2f>, std::vector<cv::Point2f> > > > v_p_p_v_points_;

	/** v_p_v_v_points Vector of pairs which associate the associated image id and points from both the images (iImageID, associated image id)
		first: image associated id
		second: vector with the pair of associated points
		  first: iImageID points
		  second: associated image id points
	*/
	std::vector< std::pair< int, std::vector< std::pair< cv::Point2f, cv::Point2f > > > > v_p_v_p_points_;
};

}	// namespace cmnipcontainer
}	// namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSCONTAINER_HPP__ */
