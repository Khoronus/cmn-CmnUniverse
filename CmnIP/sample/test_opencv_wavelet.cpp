/**
* @file sample_test_wavelet.cpp
* @brief Container for training/testing images
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
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <fstream>
#include <bitset>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

// Filter type
#define NONE 0  // no filter
#define HARD 1  // hard shrinkage
#define SOFT 2  // soft shrinkage
#define GARROT 3  // garrot filter
//--------------------------------
// signum
//--------------------------------
float sgn(float x)
{
	float res = 0;
	if (x == 0)
	{
		res = 0;
	}
	if (x>0)
	{
		res = 1;
	}
	if (x<0)
	{
		res = -1;
	}
	return res;
}
//--------------------------------
// Soft shrinkage
//--------------------------------
float soft_shrink(float d, float T)
{
	float res;
	if (fabs(d)>T)
	{
		res = sgn(d)*(fabs(d) - T);
	}
	else
	{
		res = 0;
	}

	return res;
}
//--------------------------------
// Hard shrinkage
//--------------------------------
float hard_shrink(float d, float T)
{
	float res;
	if (fabs(d)>T)
	{
		res = d;
	}
	else
	{
		res = 0;
	}

	return res;
}
//--------------------------------
// Garrot shrinkage
//--------------------------------
float Garrot_shrink(float d, float T)
{
	float res;
	if (fabs(d)>T)
	{
		res = d - ((T*T) / d);
	}
	else
	{
		res = 0;
	}

	return res;
}
//--------------------------------
// Wavelet transform
//--------------------------------
static void cvHaarWavelet(Mat &src, Mat &dst, int NIter)
{
	float c, dh, dv, dd;
	assert(src.type() == CV_32FC1);
	assert(dst.type() == CV_32FC1);
	int width = src.cols;
	int height = src.rows;
	for (int k = 0; k<NIter; k++)
	{
		for (int y = 0; y<(height >> (k + 1)); y++)
		{
			for (int x = 0; x<(width >> (k + 1)); x++)
			{
				c = (src.at<float>(2 * y, 2 * x) + src.at<float>(2 * y, 2 * x + 1) + src.at<float>(2 * y + 1, 2 * x) + src.at<float>(2 * y + 1, 2 * x + 1))*0.5;
				dst.at<float>(y, x) = c;

				dh = (src.at<float>(2 * y, 2 * x) + src.at<float>(2 * y + 1, 2 * x) - src.at<float>(2 * y, 2 * x + 1) - src.at<float>(2 * y + 1, 2 * x + 1))*0.5;
				dst.at<float>(y, x + (width >> (k + 1))) = dh;

				dv = (src.at<float>(2 * y, 2 * x) + src.at<float>(2 * y, 2 * x + 1) - src.at<float>(2 * y + 1, 2 * x) - src.at<float>(2 * y + 1, 2 * x + 1))*0.5;
				dst.at<float>(y + (height >> (k + 1)), x) = dv;

				dd = (src.at<float>(2 * y, 2 * x) - src.at<float>(2 * y, 2 * x + 1) - src.at<float>(2 * y + 1, 2 * x) + src.at<float>(2 * y + 1, 2 * x + 1))*0.5;
				dst.at<float>(y + (height >> (k + 1)), x + (width >> (k + 1))) = dd;
			}
		}
		dst.copyTo(src);
	}
}
//--------------------------------
//Inverse wavelet transform
//--------------------------------
static void cvInvHaarWavelet(Mat &src, Mat &dst, int NIter, int SHRINKAGE_TYPE = 0, float SHRINKAGE_T = 50)
{
	float c, dh, dv, dd;
	assert(src.type() == CV_32FC1);
	assert(dst.type() == CV_32FC1);
	int width = src.cols;
	int height = src.rows;
	//--------------------------------
	// NIter - number of iterations 
	//--------------------------------
	for (int k = NIter; k>0; k--)
	{
		for (int y = 0; y<(height >> k); y++)
		{
			for (int x = 0; x<(width >> k); x++)
			{
				c = src.at<float>(y, x);
				dh = src.at<float>(y, x + (width >> k));
				dv = src.at<float>(y + (height >> k), x);
				dd = src.at<float>(y + (height >> k), x + (width >> k));

				// (shrinkage)
				switch (SHRINKAGE_TYPE)
				{
				case HARD:
					dh = hard_shrink(dh, SHRINKAGE_T);
					dv = hard_shrink(dv, SHRINKAGE_T);
					dd = hard_shrink(dd, SHRINKAGE_T);
					break;
				case SOFT:
					dh = soft_shrink(dh, SHRINKAGE_T);
					dv = soft_shrink(dv, SHRINKAGE_T);
					dd = soft_shrink(dd, SHRINKAGE_T);
					break;
				case GARROT:
					dh = Garrot_shrink(dh, SHRINKAGE_T);
					dv = Garrot_shrink(dv, SHRINKAGE_T);
					dd = Garrot_shrink(dd, SHRINKAGE_T);
					break;
				}

				//-------------------
				dst.at<float>(y * 2, x * 2) = 0.5*(c + dh + dv + dd);
				dst.at<float>(y * 2, x * 2 + 1) = 0.5*(c - dh + dv - dd);
				dst.at<float>(y * 2 + 1, x * 2) = 0.5*(c + dh - dv - dd);
				dst.at<float>(y * 2 + 1, x * 2 + 1) = 0.5*(c - dh - dv + dd);
			}
		}
		Mat C = src(Rect(0, 0, width >> (k - 1), height >> (k - 1)));
		Mat D = dst(Rect(0, 0, width >> (k - 1), height >> (k - 1)));
		D.copyTo(C);
	}
}
//--------------------------------
//
//--------------------------------
int process(VideoCapture& capture)
{
	int n = 0;
	const int NIter = 4;
	char filename[200];
	string window_name = "video | q or esc to quit";
	cout << "press space to save a picture. q or esc to quit" << endl;
#if CV_MAJOR_VERSION == 3
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
#elif CV_MAJOR_VERSION == 4
	cv::namedWindow(window_name, cv::WINDOW_KEEPRATIO); //resizable window;
#endif
	Mat frame;
	capture >> frame;
	cv::resize(frame, frame, cv::Size(640, 480));

	Mat GrayFrame = Mat(frame.rows, frame.cols, CV_8UC1);
	Mat Src = Mat(frame.rows, frame.cols, CV_32FC1);
	Mat Dst = Mat(frame.rows, frame.cols, CV_32FC1);
	Mat Temp = Mat(frame.rows, frame.cols, CV_32FC1);
	Mat Filtered = Mat(frame.rows, frame.cols, CV_32FC1);
	for (;;)
	{
		Dst = 0;
		capture >> frame;
		cv::resize(frame, frame, cv::Size(640, 480));
		if (frame.empty()) continue;
#if CV_MAJOR_VERSION == 3
		cvtColor(frame, GrayFrame, CV_BGR2GRAY);
#elif CV_MAJOR_VERSION == 4
		cvtColor(frame, GrayFrame, cv::COLOR_BGR2GRAY);
#endif
		GrayFrame.convertTo(Src, CV_32FC1);
		cvHaarWavelet(Src, Dst, NIter);

		Dst.copyTo(Temp);

		cvInvHaarWavelet(Temp, Filtered, NIter, GARROT, 30);

		imshow(window_name, frame);

		double M = 0, m = 0;
		//----------------------------------------------------
		// Normalization to 0-1 range (for visualization)
		//----------------------------------------------------
		minMaxLoc(Dst, &m, &M);
		if ((M - m)>0) { Dst = Dst*(1.0 / (M - m)) - m / (M - m); }
		imshow("Coeff", Dst);

		minMaxLoc(Filtered, &m, &M);
		if ((M - m)>0) { Filtered = Filtered*(1.0 / (M - m)) - m / (M - m); }
		imshow("Filtered", Filtered);

		char key = (char)waitKey(0);
		switch (key)
		{
		case 'q':
		case 'Q':
		case 27: //escape key
			return 0;
		case ' ': //Save an image
			sprintf(filename, "filename%.3d.jpg", n++);
			imwrite(filename, frame);
			cout << "Saved " << filename << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}

int main(int ac, char** av)
{
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		return 1;
	}
	return process(capture);
}
