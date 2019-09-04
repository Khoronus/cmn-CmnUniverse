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

#ifndef CMNIP_PHOTO_FOCUS_HPP__
#define CMNIP_PHOTO_FOCUS_HPP__

#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

namespace CmnIP
{
namespace photo
{

/** @brief Class to estimate the quality of the focus in an image.
*/
class Focus
{
public:

	/** @brief Estimate the focus value
	
	    @note: OpenCV port of 'LAPM' algorithm (Nayar89)
	*/
	static double modifiedLaplacian(const cv::Mat& src);

	/** @brief Estimate the focus value
	
	    @note OpenCV port of 'LAPV' algorithm (Pech2000)
    */
	static double varianceOfLaplacian(const cv::Mat& src);

	/** @brief Estimate the focus value
	
	    @note OpenCV port of 'TENG' algorithm (Krotkov86)
    */
	static double tenengrad(const cv::Mat& src, int ksize);

	/** @brief Estimate the focus value
	
	    @note OpenCV port of 'GLVN' algorithm (Santos97)
    */
	static double normalizedGraylevelVariance(const cv::Mat& src);

};

} // namespace photo
} // namespace CmnIP

#endif /* CMNIP_PHOTO_FOCUS_HPP__ */
