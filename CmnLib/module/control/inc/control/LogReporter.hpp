// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#ifndef CMNLIB_CONTROL_LOGREPORTER_HPP__
#define CMNLIB_CONTROL_LOGREPORTER_HPP__

#include <mutex>
#include <set>
#include <string>
#include "cmnlibcore/inc/cmnlibcore/cmnlibcore_headers.hpp"

#include "LogToFile.hpp"
#include "LogToMessageBox.hpp"
#include "LogToOutputWindow.hpp"
#include "LogToStdout.hpp"

// Uncomment this to turn off the logging system.  The macros LogAssert,
// LogError, LogWarning, and LogInformation expand to nothing.  (Do this for
// optimal performance.)
//#define CMNLIB_NO_LOGGER

namespace CmnLib
{
namespace control
{

class CL_EXPORTS LogReporter
{
public:
    // Construction and destruction.  Create one of these objects in an
    // application for logging.  The GenerateProject tool creates such code.
    // If you do not want a particular logger, set the flags to
    // LISTEN_FOR_NOTHING and set logFile to "" if you do not want a file.
    ~LogReporter();
    LogReporter(std::string const& logFile, int logFileFlags,
        int logMessageBoxFlags, int logOutputWindowFlags, int logStdoutFlags);

private:
    LogToFile* mLogToFile;
    LogToMessageBox* mLogToMessageBox;
    LogToOutputWindow* mLogToOutputWindow;
    LogToStdout* mLogToStdout;
};

}  // namespace control
}  // namespace CmnLib

#endif /* CMNLIB_CONTROL_LOGREPORTER_HPP__ */
