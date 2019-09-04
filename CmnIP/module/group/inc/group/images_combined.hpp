/**
* @file organized_images.hpp
* @brief Header to display some organized images
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

#ifndef CMNIP_GROUP_IMAGESCOMBINED_HPP__
#define CMNIP_GROUP_IMAGESCOMBINED_HPP__

#include <map>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace CmnIP
{
namespace group
{


/*! Class to combine multiple images together and make a single image
\brief Combine multiple images together.
*/
class ImagesCombined
{
public:

	/** This function put together several images.
	@param[in] v_images Vector with the images to group.
	@param[in] nx Number of images in the horizontal axe. The value must be always positive.
	@param[in] ny Number of images in the vertical axe. The value must be always positive.
	@param[in] width Width of the output image.
	@param[in] height Height of the output image.
	@return Return the grouped images.
	*/
	static cv::Mat combine(std::vector<cv::Mat> &v_images, int nx, int ny,
		int width, int height);


	/** This function put together several images.
	@param[in] v_images Vector with the images to group.
	@param[in] nx Number of images in the horizontal axe. The value must be always positive.
	@param[in] ny Number of images in the vertical axe. The value must be always positive.
	@param[in] v_images_width Width of the input images. The size is already defined.
	@param[in] v_images_height Height of the input images. The size is already defined.
	@param[in] width Width of the output image.
	@param[in] height Height of the output image.
	@return Return the grouped images.
	*/
	static cv::Mat combine(std::vector<cv::Mat> &v_images, int nx, int ny,
		int v_images_width, int v_images_height, int img_w, int img_h);


	/** Compose a set of images. Size of the image must be equal to size
	All the images in input are sum together. Only the points not black
	are put together.
	It preserve the original intensity and color.
	*/
	static cv::Mat compose(std::vector<cv::Mat> &v_compose, cv::Size &size);

	/** Convert a map of images with title, in a big image
	@param[in] m_images Map of images. First: image title, Second: image
	@param[out] composed image
	*/
	static void map_images_to_image(const std::map<std::string, cv::Mat > &m_images,
		cv::Mat &out, cv::Point &position, int format, float size, cv::Scalar &color);

};



} // namespace group
} // namespace CmnIP

#endif /* CMNIP_GROUP_IMAGESCOMBINED_HPP__ */
