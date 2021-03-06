/**
* @file homography_transformation.hpp
* @brief Perform a phase correlation matching.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

 
#ifndef CMNIP_CALIB_HOMOGRAPHYTRANSFORMATION_HPP__
#define CMNIP_CALIB_HOMOGRAPHYTRANSFORMATION_HPP__

#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace CmnIP
{
namespace transform
{

//*****************************************
//	HOMOGRAPHY IMAGE TRANSFORMATION
//*****************************************


/** This class provides a Homography estimation and perspective transform
	@remarks
		In the future it should be add the inverse transformation
		es. cv::getPerspectiveTransform

	@example:

		image_trasformation.homography(point1, point2, CV_RANSAC, ransacReprojThreshold);
		image_trasformation.transform();	// src and dsize should be same to see whole image
*/
class HomographyTransformation
{
public:

	enum HomographyTransformationResult
	{
		kHomographyBad = 0,
		kHomographyGood
	};

	HomographyTransformation() : verbose_(false)	{}

	explicit HomographyTransformation(const bool verbose) : verbose_(verbose) {
	}

	/** Find the homography between two set of points (obsolete)
		@param[in] v_src1 Source of points
		@param[in] v_src2 Destination of associated points
		@param[in] method Method used. Usually CV_RANSAC (alternative) 0, 
		           CV_RANSAC, CV_LMEDS
		@param[in] threshold Threshold to adopt for the homography. i.e. 0.05f

		@remarks At least 4 points are required.
		@return Return 1 in case of success. 0 otherwise.
	*/
	int homography(std::vector< cv::Point2f > &v_src1, 
			        std::vector< cv::Point2f > &v_src2, 
					int method, double threshold);

	/** Find the homography between two set of points (obsolete)
		@param[in] v_src1 Source of points.
		@param[in] v_src2 Destination of associated points
		@param[in] method Method used. Usually CV_RANSAC (alternative) 0, 
		           CV_RANSAC, CV_LMEDS
		@param[in] threshold Threshold to adopt for the homography. i.e. 0.05f

		@remarks At least 4 points are required.
		@return Return 1 in case of success. 0 otherwise.
	*/
	int homography(const std::vector< cv::Point2f > &v_src1, 
			        const std::vector< cv::Point2f > &v_src2, 
					int method, double threshold);


	/** Find the homography between two set of points
		@param[in] v_src1 Source of points
		@param[in] v_src2 Destination of associated points
		@param[in] method Method used. Usually CV_RANSAC (alternative) 0, 
		           CV_RANSAC, CV_LMEDS
		@param[in] threshold Threshold to adopt for the homography. i.e. 0.05f
	*/
	void find_homography(std::vector< cv::Point2f > &v_src1, 
			        std::vector< cv::Point2f > &v_src2, 
					int method, double threshold);

	/** Find the homography between two set of points and verify that the 
	    homography matrix is good.
		@param[in] v_src1 Source of points
		@param[in] v_src2 Destination of associated points
		@param[in] method Method used. Usually CV_RANSAC (alternative) 0, 
		           CV_RANSAC, CV_LMEDS
		@param[in] threshold Threshold to adopt for the homography. i.e. 0.05f
		@param[in] homography_threshold Threshold to estimate if the homography
		           matrix is good
		@return Return true if the homography matrix is valid.
	*/
	bool find_good_homography(std::vector< cv::Point2f > &v_src1, 
			        std::vector< cv::Point2f > &v_src2, 
					int method, double threshold, 
					double homography_threshold);

	/** Find the homography between two set of points
		@param[in] v_src1 Source of points
		@param[in] v_src2 Destination of associated points
		@param[in] method Method used. Usually CV_RANSAC (alternative) 0, 
				   CV_RANSAC, CV_LMEDS
		@param[in] threshold Threshold to adopt for the homography. i.e. 0.05f
	*/
	void find_homography(const std::vector< cv::Point2f > &v_src1, 
			        const std::vector< cv::Point2f > &v_src2, 
					int method, double threshold);

	/** Set the homography matrix (obsolete)
		@param _shomography Homography matrix to set
	*/
	void set_homography(const cv::Mat &homography)	{
		homography_ = homography;
	}

	/** Get the homography matrix (obsolete)
		@return Return the homography matrix.
	*/
	cv::Mat homography() const	{
		return homography_;
	}

	/** Get the homography matrix (obsolete)
		@return Return the homography matrix.
	*/
	cv::Mat& homography()	{
		return homography_;
	}


