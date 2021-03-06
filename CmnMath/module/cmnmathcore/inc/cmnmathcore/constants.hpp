/**
* @file constants.hpp
* @brief Header of constants values
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

#ifndef CMNMATH_CMNMATHCORE_CONSTANTS_HPP__
#define CMNMATH_CMNMATHCORE_CONSTANTS_HPP__

#include "types.hpp"

namespace CmnMath
{
namespace core
{

const CMN_64F kPI       =  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
// pi CMN_32F
const CMN_32F kPIf       =  3.1415926535897932384f;
// pi^2
const CMN_64F kPIf_SQ   =  6.283185307179586476925286766559;
// degrees to radians conversion
const CMN_64F kDEG2RAD =  0.01745329251994329576923690768489;
// radians to degrees conversion
const CMN_64F kRAD2DEG =  57.295779513082320876798154814105;
// natural logarithmic base
const CMN_64F kE=        2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274;
// euler constant
const CMN_64F kGAMMA=    0.57721566490153286060651209008240243104215933593992359880576723488486772677766467093694706329174674;
// golden ratio = (1+sqrt(5))/2
const CMN_64F kGOLDEN_RATIO = 1.6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374;
// 1/log(2)
const CMN_64F kINV_LOG2= 1.44269504088896340735992468100189213742664595415298593413544940693110921918118507988552662289350;
// ln(10)
const CMN_64F kLN10=     2.3025850929940456840179914546843642076011014886287729760333279009675726096773524802359972050895982983;
// ln(pi)
const CMN_64F kLNPI=     1.1447298858494001741434273513530587116472948129153115715136230714721377698848260797836232702754897077;	
// lg(e)
const CMN_64F kLOG2_E=    1.44269504088896340736;
// log(e)
const CMN_64F kLOG10_E=   0.434294481903251827651;
// log10_2 -- The logarithm base 10 of two
const CMN_64F kLOG10_2 = 0.30102999566398119521;
// ln(2)
const CMN_64F kLN2=      0.693147180559945309417;	
// sqrt(2)
const CMN_64F kSQRT2=    1.4142135623730950488016887242097;
// sqrt(3)
const CMN_64F kSQRT3=    1.7320508075688772935274463415059;
// light_spd -- The speed of light in vacuum in meters per second
const CMN_64F kLIGHT_SPD = 2.99792458e8;
// newton_G  -- Newton's gravitational constant (in metric units of m^3/(kg*s^2))
const CMN_64F kNEWTON_G = 6.67384e-11;
// planck_cst -- Planck's constant (in units of Joules * seconds) 
const CMN_64F kPLANCK_CST = 6.62606957e-34;
// euler_gamma -- The Euler Mascheroni Constant 
const CMN_64F kEULER_GAMMA = 0.5772156649015328606065;
// catalan -- Catalan's Constant
const CMN_64F kCATALAN = 0.91596559417721901505; 
// glaisher -- Glaisher Kinkelin constant
const CMN_64F kGLAISHER = 1.2824271291006226369;
// khinchin -- Khinchin's constant
const CMN_64F kKHINCHIN = 2.6854520010653064453;
// apery -- Apery's constant
const CMN_64F kAPERY = 1.2020569031595942854;


// @brief Small coefficient used in the approximation of the operations
const CMN_64F kGEOMETRY_EPS = 0.0001;

// @brief Generic True value
const CMN_32S kTRUE = 1;
// @brief Generic False value
const CMN_32S kFALSE = 0;


} // namespace core
} // namespace CmnMath

#endif /* CMNMATH_CMNMATHCORE_CONSTANTS_HPP__ */
