/**
* @file chart_radar.hpp
* @brief Header of the chart visualization radar type.
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

#ifndef CMNIP_DRAW_CHARTRADAR_HPP__
#define CMNIP_DRAW_CHARTRADAR_HPP__

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "container/inc/container/container_headers.hpp"

namespace CmnIP
{
namespace draw
{


/** @brief Display a chart in a radar form.
*/
class ChartRadar
{
public:

	/** @brief Constructor.

	Setup the chart.
	@param[in] size The size of the chart in pixel. Square size.
	@param[in] min_magnitude The minumum range of the chart (positive).
	@param[in] max_magnitude The maximum range of the chart (positive).
	*/
	ChartRadar(int size, float min_magnitude, float max_magnitude);

	/** @brief Setup the chart.

		Setup the chart.
		@param[in] size The size of the chart in pixel. Square size.
		@param[in] min_magnitude The minumum range of the chart (positive).
		@param[in] max_magnitude The maximum range of the chart (positive).
	*/
	void setup(int size, float min_magnitude, float max_magnitude);

	/** @brief Clear the contents of the chart and set to the initial form.

		Clear the contents of the chart and set to the initial form.
	*/
	void clear();

	/** @brief Draw the container data on the chart.

		Draw the container data on the chart.
		@param[in] container Container with the data to display.
		@param[in] color The color used to display the data.
	*/
	void draw(const std::vector<float> &container, 
	          const cv::Scalar &color);

	/** @brief Draw the container data on the chart.

		Draw the container data on the chart.
		@param[in] container Container with the data to display. The container
		           has the min and max values to display.
		@param[in] color The color used to display the data.
	*/
	void draw(const std::vector<std::pair<float, float> > &container, 
		cv::Scalar &color);

	/** @brief Return the structure with the chart.

		Return the structure with the chart.
		@return Return the structure with the chart.
	*/
	cv::Mat& chart();

private:

	/** @brief Image with the chart.
	*/
	cv::Mat chart_;
	/** @brief Center of the image.
	*/
	cv::Point2f center_;
	/** @brief Radius of the maximum magnitude represented in the image.
	*/
	float radius_;
	/** @brief Minimum magnitude used to calculate the ratio to convert
	the data in radius.
	*/
	float min_magnitude_;
	/** @brief Maximum magnitude used to calculate the ratio to convert
	    the data in radius.
	*/
	float max_magnitude_;

	/** @brief Convert the data contained in a container in a 2D image 
	    position.

		Convert the data contained in a container in a 2D image position.
		@param[in] container Container with the data to display.
		@param[in] min_magnitude Minimum magnitude to estimate the ratio for
				   the radius.
		@param[in] max_magnitude Maximum magnitude to estimate the ratio for
		           the radius.
		@param[in] points Container with the converted value in 2D position.
	*/
	void container2points(const std::vector<float> &container,
		float min_magnitude, float max_magnitude,
		std::vector<cv::Point2f> &points);

	/** @brief Draw a set of points over the chart image.

		Draw a set of points over the chart image.
		@param[inout] chart The image where to draw.
		@param[in] points Container with the converted value in 2D position.
		@param[in] center The center of the image.
		@param[in] radius The maximum radius for the chart.
		@param[in] color The color used to draw the data.
		@param[in] show_text If true, it shows the point index in the image.
	*/
	void internal_draw(cv::Mat &chart,
		const std::vector<cv::Point2f> &points,
		cv::Point2f &center, float radius, 
		const cv::Scalar &color,
		bool show_text);
};


} // namespace drawing
} // namespace commmonip

#endif
