/**
* @file generator_zerodim_icosphere.hpp
* @brief Header of the classes and functions that generates 3D structures.
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
* @original author Eigen Library
* @bug No known bugs.
* @version 0.2.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_GENERATORZERODIM_ICOSPHERE_HPP__
#define CMNMATH_GEOMETRY_GENERATORZERODIM_ICOSPHERE_HPP__

#include <iostream>
#include <vector>
#include <map>

#include "vector_operation_xyz.hpp"

//--------------------------------------------------------------------------------
// icosahedron data
//--------------------------------------------------------------------------------
#define CMNMATH_ICOSPHERE_X .525731112119133606
#define CMNMATH_ICOSPHERE_Z .850650808352039932

namespace CmnMath
{
namespace geometry
{

static CMN_32F vdata[12][3] = {
		{ -CMNMATH_ICOSPHERE_X, 0.0, CMNMATH_ICOSPHERE_Z }, { CMNMATH_ICOSPHERE_X, 0.0, CMNMATH_ICOSPHERE_Z }, { -CMNMATH_ICOSPHERE_X, 0.0, -CMNMATH_ICOSPHERE_Z }, { CMNMATH_ICOSPHERE_X, 0.0, -CMNMATH_ICOSPHERE_Z },
		{ 0.0, CMNMATH_ICOSPHERE_Z, CMNMATH_ICOSPHERE_X }, { 0.0, CMNMATH_ICOSPHERE_Z, -CMNMATH_ICOSPHERE_X }, { 0.0, -CMNMATH_ICOSPHERE_Z, CMNMATH_ICOSPHERE_X }, { 0.0, -CMNMATH_ICOSPHERE_Z, -CMNMATH_ICOSPHERE_X },
		{ CMNMATH_ICOSPHERE_Z, CMNMATH_ICOSPHERE_X, 0.0 }, { -CMNMATH_ICOSPHERE_Z, CMNMATH_ICOSPHERE_X, 0.0 }, { CMNMATH_ICOSPHERE_Z, -CMNMATH_ICOSPHERE_X, 0.0 }, { -CMNMATH_ICOSPHERE_Z, -CMNMATH_ICOSPHERE_X, 0.0 }
};

static CMN_32F tindices[20][3] = {
		{ 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },
		{ 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
		{ 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
		{ 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 } };
//--------------------------------------------------------------------------------


/** @brief
	https://github.com/vistle/eigen/blob/master/demos/opengl/icosphere.cpp
	http://www.iquilezles.org/www/articles/patchedsphere/patchedsphere.htm
	http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
*/
template <typename _Ty3>
class GeneratorZeroDimIcoSphere
{
public:

	/** @brief 'ctor
	*/
	GeneratorZeroDimIcoSphere(CMN_32U levels = 1) {
		// init with an icosahedron
		for (CMN_32S i = 0; i < 12; i++)
			mVertices.push_back(_Ty3(vdata[i][0], vdata[i][1], vdata[i][2]));
		//mVertices.push_back(Map<Vector3f>(vdata[i]));
		mIndices.push_back(new std::vector<CMN_32S>);
		std::vector<CMN_32S>& indices = *mIndices.back();
		for (CMN_32S i = 0; i < 20; i++)
		{
			for (CMN_32S k = 0; k < 3; k++)
				indices.push_back(tindices[i][k]);
		}
		mListIds.push_back(0);

		while (mIndices.size()<levels)
			_subdivide();
	}
	~GeneratorZeroDimIcoSphere() {
		for (auto &it : mIndices) {
			delete it;
		}
	}

	const std::vector<_Ty3>& vertices() const { return mVertices; }
	const std::vector<CMN_32S>& indices(CMN_32S level) const {
		while (level >= CMN_32S(mIndices.size()))
			const_cast<IcoSphere*>(this)->_subdivide();
		return *mIndices[level];
	}

	void vertex_index(CMN_32S level,
		std::vector<_Ty3> &vertices,
		std::vector<CMN_32S> &index) {

		while (level >= CMN_32S(mIndices.size()))
			const_cast<GeneratorZeroDimIcoSphere*>(this)->_subdivide();
		//std::cout << " mVertices: " << mVertices.size() << std::endl;
		//std::cout << " mIndices: " << mIndices.size() << std::endl;
		//std::cout << " mListIds: " << mListIds.size() << std::endl;

		vertices = mVertices;

		CMN_32S iLevel = 0;
		for (auto &it : mIndices) {
			//std::cout << "+++ : " << it->size() << std::endl;
			if (iLevel != level) {
				++iLevel;
				continue;
			}
			for (auto &it2 : *it) {
				index.push_back(it2);
			}
			++iLevel;
		}
	}

protected:
	std::vector<_Ty3> mVertices;
	std::vector<std::vector<CMN_32S>*> mIndices;
	std::vector<CMN_32S> mListIds;

	void _subdivide() {
		typedef CMN_64U Key;
		std::map<Key, CMN_32S> edgeMap;
		const std::vector<CMN_32S>& indices = *mIndices.back();
		mIndices.push_back(new std::vector<CMN_32S>);
		std::vector<CMN_32S>& refinedIndices = *mIndices.back();
		int end = indices.size();
		for (CMN_32S i = 0; i<end; i += 3)
		{
			CMN_32S ids0[3],  // indices of outer vertices
				    ids1[3];  // indices of edge vertices
			for (CMN_32S k = 0; k<3; ++k)
			{
				CMN_32S k1 = (k + 1) % 3;
				CMN_32S e0 = indices[i + k];
				CMN_32S e1 = indices[i + k1];
				ids0[k] = e0;
				if (e1>e0)
					std::swap(e0, e1);
				Key edgeKey = Key(e0) | (Key(e1) << 32);
				std::map<Key, CMN_32S>::iterator it = edgeMap.find(edgeKey);
				if (it == edgeMap.end()) {
					ids1[k] = mVertices.size();
					edgeMap[edgeKey] = ids1[k];
					_Ty3 psum = mVertices[e0] + mVertices[e1];
					//CMN_32F psum_magnitude = cv::norm(psum);
					CMN_32F psum_magnitude = VectorOperationXYZ<_Ty3>::magnitude_3d<CMN_32F>(psum);
					_Ty3 psum_norm = psum * (1.0f / psum_magnitude);
					//mVertices.push_back((mVertices[e0] + mVertices[e1]).normalized());
					mVertices.push_back(psum_norm);
				} else {
					ids1[k] = it->second;
				}
			}
			refinedIndices.push_back(ids0[0]); refinedIndices.push_back(ids1[0]); refinedIndices.push_back(ids1[2]);
			refinedIndices.push_back(ids0[1]); refinedIndices.push_back(ids1[1]); refinedIndices.push_back(ids1[0]);
			refinedIndices.push_back(ids0[2]); refinedIndices.push_back(ids1[2]); refinedIndices.push_back(ids1[1]);
			refinedIndices.push_back(ids1[0]); refinedIndices.push_back(ids1[1]); refinedIndices.push_back(ids1[2]);
		}
		mListIds.push_back(0);
	}
};

} // namespace geometry
} // namespace CmnMath

#endif // CMNMATH_GEOMETRY_GENERATORZERODIM_ICOSPHERE_HPP__