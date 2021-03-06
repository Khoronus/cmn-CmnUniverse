// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.7.0 (2014/12/07)

#ifndef CMNMATH_CMNMATHCORE_WRAPPER__   
#define CMNMATH_CMNMATHCORE_WRAPPER__   

#include <memory.h>
#include <wchar.h>
#include <algorithm>

#if defined(WIN32)
#include <cstring>
#include <cwchar>
#endif

#include <cstddef>
#include "define.hpp"

namespace CmnMath
{
namespace core
{

// Wrappers around platform-specific low-level library calls.

void Memcpy(void* target, void const* source, size_t count);
void Memcpy(wchar_t* target, wchar_t const* source, size_t count);

} // namespace core
} // namespace CmnMath

#endif /* CMNMATH_CMNMATHCORE_WRAPPER__  */
