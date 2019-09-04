/**
* @file define.hpp
* @brief Header of all the core files.
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
*/

#ifndef CMNIP_CMNIPCORE_DEFINE_HPP__
#define CMNIP_CMNIPCORE_DEFINE_HPP__

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined cmnIPAPI_EXPORTS
#  define CMNIP_EXPORTS __declspec(dllexport)
#else
#  define CMNIP_EXPORTS
#endif


/* macros for wrapper generators */
#define CMNIP_EXPORTS_W CMNIP_EXPORTS
#define CMNIP_OUT
#define CMNIP_WRAP


//*****************************************************************************
// cmn type declarations
//*****************************************************************************

#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER >= 1600)

#ifndef NULLPTR
#define NULLPTR nullptr
#endif

#else

#ifndef NULLPTR
#define NULLPTR 0
#endif

#endif


#endif /* CMNIP_CORE_DEFINE_HPP__ */
