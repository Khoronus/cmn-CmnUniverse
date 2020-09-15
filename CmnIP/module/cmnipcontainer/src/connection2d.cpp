/**
* @file connection2d.cpp
* @brief Body of the classes to find connection over sparse points in 2D.
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


#include "cmnipcontainer/inc/cmnipcontainer/connection2d.hpp"


namespace CmnIP
{
namespace cmnipcontainer
{

//-----------------------------------------------------------------------------
int Connection2D::find_index(float angle, cv::Point2f &p, 
	std::vector< cv::Point2f > &v_values, 
	cv::Point2f &norm_out,
	int &index)
{
	//cv::Mat m(512,512,CV_8UC3,cv::Scalar::all(0));
	//cv::circle(m, p, 2, cv::Scalar(0,0,255));

	// normale - angolo punto-punto
	index = -1;
	int s = v_values.size();
	float min_norm = 1000;
	for (int i = 0; i < s; i++)
	{
		if (v_values[i].x == p.x &&
			v_values[i].y == p.y) continue;
		float dx = v_values[i].x - p.x;
		float dy = v_values[i].y - p.y;

		//cv::circle(m, cv::Point(v_values[i].x, v_values[i].y), 2, cv::Scalar(0,255));

		//cv::Point2f norm(-dy, dx);
		cv::Point2f norm(dy, -dx);
		//float angle_n = std::atan2( norm.y, norm.x );
		float angle_n = std::atan2( dy, dx );
		//std::cout << "Angle_n: " << angle_n << std::endl;
		angle_n = (angle_n > 0 ? angle_n : (2*CV_PI + angle_n));
		float diff = angle_n - angle;
		if (diff >= 0 && diff < min_norm) {
			//std::cout << " OK";
			//std::cout << i << " " << v_values[i] << " " << angle_n << " " << 
			//             angle << std::endl;
			min_norm = diff;
			norm_out = norm;
			index = i;
		}
		//std::cout << std::endl;

		//cv::imshow("m", m);
		//cv::waitKey(10);
	}
	// Cannot find in the positive range. Get the smaller
	if (index < 0)
	{
		for (int i = 0; i < s; i++)
		{
			if (v_values[i].x == p.x &&
				v_values[i].y == p.y) continue;
			float dx = v_values[i].x - p.x;
			float dy = v_values[i].y - p.y;
			//cv::circle(m, cv::Point(v_values[i].x, v_values[i].y), 3, cv::Scalar(255,255));

			//cv::Point2f norm(-dy, dx);
			cv::Point2f norm(dy, -dx);
			//float angle_n = std::atan2( norm.y, norm.x );
			float angle_n = std::atan2( dy, dx );
			//std::cout << "Angle_n: " << angle_n << std::endl;
			angle_n = (angle_n > 0 ? angle_n : (2*CV_PI + angle_n));
			float diff = angle_n - angle;
			//std::cout << angle_n << " " << angle << " " << diff << " " << 
			//  min_norm;
			if (diff < min_norm) {

				//cv::circle(m, cv::Point(v_values[i].x, v_values[i].y), 4, cv::Scalar(0,255,255));

				//std::cout << " OK";
				//std::cout << i << " " << v_values[i] << " " << angle_n << 
				//  " " << angle << std::endl;
				min_norm = diff;
				norm_out = norm;
				index = i;
			}
			//std::cout << std::endl;
			//cv::imshow("m", m);
			//cv::waitKey(10);
		}
	}
	//std::cout << "Best: " << index << std::endl;
	if (index >= 0) return 1;
	return 0;
}
//-----------------------------------------------------------------------------
int Connection2D::get_next_connected(cv::Point2f &norm,
	cv::Point2f &p,
	std::set< std::pair< float, float > > &vertex_sparse,
	float min_distance, float max_distance,
	cv::Point2f &norm_out,
	cv::Point2f &point_out)
{
	// Add the points
	float angle_norm = std::atan2(norm.y, norm.x);// + angle;
	// Find the vertex inside an area
	std::vector< cv::Point2f > v_inside;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = vertex_sparse.begin(); it != vertex_sparse.end(); it++)
#else
	for (std::set< std::pair< float, float > >::const_iterator it = vertex_sparse.begin(); it != vertex_sparse.end(); it++)
#endif
	{
		float dist = CmnMath::geometry::DistanceZeroDimPoint::point_point_2d<cv::Point2f, float>(p, cv::Point2f( 
			it->first, it->second ) );
		if (dist >= min_distance && dist <= max_distance) {
			v_inside.push_back( cv::Point2f(it->first, it->second) );
		}
	}

	angle_norm = (angle_norm > 0 ? angle_norm : (2*CV_PI + angle_norm));
	//cv::Point2f norm_out;
	int index_out;
	if (find_index(angle_norm, p, v_inside, norm_out, index_out))
	{
		point_out = v_inside[index_out];
		return 1;
	}
	return 0;
}


} // namespace cmnipcontainer
} // namespace CmnIP
