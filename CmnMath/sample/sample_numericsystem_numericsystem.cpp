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
* @version 0.2.0.0
*
*/

#include <iostream>
#include <string>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "numericsystem/inc/numericsystem/numericsystem_headers.hpp"

namespace
{

void test_angleconversion()
{
	CmnMath::CMN_64F angle_grad = 17;
	CmnMath::CMN_64F angle_rad = CmnMath::numericsystem::AngleConversion<CmnMath::CMN_64F>::ToRad(angle_grad);
	CmnMath::CMN_64F angle_grad2 = CmnMath::numericsystem::AngleConversion<CmnMath::CMN_64F>::ToGrad(angle_rad);
	std::cout << "Angle conversion: " << angle_grad << " " << angle_rad << " " 
		<< angle_grad2 << std::endl;
}

void test_anglebetween()
{
	CmnMath::CMN_64F angle_target1 = 17;
	CmnMath::CMN_64F angle_target2 = 170;
	CmnMath::CMN_64F angle1 = 5;
	CmnMath::CMN_64F angle2 = 150;
	std::cout << "Test angle between " << angle1 << " <= " << angle_target1 <<
		" <= " << angle2 << " is between: " << CmnMath::numericsystem::AngleBetween<CmnMath::CMN_64F>::two_angles(angle_target1, angle1, angle2) << std::endl;
	std::cout << "Test angle between " << angle1 << " <= " << angle_target2 <<
		" <= " << angle2 << " is between: " << CmnMath::numericsystem::AngleBetween<CmnMath::CMN_64F>::two_angles(angle_target2, angle1, angle2) << std::endl;
}

void test_quaternionNaive() {
	CmnMath::numericsystem::QuaternionNaive qn;
}


void test()
{
	CmnMath::algebralinear::Vector3f origin(0,0,0), src(5,0,0), 
		angle(0, CmnMath::core::kPIf / 2, 0), dst;
	CmnMath::numericsystem::PointTransformation<CmnMath::algebralinear::Vector3f>::PointRotation(
		origin, src, angle, dst);
	std::cout << src << " " << origin << " " << angle << " " << dst << 
		std::endl;

	CmnMath::numericsystem::Quaternion < CmnMath::algebralinear::Vector3f> q1(0, 0, 0), q2(1, 2, 3);
	q1.invert();
	CmnMath::numericsystem::Quaternion < CmnMath::algebralinear::Vector3f> q = q1 * q2;
	std::cout << "q1: " << q1.elem[0] << " " << q1.elem[1] << " " << q1.elem[2] << " " << q1.elem[3] << std::endl;
	std::cout << "q2: " << q2.elem[0] << " " << q2.elem[1] << " " << q2.elem[2] << " " << q2.elem[3] << std::endl;
	std::cout << "q: " << q.elem[0] << " " << q.elem[1] << " " << q.elem[2] << " " << q.elem[3] << std::endl;
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample NumericSystem" << std::endl;

	test();
	test_angleconversion();
	test_anglebetween();
	// TODO
	test_quaternionNaive();
}


