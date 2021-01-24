/**
* @file VertexIONaive.hpp
* @brief Header related to vertex IO.
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
* @original  Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/
#ifndef CMNIO_FILESIO_VERTEXIONAIVE_HPP__
#define CMNIO_FILESIO_VERTEXIONAIVE_HPP__

#define _SECURE_SCL_DEPRECATE 0
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace CmnIO
{
namespace filesio
{


/** @brief IO operation on naive vertexes
*/
class VertexIONaive
{
public:

	/** @brief It reads a naive file with vertexes in the form xy XYZ
	*/
	template <typename _Ty2, typename _Ty3>
	static bool read(const std::string &fname,
		std::string &header,
		std::vector<std::pair<_Ty2, _Ty3> > &v_xyxyz) {
		std::ifstream f(fname);
		if (!f.is_open()) return false;

		// Skip the main header
		std::string line;
		std::getline(f, line);
		std::getline(f, line);
		// get the user header
		std::getline(f, header);

		// Get the points information
		while (!f.eof()) {
			std::string line;
			std::getline(f, line);
			if (line.size() > 0) {
				float x = 0, y = 0, X = 0, Y = 0, Z = 0;
				sscanf(line.c_str(), "%f %f %f %f %f", &x, &y, &X, &Y, &Z);
				v_xyxyz.push_back(std::make_pair(_Ty2(x, y), _Ty3(X, Y, Z)));
			}
		}
		f.close();
		f.clear();

		return true;
	}

	/** @brief It reads a naive file with vertexes in the form xy XYZ
	*/
	template <typename _Ty2, typename _Ty3>
	static bool write(const std::string &fname,
		const std::string &header,
		std::vector<std::pair<_Ty2, _Ty3> > &v_xyxyz) {
		std::ofstream f(fname);
		if (!f.is_open()) return false;

		// Main header
		f << "VertexIONaive v 0.1.0" << std::endl;
		f << "x(px) y(px) X Y Z" << std::endl;
		f << header << std::endl;
		for (auto &it : v_xyxyz) {
			f << it.first.x << " " << it.first.y << " " << it.second.x << " "
				<< it.second.y << " " << it.second.z << std::endl;
		}
		f.close();
		f.clear();
		return true;
	}

};


} // namespace filesio
} // namespace CmnIO

#endif // CMNIO_FILESIO_VERTEXIONAIVE_HPP__