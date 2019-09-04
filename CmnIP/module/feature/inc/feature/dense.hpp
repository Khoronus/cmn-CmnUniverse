/**
* @file dense.hpp
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


#ifndef CMNIP_FEATURE_DENSE_HPP__
#define CMNIP_FEATURE_DENSE_HPP__

#include <iostream>
#include <fstream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "filter/inc/filter/filter_headers.hpp"
#include "draw/inc/draw/draw_headers.hpp"
#include "image2histogram.hpp"


namespace CmnIP
{
namespace feature
{

/** @brief Class to calculate a dense feature over a source image.
*/
class Dense
{
public:

	/** @brief Convert an image into an histogram.
	*/
	static void linear6histo(const cv::Mat &src, bool show, cv::Mat &output);

	/** @brief Convert an image into an histogram.
	*/
	static void linear10histo(const cv::Mat &src, bool show, cv::Mat &output);

};

}	// namespace feature
}	// namespace CmnIP


#endif /* CMNIP_FEATURE_DENSE_HPP__ */
