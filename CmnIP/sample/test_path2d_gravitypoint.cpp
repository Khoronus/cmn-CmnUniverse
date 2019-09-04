/**
* @file sample_test_gravitypoint.cpp
* @brief Test a gravity point for the movement of the camera.
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

#include "draw/inc/draw/draw_headers.hpp"
#include "graph/inc/graph/graph_headers.hpp"

namespace
{

/** @brief Point Mass
*/
typedef struct PointMass_
{
	cv::Point2f p_;
	double mass_;
	PointMass_(cv::Point2f &p, double mass) {
		p_ = p; mass_ = mass;
	}
} PointMass, *pPointMass;

/** @brief Use a feedback data to adjust the current sensor 2D position
*/
class FeedbackPosition
{
public:

	/** @brief Correct the 2D movement.

	    @param[inout] move The amount of movement estimated and adjusted.
	*/
	static void correct(cv::Point2f &expected, float M0, cv::Point2f &previous,
		float M1, double Fmin, cv::Point2f &move) {

		PointMass pm_expected(expected, M0);
		PointMass pm_previous(previous, M1);

		// calculate the force
		double F = (std::min)(force(pm_expected, pm_previous), Fmin);// 0.05);

		bool xgetting_near = false, ygetting_near = false;
		float xdiff = 0, ydiff = 0;
		getting_near(pm_expected.p_, pm_previous.p_, move,
			xgetting_near, ygetting_near, xdiff, ydiff);
		if (move.x != 0 || move.y != 0) {
			move.x += xdiff * F;
			move.y += ydiff * F;
		}
	}

	/** @brief
	*/
	static double force(PointMass &m0, PointMass &m1)
	{
		double r = std::sqrt(std::pow(m0.p_.x - m1.p_.x, 2) +
			std::pow(m0.p_.y - m1.p_.y, 2));

		double G = 6.673*10e-11;
		return G * ((m0.mass_ * m1.mass_) / std::pow(r, 2));
	}

	/** @brief It calculates if a point is getting near.
	*/
	static void getting_near(const cv::Point2f &center, const cv::Point2f &current,
		const cv::Point2f &move, bool &xgetting_near, bool &ygetting_near,
		float &xdiff, float &ydiff)
	{
		float xdiff_before = std::abs(center.x - current.x);
		float xdiff_after = std::abs(center.x - (current.x + move.x));
		float ydiff_before = std::abs(center.y - current.y);
		float ydiff_after = std::abs(center.y - (current.y + move.y));
		xgetting_near = ygetting_near = true;
		if (xdiff_after > xdiff_before) xgetting_near = false;
		if (ydiff_after > ydiff_before) ygetting_near = false;
		xdiff = center.x - (current.x + move.x);
		ydiff = center.y - (current.y + move.y);
	}

};


/*
If the point is getting near, move faster
If the point is getting far, move slower
Add a noise function to simulate the error in the movements
*/

