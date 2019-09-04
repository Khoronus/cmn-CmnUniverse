/**
* @file map2d.hpp
* @brief Header of the map 2d visualization.
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

#ifndef CMNIP_DRAW_MAP2D_HPP__
#define CMNIP_DRAW_MAP2D_HPP__

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

//#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace draw
{

/** @brief Draw a 2D map
*/
class Map2D
{
public:

	Map2D() : xmin_resetarea_(-15000), xmax_resetarea_ (15000),
		ymin_resetarea_(-15000), ymax_resetarea_(15000) {

		image_ = cv::Mat::zeros(512,512,CV_8UC3);
	}

	/** @brief Set the natural range.
	*/
	void set_natural_size(int xsize, int ysize) {
		image_ = cv::Mat::zeros(ysize, xsize, CV_8UC3);
	}

	/** @brief Set the image range.
	*/
	void set_range(float xmin_resetarea, float	ymin_resetarea, 
		float xmax_resetarea, float ymax_resetarea) {
		xmin_resetarea_ = xmin_resetarea;
		xmax_resetarea_ = xmax_resetarea;
		ymin_resetarea_ = ymin_resetarea;
		ymax_resetarea_ = ymax_resetarea;
	}

	/** @brief Calculate the position of the points in a scaled image
    */
    static void original2scaled(
        float w, float h,
        float xmin, float ymin, float xmax, float ymax,
        float xin, float yin,
        float &xout, float &yout)
    {
        // Unit measure meters
        // Calculate the scale
        float xbin = (float)w / (xmax - xmin);
        float ybin = (float)h / (ymax - ymin);

        xout = (xin - xmin) * xbin;
        yout = (yin - ymin) * ybin;
    }

	/** @brief Calculate the position of the points in a scaled image
    */
    void original2scaled(
        float xin, float yin,
        float &xout, float &yout)
    {
		original2scaled(image_.cols, image_.rows,
			xmin_resetarea_, ymin_resetarea_,
			xmax_resetarea_, ymax_resetarea_,
			xin, yin, xout, yout);
    }

	/** @brief Given the coordinate x,y in pixel, it returns the converted 
	           position in meters.
	*/
    static void scaled2original(
        float w, float h,
        float xmin, float ymin, float xmax, float ymax,
        float xin, float yin,
        float &xout, float &yout)
    {
        // Unit measure meters
        // Calculate the scale
        float xbin = (float)w / (xmax - xmin);
        float ybin = (float)h / (ymax - ymin);

        xout = xin / xbin + xmin;
        yout = yin / ybin + ymin;
    }

	/** @brief Given the coordinate x,y in pixel, it returns the converted 
	           position in meters.
	*/
    void scaled2original(
        float xin, float yin,
        float &xout, float &yout)
    {
		scaled2original(image_.cols, image_.rows,
			xmin_resetarea_, ymin_resetarea_,
			xmax_resetarea_, ymax_resetarea_,
			xin, yin, xout, yout);
    }

    /** @brief Draw over a paint box the position of the reset points.
	*/
    void reset_paint()
    {
		if (image_.empty()) return;
        float h = image_.rows;
        float w = image_.cols;

        // Center
        float xcenter = 0, ycenter = 0;
        original2scaled(h, w,
            xmin_resetarea_, ymin_resetarea_, xmax_resetarea_, ymax_resetarea_,
            0, 0, xcenter, ycenter);

		image_ = cv::Scalar::all(0);
        // Axes
		cv::line(image_, cv::Point((int)xcenter, 0), cv::Point((int)xcenter, 
			image_.rows), cv::Scalar::all(255));
		cv::line(image_, cv::Point(0, (int)ycenter), cv::Point(image_.rows, 
			(int)ycenter), cv::Scalar::all(255));
		cv::putText(image_, "X", cv::Point(image_.cols - 15, 
			image_.rows / 2 - 20), 0, 0.5, cv::Scalar::all(255));
		cv::putText(image_, "-Z", cv::Point(image_.cols / 2 + 20, 40), 0, 
			0.5, cv::Scalar::all(255));

		char buf[256];
		sprintf(buf, "%5.3f", xmin_resetarea_);
		cv::putText(image_, buf, cv::Point(0, image_.rows / 2 + 20), 0, 0.5, 
			cv::Scalar::all(255));
		sprintf(buf, "%5.3f", ymin_resetarea_);
		cv::putText(image_, buf, cv::Point(image_.cols / 2 - 40, 20), 0, 0.5, 
			cv::Scalar::all(255));
		sprintf(buf, "%5.3f", xmax_resetarea_);
		cv::putText(image_, buf, cv::Point(image_.cols - 50, 
			image_.rows / 2 + 20), 0, 0.5, cv::Scalar::all(255));
		sprintf(buf, "%5.3f", ymax_resetarea_);
		cv::putText(image_, buf, cv::Point(image_.cols / 2 - 40, 
			image_.rows - 20), 0, 0.5, cv::Scalar::all(255));

        // Center position
		cv::circle(image_, cv::Point2f(xcenter, ycenter), 2, 
			cv::Scalar::all(255), -1);
	}

