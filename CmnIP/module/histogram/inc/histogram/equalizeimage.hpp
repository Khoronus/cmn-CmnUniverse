/**
* @file algorithm.hpp
* @brief Virtual class to manage algorithms
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

#ifndef CMNIP_HISTOGRAM_EQUALIZEIMAGE_HPP__
#define CMNIP_HISTOGRAM_EQUALIZEIMAGE_HPP__

#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

namespace CmnIP
{
namespace histogram
{

// http://stackoverflow.com/questions/23862151/auto-adjust-image-intensity

/** @brief Class to equalize an image
*/
class EqualizeImage
{
public:

	/** @brief It modifies the selected channel of a defined value.

		It modifies the selected channel of a defined value.
		c' = c * value
	*/
	static void color(const cv::Mat &src, int channel, float value,
		cv::Mat &out, bool copy);

	/** @brief It adjust a channel based on a reference image

	*/
	static void color(const cv::Mat &img, const cv::Mat &ref, int channel,
		cv::Mat &out, bool copy);

	/** @brief Equalize the color of a channel with an alpha channel value
	           for the ratio.
	*/
	static void color(const cv::Mat &img, const cv::Mat &ref, int channel,
		float alpha, cv::Mat &out, bool copy);

	/** @brief It adjust a channel based on a reference image. It uses a
	           probability mask to set the pixels value
	*/
	static void color(const cv::Mat &img, const cv::Mat &ref, const cv::Mat &mprob,
		const cv::Mat &mprobneg, int channel,
		cv::Mat &out, bool copy);

	/** @brief It adjust the intensity of a source image with a reference image.

		The intensity is estimated from the YCrCb color space
	*/
	static void adjust_intensity(const cv::Mat &img, const cv::Mat &ref, cv::Mat &out,
		bool copy);

	/** @brief It equalize the intensity of an image in the YCrCb color space.
	*/
	static int equalize_intensity(const cv::Mat &img, cv::Mat &out);

	/** @brief It chanes the image contrast.
	*/
	static int change_contrast(cv::Mat &img, double alpha, cv::Mat &out);

	/** @brief It performs the rgb clahe

		It performs a clahe over the L channel of a Lab color space.
	*/
	static void rgbclahe(cv::Mat &src, cv::Mat &out);
};


} // namespace histogram
} // namespace CmnIP

#endif /* CMNIP_HISTOGRAM_EQUALIZE_HPP__ */
