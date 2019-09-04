/**
* @file transform.cpp
* @brief Body of the classes to perform some signal transformation.
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.0.0
*
*/


#include "transform/inc/transform/transform.hpp"

namespace CmnIP
{
namespace transform
{

//-----------------------------------------------------------------------------
int Transform::dft(const cv::Mat &src, cv::Mat &out)
{
	cv::Mat I;
	if (src.channels() == 3) {
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src, I, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(src, I, cv::COLOR_BGR2GRAY);
#endif
	}
	else {
		I = src;
	}
	if (I.empty())
		return 0;

	cv::Mat padded;                            //expand input image to optimal size
	int m = cv::getOptimalDFTSize(I.rows);
	int n = cv::getOptimalDFTSize(I.cols); // on the border add zero values
	cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	cv::dft(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	// Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
#if CV_MAJOR_VERSION == 3
	cv::normalize(magI, magI, 0, 1, CV_MINMAX); 
#else if CV_MAJOR_VERSION == 4
	cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);
#endif

	//cv::imshow("Input Image", I);    // Show the result
	//cv::imshow("spectrum magnitude", magI);
	//cv::waitKey(10);

	out = magI;

	return 1;
}
//-----------------------------------------------------------------------------
int Transform::dct(cv::Mat &src, cv::Mat &out) {

	if (src.empty() || (src.data == NULL)) {
		return 0;
	}
	cv::Mat originalImage(src.size(), CV_32FC1);
	src.convertTo(originalImage, CV_32FC1);
	cv::dct(originalImage, out);
	return 1;
} //-See more at : https ://www.gidforums.com/t-26418.html#sthash.A6B6kwM0.dpuf


}	// namespace transform
}	// namespace CmnIP
