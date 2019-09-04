/**
* @file transform.hpp
* @brief Header of the classes to perform some operations with a contour image.
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
* @version 1.0.0.0
*
*/


#ifndef CMNIP_TRANSFORM_TRANSFORM_HPP__
#define CMNIP_TRANSFORM_TRANSFORM_HPP__

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace transform
{

/** @brief Class to perform signal transformation over source images.

	Class to perform signal transformation over source images.
*/
class Transform
{
  public:

	  /** @brief It calculates the DFT of a source image

		It calculates the DFT of a source image
		@param[in] src The source image must be a 8bit type (1 or 3 channels).
	  */
	  static int dft(const cv::Mat &src, cv::Mat &out);

	  /** @brief It calculates the DCT of a source image.

		It calculates the DCT of a source image
		@param[in] src The source image must be a 8bit type (1 or 3 channels).
	  */
	  static int dct(cv::Mat &src, cv::Mat &out);
};

}	// namespace transform
}	// namespace CmnIP

#endif /* CMNIP_TRANSFORM_TRANSFORM_HPP__ */
