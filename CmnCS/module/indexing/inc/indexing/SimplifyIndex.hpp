/**
* @file SimplifyIndex.hpp
* @brief Class to simplify the indexing.
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

#ifndef CMNCS_INDEXING_SOLVEINDEX_HPP__
#define CMNCS_INDEXING_SOLVEINDEX_HPP__

#include <set>
#include <vector>
#include <map>
#include <iostream>

/** @brief Simplify the index
*/
class SimplifyIndex
{
public:

	/** @brief It removes all the sets that are a full subset of another

	example
	0 1 x
	x x 2
	x 1 2
	0 x 2
	0 x x 3

	result
	0 1 x
	x 1 2
	0 x 2
	0 x x 3
	*/
	static void remove_subset_bug_check_map(const std::vector<std::set<int>> &A,
		std::vector<std::set<int>> &Asub) {

		std::set<int> remove;
		// Scan all the sets
		for (size_t i = 0; i < A.size(); ++i) {
			for (size_t j = 0; j < A.size(); ++j) {
				if (i == j) continue;

				bool found = true;
				for (auto &it : A[i]) {
					if (A[j].find(it) == A[j].end()) {
						found = false;
						break;
					}
				}
				if (found) remove.insert(i);
			}
		}
		// Which elems remove
		for (size_t i = 0; i < A.size(); ++i) {
			if (remove.find(i) == remove.end()) {
				Asub.push_back(A[i]);
			}
		}
	}

	/** @brief It removes the repetitive subsets which contains same indexes.
	*/
	static void remove_subset(const std::map<int, std::set<int>> &Ain,
		std::map<int, std::set<int>> &Asub) {

		// Copy of the original set
		std::map<int, std::set<int>> A = Ain;

		// Scan all the sets
		bool remove_item = true;
		while (remove_item) {
			remove_item = false;
			std::set<int> remove;

			for (auto &itS : A) { //source
				if (remove_item) break;
				for (auto &itT : A) { // test
					if (remove_item) break;

					if (itS.first == itT.first) continue;

					bool found = true;
					for (auto &it : itS.second) {
						if (itT.second.find(it) == itT.second.end()) {
							found = false;
						}
					}
					if (found) {
						//std::cout << "Remove: " << itS.first << std::endl;
						remove.insert(itS.first);
						remove_item = true;
					}
				}
			}

			// Which elems remove
			for (auto &it : remove) A.erase(it);
		}
		Asub = A;
	}


	/** @brief Detect unique sets

	example
	0 1 x
	x 1 2
	0 x 2
	0 x x 3

	result
	x 1 2
	0 x x 3

	*/
	static void unique_set(const std::vector<std::set<int>> &A,
		std::vector<std::set<int>> &Asub) {

		std::cout << "unique_set" << std::endl;

		// Get the items instances
		std::map<int, std::pair<int, std::vector<int>>> items;
		int idx = 0;
		for (auto &it : A) {
			for (auto &it2 : it) {
				items[it2].first++;
				items[it2].second.push_back(idx);
			}
			++idx;
		}

		// Get unique keys
		std::set<int> unique;
		// Found the keys
		for (auto &it : items) {
			//std::cout << "key: " << it.first << " value: " << it.second.first << std::endl;
			// Only one item was insert
			if (it.second.first == 1) {
				unique.insert(it.second.second[0]);
				Asub.push_back(A[it.second.second[0]]);
			}
			//for (auto &it2 : it.second.second) {
			//	std::cout << it2 << " ";
			//}
			//std::cout << std::endl;
		}

		// Mark all the subsets that have an element in common with the unique

		// Remove the index in the unique key and check if the data is still valid
		std::set<std::pair<int, std::vector<int>>> subset_common;
		for (auto &it : unique) {
			// Remove a value for each element in the unique
			for (auto &it2 : A[it]) {
				// Unique items in the subset
				//std::cout << "items in unique[" << it << "]: " << it2 << std::endl;
				// For each item in the unique subset, it add the candidate
				// indexes that has that item in common
				// i.e. 0 found in the item 0, 1, 3
				//      2 found in the item 4
				//for (auto &it3 : A[it2]) {
				//	std::cout << "subset_common: " << it3 << std::endl;
				//	subset_common.insert(it3);
				//}

				std::vector<int> keys;
				for (auto &it3 : items[it2].second) {
					//std::cout << "subset_common: " << it3 << std::endl;
					keys.push_back(it3);
				}
				subset_common.insert(std::make_pair(it2, keys));
			}
		}

		// Which element is removed
		std::set<int> removed;

		// Count the item with the exception of the one set in the subset.
		// If there is at least 1 element marked as 0, it will not be removed.
		// Removed otherwise.
		for (auto &it : subset_common) {
			//std::cout << "key: " << it.first << std::endl;
			for (auto &it2 : it.second) {
				//	std::cout << "item: " << it2 << std::endl;

				// Count all the elements
				std::map<int, int> num_entries;
				int idx = 0;
				for (auto &it : A) {
					// No use the removed line
					if (removed.find(idx) != removed.end()) {
						++idx;
						continue;
					}
					for (auto &it2 : it) {
						++num_entries[it2];
					}
					++idx;
				}

				//for (auto &it : num_entries) {
				//	std::cout << "entriesB " << it.first << " " << it.second << std::endl;
				//}

				// Remove the entry marked by the item
				for (auto &it : A[it2]) {
					--num_entries[it];
				}

				// Essential element? At least one item <= 0
				bool essential = false;
				for (auto &it : num_entries) {
					if (it.second <= 0) essential = true;
					//std::cout << "entriesA " << it.first << " " << it.second << std::endl;
				}

				if (!essential) {
					//std::cout << "Remove: " << it2 << std::endl;
					removed.insert(it2);
				}

			}
		}

		for (auto &it : removed) {
			std::cout << "removed: " << it << std::endl;
		}

		// Set the new subset
		std::vector<std::set<int>> Atmp;
		idx = 0;
		for (auto &it : A) {
			// No use the removed line
			if (removed.find(idx) != removed.end()) {
				++idx;
				continue;
			}
			Atmp.push_back(it);
			++idx;
		}


		if (removed.size() > 0) {
			unique_set(Atmp, Asub);
		}
		else {
			Asub = Atmp;
		}

		//// Create a subset without the unique key
		//if (unique.size() > 0) {
		//	std::vector<std::set<int>> Atmp;
		//	for (size_t i = 0; i < A.size(); ++i) {
		//		if (unique.find(i) == unique.end()) Atmp.push_back(A[i]);
		//	}
		//	unique_set(Atmp, Asub);
		//}
	}