/** @brief Show a set of plot over the image.
*/
void test()
{
	CmnIP::draw::Map2D map2d;
	map2d.set_range(-300, -300, 300, 300);
	map2d.set_natural_size(512, 512);
	
	bool bContinue = true;
	PointMass center( cv::Point2f(100, 100), 1000000 );
	PointMass current(cv::Point2f(0, 0), 100000);
	cv::Point2f move;
	float xshift = 3, yshift = 3;
	float angle = 0, delta_angle = 0.1;
	while (bContinue)
	{
		map2d.reset_paint();

		// adjust the movement with the current rotation
		CmnMath::geometry::Rotation2D<cv::Point2f>::point(move,
			angle, cv::Point2f(0, 0), move);
		// calculate the force
		double F = (std::min)(FeedbackPosition::force(current, center), 0.05);
		std::cout << "F: " << F << std::endl;

		bool xgetting_near = false, ygetting_near = false;
		float xdiff = 0, ydiff = 0;
		FeedbackPosition::getting_near(center.p_, current.p_, move,
			xgetting_near, ygetting_near, xdiff, ydiff);
		std::cout << xdiff << " <> " << ydiff << std::endl;
		if (move.x != 0 || move.y != 0) {
			move.x += xdiff * F;
			move.y += ydiff * F;
			std::cout << xgetting_near << " " << ygetting_near << std::endl;
		}

		// Adjust the current position
		current.p_ += move;

		// Get the marker
		std::vector<cv::Point2f> points;
		map2d.scaled_marker(current.p_.x, current.p_.y, angle, 50, points);

		// Get the center
		float xcenter = 0, ycenter = 0, radius = 0;
		map2d.scaled_circle(center.p_, 20, xcenter, ycenter, radius);
		cv::circle(map2d.image(), cv::Point(xcenter, ycenter), radius,
			cv::Scalar(0, 0, 255), 1);

		cv::line(map2d.image(), points[0], points[1], cv::Scalar(0, 255));
		cv::line(map2d.image(), points[2], points[3], cv::Scalar(0, 255));
		move = cv::Point2f(0, 0);
		cv::imshow("result", map2d.image());
		char c = cv::waitKey(10);
		switch (c)
		{
		case 'q':
		case 27:
			bContinue = false;
			break;
		case '2':
			move.y += yshift;
			break;
		case '8':
			move.y -= yshift;
			break;
		case '4':
			move.x -= xshift;
			break;
		case '6':
			move.x += xshift;
			break;
		case '7':
			angle -= delta_angle;
			break;
		case '9':
			angle += delta_angle;
			break;
		case 'a':
			center.p_ = cv::Point2f(-222, -200);
			break;
		case 'b':
			center.p_ = cv::Point2f(222, -200);
			break;
		case 'c':
			center.p_ = cv::Point2f(100, 100);
			break;
		}
	}
}

//add auto movement and show the center only every # frames

