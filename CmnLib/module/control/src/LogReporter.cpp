// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "control/inc/control/LogReporter.hpp"

namespace CmnLib
{
namespace control
{

//----------------------------------------------------------------------------
LogReporter::~LogReporter()
{
    if (mLogToStdout)
    {
        Logger::Unsubscribe(mLogToStdout);
		CL_DELETE mLogToStdout;
    }

    if (mLogToOutputWindow)
    {
        Logger::Unsubscribe(mLogToOutputWindow);
		CL_DELETE mLogToOutputWindow;
    }

    if (mLogToMessageBox)
    {
        Logger::Unsubscribe(mLogToMessageBox);
		CL_DELETE mLogToMessageBox;
    }

    if (mLogToFile)
    {
        Logger::Unsubscribe(mLogToFile);
		CL_DELETE mLogToFile;
    }
}
//----------------------------------------------------------------------------
LogReporter::LogReporter(std::string const& logFile, int logFileFlags,
    int logMessageBoxFlags, int logOutputWindowFlags, int logStdoutFlags)
    :
    mLogToFile(nullptr),
    mLogToMessageBox(nullptr),
    mLogToOutputWindow(nullptr),
    mLogToStdout(nullptr)
{
    if (logFileFlags != Logger::Listener::LISTEN_FOR_NOTHING)
    {
        mLogToFile = CL_NEW LogToFile(logFile, logFileFlags);
        Logger::Subscribe(mLogToFile);
    }

    if (logMessageBoxFlags != Logger::Listener::LISTEN_FOR_NOTHING)
    {
		mLogToMessageBox = CL_NEW LogToMessageBox(logMessageBoxFlags);
        Logger::Subscribe(mLogToMessageBox);
    }

    if (logOutputWindowFlags != Logger::Listener::LISTEN_FOR_NOTHING)
    {
		mLogToOutputWindow = CL_NEW LogToOutputWindow(logOutputWindowFlags);
        Logger::Subscribe(mLogToOutputWindow);
    }

    if (logStdoutFlags != Logger::Listener::LISTEN_FOR_NOTHING)
    {
		mLogToStdout = CL_NEW LogToStdout(logStdoutFlags);
        Logger::Subscribe(mLogToStdout);
    }
}
//----------------------------------------------------------------------------
}  // namespace control
}  // namespace CmnLib