	/** @brief It estimates the unique set that minimize the reuse of the
	indexes.
	*/
	static void unique_set(const std::map<int, std::set<int>> &A,
		std::map<int, std::set<int>> &Asub) {

		// Get the items instances
		std::map<int, std::pair<int, std::vector<int>>> items;
		for (auto &it : A) {
			for (auto &it2 : it.second) {
				items[it2].first++;
				items[it2].second.push_back(it.first);
			}
		}

		// Get unique keys
		std::set<int> unique;
		// Found the keys
		for (auto &it : items) {
			//std::cout << "key: " << it.first << " value: " << it.second.first << std::endl;
			// Only one item was insert
			if (it.second.first == 1) {
				unique.insert(it.second.second[0]);
			}
			//for (auto &it2 : it.second.second) {
			//	std::cout << it2 << " ";
			//}
			//std::cout << std::endl;
		}

		// Mark all the subsets that have an element in common with the unique

		// Remove the index in the unique key and check if the data is still valid
		std::set<std::pair<int, std::vector<int>>> subset_common;
		for (auto &it : unique) {
			// Remove a value for each element in the unique
			for (auto &it2 : A.at(it)) {
				// Unique items in the subset
				//std::cout << "items in unique[" << it << "]: " << it2 << std::endl;
				// For each item in the unique subset, it add the candidate
				// indexes that has that item in common
				// i.e. 0 found in the item 0, 1, 3
				//      2 found in the item 4
				//for (auto &it3 : A[it2]) {
				//	std::cout << "subset_common: " << it3 << std::endl;
				//	subset_common.insert(it3);
				//}

				std::vector<int> keys;
				for (auto &it3 : items[it2].second) {
					//std::cout << "subset_common: " << it3 << std::endl;
					keys.push_back(it3);
				}
				subset_common.insert(std::make_pair(it2, keys));
			}
		}

		// Which element is removed
		std::set<int> removed;

		// Count the item with the exception of the one set in the subset.
		// If there is at least 1 element marked as 0, it will not be removed.
		// Removed otherwise.
		for (auto &it : subset_common) {
			//std::cout << "key: " << it.first << std::endl;
			for (auto &it2 : it.second) {
				//	std::cout << "item: " << it2 << std::endl;

				// Count all the elements
				std::map<int, int> num_entries;
				for (auto &it : A) {
					// No use the removed line
					if (removed.find(it.first) != removed.end()) {
						continue;
					}
					for (auto &it2 : it.second) {
						++num_entries[it2];
					}
				}

				//for (auto &it : num_entries) {
				//	std::cout << "entriesB " << it.first << " " << it.second << std::endl;
				//}

				// Remove the entry marked by the item
				for (auto &it : A.at(it2)) {
					--num_entries[it];
				}

				// Essential element? At least one item <= 0
				bool essential = false;
				for (auto &it : num_entries) {
					if (it.second <= 0) essential = true;
					//std::cout << "entriesA " << it.first << " " << it.second << std::endl;
				}

				if (!essential) {
					//std::cout << "Remove: " << it2 << std::endl;
					removed.insert(it2);
				}

			}
		}

		for (auto &it : removed) {
			std::cout << "removed: " << it << std::endl;
		}

		// Set the new subset
		std::map<int, std::set<int>> Atmp;
		for (auto &it : A) {
			// No use the removed line
			if (removed.find(it.first) != removed.end()) {
				continue;
			}
			Atmp.insert(it);
		}


		if (removed.size() > 0) {
			unique_set(Atmp, Asub);
		}
		else {
			Asub = Atmp;
		}

		//// Create a subset without the unique key
		//if (unique.size() > 0) {
		//	std::vector<std::set<int>> Atmp;
		//	for (size_t i = 0; i < A.size(); ++i) {
		//		if (unique.find(i) == unique.end()) Atmp.push_back(A[i]);
		//	}
		//	unique_set(Atmp, Asub);
		//}
	}

};

#endif // CMNCS_INDEXING_SOLVEINDEX_HPP__
