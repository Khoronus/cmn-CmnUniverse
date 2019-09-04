/* @file Convert2D3D.hpp
 * @brief Class to convert a 2D plane in 3D space
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */

#ifndef CMNCS_COMPUTATIONALGEOMETRY_CONVERTPLANE2D3D_HPP__
#define CMNCS_COMPUTATIONALGEOMETRY_CONVERTPLANE2D3D_HPP__

namespace CmnCS
{
namespace computationalgeometry
{

/** @brief Class to perform a transformation from 2D to 3D space.

Class to perform a transformation from 2D to 3D space
xy is consider an image space (or any 2D scale)
uv is a texture space [0, 1]
xyz is a 3D euclidean space

*/
class ConvertPlane2D3D
{
public:

	/** @brief It converts a 2D space in uv texture space.
	  
	    It converts a 2D space in uv texture space. It is expected to be a
		plane without rotations.
	*/
	template <typename _Ty2, typename Real>
	static void map_xy_uv(const _Ty2 &src, Real minx, Real miny, Real maxx,
		Real maxy, _Ty2 &dst) {
		dst.x = (src.x - minx) / (maxx - minx);
		dst.y = (src.y - miny) / (maxy - miny);
	}

	/** @brief It maps a vertex point in a 3D position in a fixed condition

	0           1                     -0.5           0.5

	uv               =====>


	1           1                      0.5           0.5

	No other assumptions are taken in consideration.
	For more complex structures, please check the SphericalView series
	*/
	template <typename _Ty2, typename _Ty3, typename Real = float>
	static void map_uv_xyz(const _Ty2 &src, Real scale, Real ydist, 
		_Ty3 &dst) {
		dst.x = (src.x - 0.5) * scale;
		dst.y = ydist;
		dst.z = (src.y - 0.5) * scale;
	}
};

} // namespace computationalgeometry
} // namespace CmnCS


#endif /* CMNCS_COMPUTATIONALGEOMETRY_CONVERTPLANE2D3D_HPP__ */