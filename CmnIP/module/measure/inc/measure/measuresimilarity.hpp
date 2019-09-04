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

#ifndef CMNIP_MEASURE_MEASURESIMILARITY_HPP__
#define CMNIP_MEASURE_MEASURESIMILARITY_HPP__

#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief Class to measure the similarity between images
*/
class MeasureSimilarities
{
public:

	/** @brief Peak signal-to-noise ratio

	@link http://en.wikipedia.org/wiki/Peak_signal-to-noise_ratio
	*/
	static double PSNR(cv::Mat& src1, cv::Mat& src2, int bb);

};


} // namespace measure
} // namespace CmnIP

#endif /* CMNIP_MEASURE_MEASURESIMILARITY_HPP__ */
