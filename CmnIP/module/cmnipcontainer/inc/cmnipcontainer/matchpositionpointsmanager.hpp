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

#ifndef CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSMANAGER_HPP__
#define CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSMANAGER_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "matchpositionpoints.hpp"
#include "matchpositionpointscontainer.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

/** Container of the image of points
*/
class MatchPositionPointsManager
{
public:

	MatchPositionPointsManager() {}

	/** @brief Clear the memory
	*/
	void clear() {
		m_image_point.clear();
	}

	/** Set the points associated from image origin and destination
		@param[in] image_id_origin Define the origin of the associate points.
		  The value must be one of the two values in the p_associated.
		@param[in] iMaxNumPointsEachImage Max number of points expected for
		  each image.
		@param[in] p_associated Index of the two images associated.
		@param[in] point_id ID of the point (< iMaxNumPointsEachImage).
		@param[in] pt Coordinate.
	*/
	int set(int image_id_origin, int iMaxNumPointsEachImage, 
		const std::pair<int, int> &p_associated, int point_id, 
		const cv::Point2f &pt, 
		bool bUnivoque)
	{
		//std::cout << "Set0: " << p_associated.first << " " << p_associated.second << " " << image_id_origin << std::endl;

		// Index must be >= 0
		if (p_associated.first < 0 || p_associated.second < 0) return 0;

		// Check that the id are different
		if (bUnivoque && p_associated.first == p_associated.second) return 0;

		//std::cout << "Set1: " << p_associated.first << " " << p_associated.second << " " << image_id_origin << std::endl;
		/// Check if the images id belong to the association point
		if (p_associated.first != image_id_origin &&
			p_associated.second != image_id_origin) return 0;

		if (p_associated.first == image_id_origin)
		{
			if (!m_image_point[p_associated.first].add( p_associated.second, 
				iMaxNumPointsEachImage )) return 0;
			m_image_point[p_associated.first].set( p_associated.second, 
				point_id, pt ); 
		} else {
			if (!m_image_point[p_associated.second].add( p_associated.first, 
				iMaxNumPointsEachImage )) return 0;
			m_image_point[p_associated.second].set( p_associated.first, 
				point_id, pt ); 
		}

		return 1;
	}

	/** Set the points associated from image origin and destination
	@param[in] image_id_origin Define the origin of the associate points.
	The value must be one of the two values in the p_associated.
	@param[in] iMaxNumPointsEachImage Max number of points expected for
	each image.
	@param[in] p_associated Index of the two images associated.
	@param[in] point_id ID of the point (< iMaxNumPointsEachImage).
	@param[in] pt Coordinate.
	*/
	int set_incremental(int image_id_origin,
		std::pair<int, int> &p_associated, cv::Point2f &pt,
		bool bUnivoque)
	{
		//std::cout << "Set0: " << p_associated.first << " " << p_associated.second << " " << image_id_origin << std::endl;

		// Index must be >= 0
		if (p_associated.first < 0 || p_associated.second < 0) return 0;

		// Check that the id are different
		if (bUnivoque && p_associated.first == p_associated.second) return 0;

		//std::cout << "Set1: " << p_associated.first << " " << p_associated.second << " " << image_id_origin << std::endl;
		/// Check if the images id belong to the association point
		if (p_associated.first != image_id_origin &&
			p_associated.second != image_id_origin) return 0;

		if (p_associated.first == image_id_origin)
		{
			m_image_point[p_associated.first].add(p_associated.second, 0);
			m_image_point[p_associated.first].set_incremental(
				p_associated.second, pt);
		} else {
			m_image_point[p_associated.second].add(p_associated.first, 0);
			m_image_point[p_associated.second].set_incremental(
				p_associated.first, pt);
		}

		return 1;
	}


	/** Display the points information
	*/
	void display()	{

		for (std::map<int, MatchPositionPoints>::iterator it = m_image_point.begin(); it != m_image_point.end(); it++)
		{
			std::cout << "Image: " << it->first << std::endl;

			std::vector<int> v_id = it->second.getIDList();

			for (std::vector<int>::const_iterator it2 = v_id.begin(); it2 != v_id.end(); it2++)
			{
				std::vector< cv::Point2f > v_points = it->second.getPoint(*it2);

				std::cout << "	-> Point: " << *it2 << std::endl;
				for (std::vector< cv::Point2f >::const_iterator it3 = v_points.begin(); it3 != v_points.end(); it3++)
				{
					std::cout << "	--> " << it3->x << " " << it3->y << std::endl;
				}
			}
		}
	}

