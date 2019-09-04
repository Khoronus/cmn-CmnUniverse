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

#ifndef CMNIP_SIGNAL_SIMPLEXNOISE_HPP__
#define CMNIP_SIGNAL_SIMPLEXNOISE_HPP__

#include <cmath>
#include "INoiseGenerator.hpp"

namespace CmnIP
{
namespace signal
{

class SimplexNoise :
	public INoiseGenerator
{
public:
	SimplexNoise();
	~SimplexNoise();

	float Get1D(float x) override;
	float Get2D(float x, float y) override;

private:
	int i, j, k;
	int A[3];

	float u, v, w;
	float T [];
	float noise(float x, float y, float z);
	float K(int a);
	float Shuffle(int i, int j, int k);

	int b4Param(int i, int j, int k, int B);
	int b2Param(int N, int B);
};

} // namespace signal
} // namespace CmnIP

#endif /* CMNIP_SIGNAL_SIMPLEXNOISE_HPP__ */
