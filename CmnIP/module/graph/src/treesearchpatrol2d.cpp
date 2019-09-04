/**
* @file patrol2d.cpp
* @brief Body of the classes to generate a patrol movement on a 2D space.
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
* @original author cforster
* @modified by Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include "graph/inc/graph/treesearchpatrol2d.hpp"

namespace CmnIP {
namespace graph {

//-----------------------------------------------------------------------------
void Patrol2D::AddGoal(const std::vector<float> &goal)	{
	goal_.push_back(goal);
}
//-----------------------------------------------------------------------------
void Patrol2D::NextEpoch()
{
	if (static_cast<int>(goal_.size()) <= 0) return;	// no goals
	bool bChanged = false;
	// Calculate the angle from the current point to the next goal
	auto a = current_;
	auto g = goal_;
	float angle = std::atan2(g[target_goal_][1] - a[1],
		g[target_goal_][0] - a[0]);
	// Calculate the distance from the current point to the next goal
	float distance = std::sqrt(std::pow(g[target_goal_][0] - a[0], 2.0f) +
		std::pow(g[target_goal_][1] - a[1], 2.0f));
	// Adjust the angle to be always inside the range [-pi,pi] degrees.
	if (current_[2] > CmnMath::core::kPIf) {
		current_[2] -= CmnMath::core::kPIf * 2.0f;
	}
	if (current_[2] < -CmnMath::core::kPIf) {
		current_[2] += CmnMath::core::kPIf * 2.0f;
	}
	// goal not reached and orientation does not match with the goal position
	if (distance > min_error_[0] &&
		std::abs(current_[2] - angle) > min_error_[1])	{
		if (rotate_same_direction_)
		{
			current_[2] += speed_[2];
		}
		else {
			if (current_[2] - angle > 0)
			{
				current_[2] -= speed_[2];
			}
			else {
				current_[2] += speed_[2];
			}
		}
		bChanged = true;
	}
	// If the distance is greater and there was no rotation, change the current
	// position.
	if (!bChanged && distance > min_error_[0])
	{
		current_[0] += std::cos(angle) * speed_[0];
		current_[1] += std::sin(angle) * speed_[1];
	}
	else if (!bChanged && distance <= min_error_[0]){
		NextGoal();
	}
}
//-----------------------------------------------------------------------------
std::vector< float > Patrol2D::current() const {
	return current_;
}
//-----------------------------------------------------------------------------
void Patrol2D::set_current(const std::vector< float > &current) {
	if (static_cast<int>(current.size()) == 3) current_ = current;
}
//-----------------------------------------------------------------------------
void Patrol2D::set_speed(const std::vector<float> &speed)	{
	if (static_cast<int>(speed.size()) == 3) speed_ = speed;
}
//-----------------------------------------------------------------------------
std::vector< float > Patrol2D::speed() const {
	return speed_;
}
//-----------------------------------------------------------------------------
std::vector< std::vector<float> > Patrol2D::goal() const {
	return goal_;
}
//-----------------------------------------------------------------------------
void Patrol2D::set_min_error(const std::vector<float> &min_error)	{
	if (static_cast<int>(min_error.size()) == 2) min_error_ = min_error;
}
//-----------------------------------------------------------------------------
void Patrol2D::set_rotate_same_direction(const bool rotate_same_direction)	{
	rotate_same_direction_ = rotate_same_direction;
}
//-----------------------------------------------------------------------------
void Patrol2D::NextGoal()	{
	target_goal_ = target_goal_ < static_cast<int>(goal_.size()) - 1 ?
		target_goal_ + 1 : 0;
}

} // namespace graph
} // namespace CmnIP
