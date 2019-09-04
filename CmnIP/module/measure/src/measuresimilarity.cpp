/**
* @file algorithm.hpp
* @brief Virtual class to manage algorithms
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
* @author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#include "measure/inc/measure/measuresimilarity.hpp"


namespace CmnIP
{
namespace measure
{

//-----------------------------------------------------------------------------
double MeasureSimilarities::PSNR(cv::Mat& src1, cv::Mat& src2, int bb)
{
	int i, j;
	double sse, mse, psnr;
	sse = 0.0;

	cv::Mat s1, s2;
	if (src1.channels() == 1) {
		s1 = src1;
	} else {
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src1, s1, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(src1, s1, cv::COLOR_BGR2GRAY);
#endif
	}
	if (src2.channels() == 1) {
		s2 = src2;
	} else {
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src2, s2, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(src2, s2, cv::COLOR_BGR2GRAY);
#endif
	}


	int count = 0;
	for (j = bb; j<s1.rows - bb; j++)
	{
		uchar* d = s1.ptr(j);
		uchar* s = s2.ptr(j);

		for (i = bb; i<s1.cols - bb; i++)
		{
			sse += ((d[i] - s[i])*(d[i] - s[i]));
			count++;
		}
	}
	if (sse == 0.0 || count == 0)
	{
		return 0;
	}
	else
	{
		mse = sse / (double)(count);
		psnr = 10.0*log10((255 * 255) / mse);
		return psnr;
	}
}


} // namespace measure
} // namespace CmnIP

