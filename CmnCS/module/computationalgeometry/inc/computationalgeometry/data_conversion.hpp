/**
 * @file structure_texture.hpp
 * @brief Contains classes to manage the 3D structure and textures, merge and
 * split.
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


#ifndef CMNCS_COMPUTATIONALGEOMETRY_DATACONVERSION_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_DATACONVERSION_HPP__

#include <limits>       // std::numeric_limits
#include <vector>
#include <map>

#include "mesh3D.hpp"

namespace CmnCS
{
namespace computationalgeometry
{

/** @brief Class to perform the transformation between 3D mapping.

	Class to perform the transformation between 3D mapping.
	It associates the 3D vertex and texture vertex by the same index.
*/
template <typename _Ty2, typename _Ty3>
class DataConversion
{
public:

	/** @brief This class is used to conver the std 3D mesh and texture in a
		2 separated structures.

		This class is used to conver the std 3D mesh and texture in a
		2 separated structures.
	*/
	static void split(const std::map< std::pair<int, int>, _Ty3 > &m_3Dmap,
		float width, float height,
		VertexN<_Ty3> &structure, VertexN<_Ty2> &texture) {
		
		structure.clear();
		texture.clear();

		INDEX index = 0;
		for (auto it = m_3Dmap.begin(); it != m_3Dmap.end(); it++)
		{
			texture.set( index, _Ty2(
				static_cast<float>(it->first.first) / width, 
				static_cast<float>(it->first.second) / height) );
			structure.set( index, it->second );
			++index;
		}
	}

	/** @brief This class is used to conver the std 3D mesh and texture in a
		2 separated structures.

		This class is used to conver the std 3D mesh and texture in a
		2 separated structures.
	*/
	static void merge(VertexN<_Ty3> &structure, VertexN<_Ty2> &texture,
		float width, float height,
		std::map< std::pair<int, int>, _Ty3 > &m_3Dmap) {
		
		m_3Dmap.clear();

		INDEX index = 0;
		for (auto it = structure.pt_data()->begin(); 
			it != structure.pt_data()->end(); it++)
		{
			// Search the element in the texture
			_Ty2 value;
			if (texture.find(it->first, value)) {
				m_3Dmap[ std::pair<int, int>(value.x * size.width, value.y * size.height) ] =
					it->second;
			}
		}
	}


};


} // namespace computationalgeometry
} // namespace CmnCS

#endif /* CMNCS_COMPUTATIONALGEOMETRY_DATACONVERSION_HPP__ */