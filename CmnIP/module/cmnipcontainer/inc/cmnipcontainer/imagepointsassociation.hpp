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

#ifndef CMNIP_CMNIPCONTAINER_IMAGEPOINTSASSOCIATION_HPP__
#define CMNIP_CMNIPCONTAINER_IMAGEPOINTSASSOCIATION_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "matchpositionpointsmanager.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

/** Wrapper class to perform the point association between multiple images
*/
class ImagePointsAssociation
{
public:

	/** @brief It clears the data
	*/
	void clear() {
		ipmpc_.clear();
	}

	/** Set the points for the homography
	*/
	void setPoint(int image_id_origin, int iMaxNumPointsEachImage, 
		const std::pair<int, int> &p_associated, int point_id, 
		const cv::Point2f &pt)
	{
		ipmpc_.set(image_id_origin, iMaxNumPointsEachImage, p_associated, 
			point_id, pt, false);
	}

	/** @brief Save the association
		
		Save the points used for the calibration. The points are defined as 
		a ImagePointMatchPositionContainer.

		@param[in] path Where the file is located.
		@param[in] filename Name of the file.
		@return Return true in case of success.
	*/
	bool save(const std::string &path, const std::string &filename_);

	/** @brief Load the points used for the calibration.
		
		Load the points used for the calibration. The points are defined as 
		a ImagePointMatchPositionContainer.

		@param[in] path Where the file is located.
		@param[in] filename Name of the file.
		@return Return true in case of success.
	*/
	bool load(const std::string &path, const std::string &filename_);

	/** @brief Load the points used for the calibration.
		
		Load the points used for the calibration. The points are defined as 
		a ImagePointMatchPositionContainer.

		@param[in] path Where the file is located.
		@param[in] filename Name of the file.
		@param[in] version Version of the filename to open.
		@return Return true in case of success.
	*/
	bool load(const std::string &path, const std::string &filename_,
		const std::string &version);


	/** Get the ImagePointMatchPosition container
	*/
	MatchPositionPointsManager& ipmpc() {
		return ipmpc_;
	}

	/** Set the points for the homography
	*/
	void toImage(int image_id_origin, double xscale, double yscale, cv::Mat &out)
	{
		std::vector< std::pair< int, std::vector<cv::Point2f> > > v_p_v_points;
		ipmpc_.getAssociated(image_id_origin, v_p_v_points);

		for (std::vector< std::pair< int, std::vector<cv::Point2f> > >::const_iterator it = v_p_v_points.begin();
			it != v_p_v_points.end(); it++)
		{
			int iPointNum = 0;
			for (std::vector<cv::Point2f>::const_iterator it2 = it->second.begin();
				it2 != it->second.end(); it2++)
			{
				char buf[256];
				sprintf(buf, "%i, %i", it->first, iPointNum);
				cv::putText(out, buf, 
					cv::Point(it2->x * xscale, it2->y * yscale), 0, 1.0, 
					cv::Scalar(0, 0, 255), 2);
				cv::rectangle(out, cv::Rect(
					cv::Point(it2->x * xscale, it2->y * yscale) - cv::Point(4,4), 
					cv::Point(it2->x * xscale, it2->y * yscale) + cv::Point(4,4)), 
					cv::Scalar(0, 255), -1);
				++iPointNum;
			}
		}
	}


 private:

	/** @brief Container with the associated points between the images
	*/
	 MatchPositionPointsManager ipmpc_;

};

} // namespace cmnipcontainer
} // namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_IMAGEPOINTSASSOCIATION_HPP__ */
