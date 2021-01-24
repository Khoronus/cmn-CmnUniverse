/**
* @file VertexOrientedIONaive.hpp
* @brief Header related to oriented vertexes IO.
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
#ifndef CMNIO_FILESIO_VERTEXORIENTEDIONAIVE_HPP__
#define CMNIO_FILESIO_VERTEXORIENTEDIONAIVE_HPP__

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
class VertexOrientedIONaive
{
public:

	/** @brief It reads a naive file with vertexes in the form xy XYZ
	*/
	template <typename _Ty2, typename _Ty3>
	static bool read(const std::string &fname,
		std::string &header,
		std::vector<std::pair<_Ty2, std::pair<_Ty3, _Ty3>> > &v_xyxyz) {
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
				float x = 0, y = 0, X = 0, Y = 0, Z = 0, Xr = 0, Yr = 0, Zr = 0;
				sscanf(line.c_str(), "%f %f %f %f %f %f %f %f", &x, &y, &X, &Y, &Z, &Xr, &Yr, &Zr);
				v_xyxyz.push_back(std::make_pair(_Ty2(x, y), std::make_pair(_Ty3(X, Y, Z), _Ty3(Xr, Yr, Zr))));
			}
		}
		f.close();
		f.clear();

		return true;
	}

	/** @brief It reads a naive file with vertexes in the form xy XYZ
	*/
	template <typename _Ty2, typename _Ty3>
	static bool write(const std::string &fname, bool append,
		const std::string &header,
		std::vector<std::pair<_Ty2, std::pair<_Ty3, _Ty3>> > &v_xyxyz) {
		std::ofstream f;
		if (!append) {
			f.open(fname);
		} else {
			f.open(fname, std::ios::app);
		}
		if (!f.is_open()) return false;

		// Main header
		if (!append) {
			f << "VertexOrientedIONaive v 0.1.0" << std::endl;
			f << "x(px) y(px) X Y Z Xr Yr Zr" << std::endl;
			f << header << std::endl;
		}
		for (auto &it : v_xyxyz) {
			f << it.first.x << " " << it.first.y << " " << it.second.first.x << " "
				<< it.second.first.y << " " << it.second.first.z << " "
				<< it.second.second.x << " " << it.second.second.y << " "
				<< it.second.second.z << std::endl;
		}
		f.close();
		f.clear();
		return true;
	}

};

} // namespace filesio
} // namespace CmnIO

#endif // CMNIO_FILESIO_VERTEXORIENTEDIONAIVE_HPP__