	/** Save the list of points
		# images
			image_id
			number of points (max)
			# association
				image_associated_id
					points position	(x,y)	
	*/
	int save(const std::string &filename)	{

		std::ofstream myfile;
		myfile.open( filename.c_str() );

		if (!myfile.is_open()) return 0;

		myfile << "MatchPositionPointsManager version 1" << std::endl;
		myfile << "iNumImages " << (int)m_image_point.size() << std::endl;
		for (std::map<int, MatchPositionPoints>::iterator it = m_image_point.begin(); it != m_image_point.end(); it++)
		{
			std::vector<int> v_id = it->second.getIDList();
			myfile << "iImageID " << it->first << std::endl;
			myfile << "iNumImagesAssociated " << (int)v_id.size() << std::endl;

			for (std::vector<int>::const_iterator it2 = v_id.begin(); it2 != v_id.end(); it2++)
			{
				myfile << "iAssociatedID " << *it2 << std::endl;
				myfile << "iMaxNumPointsEachImage " << it->second.size(*it2) << std::endl;

				std::vector< cv::Point2f > v_points = it->second.getPoint(*it2);
				for (std::vector< cv::Point2f >::const_iterator it3 = v_points.begin(); it3 != v_points.end(); it3++)
				{
					myfile << it3->x << " " << it3->y << std::endl;
				}
			}
		}

		myfile.close();
		myfile.clear();

		return 1;
	}


	/** @brief Load a set of points from a configuration file.

		Load a set of points from a configuration file.

		@param[in] filename File where the points are saved.
		@param[in] xscale Rescale the horizontal point position of the set 
		value.
		@param[in] yscale Rescale the vertical point position of the set 
		value.
		@return Return 1 in case of success.
	*/
	int load_ver1(const std::string &filename, float xscale, float yscale)	{

		std::ifstream myfile;
		myfile.open( filename.c_str() );
		
		if (!myfile.is_open()) return 0;

		// Extract the line for the version
		char buf_line[512];
		myfile.getline(buf_line, 512);

		// Reset the container
		m_image_point.clear();

		while (!myfile.eof())
		{
			char buf[512], tmp[512];
			int iNumImages = 0;
			// # points
			//myfile.getline(buf, 512);
			//sscanf(buf, "%i", &iMaxNumPointsEachImage);
			// # images
			myfile.getline(buf, 512);
			if ((int)strlen(buf) < 1) continue;
			sscanf(buf, "%s %i", tmp, &iNumImages);
			for (int i = 0; i < iNumImages; i++)
			{
				int iImageID;
				// image id
				myfile.getline(buf, 512);
				sscanf(buf, "%s %i", tmp, &iImageID);

				int iNumImagesAssociated;
				// # images associated
				myfile.getline(buf, 512);
				sscanf(buf, "%s %i", tmp, &iNumImagesAssociated);
				
				for (int j = 0; j < iNumImagesAssociated; j++)
				{
					int iAssociatedID;
					// associated id
					myfile.getline(buf, 512);
					sscanf(buf, "%s %i", tmp, &iAssociatedID);

					int iMaxNumPointsEachImage;
					myfile.getline(buf, 512);
					sscanf(buf, "%s %i", tmp, &iMaxNumPointsEachImage);

					// Get the points
					for (int k = 0; k < iMaxNumPointsEachImage; k++)
					{
						float x, y;
						// associated id
						myfile.getline(buf, 512);
						sscanf(buf, "%f %f", &x, &y);
						x *= xscale;
						y *= yscale;

						// Memorize the data
						set(iImageID, iMaxNumPointsEachImage, 
							std::pair<int, int>(iImageID, iAssociatedID), k, 
							cv::Point2f(x,y), false);
					}
				}
			}
		}

		myfile.close();
		myfile.clear();

		return 1;
	}

	/** @brief Load a set of points from a configuration file.

		Load a set of points from a configuration file.

		@param[in] filename File where the points are saved.
		@param[in] xscale Rescale the horizontal point position of the set 
		value.
		@param[in] yscale Rescale the vertical point position of the set 
		value.
		@return Return 1 in case of success.
	*/
	int load(const std::string &filename, float xscale, float yscale)	{
		std::ifstream myfile;
		myfile.open( filename.c_str() );
		
		if (!myfile.is_open()) return 0;

		bool bSuccess = false;
		while (!myfile.eof())
		{
			char buf[512], buf0[512], type[512], version[512];

			myfile.getline(buf, 512);
			if ((int)strlen(buf) < 1) continue;
			sscanf(buf, "%s %s %s", buf0, type, version);

			if (type == std::string("version"))
			{
				if (version == std::string("1"))
				{
					load_ver1(filename, xscale, yscale);
					bSuccess = true;
					break;
				}
			}
		}

		myfile.close();
		myfile.clear();

		if (bSuccess) return 1;
		return 0;
	}

