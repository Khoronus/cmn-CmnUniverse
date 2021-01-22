/**
* @file chart_radar.cpp
* @brief Body of the chart visualization radar type.
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

#include "draw/inc/draw/chart_radar.hpp"

namespace CmnIP
{
namespace draw
{

//-----------------------------------------------------------------------------
ChartRadar::ChartRadar(int size, float min_magnitude, float max_magnitude) {
	setup(size, min_magnitude, max_magnitude);
}
//-----------------------------------------------------------------------------
void ChartRadar::setup(int size, float min_magnitude, float max_magnitude) {
	chart_ = cv::Mat(size, size, CV_8UC3, cv::Scalar::all(0));
	center_ = cv::Point2f(chart_.cols / 2, chart_.rows / 2);
	radius_ = size / 2;
	min_magnitude_ = min_magnitude;
	max_magnitude_ = max_magnitude;
	clear();
}
//-----------------------------------------------------------------------------
void ChartRadar::clear() {
	chart_ = cv::Scalar::all(0);
	// Display the circles
	for (int i = 1; i <= 10; i++) {
		cv::circle(chart_, center_, radius_ / 10 * i, 
			cv::Scalar::all(255), 1); 
	}
}
//-----------------------------------------------------------------------------
void ChartRadar::draw(const std::vector<float> &container, 
                      const cv::Scalar &color)
{
	if (container.size() == 0) return;
	std::vector< cv::Point2f > points;
	container2points(container, min_magnitude_, max_magnitude_, points);
	internal_draw(chart_, points, center_, radius_, 
		color, true);
}
//-----------------------------------------------------------------------------
void ChartRadar::draw(const std::vector<std::pair<float, float> > &container, 
	cv::Scalar &color)
{
	if (container.size() == 0) return;
	std::vector<float> container_v1, container_v2;
	std::vector< cv::Point2f > points_v1, points_v2;
	CmnLib::container::ContainerCoreOperations<float>::split(
		container, container_v1, container_v2);
	container2points(container_v1, min_magnitude_, max_magnitude_, points_v1);
	container2points(container_v2, min_magnitude_, max_magnitude_, points_v2);
	internal_draw(chart_, points_v1, center_, radius_, 
		color, false);
	internal_draw(chart_, points_v2, center_, radius_, 
		color, true);
}
//-----------------------------------------------------------------------------
cv::Mat& ChartRadar::chart() {
	return chart_;
}
//-----------------------------------------------------------------------------
void ChartRadar::container2points(const std::vector<float> &container,
	float min_magnitude, float max_magnitude,
	std::vector<cv::Point2f> &points)
{
	if (max_magnitude == 0) return;
	int elements = container.size();
	float angle_bin = 360. / elements;

	int idx = 0;

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = container.begin(); it != container.end(); it++)
#else
	for (std::vector<float>::const_iterator it = container.begin(); it != container.end(); it++)
#endif
	{
		// calculate the current angle
		float angle = (angle_bin * idx) * 0.01745329251994329576923690768489;
		// calculate the ratio
		float r = (*it - min_magnitude) / max_magnitude;
		// calculate the 2D position
		points.push_back( cv::Point2f( std::sin(angle) * r, 
			std::cos(angle) * r ) );
		++idx;
	}
}
//-----------------------------------------------------------------------------
void ChartRadar::internal_draw(cv::Mat &chart,
	const std::vector<cv::Point2f> &points,
	cv::Point2f &center, float radius, const cv::Scalar &color,
	bool show_text) {
	// Draw the points
	int s = points.size();
	for (int i = 0; i < s; i++)
	{
		int j = i < s - 1 ? i + 1 : 0;
		cv::line(chart, points[i] * radius + center, points[j] * radius + 
			center,	color, 1);
		cv::circle(chart, points[i] * radius  + center, 1, color, 1);
		if (show_text) {
			char buf[256];
			sprintf(buf, "%i", i);
			cv::putText(chart, buf, points[i] * radius  + center, 0, 0.5, 
				color);
		}
	}
}

} // namespace drawing
} // namespace CmnIP
