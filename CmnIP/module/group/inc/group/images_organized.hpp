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

#ifndef CMNIP_GROUP_IMAGESORGANIZED_HPP__
#define CMNIP_GROUP_IMAGESORGANIZED_HPP__

#include <map>

#include "opencv2/opencv.hpp"


namespace CmnIP
{
namespace group
{

/** @brief Copy a set of images in a panel to visualize the content.
*/
template <typename _Ty>
class ImagesOrganized
{
public:

	/** @brief Create an image with the information in the container to	fill 
	           the regions.
	*/
	static int container(
		std::vector< _Ty > &container,
		cv::Mat& (*pFunc)(_Ty &d),
		cv::Mat &image) {
		if (image.empty()) return 0;
		image = cv::Scalar::all(0);
		int elements = container.size();
		if (elements > 0)
		{
			int w = std::sqrt((float)elements) + 1;
			int h = w;
			//if (w == 2) return;
			int wsize = image.cols / 2;
			if (w <= 2) {
				wsize = image.cols / 2;
			} else {
				wsize = image.cols / w - 2;
			}
			for (int i = 0; i < elements; i++)
			{
				int x = i % w; int y = i / w;
				cv::Mat tmp;
				cv::resize(pFunc(container[i]), tmp,
					cv::Size(wsize, wsize));
				if (tmp.type() == image.type()) {
					tmp.copyTo(image(cv::Rect(wsize * x, wsize * y,
						wsize, wsize)));
				} else {
					return 0;
				}
			}
		}
		return 1;
	}


	/** @brief Create an image with the information in the container to	fill 
	           the regions.
	*/
	static int container(
		std::vector< std::pair<_Ty, _Ty> > &container,
		cv::Mat& (*pFunc)(_Ty &d),
		cv::Mat &image) {
		if (image.empty()) return 0;
		image = cv::Scalar::all(0);
		int elements = container.size();
		if (elements > 0)
		{
			int w = std::sqrt((float)elements) + 1;
			int h = w;
			int wsize = image.cols / 2;
			if (w <= 2) {
				wsize = image.cols / 2;
			} else {
				wsize = image.cols / w - 2;
			}
			for (int i = 0; i < elements; i++)
			{
				int x = i % w; int y = i / w;
				cv::Mat tmp;
				cv::resize(pFunc(container[i].first), tmp,
					cv::Size(wsize / 2, wsize / 2));
				tmp.copyTo(image(cv::Rect(wsize * x, wsize * y,
					wsize / 2, wsize / 2)));
				cv::resize(pFunc(container[i].second), tmp,
					cv::Size(wsize / 2, wsize / 2));
				if (tmp.type() == image.type()) {
					tmp.copyTo(image(cv::Rect(wsize * x + wsize / 2,
						wsize * y + wsize / 2, wsize / 2, wsize / 2)));
				} else {
					return 0;
				}
			}
		}
		return 1;
	}

	/** @brief Display a set of images organized as groups

	@param[in] group_container Container with the groups
		First: group id
		Second: Collection of pairs of images (frame t-1, t1)
	*/
	static void groups(
		std::map<int, std::vector< _Ty* > >	&group_container,
		cv::Mat& (*pFunc)(_Ty &d),
		cv::Mat &image) {
		if (image.empty()) return;
		image = cv::Scalar::all(0);

		int min_size = 1, ifound = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = group_container.begin(); it != group_container.end(); it++)
#else
		//for (std::map<int, std::vector< _Ty* > >::const_iterator it = group_container.begin(); it != group_container.end(); it++)
		for (auto &it : group_container)
#endif
		{
			if (it->second.size() >= min_size) ++ifound;
		}
		if (ifound > 0)
		{
			int hsize = image.rows / ifound;
			int row = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = group_container.begin(); it != group_container.end(); it++)
#else
			//for (std::map<int, std::vector< _Ty* > >::const_iterator it = group_container.begin(); it != group_container.end(); it++)
			for (auto &it : group_container)
#endif
			{
				if (it->second.size() >= min_size)
				{
					//std::cout << "Group: " << it->first << " " << it->second.size() << std::endl;
					int wsize = (std::min)(hsize,
						(int)(image.cols / it->second.size()));
					int col = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
					for (auto it2 = it->second.begin();	it2 != it->second.end(); it2++)
#else
					//for (std::vector< _Ty* >::const_iterator it2 = it->second.begin();	it2 != it->second.end(); it2++)
					for (auto &it2 : it->second)
#endif
					{
						cv::Mat tmp;
						cv::resize(pFunc(**it2), tmp,
							cv::Size(wsize, wsize));
						tmp.copyTo(image(cv::Rect(wsize * col, hsize * row,
							wsize, wsize)));
						++col;
					}
					++row;
				}
			}
		}
	}


	/** @brief Display a set of images organized as groups

	@param[in] group_container Container with the groups
		First: group id
		Second: Collection of pairs of images (frame t-1, t1)
	*/
	static void groups(
		std::map<int, std::vector< std::pair<_Ty, _Ty>* > >	&group_container,
		cv::Mat& (*pFunc)(_Ty &d),
		cv::Mat &image) {
		if (image.empty()) return;
		image = cv::Scalar::all(0);

		int min_size = 1, ifound = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = group_container.begin(); it != group_container.end(); it++)
#else
		//for (std::map<int, std::vector< std::pair<_Ty, _Ty>* > >::const_iterator it = group_container.begin(); it != group_container.end(); it++)
		for (auto &it : group_container)
#endif
		{
			if (it->second.size() >= min_size) ++ifound;
		}
		if (ifound > 0)
		{
			int hsize = image.rows / ifound;
			int row = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
			for (auto it = group_container.begin(); it != group_container.end(); it++)
#else
			//for (std::map<int, std::vector< std::pair<_Ty, _Ty>* > >::const_iterator it = group_container.begin(); it != group_container.end(); it++)
			for (auto &it : group_container)
#endif
			{
				if (it->second.size() >= min_size)
				{
					//std::cout << "Group: " << it->first << " " << it->second.size() << std::endl;
					int wsize = (std::min)(hsize,
						(int)(image.cols / it->second.size()));
					int col = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
					for (auto it2 = it->second.begin();	it2 != it->second.end(); it2++)
#else
					//for (std::vector< std::pair<_Ty, _Ty>* >::const_iterator it2 = it->second.begin();	it2 != it->second.end(); it2++)
					for (auto &it2 : it->second)
#endif
					{
						cv::Mat tmp;
						cv::resize(pFunc((*it2)->first), tmp,
							cv::Size(wsize / 2, wsize / 2));
						tmp.copyTo(image(cv::Rect(wsize * col, hsize * row,
							wsize / 2, wsize / 2)));
						cv::resize(pFunc((*it2)->second), tmp,
							cv::Size(wsize / 2, wsize / 2));
						tmp.copyTo(image(cv::Rect(wsize * col + wsize / 2, 
							hsize * row + wsize / 2, wsize / 2, wsize / 2)));
						++col;
					}
					++row;
				}
			}
		}
	}

};

} // namespace group
} // namespace CmnIP

#endif /* CMNIP_GROUP_IMAGESCOMBINED_HPP__ */