	/** Get the associated point for this pair
		@param p_assiciated Association first, second image id
		@param v_p_points Vector of pair of points first image first point position, second image second point position
	*/
	int getAssociated(std::pair<int, int> &p_associated, 
		std::vector< std::pair< cv::Point2f, cv::Point2f > > &v_p_points)
	{
		/// Check that the image exist
		if (m_image_point.find( p_associated.first ) == m_image_point.end()) return 0;
		if (m_image_point.find( p_associated.second ) == m_image_point.end()) return 0;

		/// Check that the image association exist
		std::vector< cv::Point2f > v_1 = m_image_point[ p_associated.first ].getPoint( p_associated.second );
		std::vector< cv::Point2f > v_2 = m_image_point[ p_associated.second ].getPoint( p_associated.first );

		//if ( (int)v_1.size() != iMaxNumPointsEachImage || (int)v_2.size() != iMaxNumPointsEachImage) return 0;

		v_p_points.clear();
		for (int i = 0; i < iMaxNumPointsEachImage; i++)
		{
			v_p_points.push_back( std::pair< cv::Point2f, cv::Point2f >(v_1[i], v_2[i]) );
		}

		return 1;
	}

	/** Get the associated point for this pair
		@param p_assiciated Association first, second image id
		@param v_p_points Vector of pair of points first vector of image of points first image, second vector of image of points second image
	*/
	int getAssociated(std::pair<int, int> &p_associated, 
		std::pair< std::vector<cv::Point2f>, std::vector<cv::Point2f> > &p_v_points)
	{
		/// Allocate the container for the pointers
		std::vector< cv::Point2f > v_1, v_2;
		/// Check that the image exist
		if (m_image_point.find( p_associated.first ) != m_image_point.end())
			v_1 = m_image_point[ p_associated.first ].getPoint( p_associated.second );
		if (m_image_point.find( p_associated.second ) != m_image_point.end())
			v_2 = m_image_point[ p_associated.second ].getPoint( p_associated.first );

		p_v_points.first = v_1;
		p_v_points.second = v_2;

		return 1;
	}

	/** @brief Get the associated points to the image ID in all the possible combinations.
	*/
	void getAssociated(int iImageID, MatchPositionPointsContainer &container) {
		container.image_id_ = iImageID;
		getAssociated(iImageID, container.v_p_p_v_points_);
		getAssociated(iImageID, container.v_p_v_points_);
		getAssociated(iImageID, container.v_p_v_p_points_);
	}


	/** Get a vector of pairs with the associated image id and the points position
		@param[in] iImageID Index of the image which contains the associations desired
		@param[out] v_p_v_points Vector of pairs which associate the associated image id and points
					first: image associated id
					second: points vector
	*/
	int getAssociated(int iImageID, std::vector< std::pair< int, std::vector<cv::Point2f> > > &v_p_v_points)
	{
		/// Allocate the container for the pointers
		std::vector< cv::Point2f > v_1;
		/// Check that the image exist
		if (m_image_point.find( iImageID ) != m_image_point.end())
		{
			v_p_v_points.clear();

			std::vector<int> v_id = m_image_point[ iImageID ].getIDList();
			for (std::vector<int>::const_iterator it = v_id.begin(); it != v_id.end(); it++)
			{
				v_1 = m_image_point[ iImageID ].getPoint( *it );
				v_p_v_points.push_back( std::pair< int, std::vector<cv::Point2f> >( *it, v_1 ) ); 
			}
			
			return 1;
		}

		return 0;
	}