	/** Apply the image transformation, and transform an input image based on the previously calculated homography matrix
		@param src Source image
		@param dst Destination image warped.
		@param dsize Size of the destination image after the warp.
	*/
	void transform(cv::Mat &src, cv::Mat &dst, cv::Size &dsize);

	/** Apply the image transformation
	*/
	void transform(const cv::Mat &src, cv::Mat &dst, cv::Size &dsize);


	/** Apply the image transformation, and transform an input image based on the previously calculated homography matrix
		@param src Source image
		@param dst Destination image warped.
		@param dsize Size of the destination image after the warp.
	*/
	void warp_affine(cv::Mat &src, cv::Mat &dst, cv::Size &dsize);

	/** Apply the image transformation
	*/
	void warp_affine(const cv::Mat &src, cv::Mat &dst, cv::Size &dsize);

	/** Estimate if the homography matrix is acceptable
		Calculate the determinant of the homography matrix. If higher than 1 (too near to 0 is wrong) then is a good matrix
		TODO - SVD: verify the ratio of the first-to-last singual value is sane (not too high).
		@param[out] fMatch Determinant value
		@param[in] fMinDeterminant Min threshold
		@param[in] fMaxDeterminant Max threshold
		@return Return 1 if acceptable.
	*/
	int IsAcceptable(double &fMatch, double fMinDeterminant, double fMaxDeterminant);

	/** Estimate if the homography matrix is acceptable
		Calculate the determinant of the homography matrix. If higher than 1 (too near to 0 is wrong) then is a good matrix
		TODO - SVD: verify the ratio of the first-to-last singual value is sane (not too high).
		@param[out] v_ch Convex hull points. Check if they are inside the transformed matrix
		@return Return 1 if acceptable.
	*/
	int IsAcceptable(std::vector<cv::Point2f> &v_ch, int xmin, int ymin, int xmax, int ymax);


	// Check homography
	HomographyTransformationResult check_homography(const double bad_threshold);

  /** Set the verbose mode
  */
  void set_verbose(const bool verbose) {
    verbose_ = verbose;
  }

  /** Get the verbose mode
  */
  bool verbose() const {
    return verbose_;
  }

 private:

  /** Homography matrix
  */
  cv::Mat homography_;

  /** True if display the output message
  */
  bool verbose_;

};



/** Class to manipulate an homography matrix.
    For example to rescale an omography matrix without recalculate the matrix.
*/
class HomographyMatrixManipulation
{
 public:

  /** Calculate the rescaled homography matrix. The top-left vertex point does
      not change.
  */
  static void scale_fix_top_left(const cv::Mat &homography, 
	                                const cv::Rect &original,
								    float xscale, float yscale,
									cv::Mat &dst);

  /** Calculate the rescaled homography matrix. The top-left vertex point does
      not change.
  */
  static void scale_fix_top_left(const cv::Mat &homography, 
	                                const cv::Size &original,
								    float xscale, float yscale,
									cv::Mat &dst);

  /** Calculate the rescaled homography matrix. The center does not change.
  */
  static void scale_fix_center(const cv::Mat &homography, 
	                           const cv::Size &original,
							   float xscale, float yscale,
							   cv::Mat &dst);


  /** Apply a translation transformation to the homography matrix.
  */
  static void translate(const cv::Mat &homography, 
	                    const cv::Point2f &pt,
						cv::Mat &dst);

  /** Apply a translation transformation to the homography matrix.
  */
  static void add(const cv::Mat &homography, 
	              const cv::Mat &m,
				  cv::Mat &dst);

};


/** Class to estimate the apply the homography or perspective matrix to a pixel to transform in a new position
*/
class HomographyPointTransformation
{
public:

	/** Get the 2D point position transformed from transformation matrix

		tixi                  xi
		tiyi  = map_matrix *  yi
		ti                     1

		@param[in] pt Point to transform
		@param[in] map_matrix Matrix to map the point
		@return Return a matrix with the new point position
	*/
	static cv::Mat getMapPoint(cv::Mat &pt, cv::Mat &map_matrix);
	static cv::Mat getMapPoint(cv::Point2f &pt, cv::Mat &map_matrix);
	static cv::Mat getMapPoint(double x, double y, cv::Mat &map_matrix);
	/** Return a point that has been normalized based on the third value
	*/
	static cv::Mat normalizePoint(cv::Mat &ptSrc);

};


} // namespace transform
} // namespace CmnIP

#endif // CMNIP_CALIB_HOMOGRAPHYTRANSFORMATION_HPP__
