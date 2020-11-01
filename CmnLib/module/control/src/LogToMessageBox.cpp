// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/31)

#include "control/inc/control/LogToMessageBox.hpp"

#if defined _WIN32 || _WIN64
#include <Windows.h>
#endif

#if defined __linux__
#endif

#include "system/inc/system/environment.hpp"

namespace CmnLib
{
namespace control
{

//----------------------------------------------------------------------------
LogToMessageBox::LogToMessageBox(int flags)
    :
    Logger::Listener(flags)
{
}
//----------------------------------------------------------------------------
void LogToMessageBox::Report(std::string const& message)
{
    std::string output = message + "Do you want to debug?";

#ifdef USE_WIN32
    std::wstring text = system::Environment::Convert(output);
#ifdef UNICODE
    int selection = MessageBox(nullptr, text.c_str(), L"Report",
        MB_ICONERROR | MB_YESNOCANCEL | MB_APPLMODAL | MB_TOPMOST);
#else
	int selection = MessageBoxW(nullptr, text.c_str(), L"Report",
		MB_ICONERROR | MB_YESNOCANCEL | MB_APPLMODAL | MB_TOPMOST);
#endif

    switch (selection)
    {
    case IDYES:
        // Break and debug.
        __debugbreak();
        break;

    case IDNO:
        // Continue execution.
        break;

    case IDCANCEL:
    default:
        // Terminate execution.
        exit(0);
        break;
    }
#endif
}
//----------------------------------------------------------------------------
}  // namespace control
}  // namespace CmnLib
