/**
* @file mesh_naive_3D.hpp
* @brief Class to generate a mesh structure.
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.1.0.0
*
*/


#ifndef CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3D_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3D_HPP__

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace CmnCS
{
namespace computationalgeometry
{

/** @brief Class to contains all the meshes
*/
template <typename REAL>
class MeshNaive3D
{
public:

	MeshNaive3D() {}

	/** @brief Release the mesh
	*/
	void clear() {
		m_triangles_.clear();
	}

	/** @brief Return the memorized triangles
	*/
	std::map< std::string, std::vector< std::vector< REAL > > >& m_triangles() {
		return m_triangles_;
	}

	size_t size() { return m_triangles_.size(); }

	/** @brief Convert the data in a different structure
	*/
	template <typename _Ty2, typename _Ty3>
	void convertTo(std::map<int, std::pair< std::vector<_Ty2>, std::vector<_Ty3> > > &uvxyz)
	{
		int idx = 0;
		for (auto it : m_triangles_)
		{
			for (auto it2 : it.second)
			{
				for (int i = 0; i < 3; ++i)
				{
					uvxyz[idx].first.push_back(_Ty2(it2[9 + i * 2], it2[9 + i * 2 + 1]));
					uvxyz[idx].second.push_back(_Ty3(it2[i * 3], it2[i * 3 + 1], it2[i * 3 + 2]));
				}
				++idx;
			}
		}
	}

	/** @brief Convert the data in a different structure
	*/
	template <typename _Ty2, typename _Ty3>
	void convertTo(
		const cv::Point3f &scale,
		std::map<int, std::pair< std::vector<_Ty2>, std::vector<_Ty3> > > &uvxyz)
	{
		int idx = 0;
		for (auto it : m_triangles_)
		{
			for (auto it2 : it.second)
			{
				for (int i = 0; i < 3; ++i)
				{
					uvxyz[idx].first.push_back(_Ty2(it2[9 + i * 2], it2[9 + i * 2 + 1]));
					uvxyz[idx].second.push_back(_Ty3(it2[i * 3] * scale.x,
						it2[i * 3 + 1] * scale.y, it2[i * 3 + 2] * scale.z));
				}
				++idx;
			}
		}
	}

	/** @brief It is used to set the triangles contents
	*/
	void set_triangle(const std::string &&id,
		std::vector< std::vector< REAL > > &triangles)
	{
		m_triangles_[id] = triangles;
	}


private:

	/** @brief Container with all the triangles from different images.
	Defined as:
	first: name of the mesh
	second: container with triangles
	triangle: X0Y0Z0 X1Y1Z1 X2Y2Z2 U0V1 U1V1 U2V2
	alternatively UV is considered as XY in 2D plane
	*/
	std::map< std::string, std::vector< std::vector< REAL > > > m_triangles_;

};



} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_MESHNAIVE3D_HPP__ */
