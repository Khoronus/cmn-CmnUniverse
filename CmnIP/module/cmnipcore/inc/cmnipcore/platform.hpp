/**
* @file types.hpp
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
// Copyright (C) 2006  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
*/

#ifndef CMNIP_CMNIPCORE_PLATFORM_HPP__
#define CMNIP_CMNIPCORE_PLATFORM_HPP__


/*!
    This file ensures that:
        - if (we are compiling under a posix platform) then
            - POSIX will be defined
            - if (this is also Mac OS X) then
                - MACOSX will be defined
            - if (this is also HP-UX) then
                - HPUX will be defined
        - if (we are compiling under an MS Windows platform) then
            - WIN32 will be defined
!*/


/*
    A good reference for this sort of information is
    http://predef.sourceforge.net/
*/

// Define WIN32 if this is MS Windows
#ifndef WIN32
    #if defined( _MSC_VER) || defined(__BORLANDC__) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
    #define WIN32 
    #endif 
#endif

#ifndef WIN32
    // since this is the only other platform the library currently supports
    // just assume it is POSIX if it isn't WIN32
    #ifndef POSIX
        #define POSIX
    #endif
 
    #ifndef HPUX
       #if defined(__hpux ) || defined(hpux) || defined (_hpux)
       #define HPUX
       #endif	
    #endif

    #ifndef MACOSX
        #ifdef __MACOSX__
        #define MACOSX
        #endif 
        #ifdef __APPLE__
        #define MACOSX
        #endif
    #endif

#endif

#endif /* CMNIP_CORE_PLATFORM_HPP__ */
