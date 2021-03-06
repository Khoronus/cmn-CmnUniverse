/**
* @file patrol.hpp
* @brief Class to generate a patrol movement on a 2D space.
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

#ifndef CMNIP_GROUP_IMAGESSPLIT_HPP__
#define CMNIP_GROUP_IMAGESSPLIT_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

namespace CmnIP
{
namespace group
{


/** @brief Class to split an image
*/
class ImageSplit
{
public:
	ImageSplit() {}

	// calculate the subregions
	void split(int natural_width, int natural_height, int cols, int rows) {

		int width = natural_width / cols;
		int height = natural_height / rows;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				rois_[std::make_pair(x, y)] = cv::Rect(x * cols, y * rows, cols, rows);
			}
		}

	}

	// calculate the subregions
	void split(cv::Mat &src, int natural_width, int natural_height, int cols, int rows) {

		int width = natural_width / cols;
		int height = natural_height / rows;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				rois_img_[std::make_pair(x, y)] = src(cv::Rect(x * cols, y * rows, cols, rows));
			}
		}

	}

	std::map< std::pair< int, int >, cv::Rect > rois_;
	std::map< std::pair< int, int >, cv::Mat > rois_img_;
};



} // namespace group
} // namespace CmnIP

#endif // CMNIP_GROUP_IMAGESSPLIT_HPP__
