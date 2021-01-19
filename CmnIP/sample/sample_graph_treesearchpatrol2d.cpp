/**
* @file sample_graph_treesearch_patrol2d.cpp
* @brief Test the patrol2d.
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

#include <iostream>
#include <string>
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "graph/inc/graph/graph_headers.hpp"

namespace
{

	
/** Test the patrol system
*/
void test()
{
	CmnIP::graph::Patrol2D patrol;
	patrol.set_rotate_same_direction(false);
	// Set speed
	std::vector<float> speed;
	speed.push_back(1.0f);
	speed.push_back(1.0f);
	speed.push_back(0.1f);
	patrol.set_speed(speed);
	// Set position
	std::vector<float> current;
	current.push_back(10.0f);
	current.push_back(20.0f);
	current.push_back(0.0f);
	patrol.set_current(current);
	// Set goal
	std::vector<float> goal;
	goal.push_back(50.0f);
	goal.push_back(100.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(250.0f);
	goal.push_back(180.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(450.0f);
	goal.push_back(370.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(150.0f);
	goal.push_back(200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(90.0f);
	goal.push_back(100.0f);
	patrol.AddGoal(goal);
	// Set min_error
	std::vector<float> min_error;
	min_error.push_back(1.0f);
	min_error.push_back(0.2f);
	patrol.set_min_error(min_error);

	cv::Mat world(512, 512, CV_8UC3);
	bool bContinue = true;
	while (bContinue)
	{
		world = cv::Scalar(0, 0, 0);
		// Draw the current goal position
		auto g = patrol.goal();
		int n_goal = static_cast<int>(g.size());
		for (int i = 0; i < n_goal; i++)
		{
			cv::circle(world, cv::Point(cvRound(g[i][0]), cvRound(g[i][1])),
				5, cv::Scalar(0, 255, 0), 1);
		}
		// Draw the current position
		auto a = patrol.current();
		cv::circle(world, cv::Point(cvRound(a[0]), cvRound(a[1])),
			5, cv::Scalar(0, 0, 255), 1);
		// Draw the current orientation
		cv::line(world, cv::Point(cvRound(a[0]), cvRound(a[1])),
			cv::Point(cvRound(a[0] + std::cos(a[2]) * 5.0f), cvRound(a[1] + std::sin(a[2]) * 5.0f)),
			cv::Scalar(0, 255, 255));
		cv::imshow("world", world);
		char c = cv::waitKey(10);
		if (c == 27) bContinue = false;

		patrol.NextEpoch();
	}

}

} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Test patrol2d" << std::endl;

	test();
	return 0;
}
