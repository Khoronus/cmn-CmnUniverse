// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/31)

#include "control/inc/control/LogToOutputWindow.hpp"

#ifdef USE_WIN32
#include <Windows.h>
#include "system/inc/system/environment.hpp"
#endif

namespace CmnLib
{
namespace control
{

//----------------------------------------------------------------------------
LogToOutputWindow::LogToOutputWindow(int flags)
    :
    Logger::Listener(flags)
{
}
//----------------------------------------------------------------------------
void LogToOutputWindow::Report(std::string const& message)
{
#ifdef USE_WIN32
    std::wstring text = system::Environment::Convert(message);
#ifdef UNICODE
    OutputDebugString(text.c_str());
#else
	OutputDebugStringW(text.c_str());
#endif

#endif
}
//----------------------------------------------------------------------------

}  // namespace control
}  // namespace CmnLib
