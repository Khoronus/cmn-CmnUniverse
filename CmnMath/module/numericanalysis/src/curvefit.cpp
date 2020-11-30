/* @file curvefit.hpp
* @brief Body of the curve fit class
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.IN NO EVENT SHALL THE AUTHOR / AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author From Codeproject(please find the reference)
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include "numericanalysis/inc/numericanalysis/curvefit.hpp"
#include "cmnlibcore/inc/cmnlibcore/exception.hpp"

namespace CmnMath
{
namespace numericalanalysis
{
 
//-----------------------------------------------------------------------------
CCurveFit::CCurveFit(void)
{
}
//-----------------------------------------------------------------------------
CCurveFit::~CCurveFit(void)
{
}
//-----------------------------------------------------------------------------
void CCurveFit::AddPoints(double x, double y)
{
	AddPoints( CDataPoint( x, y ) );
}
//-----------------------------------------------------------------------------
void CCurveFit::AddPoints(const CDataPoint &dp)
{
	m_dataPoints.push_back( dp );
	m_a.Reset();
	m_b.Reset();
	m_c.Reset();
}
//-----------------------------------------------------------------------------
void CCurveFit::AddPoints(const CDataPointArray &dpArray)
{
	m_dataPoints.insert( 
		m_dataPoints.rbegin().base(), 
		dpArray.begin(),
		dpArray.end() );
 
	m_a.Reset();
	m_b.Reset();
	m_c.Reset();
}
//-----------------------------------------------------------------------------
double CCurveFit::GetATerm()
{
	if (m_dataPoints.size() < CURVEFIT_MIN_VALUES)
	{
		std::string err_msg = "Insufficient pairs of co-ordinates";
		throw CmnLib::core::Exception(100, err_msg, __FILE__, __LINE__);
	}
 
	if( m_a.IsInitialised() )
		return m_a;
 
	// notation sjk to mean the sum of x_i^j_i^k.
	double s40 = getSxy( 4, 0 );
	double s30 = getSxy( 3, 0 );
	double s20 = getSxy( 2, 0 );
	double s10 = getSxy( 1, 0 );
	double s00 = (double)m_dataPoints.size();
 
	double s21 = getSxy( 2, 1 );
	double s11 = getSxy( 1, 1 );
	double s01 = getSxy( 0, 1 );
 
	// Da / D
	m_a = (s21 * (s20 * s00 - s10 * s10) - s11 * (s30 * s00 - s10 * s20) + s01 * (s30 * s10 - s20 * s20))
				/
				(s40 * (s20 * s00 - s10 * s10) - s30 * (s30 * s00 - s10 * s20) + s20 * (s30 * s10 - s20 * s20));
 
	return m_a;
}
//-----------------------------------------------------------------------------
double CCurveFit::GetBTerm()
{
	if (m_dataPoints.size() < CURVEFIT_MIN_VALUES)
	{
		throw std::exception( "Insufficient pairs of co-ordinates" );
	}
 
	if( m_b.IsInitialised() )
		return m_b;
 
	// notation sjk to mean the sum of x_i^j_i^k.
	double s40 = getSxy( 4, 0 );
	double s30 = getSxy( 3, 0 );
	double s20 = getSxy( 2, 0 );
	double s10 = getSxy( 1, 0 );
	double s00 = (double)m_dataPoints.size();
 
	double s21 = getSxy( 2, 1 );
	double s11 = getSxy( 1, 1 );
	double s01 = getSxy( 0, 1 );
 
	//   Db / D
	m_b = (s40 * (s11 * s00 - s01 * s10) - s30 * (s21 * s00 - s01 * s20) + s20 * (s21 * s10 - s11 * s20))
		/
		(s40 * (s20 * s00 - s10 * s10) - s30 * (s30 * s00 - s10 * s20) + s20 * (s30 * s10 - s20 * s20));
 
	return m_b;
}
//-----------------------------------------------------------------------------
double CCurveFit::GetCTerm()
{
	if (m_dataPoints.size() < CURVEFIT_MIN_VALUES)
	{
		throw std::exception( "Insufficient pairs of co-ordinates" );
	}
 
	if( m_c.IsInitialised() )
		return m_c;
 
	// notation sjk to mean the sum of x_i^j_i^k.
	double s40 = getSxy( 4, 0 );
	double s30 = getSxy( 3, 0 );
	double s20 = getSxy( 2, 0 );
	double s10 = getSxy( 1, 0 );
	double s00 = (double)m_dataPoints.size();
 
	double s21 = getSxy( 2, 1 );
	double s11 = getSxy( 1, 1 );
	double s01 = getSxy( 0, 1 );
 
	//   Dc / D
	m_c = (s40*(s20 * s01 - s10 * s11) - s30*(s30 * s01 - s10 * s21) + s20*(s30 * s11 - s20 * s21))
			/
			(s40 * (s20 * s00 - s10 * s10) - s30 * (s30 * s00 - s10 * s20) + s20 * (s30 * s10 - s20 * s20));
 
	return m_c;
}
//-----------------------------------------------------------------------------
double CCurveFit::GetRSquare()
{
	if (m_dataPoints.size() < CURVEFIT_MIN_VALUES)
	{
		throw std::exception( "Insufficient pairs of co-ordinates" );
	}
 
	return (1.0 - getSSerr() / getSStot());
 
}
//-----------------------------------------------------------------------------
double CCurveFit::getSxy(int nXPower, int nYPower)
{
	double dSxy = 0.0;
 
	std::for_each( m_dataPoints.begin(), m_dataPoints.end(),
		[ &dSxy, nXPower, nYPower ]( const CDataPoint &dp )
	{
		dSxy += pow( dp.x(), nXPower ) * pow( dp.y(), nYPower );
	} );
 
	return dSxy;
}
//-----------------------------------------------------------------------------
double CCurveFit::getYMean()
{
	double dTotal = 0.0;
	int nCount = 0;
	std::for_each( m_dataPoints.begin(), m_dataPoints.end(),
		[ &dTotal, &nCount ]( const CDataPoint &dp )
	{
		dTotal += dp.y();
		nCount++;
	} );
 
	return dTotal / nCount;
}
//-----------------------------------------------------------------------------
double CCurveFit::getSStot()
{
	double ssTot = 0.0;
	double dYMean = getYMean();
 
	std::for_each( m_dataPoints.begin(), m_dataPoints.end(),
		[ &ssTot, dYMean ]( const CDataPoint &dp )
	{
		ssTot += pow( (dp.y() * dYMean), 2 );
	} );
 
	return ssTot;
}
//-----------------------------------------------------------------------------
double CCurveFit::getSSerr()
{
	double ssErr = 0.0;
 
	auto pThis = this;
 
	std::for_each( m_dataPoints.begin(), m_dataPoints.end(),
		[ &ssErr, pThis ]( const CDataPoint &dp )
	{
		ssErr += pow( (dp.y() - pThis->getPredictedY( dp.x() )), 2 );
	} );
	
	return ssErr;
}
//-----------------------------------------------------------------------------
double CCurveFit::getPredictedY(double x)
{
	return (GetATerm() * pow( x, 2 )) + (GetBTerm() * x) + GetCTerm();
}


}	// namespace numericalanalysis
}	// namespace CmnMath
