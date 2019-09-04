// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#ifndef CMNLIB_CONTROL_LOGTOSTRINGARRAY_HPP__
#define CMNLIB_CONTROL_LOGTOSTRINGARRAY_HPP__

#include <vector>
#include "cmnlibcore\inc\cmnlibcore\cmnlibcore_headers.hpp"
#include "Logger.hpp"

namespace CmnLib
{
namespace control
{

class CL_EXPORTS LogToStringArray : public Logger::Listener
{
public:
    LogToStringArray(std::string const& name, int flags);

    std::string const& GetName() const;
    std::vector<std::string> const& GetMessages() const;
    std::vector<std::string>& GetMessages();

private:
    virtual void Report(std::string const& message);

    std::string mName;
    std::vector<std::string> mMessages;
};

}  // namespace control
}  // namespace CmnLib

#endif /* CMNLIB_CONTROL_LOGTOSTRINGARRAY_HPP__ */