	/** Get a vector of pairs with the associated image id and the points position
		@param[in] iImageID Index of the image which contains the associations desired
		@param[out] v_p_p_v_points Vector of pairs which associate the associated image id and points from both the images (iImageID, associated image id)
					first: image associated id
					second: pair of vector of points
						first: iImageID points vector
						second: associated image id points vector
	*/
	int getAssociated(int iImageID, std::vector< std::pair< int, std::pair< std::vector<cv::Point2f>, std::vector<cv::Point2f> > > > &v_p_p_v_points)
	{
		/// Allocate the container for the pointers
		std::vector< cv::Point2f > v_1, v_2;
		/// Check that the image exist
		if (m_image_point.find( iImageID ) != m_image_point.end())
		{
			v_p_p_v_points.clear();

			std::vector<int> v_id = m_image_point[ iImageID ].getIDList();
			for (std::vector<int>::const_iterator it = v_id.begin(); it != v_id.end(); it++)
			{
				/// Find if it exist and association searching if points are set on the associated image which points to imageID
				if (m_image_point.find( *it ) != m_image_point.end())
				{
					// Try to get the list of points
					v_2 = m_image_point[ *it ].getPoint( iImageID );

					if ((int)v_2.size() > 0)
					{
						v_1 = m_image_point[ iImageID ].getPoint( *it );
						v_p_p_v_points.push_back( std::pair< int, std::pair< std::vector<cv::Point2f>, std::vector<cv::Point2f> > >( *it, std::pair< std::vector<cv::Point2f>, std::vector<cv::Point2f> >(v_1, v_2) ) ); 
					}
				}
			}
			
			return 1;
		}

		return 0;
	}

	/** Get a vector of pairs with the associated image id and the points position
		@param[in] iImageID Index of the image which contains the associations desired
		@param[out] v_p_v_v_points Vector of pairs which associate the associated image id and points from both the images (iImageID, associated image id)
					first: image associated id
					second: vector with the pair of associated points
						first: iImageID points
						second: associated image id points
	*/
	int getAssociated(int iImageID, std::vector< std::pair< int, std::vector< std::pair< cv::Point2f, cv::Point2f > > > > &v_p_v_p_points)
	{
		/// Allocate the container for the pointers
		std::vector< cv::Point2f > v_1, v_2;
		/// Check that the image exist
		if (m_image_point.find( iImageID ) != m_image_point.end())
		{
			v_p_v_p_points.clear();

			std::vector<int> v_id = m_image_point[ iImageID ].getIDList();
			for (std::vector<int>::const_iterator it = v_id.begin(); it != v_id.end(); it++)
			{
				/// Find if it exist and association searching if points are set on the associated image which points to imageID
				if (m_image_point.find( *it ) != m_image_point.end())
				{
					// Try to get the list of points
					v_2 = m_image_point[ *it ].getPoint( iImageID );

					if ((int)v_2.size() > 0)
					{
						v_1 = m_image_point[ iImageID ].getPoint( *it );
						/// Temporary container for the points just to create a vector of pair of points (according to the structure)
						std::vector< std::pair< cv::Point2f, cv::Point2f > > tmp;
						for (int i = 0; i < (int)v_2.size(); i++)
							tmp.push_back( std::pair< cv::Point2f, cv::Point2f >(v_1[i], v_2[i]) );
						v_p_v_p_points.push_back( std::pair< int, std::vector< std::pair< cv::Point2f, cv::Point2f > > >( *it, tmp ) ); 
					}
				}
			}
			
			return 1;
		}

		return 0;
	}


	/** Get the center of the points associated
	*/
	void getCenter(int iImageID, std::vector< std::pair<int, cv::Point2f> > &v_p_center)
	{
		v_p_center.clear();

		/// Container with the points associated
		std::vector< std::pair< int, std::vector<cv::Point2f> > > v_p_v_points;
		/// Get the associated points
		getAssociated( iImageID, v_p_v_points );

		/// Scan all the associated points with the image
		for (std::vector< std::pair< int, std::vector<cv::Point2f> > >::const_iterator it = v_p_v_points.begin(); it != v_p_v_points.end(); it++)
		{
			/// Rescale the points to place correctly over the rescaled image
			cv::Point pt(0,0);
			for (int j = 0; j < (int)it->second.size(); j++)
			{
				pt.x += it->second[j].x;
				pt.y += it->second[j].y;
			}
			/// Normalize the position of the center
			pt.x /= (int)it->second.size();
			pt.y /= (int)it->second.size();

			/// Add the center point information
			v_p_center.push_back( std::pair< int, cv::Point2f >( it->first, pt ) );
		}

	}