	/** @brief Draw a scaled circle over the image.
	*/
	void scaled_circle(cv::Point2f &p, float radius,
		float &xcenter_scale, float &ycenter_scale, float &radius_scale) {
		
		scaled_circle(p.x, p.y, radius, xcenter_scale, ycenter_scale, 
			radius_scale);
	}

	/** @brief Draw a scaled circle over the image.
	*/
	void scaled_circle(float xcenter, float ycenter, float radius,
		float &xcenter_scale, float &ycenter_scale, float &radius_scale) {

		// Calculate the scaled position
        original2scaled(image_.rows, image_.cols,
            xmin_resetarea_, ymin_resetarea_, xmax_resetarea_, ymax_resetarea_,
            xcenter, ycenter, xcenter_scale, ycenter_scale);

		// Calculate the scaled radius (add radius on x)
		float xradius_scale = 0, yradius_scale = 0;
        original2scaled(image_.rows, image_.cols,
            xmin_resetarea_, ymin_resetarea_, xmax_resetarea_, ymax_resetarea_,
            xcenter + radius, ycenter, xradius_scale, yradius_scale);

		// Calculate the radius scaled
		radius_scale = std::sqrt( std::pow(xcenter_scale - xradius_scale, 2) + 
			std::pow(ycenter_scale - yradius_scale, 2) );
	}

	/** @brief Return a rotated scaled marker.
	*/
	void scaled_marker(float xcenter, float ycenter, double angle, float radius,
		std::vector< cv::Point2f > &points) {
		
		// create 4 vertexes
		//     d
		//     |
		// a___|___b
        //     c
        //
		// left
		cv::Point2f a(xcenter - radius, ycenter);
		// right
		cv::Point2f b(xcenter + radius, ycenter);
		// center
		cv::Point2f c(xcenter, ycenter);
		// top
		cv::Point2f d(xcenter, ycenter - radius);
		original2scaled(a.x, a.y, a.x, a.y);
		original2scaled(b.x, b.y, b.x, b.y);
		original2scaled(c.x, c.y, c.x, c.y);
		original2scaled(d.x, d.y, d.x, d.y);
		cv::Point2f aout, bout, dout;
		CmnMath::geometry::Rotation2D<cv::Point2f>::point(a, angle, c, aout);
		CmnMath::geometry::Rotation2D<cv::Point2f>::point(b, angle, c, bout);
		CmnMath::geometry::Rotation2D<cv::Point2f>::point(d, angle, c, dout);
		points.clear();
		points.push_back(aout);
		points.push_back(bout);
		points.push_back(c);
		points.push_back(dout);
	}

	/** @brief Return the image.
	*/
	cv::Mat& image() {
		return image_;
	}

  private:

	/** @brief Image to display
	*/
	cv::Mat image_;

    /// <summary>
    /// Min position X for the reset area
    /// </summary>
    float xmin_resetarea_;
    /// <summary>
    /// Max position X for the reset area
    /// </summary>
    float xmax_resetarea_;
    /// <summary>
    /// Min position Y for the reset area
    /// </summary>
    float ymin_resetarea_;
    /// <summary>
    /// Max position Y for the reset area
    /// </summary>
    float ymax_resetarea_;
};


} // namespace draw
} // namespace CmnIP

#endif