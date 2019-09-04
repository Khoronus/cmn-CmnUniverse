/* @file color_conversion.hpp
 * @brief Class to convert a color space in another.
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
 * @version 0.2.0.0
 * 
 */

#include "group/inc/group/images_combined.hpp"

namespace CmnIP
{
namespace group
{

//-----------------------------------------------------------------------------
cv::Mat ImagesCombined::combine(
	std::vector<cv::Mat> &v_images, int nx, int ny, int width, int height)	{

	int h = height / ny;
	int w = width / nx;

	std::vector<cv::Mat> v_out;
	// resize the input image
	for (std::vector<cv::Mat>::const_iterator it = v_images.begin();
		it != v_images.end(); it++)
	{
		cv::Mat res_out;
		//std::cout << "it: " << it->empty() << " " << it->cols << " " << 
		//	it->rows << std::endl;
		cv::resize(*it, res_out, cv::Size(w, h));
		if (res_out.channels() == 1)
		{
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(res_out, res_out, CV_GRAY2BGR);
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(res_out, res_out, cv::COLOR_GRAY2BGR);
#endif
		}
		v_out.push_back(res_out);
	}

	// Create an image of expected size
	cv::Mat out(height, width, CV_8UC3, cv::Scalar::all(0));

	// Copy the images
	int id = 0;
	for (int y = 0; y < ny; y++)
	{
		for (int x = 0; x < nx; x++)
		{
			if (id < static_cast<int>(v_out.size()))
			{
				v_out[id++].copyTo(
					out(cv::Rect(x * w, y * h, w, h)));
			}
		}
	}

	return out;
}
//-----------------------------------------------------------------------------
cv::Mat ImagesCombined::combine(
	std::vector<cv::Mat> &v_images, int nx, int ny, int v_images_width,
	int v_images_height, int img_w, int img_h)
{

	int h = v_images_height;
	int w = v_images_width;

	std::vector<cv::Mat> v_out;
	// resize the input image
	for (std::vector<cv::Mat>::const_iterator it = v_images.begin();
		it != v_images.end(); it++)
	{
		cv::Mat res_out;
		cv::resize(*it, res_out, cv::Size(w, h));
		if (res_out.channels() == 1)
		{
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(res_out, res_out, CV_GRAY2BGR);
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(res_out, res_out, cv::COLOR_GRAY2BGR);
#endif
		}
		v_out.push_back(res_out);
	}

	// Create an image of expected size
	cv::Mat out(img_h, img_w, CV_8UC3, cv::Scalar::all(0));

	// Copy the images
	int id = 0;
	for (int y = 0; y < ny; y++)
	{
		for (int x = 0; x < nx; x++)
		{
			if (id < static_cast<int>(v_out.size()))
			{
				v_out[id++].copyTo(
					out(cv::Rect(x * w, y * h, w, h)));
			}
		}
	}

	return out;
}
//-----------------------------------------------------------------------------
cv::Mat ImagesCombined::compose(
	std::vector<cv::Mat> &v_compose, cv::Size &size)
{
	cv::Mat compose(size, CV_8UC3);
	compose = cv::Scalar::all(0);
	cv::Mat compose_img(size, CV_32SC3);
	compose_img = cv::Scalar::all(0);
	cv::Mat compose_istances(size, CV_32SC1);
	compose_istances = cv::Scalar::all(0);
	//std::vector< cv::Mat > v_compose;
	//for (int i = 0; i < (int)v_img.size(); i++)
	//	v_compose.push_back( cv::Mat(size, CV_8UC3) );

	for (int y = 0; y < compose.rows; y++)
	{
		for (int x = 0; x < compose.cols; x++)
		{
			/// Reset the contents
			compose_istances.at<int>(y, x) = 0;
			compose_img.at<cv::Vec3i>(y, x) = 0;
			for (int c = 0; c < 3; c++)
				compose.at<cv::Vec3b>(y, x)[c] = 0;

			for (int i = 0; i < (int)v_compose.size(); i++)
			{
				if (v_compose[i].at<cv::Vec3b>(y, x)[0] != 0 ||
					v_compose[i].at<cv::Vec3b>(y, x)[1] != 0 ||
					v_compose[i].at<cv::Vec3b>(y, x)[2] != 0)
				{
					compose_istances.at<int>(y, x)++;
					for (int c = 0; c < 3; c++)
						compose_img.at<cv::Vec3i>(y, x)[c] +=
						v_compose[i].at<cv::Vec3b>(y, x)[c];
				}
			}
			if (compose_istances.at<int>(y, x) > 0)
				for (int c = 0; c < 3; c++)
				{
				compose.at<cv::Vec3b>(y, x)[c] =
					compose_img.at<cv::Vec3i>(y, x)[c] /
					compose_istances.at<int>(y, x);
				}
		}
	}

	return compose;
}
//-----------------------------------------------------------------------------
void ImagesCombined::map_images_to_image(
	const std::map<std::string, cv::Mat > &m_images,
	cv::Mat &out, cv::Point &position, int format, float size,
	cv::Scalar &color)
{
	std::vector< cv::Mat > v_images;
	for (std::map<std::string, cv::Mat >::const_iterator it = m_images.begin();
		it != m_images.end(); it++)
	{
		//std::cout << "Title: " << it->first << std::endl;
		cv::Mat img = it->second.clone();
		if (img.channels() == 1) {
#if CV_MAJOR_VERSION == 3
			cv::cvtColor(img, img, CV_GRAY2BGR);
#else if CV_MAJOR_VERSION == 4
			cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
#endif
		}
		cv::putText(img, it->first, position, format, size,
			cv::Scalar(0, 0, 255));
		v_images.push_back(img.clone());
	}

	// Generate image
	if (v_images.size() > 0)
	{
		double nx = std::sqrt(static_cast<double>(v_images.size()));
		if (nx - static_cast<int>(nx) > 0.00001) nx += 1;
		out = combine(v_images, static_cast<int>(nx), static_cast<int>(nx),
			v_images[0].cols * static_cast<int>(nx),
			v_images[0].rows * static_cast<int>(nx));
	}
}


} // namespace group
} // namespace CmnIP

