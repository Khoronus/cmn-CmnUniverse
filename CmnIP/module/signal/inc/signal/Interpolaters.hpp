/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.IN NO EVENT SHALL THE AUTHOR / AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author  Davejza
* @link https ://sharpnoise.codeplex.com/
*@bug No known bugs.
* @version 1.0.0.0
*
* @Check Speckle Noise Generation
*        http://lodev.org/cgtutor/randomnoise.html
*
*/

#ifndef CMNIP_SIGNAL_INTERPOLATERS_HPP__
#define CMNIP_SIGNAL_INTERPOLATERS_HPP__

#include <cmath>

namespace CmnIP
{
namespace signal
{

class Interpolaters
{
public:
	Interpolaters();
	~Interpolaters();
	float Lerp(float v0, float v1, float t);
	float Linear(float v0, float v1, float t);
	float Cosine(float v0, float v1, float t);
	float Cubic(float v0, float v1, float v2, float v3, float t);
	float CatmullRom(float v0, float v1, float v2, float v3, float t);
	float Hermite(float v0, float v1, float v2, float v3, float t, float tension, float bias);
};
 

} // namespace signal
} // namespace CmnIP

#endif /* CMNIP_SIGNAL_INTERPOLATERS_HPP__ */
