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

#ifndef CMNIP_CMNIPCONTATINER_MATCHPOSITIONPOINTS_HPP__
#define CMNIP_CMNIPCONTATINER_MATCHPOSITIONPOINTS_HPP__

#include <iostream>
#include <map>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


namespace CmnIP
{
namespace cmnipcontainer
{


/** @brief Class to manage the matching of points between different images.

    Class to manage the matching of points between different images.
	This class contains and modify the relation between the points of different
	images.
*/
class MatchPositionPoints
{
public:

	MatchPositionPoints()	{}

	/** Clear the previously memorized information
	*/
	void clear()	{
		m_v_point_.clear();
	}

	/** Erease an element from the memorized set of points
	*/
	void erase(int image_id)	{
		if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			m_v_point_.erase( m_v_point_.find( image_id ) );
		}
	}

	/** Add a new associated points
	    @param[in] image_id The image to add
		@param[in] num_points The number of points associated to the image
		@remarks
			If the image has already been initialized and the number of points do not match, return 0.
	*/
	int add(int image_id, int num_points)	{

		if (m_v_point_.find( image_id ) == m_v_point_.end())
		{
			// add empty container
			m_v_point_[image_id];
			// add the points
			for (int i = 0; i < num_points; i++)
				m_v_point_[image_id].push_back( cv::Point(0,0) );

			return 1;
		}
		else if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			if ( (int)m_v_point_[image_id].size() != num_points)
			{
				return 0;
			}
		}

		return 1;
	}


	/** Add a new associated points
		@remarks
			If the image has already been initialized and the number of points do not match, the container is initialized with the new size.
	*/
	int add_resize(int image_id, int num_points)	{

		if (m_v_point_.find( image_id ) == m_v_point_.end())
		{
			for (int i = 0; i < num_points; i++)
				m_v_point_[image_id].push_back( cv::Point(0,0) );

			return 1;
		}
		else if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			if ( (int)m_v_point_[image_id].size() != num_points)
			{
				erase( image_id );
				add(image_id, num_points);
				return 0;
			}
		}

		return 1;
	}


	/** Set the point position and image associated
	*/
	void set(int image_id, int point_id, cv::Point2f &pt)
	{
		if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			if (point_id >= 0 && point_id < (int)m_v_point_[image_id].size())
			{
				m_v_point_[image_id][point_id] = pt;
			}
		}
	}

	/** @brief Set the point position and image associated.

		Set the point position and image associated.
		The index is equal to the size of the total points memorized.
	*/
	void set_incremental(int image_id, cv::Point2f &pt)
	{
		if (m_v_point_.find(image_id) != m_v_point_.end())
		{
			m_v_point_[image_id].push_back(pt);
		}
	}



	/** Move the point position and image associated
	*/
	void move(int image_id, int point_id, cv::Point2f &pt)
	{
		if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			if (point_id >= 0 && point_id < (int)m_v_point_[image_id].size())
			{
				m_v_point_[image_id][point_id] += pt;
			}
		}
	}


	/** Return the memorized points
	*/
	std::vector< cv::Point2f > getPoint(int image_id)
	{
		if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			return m_v_point_[image_id];
		}

		return std::vector< cv::Point2f >();
	}

	/** Get the image id available
	*/
	std::vector<int> getIDList()	{

		std::vector<int> v_id;

		//std::cout << "getIDList: " << (int)m_v_point.size() << std::endl;

		for (std::map<int, std::vector< cv::Point2f > >::const_iterator it = m_v_point_.begin(); it != m_v_point_.end(); it++)
			v_id.push_back( it->first );

		return v_id;
	}

	/** @brief Get the current maximum number of images.

	    Get the current maximum number of images.
	*/
	int size() const	{
		return m_v_point_.size();
	}

	/** @brief Get the current maximum number of images.

	Get the current maximum number of images.
	*/
	int size()			{
		return m_v_point_.size();
	}

	/** @brief Get the maximum number of points that can be memorized for a 
	           selected image.
	
	    Get the maximum number of points that can be memorized for a selected 
		image.
		@param[in] image_id Index of the associated image. The maximum number 
		                    of points is returned.
		@return Return 0 in case no points can be memorized (also in the case
		        the image has not be found).
	*/
	int size(int image_id)			{

		if (m_v_point_.find( image_id ) != m_v_point_.end())
		{
			return (int)m_v_point_[ image_id ].size();
		}
		return 0;
	}


private:

	/** @brief map to associate the points from the current image and another
		@first index of the image to map
		@second vector of points which match between the two images. In the case of image warping, the points must belong to the same point from different view
	*/
	std::map<int, std::vector< cv::Point2f > > m_v_point_;
};

}	// namespace cmnipcontainer
}	// namespace CmnIP

#endif /* CMNIP_CMNIPCONTATINER_MATCHPOSITIONPOINTS_HPP__ */
