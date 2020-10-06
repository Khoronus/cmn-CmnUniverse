// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#ifndef CMNLIB_CONTROL_LOGTOFILE_HPP__
#define CMNLIB_CONTROL_LOGTOFILE_HPP__

#include <fstream>
#include "cmnlibcore/inc/cmnlibcore/cmnlibcore_headers.hpp"
#include "Logger.hpp"

namespace CmnLib
{
namespace control
{

class CL_EXPORTS LogToFile : public Logger::Listener
{
public:
    LogToFile(std::string const& filename, int flags);

private:
    virtual void Report(std::string const& message);

    std::string mFilename;
};

}  // namespace control
}  // namespace CmnLib

#endif /* CMNLIB_CONTROL_LOGTOFILE_HPP__ */
