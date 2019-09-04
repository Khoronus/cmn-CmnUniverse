/**
* @file assert.hpp
* @brief Header of all the types.
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR/AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @original author
* @bug No known bugs.
* @version 0.1.0.0
*
// Copyright (C) 2003  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
*/

#ifndef CMNIP_CMNIPCORE_ASSERT_HPP__
#define CMNIP_CMNIPCORE_ASSERT_HPP__

#include <sstream>
#include <iosfwd>
#include "error.hpp"

// -----------------------------

// Use some stuff from boost here
//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Darin Adler 2001.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright Bill Kempf 2002.
//  (C) Copyright Jens Maurer 2002.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Gennaro Prota 2003.
//  (C) Copyright Eric Friedman 2003.
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef BOOST_JOIN
#define BOOST_JOIN( X, Y ) BOOST_DO_JOIN( X, Y )
#define BOOST_DO_JOIN( X, Y ) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2( X, Y ) X##Y
#endif

// -----------------------------

namespace CmnIP
{
    template <bool value> struct compile_time_assert;
    template <> struct compile_time_assert<true> { enum {value=1};  };

    template <typename T, typename U> struct assert_are_same_type;
    template <typename T> struct assert_are_same_type<T,T> {enum{value=1};};
    template <typename T, typename U> struct assert_are_not_same_type {enum{value=1}; };
    template <typename T> struct assert_are_not_same_type<T,T> {};
} // namespace CmnIP


// gcc 4.8 will warn about unused typedefs.  But we use typedefs in some of the compile
// time assert macros so we need to make it not complain about them "not being used".
#ifdef __GNUC__
#define CMNIP_NO_WARN_UNUSED __attribute__ ((unused))
#else
#define CMNIP_NO_WARN_UNUSED 
#endif

#define COMPILE_TIME_ASSERT(expression) \
        CMNIP_NO_WARN_UNUSED typedef char BOOST_JOIN(CMNIP_CTA, __LINE__)[::CmnIP::compile_time_assert<(bool)(expression)>::value] 

#define ASSERT_ARE_SAME_TYPE(type1, type2) \
        CMNIP_NO_WARN_UNUSED typedef char BOOST_JOIN(CMNIP_AAST, __LINE__)[::CmnIP::assert_are_same_type<type1,type2>::value] 

#define ASSERT_ARE_NOT_SAME_TYPE(type1, type2) \
        CMNIP_NO_WARN_UNUSED typedef char BOOST_JOIN(CMNIP_AANST, __LINE__)[::CmnIP::assert_are_not_same_type<type1,type2>::value] 

// -----------------------------

#if defined CMNIP_DISABLE_ASSERTS
    // if CMNIP_DISABLE_ASSERTS is on then never enable CMNIP_ASSERT no matter what.
    #undef ENABLE_ASSERTS
#endif

#if !defined(CMNIP_DISABLE_ASSERTS) && ( defined DEBUG || defined _DEBUG)
    // make sure ENABLE_ASSERTS is defined if we are indeed using them.
    #ifndef ENABLE_ASSERTS
        #define ENABLE_ASSERTS
    #endif
#endif

// -----------------------------

#ifdef __GNUC__
// There is a bug in version 4.4.5 of GCC on Ubuntu which causes GCC to segfault
// when __PRETTY_FUNCTION__ is used within certain templated functions.  So just
// don't use it with this version of GCC.
#  if !(__GNUC__ == 4 && __GNUC_MINOR__ == 4 && __GNUC_PATCHLEVEL__ == 5)
#    define CMNIP_FUNCTION_NAME __PRETTY_FUNCTION__
#  else
#    define CMNIP_FUNCTION_NAME "unknown function" 
#  endif
#elif defined(_MSC_VER)
#define CMNIP_FUNCTION_NAME __FUNCSIG__
#else
#define CMNIP_FUNCTION_NAME "unknown function" 
#endif

#define CMNIP_CASSERT(_exp,_message)                                              \
    {if ( !(_exp) )                                                         \
    {                                                                       \
        CMNIP_assert_breakpoint();                                           \
        std::ostringstream CMNIP_o_out;                                       \
        CMNIP_o_out << "\n\nError detected at line " << __LINE__ << ".\n";    \
        CMNIP_o_out << "Error detected in file " << __FILE__ << ".\n";      \
        CMNIP_o_out << "Error detected in function " << CMNIP_FUNCTION_NAME << ".\n\n";      \
        CMNIP_o_out << "Failing expression was " << #_exp << ".\n";           \
        CMNIP_o_out << std::boolalpha << _message << "\n";                    \
        throw CmnIP::fatal_error(CmnIP::EBROKEN_ASSERT,CMNIP_o_out.str());      \
    }}                                                                      


#ifdef ENABLE_ASSERTS 
    #define CMNIP_ASSERT(_exp,_message) CMNIP_CASSERT(_exp,_message)
    #define CMNIP_IF_ASSERT(exp) exp
#else
    #define CMNIP_ASSERT(_exp,_message) {}
    #define CMNIP_IF_ASSERT(exp) 
#endif

// ----------------------------------------------------------------------------------------

    /*!A CMNIP_ASSERT_HAS_STANDARD_LAYOUT 
    
        This macro is meant to cause a compiler error if a type doesn't have a simple
        memory layout (like a C struct). In particular, types with simple layouts are
        ones which can be copied via memcpy().
        
        
        This was called a POD type in C++03 and in C++0x we are looking to check if 
        it is a "standard layout type".  Once we can use C++0x we can change this macro 
        to something that uses the std::is_standard_layout type_traits class.  
        See: http://www2.research.att.com/~bs/C++0xFAQ.html#PODs
    !*/
    // Use the fact that in C++03 you can't put non-PODs into a union.
#define CMNIP_ASSERT_HAS_STANDARD_LAYOUT(type)   \
    union  BOOST_JOIN(DAHSL_,__LINE__) { type TYPE_NOT_STANDARD_LAYOUT; };  \
    CMNIP_NO_WARN_UNUSED typedef char BOOST_JOIN(DAHSL2_,__LINE__)[sizeof(BOOST_JOIN(DAHSL_,__LINE__))]; 

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

// breakpoints
extern "C"
{
    inline void CMNIP_assert_breakpoint(
    ) {}
    /*!
        ensures
            - this function does nothing 
              It exists just so you can put breakpoints on it in a debugging tool.
              It is called only when an CMNIP_ASSERT or CMNIP_CASSERT fails and is about to
              throw an exception.
    !*/
}

#endif /* CMNIP_CORE_ASSERT_HPP__ */
