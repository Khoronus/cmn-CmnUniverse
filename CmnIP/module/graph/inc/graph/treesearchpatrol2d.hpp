/**
* @file patrol.hpp
* @brief Class to generate a patrol movement on a 2D space.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNIP_GRAPH_TREESEARCHPATROL2D_HPP__
#define CMNIP_GRAPH_TREESEARCHPATROL2D_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "cmnmathworld/inc/cmnmathworld/cmnmathworld_headers.hpp"

namespace CmnIP
{
namespace graph
{


/** @brief Class to manage the patrolling.

	This class provide an algorithm to move a point from goal to goal.
	It is expected that it is a plane, and that not obstacles are in the way.

	@note: This class is thought for a planar patrolling. Only rotation to
	the target.
*/
class Patrol2D
{
public:
	Patrol2D() : target_goal_(0), rotate_same_direction_(true)	{
		for (int i = 0; i < 3; i++)
		{
			current_.push_back(0);
			speed_.push_back(0);
			min_error_.push_back(0);
		}
	}
	explicit Patrol2D(const std::vector<float> &current) :
		target_goal_(0),
		current_(current),
		rotate_same_direction_(true) {
		for (int i = 0; i < 3; i++)
		{
			speed_.push_back(0);
			min_error_.push_back(0);
		}
	}
	~Patrol2D()	{}
	/** Add goal position
	*/
	void AddGoal(const std::vector<float> &goal);
	/** Calculate the next position and orientation based on the target goal position.
	*/
	void NextEpoch();
	/** Get the current position
	*/
	std::vector< float > current() const;
	/** Set the current position
	*/
	void set_current(const std::vector< float > &current);
	/** Set the speed
	*/
	void set_speed(const std::vector<float> &speed);
	/** Get the speed
	*/
	std::vector< float > speed() const;
	/** Get the goals
	*/
	std::vector< std::vector<float> > goal() const;
	/** Set the min error admitted
	*/
	void set_min_error(const std::vector<float> &min_error);
	/** Set if the rotation direction is fixed or optimized.
	If optimized, the rotation direction will change to minimize the steps.
	*/
	void set_rotate_same_direction(const bool rotate_same_direction);

private:
	/** Switch the goal
	*/
	void NextGoal();

	/** @brief Current position and orientation
	It is expected to be in the format
	[0] : x; [1] : y; [2] : angle
	*/
	std::vector< float > current_;
	/** @brief Goal position
	first: goal id
	second: goal x,y,... point position
	*/
	std::vector< std::vector< float > > goal_;
	/** @brief Current speed
	It is used to set the movement and rotation speed. Format
	[0] : x; [1] : y; [2] : angle
	*/
	std::vector< float > speed_;
	/** @brief Goal id where the object is targeting
	*/
	int target_goal_;
	/** @brief Expected minimum error before to change the goal
	It is used to check the minimum distance or minimum rotation
	[0] : distance; [1] : rotation
	*/
	std::vector<float> min_error_;
	/** @brief Rotate in the same direction
	*/
	bool rotate_same_direction_;
};


} // namespace graph
} // namespace CmnIP

#endif // CMNIP_GRAPH_TREESEARCHPATROL2D_HPP__
