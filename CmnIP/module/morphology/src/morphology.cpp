/**
* @file morphology.cpp
* @brief Body of all the files related to the algorithm
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#include "morphology/inc/morphology/morphology.hpp"


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
