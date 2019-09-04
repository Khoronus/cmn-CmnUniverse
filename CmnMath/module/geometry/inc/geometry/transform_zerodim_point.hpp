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

#ifndef CMNMATH_GEOMETRY_TRANSFORMZERODIMPOINT_HPP__
#define CMNMATH_GEOMETRY_TRANSFORMZERODIMPOINT_HPP__

#include <cmath>
#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace CmnMath
{
namespace geometry
{


/** Class to provide the geometric transformations
@remarks
static functions
angles must be express in radians
*/
class TransformZeroDimPoint
{
public:


	// ######################
	//	3D TRANSFORMATION
	// ######################

	/** Generate a rotation matrix given the 3 angles
	*/
	static void GetRotationMatrix44(CMN_32F *R, CMN_32F *angle)
	{
		R[0] = std::cos(angle[1]) * std::cos(angle[0]);
		R[1] = -std::cos(angle[2]) * std::sin(angle[0]) + std::sin(angle[2]) * std::sin(angle[1]) * std::cos(angle[0]);
		R[2] = std::sin(angle[2]) * std::sin(angle[0]) + std::cos(angle[2]) * std::sin(angle[1]) * std::cos(angle[0]);
		R[3] = 0;

		R[4] = std::cos(angle[1]) * std::sin(angle[0]);
		R[5] = std::cos(angle[2]) * std::cos(angle[0]) + std::sin(angle[2]) * std::sin(angle[1]) * std::sin(angle[0]);
		R[6] = -std::sin(angle[2]) * std::cos(angle[0]) + std::cos(angle[2]) * std::sin(angle[1]) * std::sin(angle[0]);
		R[7] = 0;

		R[8] = -std::sin(angle[1]);
		R[9] = std::sin(angle[2]) * std::cos(angle[1]);
		R[10] = std::cos(angle[2]) * std::cos(angle[1]);
		R[11] = 0;

		R[12] = 0;
		R[13] = 0;
		R[14] = 0;
		R[15] = 1;
	}

	/** This function rotate a point which center is the origin to anoter
	*/
	static void RotatePoint(CMN_32F *angle, CMN_32F *initial_position, CMN_32F *final_position)
	{
		CMN_32F R[16];	// Contains the transformation matrix
		GetRotationMatrix44(R, angle);
		algebralinear::MatrixOperation::mat_mul(R, initial_position, final_position, 4, 4, 4, 1);
	}

	/** This function rotate a point which center is not the origin
	@remarks
	Use only for the Camera System. Rotate before the PIV and observed point to counterbalance the pitch. Only pitch angle is used
	*/
	static void RotatePointNoOrigin(CMN_32F *angle, CMN_32F *origin, CMN_32F *initial_position, CMN_32F *final_position)
	{
		CMN_32F R[16];	// Contains the transformation matrix
		CMN_32F tmp[4];
		GetRotationMatrix44(R, angle);

		for (CMN_32S i = 0; i < 4; ++i)
			tmp[i] = initial_position[i] - origin[i];

		algebralinear::MatrixOperation::mat_mul(R, tmp, final_position, 4, 4, 4, 1);

		for (CMN_32S i = 0; i < 4; ++i)
			final_position[i] += origin[i];
	}


	/** This function rotate a point which center is not the origin
	@remarks
	Use only for the Camera System. Rotate before the PIV and observed point to counterbalance the pitch. Only pitch angle is used
	*/
	static void RotateTranslatePointNoOrigin(CMN_32F *angle, CMN_32F *origin, CMN_32F *initial_position, CMN_32F *final_position)
	{
		CMN_32F R[16];	// Contains the transformation matrix
		CMN_32F tmp[4];
		GetRotationMatrix44(R, angle);

		for (CMN_32S i = 0; i < 4; i++)
			tmp[i] = initial_position[i] - origin[i];

		algebralinear::MatrixOperation::mat_mul(R, tmp, final_position, 4, 4, 4, 1);
	}


	/** Get the transformation matrix
	@remarks
	Given the 3 rotation axes (x, y, z) return the transformation matrix
	It can be used with OpenGL or Illusion
	*/
	template <typename T>
	static void GetRotationMatrix34(T *R, CMN_32F *angle)
	{
		// New angles
		R[0] = cos(angle[1]) * cos(angle[0]);
		R[1] = -cos(angle[2]) * sin(angle[0]) + sin(angle[2]) * sin(angle[1]) * cos(angle[0]);
		R[2] = sin(angle[2]) * sin(angle[0]) + cos(angle[2]) * sin(angle[1]) * cos(angle[0]);
		R[3] = 0;

		R[4] = cos(angle[1]) * sin(angle[0]);
		R[5] = cos(angle[2]) * cos(angle[0]) + sin(angle[2]) * sin(angle[1]) * sin(angle[0]);
		R[6] = -sin(angle[2]) * cos(angle[0]) + cos(angle[2]) * sin(angle[1]) * sin(angle[0]);
		R[7] = 0;

		R[8] = -sin(angle[1]);
		R[9] = sin(angle[2]) * cos(angle[1]);
		R[10] = cos(angle[2]) * cos(angle[1]);
		R[11] = 0;
	}

	template <typename T>
	static void GetRotationMatrix33(T *R, CMN_32F *angle)
	{
		// New angles
		R[0] = cos(angle[1]) * cos(angle[0]);
		R[1] = -cos(angle[2]) * sin(angle[0]) + sin(angle[2]) * sin(angle[1]) * cos(angle[0]);
		R[2] = sin(angle[2]) * sin(angle[0]) + cos(angle[2]) * sin(angle[1]) * cos(angle[0]);

		R[3] = cos(angle[1]) * sin(angle[0]);
		R[4] = cos(angle[2]) * cos(angle[0]) + sin(angle[2]) * sin(angle[1]) * sin(angle[0]);
		R[5] = -sin(angle[2]) * cos(angle[0]) + cos(angle[2]) * sin(angle[1]) * sin(angle[0]);

		R[6] = -sin(angle[1]);
		R[7] = sin(angle[2]) * cos(angle[1]);
		R[8] = cos(angle[2]) * cos(angle[1]);
	}

};


} // namespace geometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRY_TRANSFORMZERODIMPOINT_HPP__ */
