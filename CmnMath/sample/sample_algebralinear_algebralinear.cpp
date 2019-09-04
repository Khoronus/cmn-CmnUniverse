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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include "algebralinear/inc/algebralinear/algebralinear_headers.hpp"

namespace
{

void test()
{
	CmnMath::algebralinear::Vector2f v(1,2);
	// Square root
	std::cout << "SqrRoot(ulong fast): " <<
		CmnMath::algebralinear::AppriximateCompute::square_root(12345) << 
		" invSqr(CMN_32F fast): " << CmnMath::algebralinear::AppriximateCompute::square_root(12345) <<
		" expected (slow): " << std::sqrt(12345.0) << std::endl;
	// Saturation
	std::cout << "Saturation: " <<
		CmnMath::algebralinear::Saturation::clamp<CmnMath::CMN_32F>(13, 5, 10) <<
		" expected: 10" << std::endl;

	// Shrink
	std::cout << "Shrink::Garrot: " << 
		CmnMath::algebralinear::Shrink::Garrot(13.65f, 2.0f) << std::endl;
	std::cout << "Shrink::hard: " <<
		CmnMath::algebralinear::Shrink::hard(13.65f, 2.0f) << std::endl;
	std::cout << "Shrink::sgn: " <<
		CmnMath::algebralinear::Shrink::sgn(13.65f) << std::endl;
	std::cout << "Shrink::soft: " <<
		CmnMath::algebralinear::Shrink::soft(13.65f, 2.0f) << std::endl;

	// Quadric Equation
	CmnMath::CMN_32F a = 1, b = 2, c = 3;
	std::vector<CmnMath::CMN_32F> _x, _i;
	int s = CmnMath::algebralinear::QuadricEquation::solvef(a, b, c, _x, _i);
	std::cout << "s: ";
	for (size_t i = 0; i < _x.size(); ++i) {
		std::cout << "x: " << _x[i] << " ";
		if (_i.size() < i) std::cout << "i: " << _i[i] << " ";
	}
	std::cout << std::endl;
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample NumericSystem" << std::endl;
	test();
}


