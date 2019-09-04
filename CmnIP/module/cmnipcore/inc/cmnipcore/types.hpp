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
*/

#ifndef CMNIP_CMNIPCORE_TYPES_HPP__
#define CMNIP_CMNIPCORE_TYPES_HPP__


#include <string>

namespace CmnIP
{
namespace core
{

typedef char CIP_8S;
typedef unsigned char CIP_8U;
typedef unsigned int CIP_32U;
typedef int CIP_32S;
typedef float CIP_32F;
typedef double CIP_64F;
typedef bool CIP_BOOL;
typedef void CIP_VOID;

// @link http://stackoverflow.com/questions/724617/examples-of-union-in-c

/** @brief It defines a 
*/
struct AtomicParam
{
  enum { INT=0, BOOLEAN=1, REAL=2, STRING=3, FLOAT=4, DOUBLE=5, 
	  UNSIGNED_INT=6, UINT64=7, SHORT=8, UCHAR=9 };
  int type_;
  std::string help_;

  union {
  CIP_32S integer;
  const CIP_8S *string;
  CIP_32F real;
  CIP_64F dword;
  CIP_VOID *pointer;
  } x_;

  AtomicParam() : type_(INT) {}
  AtomicParam(CIP_32S value, const std::string &help=std::string()) : type_(INT) {
    x_.integer = value; }
  AtomicParam(CIP_32F value, const std::string &help=std::string()) : type_(REAL) {
    x_.real = value; }
  AtomicParam(CIP_64F value, const std::string &help=std::string()) : type_(DOUBLE) {
    x_.dword = value; }
  AtomicParam(const std::string &value, const std::string &help=std::string()) : type_(STRING) {
    x_.string = value.c_str(); }
};

} // namespace core
} // namespace CmnIP


#endif /* CMNIP_CORE_TYPES_HPP__ */