void test2(const std::string &filename_coordinate, 
	const std::string &filename_result, bool use_force)
{
	// Create a path planning
	CmnIP::graph::Patrol2D patrol;
	patrol.set_rotate_same_direction(false);
	// Set speed
	std::vector<float> speed;
	speed.push_back(3.0f);
	speed.push_back(3.0f);
	speed.push_back(0.1f);
	patrol.set_speed(speed);
	// Set position
	std::vector<float> position;
	position.push_back(-200.0f);
	position.push_back(-200.0f);
	position.push_back(0.0f);
	patrol.set_current(position);
	// Set goal
	std::vector<float> goal;
	goal.push_back(-200.0f);
	goal.push_back(-200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(200.0f);
	goal.push_back(-200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(200.0f);
	goal.push_back(200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(-200.0f);
	goal.push_back(200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	// Set min_error
	std::vector<float> min_error;
	min_error.push_back(3.0f);
	min_error.push_back(0.1f);
	patrol.set_min_error(min_error);

	// Read the points
	std::vector< cv::Point2f > noise;
	std::ifstream myfile(filename_coordinate);
	while (!myfile.eof())
	{
		char buf[256];
		myfile.getline(buf, 256);
		float x = 0, y = 0;
		sscanf(buf, "%f %f", &x, &y);
		noise.push_back(cv::Point2f(x, y));
	}
	myfile.clear();
	myfile.close();

	// 2D map to display the position of the marker and expected position
	CmnIP::draw::Map2D map2d;
	map2d.set_range(-500, -500, 500, 500);
	map2d.set_natural_size(512, 512);

	// If true it uses automatic movements
	bool use_patrol = true;

	// Use the center every # frames
	int center_every_n_frames = 10;
	bool is_center_active = true;

	// Use the noise effect
	bool use_noise = true;

	// Memorize the results
	std::ofstream outputf(filename_result);
	int iMaxFrames = 1000;

	bool bContinue = true;
	PointMass center(cv::Point2f(patrol.current()[0], patrol.current()[1]), 10000000);
	PointMass current(center.p_, 10000000);
	cv::Point2f move, move_center;
	float xshift = 3, yshift = 3;
	float angle = 0, delta_angle = 0.1;
	int iFrame = 0;
	while (bContinue)
	{
		map2d.reset_paint();

		// Check if the center is active
		if (iFrame % center_every_n_frames == 0) {
			is_center_active = true;
		} else {
			is_center_active = false;
		}

		// adjust the movement with the current rotation
		if (!use_patrol) {
			CmnMath::geometry::Rotation2D<cv::Point2f>::point(move_center,
				angle, cv::Point2f(0, 0), move_center);
		}

		// Ideal condition, the marker move like the center
		move = move_center;

		// add some noise
		if (use_noise && (move.x != 0 || move.y != 0))
		{
			move += noise[iFrame % noise.size()];
		}

		// adjust the center
		center.p_ += move_center;

		// Apply the force
		if (use_force && is_center_active)
		{
			// calculate the force
			double F = (std::min)(FeedbackPosition::force(current, center), 0.5);// 0.05);
			//std::cout << "F: " << F << std::endl;

			bool xgetting_near = false, ygetting_near = false;
			float xdiff = 0, ydiff = 0;
			FeedbackPosition::getting_near(center.p_, current.p_, move,
				xgetting_near, ygetting_near, xdiff, ydiff);
			//std::cout << xdiff << " <> " << ydiff << std::endl;
			//std::cout << "move: " << move;
			if (move.x != 0 || move.y != 0) {
				move.x += xdiff * F;
				move.y += ydiff * F;
				//std::cout << xgetting_near << " " << ygetting_near << std::endl;
				//std::cout << " ->" << move;
			}
			//std::cout << std::endl;
		}

		// Adjust the current position
		current.p_ += move;

		// Get the marker
		std::vector<cv::Point2f> points;
		map2d.scaled_marker(current.p_.x, current.p_.y, angle, 50, points);

		// Get the center
		if (is_center_active)
		{
			float xcenter = 0, ycenter = 0, radius = 0;
			map2d.scaled_circle(center.p_, 20, xcenter, ycenter, radius);
			cv::circle(map2d.image(), cv::Point(xcenter, ycenter), radius,
				cv::Scalar(0, 0, 255), 1);
		}

		if (iFrame < iMaxFrames) {
			outputf << center.p_.x << " " << center.p_.y << " " << current.p_.x << " " << current.p_.y << std::endl;
		} else {
			bContinue = false;
		}

		// Display the marker position
		cv::line(map2d.image(), points[0], points[1], cv::Scalar(0, 255));
		cv::line(map2d.image(), points[2], points[3], cv::Scalar(0, 255));
		cv::imshow("result", map2d.image());

		// Reset the data
		move = cv::Point2f(0, 0);
		move_center = cv::Point2f(0, 0);
		char c = cv::waitKey(1);
		switch (c)
		{
		case 'q':
		case 27:
			bContinue = false;
			break;
		case '2':
			move.y += yshift;
			break;
		case '8':
			move.y -= yshift;
			break;
		case '4':
			move.x -= xshift;
			break;
		case '6':
			move.x += xshift;
			break;
		case '7':
			angle -= delta_angle;
			break;
		case '9':
			angle += delta_angle;
			break;
		case 'a':
			move_center.x -= xshift;
			break;
		case 's':
			move_center.x += xshift;
			break;
		case 'w':
			move_center.y -= yshift;
			break;
		case 'z':
			move_center.y += yshift;
			break;
		}

		// Use the automatic movement?
		if (use_patrol) {
			auto cb = patrol.current();
			patrol.NextEpoch();
			auto ca = patrol.current();
			move_center.x = ca[0] - cb[0];
			move_center.y = ca[1] - cb[1];
			angle = ca[2];
		}

		++iFrame;
	}
}



void test3(const std::string &filename_coordinate, 
	const std::string &filename_result, bool use_force)
{
	// Create a path planning
	CmnIP::graph::Patrol2D patrol;
	patrol.set_rotate_same_direction(false);
	// Set speed
	std::vector<float> speed;
	speed.push_back(3.0f);
	speed.push_back(3.0f);
	speed.push_back(0.1f);
	patrol.set_speed(speed);
	// Set position
	std::vector<float> position;
	position.push_back(-200.0f);
	position.push_back(-200.0f);
	position.push_back(0.0f);
	patrol.set_current(position);
	// Set goal
	std::vector<float> goal;
	goal.push_back(-200.0f);
	goal.push_back(-200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(200.0f);
	goal.push_back(-200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(200.0f);
	goal.push_back(200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	goal.push_back(-200.0f);
	goal.push_back(200.0f);
	patrol.AddGoal(goal);
	goal.clear();
	// Set min_error
	std::vector<float> min_error;
	min_error.push_back(3.0f);
	min_error.push_back(0.1f);
	patrol.set_min_error(min_error);

	// Read the points
	std::vector< cv::Point2f > noise;
	std::ifstream myfile(filename_coordinate);
	while (!myfile.eof())
	{
		char buf[256];
		myfile.getline(buf, 256);
		float x = 0, y = 0;
		sscanf(buf, "%f %f", &x, &y);
		noise.push_back(cv::Point2f(x, y));
	}
	myfile.clear();
	myfile.close();

	// 2D map to display the position of the marker and expected position
	CmnIP::draw::Map2D map2d;
	map2d.set_range(-500, -500, 500, 500);
	map2d.set_natural_size(512, 512);

	// If true it uses automatic movements
	bool use_patrol = true;

	// Use the center every # frames
	int center_every_n_frames = 10;
	bool is_center_active = true;

	// Use the noise effect
	bool use_noise = true;

	// Memorize the results
	std::ofstream outputf(filename_result);
	if (!outputf.is_open()) {
		std::cout << "Unable to open the file: " << filename_result << std::endl;
		return;
	}
	int iMaxFrames = 1000;

	bool bContinue = true;
	cv::Point2f move, move_center;
	cv::Point2f estimated = cv::Point2f(patrol.current()[0], patrol.current()[1]);
	float xshift = 3, yshift = 3;
	float angle = 0, delta_angle = 0.1;
	int iFrame = 0;
	while (bContinue)
	{
		map2d.reset_paint();

		cv::Point2f expected = cv::Point2f(patrol.current()[0], patrol.current()[1]);

		// Check if the center is active
		if (iFrame % center_every_n_frames == 0) {
			is_center_active = true;
		}
		else {
			is_center_active = false;
		}

		// Ideal condition, the marker move like the center
		estimated += move_center;

		// add some noise
		move = cv::Point2f(0, 0);
		if (use_noise)
		{
			move += noise[iFrame % noise.size()];
		}

		// Apply the force
		if (use_force && is_center_active)
		{
			FeedbackPosition::correct(expected, 1000000, estimated, 1000000,
				0.5, move);
		}

		// Adjust the current position
		estimated += move;

		// Get the marker
		std::vector<cv::Point2f> points;
		map2d.scaled_marker(estimated.x, estimated.y, angle, 50, points);

		// Get the center
		if (is_center_active)
		{
			float xcenter = 0, ycenter = 0, radius = 0;
			map2d.scaled_circle(expected, 20, xcenter, ycenter, radius);
			cv::circle(map2d.image(), cv::Point(xcenter, ycenter), radius,
				cv::Scalar(0, 0, 255), 1);
		}

		if (iFrame < iMaxFrames) {
			outputf << expected.x << " " << expected.y << " " << estimated.x << " " << estimated.y << std::endl;
		}
		else {
			bContinue = false;
		}

		// Display the marker position
		cv::line(map2d.image(), points[0], points[1], cv::Scalar(0, 255));
		cv::line(map2d.image(), points[2], points[3], cv::Scalar(0, 255));
		cv::imshow("result", map2d.image());

		// Reset the data
		move = cv::Point2f(0, 0);
		move_center = cv::Point2f(0, 0);
		char c = cv::waitKey(1);
		switch (c)
		{
		case 'q':
		case 27:
			bContinue = false;
			break;
		case '2':
			move.y += yshift;
			break;
		case '8':
			move.y -= yshift;
			break;
		case '4':
			move.x -= xshift;
			break;
		case '6':
			move.x += xshift;
			break;
		case '7':
			angle -= delta_angle;
			break;
		case '9':
			angle += delta_angle;
			break;
		case 'a':
			move_center.x -= xshift;
			break;
		case 's':
			move_center.x += xshift;
			break;
		case 'w':
			move_center.y -= yshift;
			break;
		case 'z':
			move_center.y += yshift;
			break;
		}

		// Use the automatic movement?
		if (use_patrol) {
			auto cb = patrol.current();
			patrol.NextEpoch();
			auto ca = patrol.current();
			move_center.x = ca[0] - cb[0];
			move_center.y = ca[1] - cb[1];
			angle = ca[2];
		}

		++iFrame;
	}
}



/** @brief It displays the result of the measurement
*/
void display(const std::string &filename_result_false,
	const std::string &filename_result_true )
{
	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));

	{
		std::ifstream myfile(filename_result_false);
		while (!myfile.eof())
		{
			char buf[512];
			myfile.getline(buf, 512);
			float xc, yc, x, y;
			sscanf(buf, "%f %f %f %f", &xc, &yc, &x, &y);
			cv::circle(m, cv::Point(xc + m.cols / 2, yc + m.rows / 2), 0, cv::Scalar(255));
			cv::circle(m, cv::Point(x + m.cols / 2, y + m.rows / 2), 0, cv::Scalar(0,0,255));
		}
	}
	{
		std::ifstream myfile(filename_result_true);
		while (!myfile.eof())
		{
			char buf[512];
			myfile.getline(buf, 512);
			float xc, yc, x, y;
			sscanf(buf, "%f %f %f %f", &xc, &yc, &x, &y);
			cv::circle(m, cv::Point(xc + m.cols / 2, yc + m.rows / 2), 0, cv::Scalar(255));
			cv::circle(m, cv::Point(x + m.cols / 2, y + m.rows / 2), 0, cv::Scalar(0, 255));
		}
	}
	cv::imshow("m", m);
	cv::waitKey();


}


} // namespace anonymous

// ############################################################################

void main()
{
	// Generate a set of random points for the coordinate
	std::ifstream myfile("../../data/gravitypoint_coordinate.txt");
	if (!myfile.is_open())
	{
		std::ofstream myfilew("../../data/gravitypoint_coordinate.txt");
		for (int i = 0; i < 10000; i++)
		{
			myfilew << std::pow(-1.0f, std::rand()) * (float)std::rand() / (float)RAND_MAX * 5 << " " <<
				std::pow(-1.0f, std::rand()) * (float)std::rand() / (float)RAND_MAX * 5 << std::endl;
		}
		myfilew.clear();
		myfilew.close();
	}
	myfile.clear();
	myfile.close();

	std::cout << "Example of gravity point (use the num pad and a,b,c to move"\
		" the cursor" << std::endl;
	test();

	std::cout << "Example of gravity point with animation" << std::endl;
	test2("../../data/gravitypoint_coordinate.txt", 
		"../../data/result_f2.txt", true);

	std::cout << "Compare the gravity point" << std::endl;
	test3("../../data/gravitypoint_coordinate.txt",
		"../../data/result_f.txt", false);
	test3("../../data/gravitypoint_coordinate.txt",
		"../../data/result_t.txt", true);
	display("../../data/result_f.txt", "../../data/result_t.txt");
}