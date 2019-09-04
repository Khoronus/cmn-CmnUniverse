/**
* @file sample_matching_phase_correlation.cpp
* @brief Sample test of phase correlation.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "measure/inc/measure/measure_headers.hpp"

namespace
{

/** @brief Perform an affine transformation to rotate an image.
*/
void rotate(cv::Mat& image, double angle, cv::Mat &out)
{
	cv::Point2f src_center(image.cols / 2.0F, image.rows / 2.0F);

	cv::Mat rot_matrix = getRotationMatrix2D(src_center, angle, 1.0);

	cv::Mat rotated_img(cv::Size(image.size().height, image.size().width), image.type());

	cv::warpAffine(image, rotated_img, rot_matrix, image.size());
	out = rotated_img;
}

int sample_dft(cv::Mat &src)
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
		return -1;

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
	cv::Mat mmagnitude, mangle;
	cv::cartToPolar(planes[0], planes[1], mmagnitude, mangle);
	cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	cv::Mat magI = mmagnitude;// planes[0];

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
#if CV_MAJOR_VERSION == 3
	cv::normalize(magI, magI, 0, 1, CV_MINMAX); 
#else if CV_MAJOR_VERSION == 4
	cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);
#endif

	// viewable image form (float between values 0 and 1).
	cv::imshow("Input Image", I);    // Show the result
	cv::imshow("spectrum magnitude", magI);
#if CV_MAJOR_VERSION == 3
	cv::normalize(mangle, mangle, 0, 1, CV_MINMAX);
#else if CV_MAJOR_VERSION == 4
	cv::normalize(mangle, mangle, 0, 1, cv::NORM_MINMAX);
#endif
	cv::imshow("specturm phase", mangle);
	cv::waitKey(10);

	//calculating the idft
	cv::Mat inverseTransform;
	cv::dft(complexI, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
	// Transform the matrix with float values into a
#if CV_MAJOR_VERSION == 3
	cv::normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
#else if CV_MAJOR_VERSION == 4
	cv::normalize(inverseTransform, inverseTransform, 0, 1, cv::NORM_MINMAX);
#endif
	cv::imshow("Reconstructed", inverseTransform);
	cv::waitKey(10);

	return 0;
}



/** @brief Show a set of plot over the image.
*/
void test()
{
	//cv::VideoCapture video(0);
	cv::Mat src = cv::imread("../../data/test.png");
	cv::Mat frame, curr, prev;
	cv::Point2d shift;

	CmnIP::measure::PhaseCorrelationItems phase_correlation_items;
	int key = 0;

	int iFrame = 0;
	int rot_angle = 0;
	do
	{
		//video >> frame;
		rotate(src, rot_angle, frame);

		char buf[512];
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(frame, curr, CV_RGB2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(frame, curr, cv::COLOR_RGB2GRAY);
#endif
		if (prev.empty()) {
			prev = curr.clone();
			continue;
		}
		phase_correlation_items.test(prev, curr, shift);
		double radius = std::sqrt(shift.x*shift.x + shift.y*shift.y);

		// Sample DFT
		sample_dft(curr);

		//if(radius > 5)
		{
			// draw a circle and line indicating the shift direction...
			cv::Point center(curr.cols >> 1, curr.rows >> 1);
#if CV_MAJOR_VERSION == 3
			cv::circle(frame, center, (int)radius, cv::Scalar(0, 255, 0), 3, 
				CV_AA);
			cv::line(frame, center, cv::Point(
				center.x + static_cast<int>(shift.x * 10),
				center.y + static_cast<int>(shift.y * 10)), cv::Scalar(0, 255, 0),
				3, CV_AA);
#else if CV_MAJOR_VERSION == 4
			cv::circle(frame, center, (int)radius, cv::Scalar(0, 255, 0), 3, 
				cv::LINE_AA);
			cv::line(frame, center, cv::Point(
				center.x + static_cast<int>(shift.x * 10),
				center.y + static_cast<int>(shift.y * 10)), cv::Scalar(0, 255, 0),
				3, cv::LINE_AA);
#endif
		}

		imshow("phase shift", frame);
		key = cv::waitKey(2);

		//std::swap(prev, curr);

		++rot_angle;
	} while ((char)key != 27); // Esc to exit...
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample Matching Phase Correlation" << std::endl;

	test();
}