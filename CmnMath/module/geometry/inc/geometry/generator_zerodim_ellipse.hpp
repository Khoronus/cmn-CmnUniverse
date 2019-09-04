/**
* @file generator_zerodim_ellipse.hpp
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNMATH_GEOMETRY_GENERATORZERODIM_ELLIPSE_HPP__
#define CMNMATH_GEOMETRY_GENERATORZERODIM_ELLIPSE_HPP__

#include <set>
#include <vector>
#include <map>
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{

/** @brief Class to manage an Ellipsoid mesh.

Class to manage an Ellipsoid mesh.
*/
template <typename _Ty>
class GeneratorZeroDimEllipse
{
public:

	/** @brief Create a complete ellipsoid set of vertex points.

	Create a complete ellipsoid set of vertex points.
	@param[in] a Horizontal X axe.
	@param[in] b Vertical Y axe.
	@param[in] c Depth Z axe.
	@param[out] m_points Set of points which defines the ellipsoid mesh.
	first_first: x coordinate.
	first_second_first: y coordinate.
	first_second_second: z coordinate.
	*/
	static void CreateFullEllipsoidPoints(CMN_64F a, CMN_64F b, CMN_64F c,
		int kI, int kJ, _Ty &minRange, _Ty &maxRange,
		std::map< std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >, int > &m_points)
	{
		m_points.clear();

		for (int i = 0; i <= kI; i++)
		{
			//m_3Dmap.clear();
			for (int j = 0; j <= kJ; j++)
			{
				CMN_64F u_bin = core::kPI * 2 / kI;
				CMN_64F v_bin = core::kPI * 2 / kJ;
				CMN_64F u = j * u_bin - core::kPI; // x
				CMN_64F v = i * v_bin - core::kPI;  // y
				_Ty p(a * std::sin(u) * std::cos(v),
					b * std::sin(u) * std::sin(v),
					c * std::cos(u));

				if (p.x >= minRange.x && p.y >= minRange.y && p.z >= minRange.z &&
					p.x <= maxRange.x && p.y <= maxRange.y && p.z <= maxRange.z)
				{
					// Check if the point already exist
					m_points[
						std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >(
							p.x, std::pair< CMN_64F, CMN_64F >(p.y, p.z))] = 1;
				}
			}
		}
	}


	/** @brief Create a complete ellipsoid set of vertex points.

	Create a complete ellipsoid set of vertex points.
	@param[in] a Horizontal X axe.
	@param[in] b Vertical Y axe.
	@param[in] c Depth Z axe.
	@param[out] m_points Set of points which defines the ellipsoid mesh.
	first_first: x coordinate.
	first_second_first: y coordinate.
	first_second_second: z coordinate.
	*/
	static void CreateFullEllipsoidPoints(CMN_64F a, CMN_64F b, CMN_64F c,
		std::map< std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >, int > &m_points)
	{
		m_points.clear();

		//int kI = 200, kJ = 200; 300  300
		//int kI = 100, kJ = 100;
		int kI = 200, kJ = 200;
		for (int i = 0; i <= kI; i++)
		{
			//m_3Dmap.clear();
			for (int j = 0; j <= kJ; j++)
			{
				CMN_64F u_bin = core::kPI * 2 / kI;
				CMN_64F v_bin = core::kPI * 2 / kJ;
				CMN_64F u = j * u_bin - core::kPI; // x
				CMN_64F v = i * v_bin - core::kPI;  // y
				_Ty p(a * std::sin(u) * std::cos(v),
					b * std::sin(u) * std::sin(v),
					c * std::cos(u));
				// Check if the point already exist
				m_points[
					std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >(
						p.x, std::pair< CMN_64F, CMN_64F >(p.y, p.z))] = 1;
			}
		}
	}


	/** @brief Create a complete ellipsoid set of vertex points.

	Create a complete ellipsoid set of vertex points.
	@param[in] a Horizontal X axe.
	@param[in] b Vertical Y axe.
	@param[in] c Depth Z axe.
	@param[out] m_points Set of points which defines the ellipsoid mesh.
	first_first: x coordinate.
	first_second_first: y coordinate.
	first_second_second: z coordinate.
	*/
	static void CreateFullEllipsoidPoints(CMN_64F a, CMN_64F b, CMN_64F c,
		int kI, int kJ,
		std::set< std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > > > &s_points)
	{
		s_points.clear();

		//int kI = 200, kJ = 200; 300  300
		//int kI = 100, kJ = 100;
		//int kI = 200, kJ = 200;
		for (int i = 0; i <= kI; i++)
		{
			//m_3Dmap.clear();
			for (int j = 0; j <= kJ; j++)
			{
				CMN_64F u_bin = core::kPI * 2 / kI;
				CMN_64F v_bin = core::kPI * 2 / kJ;
				CMN_64F u = j * u_bin - core::kPI; // x
				CMN_64F v = i * v_bin - core::kPI;  // y
				_Ty p(a * std::sin(u) * std::cos(v),
					b * std::sin(u) * std::sin(v),
					c * std::cos(u));
				// Check if the point already exist
				s_points.insert(
					std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >(
					p.x, std::pair< CMN_64F, CMN_64F >(p.y, p.z))
					);
			}
		}
	}

	/** @brief Create a complete half ellipsoid set of vertex points.

	Create a complete half ellipsoid set of vertex points.
	@param[in] a Horizontal X axe.
	@param[in] b Vertical Y axe.
	@param[in] c Depth Z axe.
	@param[out] m_points Set of points which defines the ellipsoid mesh.
	first_first: x coordinate.
	first_second_first: y coordinate.
	first_second_second: z coordinate.
	*/
	static void CreateHalfEllipsoidPoints(CMN_64F a, CMN_64F b, CMN_64F c,
		std::map< std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >, int > &m_points)
	{
		m_points.clear();

		int kI = 100, kJ = 100;
		for (int i = 0; i <= kI; i++)
		{
			//m_3Dmap.clear();
			for (int j = 0; j <= kJ; j++)
			{
				CMN_64F u_bin = core::kPI / kI;
				CMN_64F v_bin = core::kPI * 2 / kJ;
				CMN_64F u = i * u_bin - core::kPI / 2;
				CMN_64F v = j * v_bin - core::kPI;
				_Ty p(a * std::sin(u) * std::cos(v),
					-c * std::cos(u),
					b * std::sin(u) * std::sin(v));
				// Check if the point already exist
				m_points[
					std::pair< CMN_64F, std::pair< CMN_64F, CMN_64F > >(
						p.x, std::pair< CMN_64F, CMN_64F >(p.y, p.z))] = 1;
			}
		}
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_GENERATORZERODIM_ELLIPSE_HPP__ */
