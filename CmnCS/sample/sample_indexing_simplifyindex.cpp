/**
* @file sample_numericsystem_numericsystem.cpp
* @brief Sample dynamic.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>
#include <fstream>

#include "cmnlibworld/inc/cmnlibworld/cmnlibworld_headers.hpp"

#include "indexing/inc/indexing/indexing_headers.hpp"

namespace
{

/** @brief Display the set container
*/
void show_set(std::map<int, std::set<int>> &A) {
	for (auto &it : A) {
		std::cout << "A[" << it.first << "]:";
		for (auto &it2 : it.second) {
			std::cout << it2 << " ";
		}
		std::cout << std::endl;
	}
}


/** @brief It extract the faces that are observed by a camera.

It extract the faces that are observed by a camera.
*/
bool scan_file(const std::string &fname_source,
	std::map<int, std::set<int>> &A) {
	std::ifstream f(fname_source);
	if (!f.is_open()) return false;

	int idx = 0;
	while (!f.eof()) {
		std::string line;
		std::getline(f, line);
		if (line.size() > 0) {
			CmnLib::text::stringTokenizer st1(line, '|');
			std::vector<std::string> words1;
			st1.to_vector(words1);
			// Found at least 3 elements
			if (words1.size() >= 5) {
				// Scan the position and orientation
				CmnLib::text::stringTokenizer st2(words1[4], ' ');
				std::vector<std::string> words2;
				st2.to_vector(words2);
				std::set<int> items;
				for (auto &it : words2) {
					if (it.size() > 0) {
						int v = std::stoi(it);
						items.insert(v);
					}
				}
				A[idx++] = items;
			}
		}
	}

	return true;
}


/** @brief It creates a subset of a source file where the lines are the ones
that are pointed by the container A.
*/
bool subset_file(const std::string &fname_source,
	const std::map<int, std::set<int>> &A,
	const std::string &fname_out) {

	std::ifstream f(fname_source);
	if (!f.is_open()) return false;

	std::ofstream fout(fname_out);

	int idx = 0;
	while (!f.eof()) {
		std::string line;
		std::getline(f, line);
		if (line.size() > 0) {
			if (A.find(idx) != A.end()) {
				fout << line << std::endl;
			}
			++idx;
		}
	}

	return true;
}

/** @brief Test function
*/
int test_simple()
{
	std::cout << "Compiled: " << __DATE__ << " " << __TIME__ << std::endl;

	/*

	0 1 x
	x x 2
	x 1 2
	0 x 2

	*/

	// Container with the items association found
	std::map<int, std::set<int>> A;
	std::set<int> s;
	s.insert(0); s.insert(1);
	A[0] = s;
	s.clear();
	s.insert(1); s.insert(2); //s.insert(4);
	A[1] = s;
	s.clear();
	s.insert(0); s.insert(3);
	A[2] = s;
	s.clear();
	s.insert(0); s.insert(2); //s.insert(5);
	A[3] = s;

	std::cout << "-------- set: " << std::endl;
	show_set(A);

	std::map<int, std::set<int>> Asub, Asub2;
	SimplifyIndex::remove_subset(A, Asub);
	std::cout << "-------- remove subset" << std::endl;
	show_set(Asub);

	SimplifyIndex::unique_set(Asub, Asub2);
	std::cout << "-------- unique_set" << std::endl;
	show_set(Asub2);
	return 0;
}


/** @brief Test function1
*/
int test()
{
	std::cout << "Compiled: " << __DATE__ << " " << __TIME__ << std::endl;

	std::cout << "This function is used to reduce the indexes in a sequence ";
	std::cout << "that have a overlay. Only non removable items remain." <<
		std::endl;
	std::cout << "i.e. |0,1,2| and |0, 2|, the last is removed." << std::endl;

	std::cout << "Source must be in the format:" << std::endl;
	std::cout << "x y z xr yr zr| mesh_id0 num_faces %face cover| face_idA face_idB face_idE ...| mesh_id1 ..." << std::endl;

	std::cout << "SolveIndex.exe result\\faces0.txt result\\subset.txt" <<
		std::endl;
	std::cout << "exe [fname_source] [fname_out]" << std::endl;

	/*

	0 1 x
	x x 2
	x 1 2
	0 x 2

	*/

	// Mesh to perform the raycast
	std::string fname_source = "..\\..\\data\\faces0.txt";
	std::string fname_out = "simplifyindex_test.txt";
	//std::string fname_source = "result\\faces0.txt";
	//std::string fname_out = "subset.txt";

	// Container with the items association found
	std::map<int, std::set<int>> A;
	std::set<int> s;
	//s.insert(0); s.insert(1);
	//A.push_back(s);
	//s.clear();
	//s.insert(2);
	//A.push_back(s);
	//s.clear();
	//s.insert(1); s.insert(2);
	//A.push_back(s);
	//s.clear();
	//s.insert(0); s.insert(2);
	//A.push_back(s);
	//s.clear();
	//s.insert(0); s.insert(3);
	//A.push_back(s);

	//s.insert(0); s.insert(1);
	//A[0] = s;
	//s.clear();
	//s.insert(1); s.insert(2); //s.insert(4);
	//A[1] = s;
	//s.clear();
	//s.insert(0); s.insert(3);
	//A[2] = s;
	//s.clear();
	//s.insert(0); s.insert(2); //s.insert(5);
	//A[3] = s;

	//A.clear();
	scan_file(fname_source, A);
	std::cout << "-------- set: " << std::endl;
	show_set(A);

	std::map<int, std::set<int>> Asub, Asub2;
	SimplifyIndex::remove_subset(A, Asub);
	std::cout << "-------- remove subset" << std::endl;
	show_set(Asub);

	SimplifyIndex::unique_set(Asub, Asub2);
	std::cout << "-------- unique_set" << std::endl;
	show_set(Asub2);

	subset_file(fname_source,
		Asub2, fname_out);

	return 0;
}



} // namespace anonymous

// ############################################################################

void main(int argc, char* argv[])
{
	std::cout << "Sample SimplifyIndex" << std::endl;
	test_simple();
	test();
}


