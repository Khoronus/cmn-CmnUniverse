// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.9.1 (2015/03/13)

#ifndef CMNMATH_FUNCTION_FUNCTIONS_HPP__
#define CMNMATH_FUNCTION_FUNCTIONS_HPP__

#include "cmnmathcore/inc/cmnmathcore/define_constants.hpp"
#include "arithmetic/inc/arithmetic/arithmetic.hpp"

namespace CmnMath
{
namespace function
{

template <typename Real>
class Function
{
public:
    static Real ACos(Real const& x);                    // acos(x)
    static Real ACosh(Real const& x);                   // acosh(x)
    static Real ASin(Real const& x);                    // asin(x)
    static Real ASinh(Real const& x);                   // asinh(x)
    static Real ATan(Real const& x);                    // atan(x)
    static Real ATanh(Real const& x);                   // atanh(x)
    static Real ATan2(Real const& y, Real const& x);    // atan2(y, x)
    static Real ATanpi(Real const& x);                  // atan(x)/pi
    static Real ATan2pi(Real const& y, Real const& x);  // atan2(y,x)/pi
    static Real Ceil(Real const& x);                    // ceil(x)
    static Real Cos(Real const& x);                     // cos(x)
    static Real Cosh(Real const& x);                    // cosh(x)
    static Real Cospi(Real const& x);                   // cos(pi*x)
    static Real Exp(Real const& x);                     // e^x
    static Real Exp2(Real const& x);                    // 2^x
    static Real Exp10(Real const& x);                   // 10^x
    static Real FAbs(Real const& x);                    // |x|
    static Real Floor(Real const& x);                   // floor(x)
    static Real FMod(Real const& x, Real const& y);     // fmod(x,y)
    static Real InvSqrt(Real const& x);                 // x^{-1/2}
    static Real Log(Real const& x);                     // log_e(x)
    static Real Log2(Real const& x);                    // log_2(x)
    static Real Log10(Real const& x);                   // log_10(x)
    static Real Pow(Real const& x, Real const& y);      // x^y
    static Real Sin(Real const& x);                     // sin(x)
    static Real Sinh(Real const& x);                    // sinh(x)
    static Real Sinpi(Real const& x);                   // sin(pi*x)
    static Real Sqr(Real const& x);                     // x^2
    static Real Sqrt(Real const& x);                    // x^{1/2}
    static Real Tan(Real const& x);                     // tan(x)
    static Real Tanh(Real const& x);                    // tanh(x)

    static Real Sign(Real const& x);    // sign of x as a Real number
    static int ISign(Real const& x);    // sign of x as an integer

    // Clamp x to the interval [min,max].
    static Real Clamp(Real const& x, Real const& min, Real const & max);

    // Clamp x to the interval [0,1].
    static Real Saturate(Real const& x);

private:
    // The tag-dispatch pattern is used for template-parameter-controlled
    // instantiation of mathematics functions.

