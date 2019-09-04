/**
* @file histogram.cpp
* @brief Example of the drawing organized images.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.0.1
*
*/


#ifndef CMNIP_DRAW_HISTOGRAM2IMAGE_HPP__
#define CMNIP_DRAW_HISTOGRAM2IMAGE_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


namespace CmnIP
{
namespace draw
{

/** @brief It converts an histogram in a visualizable image
*/
class Histogram2Image
{
public:

	/** @brief Convert an histogram in an image.

		Convert an histogram in an image.
	*/
	static void onechannel_hist(cv::Mat &image, cv::Mat &hist, int hist_w, 
		int hist_h,	int histSize, cv::Scalar &color) {

	  // Draw the histograms for B, G and R
	  int bin_w = cvRound( (double) hist_w/histSize );

	  /// Normalize the result to [ 0, histImage.rows ]
	  cv::Mat hist_out;
	  cv::normalize(hist, hist_out, 0, image.rows, cv::NORM_MINMAX, -1, 
		  cv::Mat() );

	  /// Draw for each channel
	  for( int i = 1; i < histSize; i++ )
	  {
		  cv::line( image, 
			  cv::Point( bin_w*(i-1), 
			             hist_h - cvRound(hist_out.at<float>(i-1)) ) ,
			  cv::Point( bin_w*(i), 
			             hist_h - cvRound(hist_out.at<float>(i)) ),
			  color, 2, 8, 0  );
	  }
	}
};


}	// namespace draw
}	// namespace CmnIP

#endif /* CMNIP_DRAW_HISTOGRAM2IMAGE_HPP__ */
