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

#ifndef CMNIP_SIGNAL_WORLEYNOISE_HPP__
#define CMNIP_SIGNAL_WORLEYNOISE_HPP__

#include <algorithm>
#include <cmath>

#include <opencv2/core/core.hpp>

#include "INoiseGenerator.hpp"

namespace CmnIP
{
namespace signal
{

class WorleyNoise :
	public INoiseGenerator
{
private:
	float DistanceArray[3];

	float CombinerFunction1(float ar[]);
	float CombinerFunction2(float ar[]);
	float CombinerFunction3(float ar[]);

	float EuclidianDistanceFunc(cv::Point3f p1, cv::Point3f p2);
	float ManhattanDistanceFunc(cv::Point3f p1, cv::Point3f p2);
	float ChebyshevDistanceFunc(cv::Point3f p1, cv::Point3f p2);

	long probLookup(long value);
	void insert(float  arr[], float value);
	long lcgRandom(long lastValue);
	long hash(long i, long j, long k);
	float noise(cv::Point3f input);
public:
	int DistanceFunction;
	int CombineDistanceFunction;
	int Seed;

	int OFFSET_BASIS;
	int FNV_PRIME;

	float Get1D(float x) override;
	float Get2D(float x, float y) override;

	WorleyNoise();
	~WorleyNoise();
};

} // namespace signal
} // namespace CmnIP

#endif /* CMNIP_SIGNAL_WORLEYNOISE_HPP__ */