    template <typename T> static T ACosImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ACosImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ACosImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ACoshImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ACoshImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ACoshImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ASinImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ASinImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ASinImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ASinhImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ASinhImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ASinhImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ATanImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ATanImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ATanImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ATanhImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ATanhImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ATanhImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ATan2Impl(T y, T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ATan2Impl(T y, T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ATan2Impl(T const& y, T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ATanpiImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ATanpiImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ATanpiImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ATan2piImpl(T y, T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ATan2piImpl(T y, T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ATan2piImpl(T const& y, T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T CeilImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T CeilImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T CeilImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T CosImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T CosImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T CosImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T CoshImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T CoshImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T CoshImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T CospiImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T CospiImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T CospiImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T ExpImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T ExpImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T ExpImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T Exp2Impl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T Exp2Impl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T Exp2Impl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T Exp10Impl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T Exp10Impl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T Exp10Impl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T FAbsImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T FAbsImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T FAbsImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T FloorImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T FloorImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T FloorImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T FModImpl(T x, T y, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T FModImpl(T x, T y, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T FModImpl(T const& x, T const& y, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T InvSqrtImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T InvSqrtImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T InvSqrtImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T LogImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T LogImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T LogImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T Log2Impl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T Log2Impl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T Log2Impl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T Log10Impl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T Log10Impl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T Log10Impl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T PowImpl(T x, T y, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T PowImpl(T x, T y, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T PowImpl(T const& x, T const& y, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SinImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SinImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SinImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SinhImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SinhImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SinhImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SinpiImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SinpiImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SinpiImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SqrtImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SqrtImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SqrtImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T TanImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T TanImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T TanImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T TanhImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T TanhImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T TanhImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SignImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SignImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SignImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static int ISignImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static int ISignImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static int ISignImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);

	template <typename T> static T SaturateImpl(T x, arithmetic::Arithmetic::IsFPType tag);
	template <typename T> static T SaturateImpl(T x, arithmetic::Arithmetic::IsFP16Type tag);
	template <typename T> static T SaturateImpl(T const& x, arithmetic::Arithmetic::IsBSType tag);
};

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ACos(Real const& x)
{
    return ACosImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACosImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return acos(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACosImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)acos((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACosImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)acos((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ACosh(Real const& x)
{
    return ACoshImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACoshImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log(x + sqrt(x * x - (Real)1));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACoshImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (float)x;
    return (T)log(y + sqrt(y * y - 1.0f));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ACoshImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    double y = (double)x;
    return (T)log(y + sqrt(y * y - 1.0));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ASin(Real const& x)
{
    return ASinImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return asin(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)asin((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)asin((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ASinh(Real const& x)
{
    return ASinhImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinhImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log(x + sqrt(x * x + (Real)1));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinhImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (float)x;
    return (T)log(y + sqrt(y * y + 1.0f));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ASinhImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    double y = (double)x;
    return (T)log(y + sqrt(y * y + 1.0));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ATan(Real const& x)
{
    return ATanImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return atan(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)atan((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)atan((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ATanh(Real const& x)
{
    return ATanhImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanhImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log( ((Real)1 + x) / ((Real)1 - x) ) * (Real)0.5;
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanhImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (float)x;
    return (T)(log( (1.0f + y) / (1.0f - y) ) * 0.5f);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanhImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    double y = (double)x;
    return (T)(log( (1.0 + y) / (1.0 - y) ) * 0.5);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ATan2(Real const& y, Real const& x)
{
    return ATan2Impl<Real>(y, x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2Impl(T y, T x, arithmetic::Arithmetic::IsFPType)
{
    return atan2(y, x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2Impl(T y, T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)atan2((float)y, (float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2Impl(T const& y, T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)atan2((double)y, (double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ATanpi(Real const& x)
{
    return ATanpiImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanpiImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return atan(x) * (Real)GTE_C_INV_PI;
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanpiImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)(atan((float)x) * (float)GTE_C_INV_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATanpiImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)(atan((double)x) * GTE_C_INV_PI);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::ATan2pi(Real const& y, Real const& x)
{
    return ATan2piImpl<Real>(y, x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2piImpl(T y, T x, arithmetic::Arithmetic::IsFPType)
{
    return atan2(y, x) * (Real)GTE_C_INV_PI;
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2piImpl(T y, T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)(atan2((float)y, (float)x) * (float)GTE_C_INV_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ATan2piImpl(T const& y, T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)(atan2((double)y, (double)x) * GTE_C_INV_PI);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Ceil(Real const& x)
{
    return CeilImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CeilImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return ceil(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CeilImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)ceil((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CeilImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)ceil((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Cos(Real const& x)
{
    return CosImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CosImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return cos(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CosImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)cos((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CosImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)cos((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Cosh(Real const& x)
{
    return CoshImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CoshImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return cosh(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CoshImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)cosh((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CoshImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)cosh((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Cospi(Real const& x)
{
    return CospiImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CospiImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return cos(x * (Real)GTE_C_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CospiImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)cos((float)x * (float)GTE_C_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::CospiImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)cos((double)(x * (T)GTE_C_PI));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Exp(Real const& x)
{
    return ExpImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ExpImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return exp(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ExpImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)exp((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::ExpImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)exp((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Exp2(Real const& x)
{
    return Exp2Impl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp2Impl(T x, arithmetic::Arithmetic::IsFPType)
{
    return exp(x * (Real)GTE_C_LN_2);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp2Impl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)exp((float)x * (float)GTE_C_LN_2);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp2Impl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)exp((double)(x * (T)GTE_C_LN_2));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Exp10(Real const& x)
{
    return Exp10Impl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp10Impl(T x, arithmetic::Arithmetic::IsFPType)
{
    return exp(x * (Real)GTE_C_LN_10);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp10Impl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)exp((float)x * (float)GTE_C_LN_10);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Exp10Impl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)exp((double)(x * (T)GTE_C_LN_10));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::FAbs(Real const& x)
{
    return FAbsImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FAbsImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return fabs(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FAbsImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (Real)fabs((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FAbsImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (x.GetSign() >= 0 ? x : -x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Floor(Real const& x)
{
    return FloorImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FloorImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return floor(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FloorImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)floor((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FloorImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)floor((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::FMod(Real const& x, Real const& y)
{
    return FModImpl<Real>(x, y, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FModImpl(T x, T y, arithmetic::Arithmetic::IsFPType)
{
    return fmod(x, y);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FModImpl(T x, T y, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)fmod((float)x, (float)y);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::FModImpl(T const& x, T const& y, arithmetic::Arithmetic::IsBSType)
{
    return (T)fmod((double)x, (double)y);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::InvSqrt(Real const& x)
{
    return InvSqrtImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::InvSqrtImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return ((T)1) / sqrt(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::InvSqrtImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)(1.0f / sqrt((float)x));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::InvSqrtImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)(1.0 / sqrt((double)x));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Log(Real const& x)
{
    return LogImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::LogImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::LogImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)log((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::LogImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)log((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Log2(Real const& x)
{
    return Log2Impl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log2Impl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log(x) * (Real)GTE_C_INV_LN_2;
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log2Impl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)(log((float)x) * (float)GTE_C_INV_LN_2);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log2Impl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)(log((double)x) * GTE_C_INV_LN_2);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Log10(Real const& x)
{
    return Log10Impl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log10Impl(T x, arithmetic::Arithmetic::IsFPType)
{
    return log10(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log10Impl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)log10((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::Log10Impl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)log10((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Pow(Real const& x, Real const& y)
{
    return PowImpl<Real>(x, y, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::PowImpl(T x, T y, arithmetic::Arithmetic::IsFPType)
{
    return pow(x, y);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::PowImpl(T x, T y, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)pow((float)x, (float)y);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::PowImpl(T const& x, T const& y, arithmetic::Arithmetic::IsBSType)
{
    return (T)pow((double)x, (double)y);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sin(Real const& x)
{
    return SinImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return sin(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)sin((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)sin((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sinh(Real const& x)
{
    return SinhImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinhImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return sinh(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinhImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)sinh((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinhImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)sinh((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sinpi(Real const& x)
{
    return SinpiImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinpiImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return sin(x * (Real)GTE_C_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinpiImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)sin((float)x * (float)GTE_C_PI);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SinpiImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)sin((double)(x * (T)GTE_C_PI));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sqr(Real const& x)
{
    return x * x;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sqrt(Real const& x)
{
    return SqrtImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SqrtImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return sqrt(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SqrtImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)sqrt((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SqrtImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)sqrt((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Tan(Real const& x)
{
    return TanImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return tan(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)tan((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)tan((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Tanh(Real const& x)
{
    return TanhImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanhImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return tanh(x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanhImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    return (T)tanh((float)x);
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::TanhImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (T)tanh((double)x);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Sign(Real const& x)
{
    return SignImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SignImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return (x > (Real)0 ? (Real)1 : (x < (Real)0 ? (Real)-1 : (Real)0));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SignImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (Real)x;
    return (y > 0.0f ? 1.0f : (y < 0.0f ? -1.0f : 0.0f));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SignImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return (Real)x.GetSign();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
int Function<Real>::ISign(Real const& x)
{
    return ISignImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
int Function<Real>::ISignImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return (x > (Real)0 ? 1 : (x < (Real)0 ? -1 : 0));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
int Function<Real>::ISignImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (Real)x;
    return (y > 0.0f ? 1 : (y < 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
int Function<Real>::ISignImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    return x.GetSign();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Clamp(Real const& x, Real const& min, Real const& max)
{
    return (x <= min ? min : (x >= max ? max : x));
}
//----------------------------------------------------------------------------
template <typename Real>
Real Function<Real>::Saturate(Real const& x)
{
    return SaturateImpl<Real>(x, arithmetic::Arithmetic::WhichType<Real>());
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SaturateImpl(T x, arithmetic::Arithmetic::IsFPType)
{
    return (x <= (Real)0 ? (Real)0 : (x >= (Real)1 ? (Real)1 : x));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SaturateImpl(T x, arithmetic::Arithmetic::IsFP16Type)
{
    float y = (float)x;
    return (y <= 0.0f ? 0.0f : (y >= 1.0f ? 1.0f : y));
}
//----------------------------------------------------------------------------
template <typename Real> template <typename T>
T Function<Real>::SaturateImpl(T const& x, arithmetic::Arithmetic::IsBSType)
{
    Real const zero(0), one(1);
    return (x <= zero ? zero : (x >= one ? one : x));
}
//----------------------------------------------------------------------------

} // namespace function
} // namespace CmnMath

#endif /* CMNMATH_FUNCTION_FUNCTION_HPP__ */
