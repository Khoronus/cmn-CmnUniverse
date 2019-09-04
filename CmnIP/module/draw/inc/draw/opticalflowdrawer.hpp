/**
* @file pairs.hpp
* @brief Header of the pairs visualization.
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

#ifndef CMNIP_DRAWING_OPTICALFLOWDENSE_HPP__
#define CMNIP_DRAWING_OPTICALFLOWDENSE_HPP__

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "transform/inc/transform/transform_headers.hpp"

namespace CmnIP
{
namespace draw
{

/** Some optical flow utilities
*/
class OpticalFlowDrawer
{
public:

	/** Draw the map if moving
	*/
	static void OptFlowMoving(const cv::Mat& flow, int step, double thr,
		cv::Mat& cflowmap);

	/** Draw if something is moving
	*/
	static void drawOptFlowMoving(const cv::Mat& flow,
		cv::Mat& cflowmap, int step, double thr);

	/** Draw an optical flow map
	*/
	static void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
		double, const cv::Scalar& color);

	/** Draw an optical flow map
	*/
	static void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step);

	/** A simple function to estimate if the scenario changed
	*/
	static bool scenario_changed(const cv::Mat& flow, int step, float threshold);


	static void flow2rgb(cv::Mat &flow, cv::Mat &rgb);

	/** Draw an optical flow map
	*/
	static void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
		int colormode);
};


} // namespace draw
} // namespace CmnIP

#endif