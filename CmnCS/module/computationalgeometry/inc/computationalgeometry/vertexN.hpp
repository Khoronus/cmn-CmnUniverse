/**
* @file vertexN.hpp
* @brief Contains classes to manage the ND vertex structure.
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
* @version 1.1.1.0
*
*/


#ifndef CMNCS_COMPUTATIONALGEOMETRY_VERTEXN_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_VERTEXN_HPP__

#include <limits>       // std::numeric_limits
#include <vector>
#include <map>

#include "cmncscore/inc/cmncscore/type.hpp"

namespace CmnCS
{
namespace computationalgeometry
{


/** @brief Class to manage N dimension vertex.

	Class to manage N dimension vertex.
*/
template <typename _Ty>
class VertexN
{
public:

	VertexN() {}

	/** @brief Clear all the data.

	Clear all the data.
	*/
	void clear() {
		data_.clear();
	}

	/** @brief Remove an element from the list.

	Remove an element from the list.
	@param[in] index Index to remove.
	*/
	void remove(const INDEX index) {
		data_.erase(index);
	}

	/** @brief Add an element to the list.

	Add an element to the list.
	*/
	void set(const INDEX index, const _Ty &value) {
		data_[index] = value;
	}

	/** @brief Return if an element exist in the list.
	*/
	bool exist(const INDEX index) {
		return data_.find(index) != data_.end() ? true : false;
	}

	/** @brief Return the current number of elements memorized.

	Return the current number of elements memorized.
	@warning The size does not match with the keys.
	*/
	int size() {
		return data_.size();
	}

	/** @brief Get the structure.

	Get the structure.
	*/
	std::map< INDEX, _Ty >& data() {
		return data_;
	}

	/** @brief Get the structure pointer.

	Get the structure pointer.
	*/
	std::map< INDEX, _Ty >* pt_data() {
		return &data_;
	}

	/** @brief Get the structure pointer.

	Get the structure pointer.
	*/
	const std::map< INDEX, _Ty >* pt_data() const{
		return &data_;
	}


	/** @brief Set the structure.

	Set the structure.
	*/
	void set_data(const std::map< INDEX, _Ty > &data) {
		data_ = data;
	}


	/** @brief Find the key based on the index value.

	Find the key based on the index value.
	*/
	int find(const _Ty &value, INDEX &key) {
		for (auto it = data_.begin(); it != data_.end(); it++)
		{
			if (it->second == value) {
				key = it->first;
				return 1;
			}
		}
		return 0;
	}

	/** @brief Find the value of a given key.

	Find the value of a given key.
	*/
	int find(const INDEX &key, _Ty &value) {
		if (data_.find(key) != data_.end())
		{
			value = data_[key];
			return 1;
		}
		return 0;
	}

	/** @brief Find the key based on the nearest index value.

		Find the key based on the index value. It search the nearest element.
		@param[in] value The value to search.
		@param[out] key The key of the item found.
		@param[out] min_distance_out The minimum distance calculated.
		@return Return 1 in case of success. 0 if there are no items.
	*/
	int find_nearest(const _Ty &value, INDEX &key, float &min_distance_out) {
		if (data_.size() == 0) return 0;
		double distance = std::numeric_limits<double>::max();

		int iFound = 0;
		for (auto it = data_.begin(); it != data_.end(); it++)
		{
			float d = Distance::point_point(value, it->second);
			if (d < distance) {
				distance = d;
				key = it->first;
				iFound = 1;
			}
		}
		min_distance_out = distance;
		return iFound;
	}

	/** @brief Find the key based on the nearest index value.

	Find the key based on the index value. It search the nearest element.
	@param[in] value The value to find.
	@param[in] min_distance The minimum distance allowed (<=).
	@param[out] key The returned key.
	@return Return 1 if found. 0 otherwise.
	*/
	int find_nearest(const _Ty &value, double min_distance,
		INDEX &key) {
		if (data_.size() == 0) return 0;
		double distance = std::numeric_limits<double>::max();
		int iFound = 0;
		for (auto it = data_.begin(); it != data_.end(); it++)
		{
			float d = Distance::point_point(value, it->second);
			if (d < distance && d <= min_distance) {
				iFound = 1;
				distance = d;
				key = it->first;
			}
		}
		return iFound;
	}


private:

	/** @brief Container with the 3D points used to describe a structure.

	first_first: x coordinate
	first_second_first: y coordinate
	first_second_second: z coordinate
	second: univoque index name
	*/
	std::map< INDEX, _Ty > data_;
};




} // namespace computationalgeometry
} // namespace CmnCS

#endif // CMNCS_COMPUTATIONALGEOMETRY_VERTEXN_HPP__
