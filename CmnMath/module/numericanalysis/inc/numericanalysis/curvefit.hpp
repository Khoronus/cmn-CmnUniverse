/* @file curvefit.hpp
* @brief Class to perform a curve fitting.
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

#ifndef CMNMATH_NUMERICALANALYSIS_CURVEFIT_HPP__
#define CMNMATH_NUMERICALANALYSIS_CURVEFIT_HPP__

#include <vector>
#include <algorithm>    // std::for_each
#include <cmath>

#include "cmnmathcore/inc/cmnmathcore/cmnmathcore_headers.hpp"
#include "cmnlibcore/inc/cmnlibcore/exception.hpp"

#include "TCheckedVariable.hpp"

namespace CmnMath
{
namespace numericalanalysis
{

const int CURVEFIT_MIN_VALUES = 3;


///-------------------------------------------------------------------------------------------------
/// \class	CDataPoint
///
/// \brief	Data point class.
///-------------------------------------------------------------------------------------------------
class CDataPoint
{
public:
	CDataPoint() : m_x(0.0), m_y(0.0) {}
	CDataPoint(CMN_64F x, CMN_64F y) : m_x(x), m_y(y) {}
 
	// attributes
protected:
	CMN_64F m_x;
	CMN_64F m_y;
 
public:
	inline CMN_64F x() const { return m_x; }
	inline CMN_64F y() const	{ return m_y; }
	inline void x(CMN_64F x) { m_x = x; }
	inline void y(CMN_64F y) { m_y = y; }
};
 
typedef std::vector<CDataPoint> CDataPointArray;
 
///-------------------------------------------------------------------------------------------------
/// \class	CCurveFit
///
/// \brief	Curve fit.
///-------------------------------------------------------------------------------------------------
class CCurveFit
{
public:
	CCurveFit(void);
	~CCurveFit(void);	
 
	// attributes
protected:
	CDataPointArray m_dataPoints;
 
	TCheckedVariable<CMN_64F> m_a;
	TCheckedVariable<CMN_64F> m_b;
	TCheckedVariable<CMN_64F> m_c;
 
public:

	/// \fn	void CCurveFit::AddPoints( double x, double y )
	///
	/// \brief	Adds the points to 'y'.
	///
	/// \param	x	The double to process.
	/// \param	y	The double to process.
	void AddPoints(CMN_64F x, CMN_64F y);
	/// \fn	void CCurveFit::AddPoints( const CDataPoint &dp )
	///
	/// \brief	Adds the points.
	///
	/// \param	dp	The dp.
	void AddPoints( const CDataPoint &dp );
	/// \fn	void CCurveFit::AddPoints( const CDataPointArray &dpArray )
	///
	/// \brief	Adds the points.
	///
	/// \param	dpArray	Array of dps.
	void AddPoints( const CDataPointArray &dpArray );
 
	// operations
public:


	/*
	y = ax^2 + bx + c

	notation Sjk to mean the sum of x_i^j*y_i^k.
	2a*S40 + 2c*S20 + 2b*S30 - 2*S21 = 0
	2b*S20 + 2a*S30 + 2c*S10 - 2*S11 = 0
	2a*S20 + 2c*S00 + 2b*S10 - 2*S01 = 0

	solve the system of simultaneous equations using Cramer's law

	[ S40  S30  S20 ] [ a ]   [ S21 ]
	[ S30  S20  S10 ] [ b ] = [ S11 ]
	[ S20  S10  S00 ] [ c ]   [ S01 ]

	D = [ S40  S30  S20 ]
	[ S30  S20  S10 ]
	[ S20  S10  S00 ]

	S40(S20*S00 - S10*S10) - S30(S30*S00 - S10*S20) + S20(S30*S10 - S20*S20)

	Da = [ S21  S30  S20 ]
	[ S11  S20  S10 ]
	[ S01  S10  S00 ]

	S21(S20*S00 - S10*S10) - S11(S30*S00 - S10*S20) + S01(S30*S10 - S20*S20)

	Db = [ S40  S21  S20 ]
	[ S30  S11  S10 ]
	[ S20  S01  S00 ]

	S40(S11*S00 - S01*S10) - S30(S21*S00 - S01*S20) + S20(S21*S10 - S11*S20)

	Dc = [ S40  S30  S21 ]
	[ S30  S20  S11 ]
	[ S20  S10  S01 ]

	S40(S20*S01 - S10*S11) - S30(S30*S01 - S10*S21) + S20(S30*S11 - S20*S21)

	*/


	// Gets the a term of the equation ax^2 + bx + c.
	CMN_64F GetATerm();
	
	// Gets the b term of the equation ax^2 + bx + c.
	CMN_64F GetBTerm();
 
	// Gets c term of the equation ax^2 + bx + c.
	CMN_64F GetCTerm();
 
	/// Gets r squared value.
	CMN_64F GetRSquare();
 
protected:
	// helper functions

	// Gets sum if x^nXPower * y^nYPower.
	/// \brief	Gets sum if x^nXPower * y^nYPower.
	///
	/// \param	nXPower	The x power.
	/// \param	nYPower	The y power.
	CMN_64F getSxy(CMN_32S nXPower, CMN_32S nYPower);
	/// \brief	Get y coordinate mean.
	CMN_64F getYMean();
	/// \brief	Gets s stot.
	CMN_64F getSStot();
	/// \brief	Gets s serr.
	CMN_64F getSSerr();
	/// \brief	Gets predicted y coordinate.
	CMN_64F getPredictedY(CMN_64F x);
};

}	// namespace numericalanalysis
}	// namespace CmnMath


#endif /* CMNMATH_NUMERICALANALYSIS_CURVEFIT_HPP__ */
