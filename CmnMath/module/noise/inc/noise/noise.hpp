/**
* @file noise.hpp
* @brief Class to generate noise
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
* @original author Will Perone (will.perone@gmail.com)
* @modified by Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_NOISE_NOISE_HPP__
#define CMNMATH_NOISE_NOISE_HPP__

#include <vector>
#include <cmath>

namespace CmnMath
{
namespace noise
{

/** @brief Class to add a noise to the scene
*/
template <typename _Ty3>
class Noise
{
public:

	/** @brief Add a random noise to the sensor
	*/
	static void random_noise(
		double prob, float noise_magnitude,
		std::map<int, std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > > &items) {

		// add a noise
		for (auto &it : items) {
			if (it.first == 1) continue;
			for (auto &it2 : it.second) {
				if ((float)rand() / RAND_MAX > prob) {
					noise(noise_magnitude, it2.first.first);
				}
			}
		}

	}

	/** @brief Add a random noise to the sensor
	*/
	static void localized_random_noise(
		const std::vector<_Ty3> &pts, float min_distance,
		double prob, float noise_magnitude,
		std::map<int, std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > > &items) {

		// add a noise
		for (auto &it : items) {
			if (it.first == 1) continue;
			for (auto &it2 : it.second) {
				for (auto it3 : pts) {
					if (distance(it3, it2.first.first) < min_distance) {
						noise(noise_magnitude, it2.first.first);
						if ((float)rand() / RAND_MAX > prob) {
							noise(1.3, it2.first.first);
						}
					}
				}
			}
		}
	}

	/** @brief Adjust all the points that hit (nearby) the pts list
	*/
	static void localized_adjustment(
		const std::vector<_Ty3> &pts, float min_distance,
		float z_new_value,
		std::map<int, std::vector< std::pair< std::pair< _Ty3, _Ty3>,
		std::pair<_Ty3, float> > > > &items) {

		// add a noise
		for (auto &it : items) {
			if (it.first == 1) continue;
			for (auto &it2 : it.second) {
				for (auto it3 : pts) {
					if (distance(it3, it2.first.first) < min_distance) {
						it2.first.first.z = z_new_value;
					}
				}
			}
		}
	}


private:

	/** @brief Add a noise to a point
	*/
	static void noise(float amount, _Ty3 &v) {
		v.x += ((float)rand() / RAND_MAX - 0.5f) * amount;
		v.y += ((float)rand() / RAND_MAX - 0.5f) * amount;
		v.z += ((float)rand() / RAND_MAX - 0.5f) * amount;
	}

	/** @brief Distance between two points
	*/
	static float distance(const _Ty3 &a, const _Ty3 &b) {
		return sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) +
			std::pow(a.z - b.z, 2));
	}
};

} // namespace noise
} // namespace CmnMath


#endif // CMNMATH_NOISE_NOISE_HPP__