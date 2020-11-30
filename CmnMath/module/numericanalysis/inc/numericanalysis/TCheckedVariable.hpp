/* @file TCheckedVariable.hpp
* @brief Declares the checked variable class
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
* @author From Codeproject (please find the reference)
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNMATH_NUMERICALANALYSIS_TCHECKEDVARIABLE_HPP__
#define CMNMATH_NUMERICALANALYSIS_TCHECKEDVARIABLE_HPP__

#include <utility>
 
#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"

namespace CmnMath
{
namespace numericalanalysis
{

///-------------------------------------------------------------------------------------------------
/// \class	TCheckedVariable
///
/// \brief	Checked variable class - provides a wrapper arround a variable to allow for checking
///			that it has been initialized or not.
///-------------------------------------------------------------------------------------------------
template<typename T>
class TCheckedVariable : private std::pair<CMN_BOOL,T>
{
public:
 
	TCheckedVariable(void)
	{
		this->first = false;
	}
 
	TCheckedVariable( T t )
	{
		this->first = true;
		this->second = t;
	}
 
	CMN_BOOL IsInitialised() const
	{
		return this->first;
	}
 
	void Reset()
	{
		this->first = false;
	}
 
	const T& operator=( const T &rhs )
	{
		this->first = true;
		this->second = rhs;
		return this->second;
	}
 
	operator T() const
	{
		return this->second;
	}
};

}	// namespace numericalanalysis
}	// namespace CmnMath

#endif /* CMNMATH_NUMERICALANALYSIS_TCHECKEDVARIABLE_HPP__ */