	/** Get the center of the points associated
	*/
	void getIndex(int iImageID, std::vector< int > &v_index)
	{
		v_index.clear();

		/// Container with the points associated
		std::vector< std::pair< int, std::vector<cv::Point2f> > > v_p_v_points;
		/// Get the associated points
		getAssociated( iImageID, v_p_v_points );

		/// Scan all the associated points with the image
		for (std::vector< std::pair< int, std::vector<cv::Point2f> > >::const_iterator it = v_p_v_points.begin(); it != v_p_v_points.end(); it++)
		{
			/// Add the center point information
			v_index.push_back( it->first );
		}

	}


private:

	/** Number of points used for each image
	*/
	int iMaxNumPointsEachImage;

	/** Container with the detected image points
		first:  image id
		second: image point match position
	*/
	std::map<int, MatchPositionPoints > m_image_point;
};


/** Utilities class to increase the information of the ImagePointMatchPositionContainer
*/
class ImagePointMatchPositionContainerUtils
{
public:
			
	/** Create an image with the point 
	*/
	static cv::Mat toImage(MatchPositionPointsManager &manager, cv::Size &size, int id)
	{
		cv::Mat out(size, CV_8UC3);
		//out = cv::Scalar(255, 255, 255);
		out = cv::Scalar(0,0,0);


		/// Container with the points associated
		std::vector< std::pair< int, std::vector<cv::Point2f> > > v_p_v_points;
		/// Get the associated points
		manager.getAssociated( id, v_p_v_points );

		float scale = ( size.width < size.height ? size.width : size.height ) / 100.0f;

		/// Scan all the associated points with the image
		for (std::vector< std::pair< int, std::vector<cv::Point2f> > >::const_iterator it = v_p_v_points.begin(); it != v_p_v_points.end(); it++)
		{
			/// Rescale the points to place correctly over the rescaled image
			cv::Point2f pt(0,0);
			std::vector< cv::Point2f > v_scaled;
			for (int j = 0; j < (int)it->second.size(); j++)
			{
				cv::circle( out, it->second[j], scale, cv::Scalar(255, 0, 255));
				pt.x += it->second[j].x;
				pt.y += it->second[j].y;

				/// Put text
				char buf[256];
				sprintf(buf, "%i %i", it->first, j);
				cv::putText(out, std::string(buf), it->second[j], 0, 0.05f * scale, cv::Scalar(0, 0, 255), 1);
			}
			/// Normalize the position of the center
			pt.x /= (int)it->second.size();
			pt.y /= (int)it->second.size();

			//std::cout << "Debug: size " << (int)it->second.size() << std::endl;
			/// Put text
			char buf[256];
			sprintf(buf, "%i %i", id, it->first);
			cv::putText(out, std::string(buf), pt, 0, 0.05f * scale, cv::Scalar(0, 255), 2);
		}

		return out;
	}

	/** Create an image with the point 
	*/
	static cv::Mat toImage(int id,
		const std::vector< std::pair< int, std::vector<cv::Point2f> > > &v_p_v_points, 
		cv::Size &size)
	{
		cv::Mat out = cv::Mat::zeros(size, CV_8UC3);
		float scale = ( size.width < size.height ? size.width : size.height ) / 100.0f;

		/// Scan all the associated points with the image
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_p_v_points.begin(); it != v_p_v_points.end(); it++)
#else
		for (std::vector< std::pair< int, std::vector<cv::Point2f> > >::const_iterator it = v_p_v_points.begin(); it != v_p_v_points.end(); it++)
#endif
		{
			/// Rescale the points to place correctly over the rescaled image
			cv::Point pt(0,0);
			std::vector< cv::Point2f > v_scaled;
			for (int j = 0; j < (int)it->second.size(); j++)
			{
				cv::circle( out, it->second[j], scale, cv::Scalar(255, 0, 255));
				pt.x += it->second[j].x;
				pt.y += it->second[j].y;

				/// Put text
				char buf[256];
				sprintf(buf, "%i %i", it->first, j);
				cv::putText(out, std::string(buf), it->second[j], 0, 0.05f * scale, 
					cv::Scalar(0, 0, 255), 1);
			}
			/// Normalize the position of the center
			pt.x /= (int)it->second.size();
			pt.y /= (int)it->second.size();

			/// Put text
			char buf[256];
			sprintf(buf, "%i %i", id, it->first);
			cv::putText(out, std::string(buf), pt, 0, 0.05f * scale, 
				cv::Scalar(0, 255), 2);
		}

		return out;
	}
};


}	// namespace cmnipcontainer
}	// namespace CmnIP

#endif /* CMNIP_CMNIPCONTAINER_MATCHPOSITIONPOINTSMANAGER_HPP__ */
