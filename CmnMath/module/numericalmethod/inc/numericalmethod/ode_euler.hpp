// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/12/13)

// The TVector template parameter allows you to create solvers with
// Vector<N,Real> when the dimension N is known at compile time or
// GVector<Real> when the dimension N is known at run time.  Both classes
// have 'int GetSize() const' that allow OdeSolver-derived classes to query
// for the dimension.

#ifndef CMNMATH_NUMERICALMETHOD_ODEEULER_HPP__
#define CMNMATH_NUMERICALMETHOD_ODEEULER_HPP__

#include "ode_solver.hpp"

namespace CmnMath
{
namespace numericalmethod
{

template <typename Real, typename TVector>
class OdeEuler : public OdeSolver<Real,TVector>
{
public:
    // Construction and destruction.
    virtual ~OdeEuler();
    OdeEuler(Real tDelta,
        std::function<TVector(Real, TVector const&)> const& F);

    // Estimate x(t + tDelta) from x(t) using dx/dt = F(t,x).  You may allow
    // xIn and xOut to be the same object.
    virtual void Update(Real tIn, TVector const& xIn, Real& tOut,
        TVector& xOut);
};

//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeEuler<Real, TVector>::~OdeEuler()
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeEuler<Real, TVector>::OdeEuler(Real tDelta,
    std::function<TVector(Real, TVector const&)> const& F)
    :
    OdeSolver<Real, TVector>(tDelta, F)
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
void OdeEuler<Real, TVector>::Update(Real tIn, TVector const& xIn,
    Real& tOut, TVector& xOut)
{
    TVector fVector = this->mFunction(tIn, xIn);
    tOut = tIn + this->mTDelta;
    xOut = xIn + this->mTDelta * fVector;
}
//----------------------------------------------------------------------------

} // namespace numericalmethod
} // namespace CmnMath

#endif /* CMNMATH_NUMERICALMETHOD_GAUSSIANELIMINATION_HPP__ */