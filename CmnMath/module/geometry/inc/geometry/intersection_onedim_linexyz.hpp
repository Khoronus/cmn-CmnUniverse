/**
* @file statistics_headers.hpp
* @brief Header of all the files related to the statistics
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

#ifndef CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXYZ_HPP__
#define CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXYZ_HPP__

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** @brief Class to perform interpolations with one dimension geometrical
           structures.

	Class to perform interpolations with one dimension geometrical
	structures.
*/
template <typename _Ty>
class IntersectionOneDimLineXYZ
{
public:

	/*
	Calculate the line segment PaPb that is the shortest route between
	two lines P1P2 and P3P4. Calculate also the values of mua and mub where
	Pa = P1 + mua (P2 - P1)
	Pb = P3 + mub (P4 - P3)
	Return FALSE if no solution exists.
	*/
	static CMN_32S line_line(
		const _Ty& p1, const _Ty& p2, const _Ty& p3, const _Ty& p4,
		_Ty *pa, _Ty *pb,
		CMN_64F *mua, CMN_64F *mub)
	{
		_Ty p13, p43, p21;
		CMN_64F d1343, d4321, d1321, d4343, d2121;
		CMN_64F numer, denom;

		p13.x = p1.x - p3.x;
		p13.y = p1.y - p3.y;
		p13.z = p1.z - p3.z;
		p43.x = p4.x - p3.x;
		p43.y = p4.y - p3.y;
		p43.z = p4.z - p3.z;
		if (std::abs(p43.x) < core::kGEOMETRY_EPS && 
			std::abs(p43.y) < core::kGEOMETRY_EPS &&
			std::abs(p43.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		p21.x = p2.x - p1.x;
		p21.y = p2.y - p1.y;
		p21.z = p2.z - p1.z;
		if (std::abs(p21.x) < core::kGEOMETRY_EPS && 
			std::abs(p21.y) < core::kGEOMETRY_EPS &&
			std::abs(p21.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;

		d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
		d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
		d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
		d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
		d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

		denom = d2121 * d4343 - d4321 * d4321;
		//std::cout << "denom: " << denom << std::endl;
		if (std::abs(denom) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		numer = d1343 * d4321 - d1321 * d4343;

		*mua = numer / denom;
		*mub = (d1343 + d4321 * (*mua)) / d4343;

		pa->x = p1.x + *mua * p21.x;
		pa->y = p1.y + *mua * p21.y;
		pa->z = p1.z + *mua * p21.z;
		pb->x = p3.x + *mub * p43.x;
		pb->y = p3.y + *mub * p43.y;
		pb->z = p3.z + *mub * p43.z;

		return core::kTRUE;
	}

	/*
	Calculate the line segment PaPb that is the shortest route between
	two lines P1P2 and P3P4. Calculate also the values of mua and mub where
	Pa = P1 + mua (P2 - P1)
	Pb = P3 + mub (P4 - P3)
	Return FALSE if no solution exists.
	*/
	static CMN_32S line_linef(
		const _Ty& p1, const _Ty& p2, const _Ty& p3, const _Ty& p4,
		_Ty *pa, _Ty *pb,
		CMN_32F *mua, CMN_32F *mub)
	{
		_Ty p13, p43, p21;
		CMN_32F d1343, d4321, d1321, d4343, d2121;
		CMN_32F numer, denom;

		p13.x = p1.x - p3.x;
		p13.y = p1.y - p3.y;
		p13.z = p1.z - p3.z;
		p43.x = p4.x - p3.x;
		p43.y = p4.y - p3.y;
		p43.z = p4.z - p3.z;
		if (std::abs(p43.x) < core::kGEOMETRY_EPS &&
			std::abs(p43.y) < core::kGEOMETRY_EPS &&
			std::abs(p43.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		p21.x = p2.x - p1.x;
		p21.y = p2.y - p1.y;
		p21.z = p2.z - p1.z;
		if (std::abs(p21.x) < core::kGEOMETRY_EPS &&
			std::abs(p21.y) < core::kGEOMETRY_EPS &&
			std::abs(p21.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;

		d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
		d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
		d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
		d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
		d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

		denom = d2121 * d4343 - d4321 * d4321;
		//std::cout << "denom: " << denom << std::endl;
		if (std::abs(denom) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		numer = d1343 * d4321 - d1321 * d4343;

		*mua = numer / denom;
		*mub = (d1343 + d4321 * (*mua)) / d4343;

		pa->x = p1.x + *mua * p21.x;
		pa->y = p1.y + *mua * p21.y;
		pa->z = p1.z + *mua * p21.z;
		pb->x = p3.x + *mub * p43.x;
		pb->y = p3.y + *mub * p43.y;
		pb->z = p3.z + *mub * p43.z;

		return core::kTRUE;
	}



	/*
		Calculate the line segment PaPb that is the shortest route between
		two lines P1P2 and P3P4. Calculate also the values of mua and mub where
		Pa = P1 + mua (P2 - P1)
		Pb = P3 + mub (P4 - P3)
		Return FALSE if no solution exists.
	*/
	static CMN_32S line_line_3d_nocheck(
		const _Ty& p1, const _Ty& p2, const _Ty& p3, const _Ty& p4,
		_Ty *pa, _Ty *pb,
		CMN_64F *mua, CMN_64F *mub)
	{
		_Ty p13, p43, p21;
		CMN_64F d1343, d4321, d1321, d4343, d2121;
		CMN_64F numer, denom;

		p13.x = p1.x - p3.x;
		p13.y = p1.y - p3.y;
		p13.z = p1.z - p3.z;
		p43.x = p4.x - p3.x;
		p43.y = p4.y - p3.y;
		p43.z = p4.z - p3.z;
		if (std::abs(p43.x) < core::kGEOMETRY_EPS &&
			std::abs(p43.y) < core::kGEOMETRY_EPS &&
			std::abs(p43.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		p21.x = p2.x - p1.x;
		p21.y = p2.y - p1.y;
		p21.z = p2.z - p1.z;
		if (std::abs(p21.x) < core::kGEOMETRY_EPS &&
			std::abs(p21.y) < core::kGEOMETRY_EPS &&
			std::abs(p21.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;

		d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
		d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
		d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
		d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
		d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

		denom = d2121 * d4343 - d4321 * d4321;
		//std::cout << "denom: " << denom << std::endl;
		//if (std::abs(denom) < core::kGEOMETRY_EPS)
		//	return core::kFALSE;
		if (std::abs(denom) == 0)
			return core::kFALSE;
		numer = d1343 * d4321 - d1321 * d4343;

		*mua = numer / denom;
		*mub = (d1343 + d4321 * (*mua)) / d4343;

		pa->x = p1.x + *mua * p21.x;
		pa->y = p1.y + *mua * p21.y;
		pa->z = p1.z + *mua * p21.z;
		pb->x = p3.x + *mub * p43.x;
		pb->y = p3.y + *mub * p43.y;
		pb->z = p3.z + *mub * p43.z;

		return core::kTRUE;
	}

	/*
		Calculate the line segment PaPb that is the shortest route between
		two lines P1P2 and P3P4. Calculate also the values of mua and mub where
		Pa = P1 + mua (P2 - P1)
		Pb = P3 + mub (P4 - P3)
		Return FALSE if no solution exists.
	*/
	static CMN_32S line_line_3d_nocheckf(
		const _Ty& p1, const _Ty& p2, const _Ty& p3, const _Ty& p4,
		_Ty *pa, _Ty *pb,
		CMN_32F *mua, CMN_32F *mub)
	{
		_Ty p13, p43, p21;
		CMN_32F d1343, d4321, d1321, d4343, d2121;
		CMN_32F numer, denom;

		p13.x = p1.x - p3.x;
		p13.y = p1.y - p3.y;
		p13.z = p1.z - p3.z;
		p43.x = p4.x - p3.x;
		p43.y = p4.y - p3.y;
		p43.z = p4.z - p3.z;
		if (std::abs(p43.x) < core::kGEOMETRY_EPS &&
			std::abs(p43.y) < core::kGEOMETRY_EPS &&
			std::abs(p43.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;
		p21.x = p2.x - p1.x;
		p21.y = p2.y - p1.y;
		p21.z = p2.z - p1.z;
		if (std::abs(p21.x) < core::kGEOMETRY_EPS &&
			std::abs(p21.y) < core::kGEOMETRY_EPS &&
			std::abs(p21.z) < core::kGEOMETRY_EPS)
			return core::kFALSE;

		d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
		d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
		d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
		d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
		d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

		denom = d2121 * d4343 - d4321 * d4321;
		//std::cout << "denom: " << denom << std::endl;
		//if (std::abs(denom) < core::kGEOMETRY_EPS)
		//	return core::kFALSE;
		if (std::abs(denom) == 0)
			return core::kFALSE;
		numer = d1343 * d4321 - d1321 * d4343;

		*mua = numer / denom;
		*mub = (d1343 + d4321 * (*mua)) / d4343;

		pa->x = p1.x + *mua * p21.x;
		pa->y = p1.y + *mua * p21.y;
		pa->z = p1.z + *mua * p21.z;
		pb->x = p3.x + *mub * p43.x;
		pb->y = p3.y + *mub * p43.y;
		pb->z = p3.z + *mub * p43.z;

		return core::kTRUE;
	}

};

} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_INTERSECTIONONEDIMLINEXYZ_HPP__ */
