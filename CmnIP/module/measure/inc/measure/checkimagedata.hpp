/**
* @file checkimagedata.hpp
* @brief Check if the image data is valid.
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
* @author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNIP_MEASURE_CHECKIMAGEDATA_HPP__
#define CMNIP_MEASURE_CHECKIMAGEDATA_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief A set of functions to evaluate if the image data is valid.
*/
class CheckImageData
{
public:

	/** @brief Function to check if a rectangle is inside an image.
	*/
	static bool is_valid(const cv::Mat &image, const cv::Rect &rect)
	{
		if (rect.x < 0 || rect.y < 0 || rect.x + rect.width >= image.cols ||
			rect.y + rect.height >= image.rows ||
			rect.width == 0 || rect.height == 0) return false;
		return true;
	}
};

} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_CHECKIMAGEDATA_HPP__
