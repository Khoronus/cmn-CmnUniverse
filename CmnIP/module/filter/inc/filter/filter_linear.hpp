/**
* @file filter_linear.hpp
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


#ifndef CMNIP_FILTER_FILTERLINEAR_HPP__
#define CMNIP_FILTER_FILTERLINEAR_HPP__

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
namespace filter
{

/** @brief Class to perform some filter linear on source images.

	Class to perform some filter linear on source images.
*/
class FilterLinear
{
  public:

	  /** @brief Perform a gabor filtering over a source image.

	  Perform a gabor filtering over a source image.
	  @param[in] src Source
	  @param[in] kernel_size Kernel size
	  @param[in] pos_sigma Sigma
	  @param[in] pos_lm Lambda
	  @param[in] pos_th Theta
	  @param[in] pos_psi Psi
	  @param[out] dest Destination
	  */
	  static void get_gabor(const cv::Mat &src, int kernel_size,
		  int pos_sigma, int pos_lm, int pos_th, int pos_psi,
		  cv::Mat &dest);

	/** @brief Get the laplace filter.

		Perform a LOG filtering over a source image.
		@param[in] src Source
		@param[in] kernel_size Kernel size
		@param[in] scale Scale
		@param[in] delta Delta
		@param[in] ddepth The result depth
		@param[in] blur_size A blur filter to remove the noise. If values are
							 negative, the filter is not performed.
		@param[in] convert_scale If true, convert the result in absolute scale
								 values.
		@param[out] dest Destination
	*/
	static int get_laplace(const cv::Mat &src, int kernel_size, int scale, 
		int delta, int ddepth, const cv::Size &blur_size, bool convert_scale,
		cv::Mat &dst);

	/** @brief Apply a 2D filter

		@link http://stackoverflow.com/questions/23471083/create-2d-log-kernel-in-opencv-like-fspecial-in-matlab
		@link http://opencv-users.1802565.n2.nabble.com/Laplacian-of-the-Gaussian-td7580336.html
	*/
	static int filter2D(const cv::Mat src, const cv::Mat &kernel, 
		cv::Mat dst);


	/** Create a kernel

		LoG(x,y) = (1/(pi*sigma^4)) * (1 - (x^2+y^2)/(sigma^2))* (e ^ (- (x^2 + y^2) / 2sigma^2)

		http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm
	*/
	static void create_kernel(cv::Size &size, double sigma, cv::Mat &kernel);

	static void create_gauss_filter(cv::Mat &kernel);

	static void create_laplace_filter(cv::Mat &kernel);

  private:

	  /** @brief Create a kernel for the filter.

		@param[in] ks Kernel size
		@param[in] sig Sigma
		@param[in] th Theta
		@param[in] lm Lambda
		@param[in] ps Psi
		@return Return the kernel.
	  */
	  static cv::Mat mkKernel(int ks, double sig, double th, 
		  double lm, double ps);
};

}	// namespace filter
}	// namespace CmnIP

#endif /* CMNIP_FILTER_FILTERLINEAR_HPP__ */
