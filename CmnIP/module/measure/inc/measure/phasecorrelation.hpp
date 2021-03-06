/**
* @file phase_correlation.hpp
* @brief Perform a phase correlation matching.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNIP_MEASURE_PHASECORRELATION_HPP__
#define CMNIP_MEASURE_PHASECORRELATION_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"

namespace CmnIP
{
namespace measure
{

/** @brief Performs phase correlation.
*/
class PhaseCorrelation
{
public:

	/** @brief It performs a phase correlation between two images.
	*/
	static cv::Point2d phaseCorrelateTest(cv::InputArray &_src1,
		cv::InputArray &_src2, cv::InputArray &_window, double* response)
	{
		cv::Mat src1 = _src1.getMat();
		cv::Mat src2 = _src2.getMat();
		cv::Mat window = _window.getMat();

		CV_Assert(src1.type() == src2.type());
		CV_Assert(src1.type() == CV_32FC1 || src1.type() == CV_64FC1);
		CV_Assert(src1.size == src2.size);

		if (!window.empty())
		{
			CV_Assert(src1.type() == window.type());
			CV_Assert(src1.size == window.size);
		}

		int M = cv::getOptimalDFTSize(src1.rows);
		int N = cv::getOptimalDFTSize(src1.cols);

		cv::Mat padded1, padded2, paddedWin;

		if (M != src1.rows || N != src1.cols)
		{
			cv::copyMakeBorder(src1, padded1, 0, M - src1.rows, 0,
				N - src1.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
			cv::copyMakeBorder(src2, padded2, 0, M - src2.rows, 0,
				N - src2.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

			if (!window.empty())
			{
				cv::copyMakeBorder(window, paddedWin, 0, M - window.rows, 0,
					N - window.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
			}
		}
		else
		{
			padded1 = src1;
			padded2 = src2;
			paddedWin = window;
		}

		cv::Mat FFT1, FFT2, P, Pm, C;

		// perform window multiplication if available
		if (!paddedWin.empty())
		{
			// apply window to both images before proceeding...
			cv::multiply(paddedWin, padded1, padded1);
			cv::multiply(paddedWin, padded2, padded2);
		}

		// execute phase correlation equation
		// Reference: http://en.wikipedia.org/wiki/Phase_correlation
		cv::dft(padded1, FFT1, cv::DFT_REAL_OUTPUT);
		cv::dft(padded2, FFT2, cv::DFT_REAL_OUTPUT);

		cv::mulSpectrums(FFT1, FFT2, P, 0, true);

		magSpectrumsTest(P, Pm);
		divSpectrumsTest(P, Pm, C, 0, false); // FF* / |FF*| (phase correlation equation completed here...)

		cv::idft(C, C); // gives us the nice peak shift location...

		fftShiftTest(C); // shift the energy to the center of the frame.

		cv::Mat tmp = C.clone();
		// Transform the matrix with float values into a
#if CV_MAJOR_VERSION == 3
		cv::normalize(tmp, tmp, 0, 1, CV_MINMAX); 
#elif CV_MAJOR_VERSION == 4
		cv::normalize(tmp, tmp, 0, 1, cv::NORM_MINMAX); 
#endif

		cv::Scalar mean_ = cv::mean(tmp);
		std::cout << "Mean: " << mean_ << std::endl;
		// viewable image form (float between values 0 and 1).
		cv::imshow("PhaseCorrelation::spectrum", tmp);
		//   // Save the spectrum
		//cv::Mat tmp_gray(tmp.size(), CV_8UC1);
		//for (int y = 0; y < tmp.rows; y++)
		//{
		//	for (int x = 0; x < tmp.cols; x++)
		//	{
		//		tmp_gray.at<char>(y,x) = tmp.at<double>(y,x) * 256;
		//	}
		//}
		//cv::imwrite("C:\\Users\\moro\\Desktop\\BView\\data\\Spectrum.bmp", tmp_gray);



		// locate the highest peak
		cv::Point peakLoc;
		cv::minMaxLoc(C, NULL, NULL, NULL, &peakLoc);

		// get the phase shift with sub-pixel accuracy, 5x5 window seems about right here...
		cv::Point2d t;
		t = weightedCentroidTest(C, peakLoc, cv::Size(5, 5), response);

		//cv::Mat tmp = C.clone();
		//normalize(tmp, tmp, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
		//                                           // viewable image form (float between values 0 and 1).
		//cv::Mat tmp_gray(tmp.size(), CV_8UC1);
		//for (int y = 0; y < tmp.rows; y++)
		//{
		//	for (int x = 0; x < tmp.cols; x++)
		//	{
		//		tmp_gray.at<char>(y,x) = tmp.at<double>(y,x) * 256;
		//	}
		//}
		//cv::cvtColor(tmp_gray, tmp_gray, CV_GRAY2RGB);
		//cv::circle(tmp_gray, t, 10, cv::Scalar(0, 255));
		//imshow("spectrum magnitude", tmp_gray);


		// max response is M*N (not exactly, might be slightly larger due to rounding errors)
		if (response)
			*response /= M*N;

		// adjust shift relative to image center...
		cv::Point2d center((double)padded1.cols / 2.0,
			(double)padded1.rows / 2.0);

		return (center - t);
	}


private:

	static void magSpectrumsTest(cv::InputArray &_src, cv::OutputArray &_dst)
	{
		cv::Mat src = _src.getMat();
		int depth = src.depth(), cn = src.channels(), type = src.type();
		int rows = src.rows, cols = src.cols;
		int j, k;

		CV_Assert(type == CV_32FC1 || type == CV_32FC2 || type == CV_64FC1 || type == CV_64FC2);

		if (src.depth() == CV_32F)
			_dst.create(src.rows, src.cols, CV_32FC1);
		else
			_dst.create(src.rows, src.cols, CV_64FC1);

		cv::Mat dst = _dst.getMat();
		dst.setTo(0);//Mat elements are not equal to zero by default!

		bool is_1d = (rows == 1 || (cols == 1 && src.isContinuous() && dst.isContinuous()));

		if (is_1d)
			cols = cols + rows - 1, rows = 1;

		int ncols = cols*cn;
		int j0 = cn == 1;
		int j1 = ncols - (cols % 2 == 0 && cn == 1);

		if (depth == CV_32F)
		{
			const float* dataSrc = (const float*)src.data;
			float* dataDst = (float*)dst.data;

			size_t stepSrc = src.step / sizeof(dataSrc[0]);
			size_t stepDst = dst.step / sizeof(dataDst[0]);

			if (!is_1d && cn == 1)
			{
				for (k = 0; k < (cols % 2 ? 1 : 2); k++)
				{
					if (k == 1)
						dataSrc += cols - 1, dataDst += cols - 1;
					dataDst[0] = dataSrc[0] * dataSrc[0];
					if (rows % 2 == 0)
						dataDst[(rows - 1)*stepDst] = dataSrc[(rows - 1)*stepSrc] * dataSrc[(rows - 1)*stepSrc];

					for (j = 1; j <= rows - 2; j += 2)
					{
						dataDst[j*stepDst] = (float)std::sqrt((double)dataSrc[j*stepSrc] * dataSrc[j*stepSrc] +
							(double)dataSrc[(j + 1)*stepSrc] * dataSrc[(j + 1)*stepSrc]);
					}

					if (k == 1)
						dataSrc -= cols - 1, dataDst -= cols - 1;
				}
			}

			for (; rows--; dataSrc += stepSrc, dataDst += stepDst)
			{
				if (is_1d && cn == 1)
				{
					dataDst[0] = dataSrc[0] * dataSrc[0];
					if (cols % 2 == 0)
						dataDst[j1] = dataSrc[j1] * dataSrc[j1];
				}

				for (j = j0; j < j1; j += 2)
				{
					dataDst[j] = (float)std::sqrt((double)dataSrc[j] * dataSrc[j] + (double)dataSrc[j + 1] * dataSrc[j + 1]);
				}
			}
		}
		else
		{
			const double* dataSrc = (const double*)src.data;
			double* dataDst = (double*)dst.data;

			size_t stepSrc = src.step / sizeof(dataSrc[0]);
			size_t stepDst = dst.step / sizeof(dataDst[0]);

			if (!is_1d && cn == 1)
			{
				for (k = 0; k < (cols % 2 ? 1 : 2); k++)
				{
					if (k == 1)
						dataSrc += cols - 1, dataDst += cols - 1;
					dataDst[0] = dataSrc[0] * dataSrc[0];
					if (rows % 2 == 0)
						dataDst[(rows - 1)*stepDst] = dataSrc[(rows - 1)*stepSrc] * dataSrc[(rows - 1)*stepSrc];

					for (j = 1; j <= rows - 2; j += 2)
					{
						dataDst[j*stepDst] = std::sqrt(dataSrc[j*stepSrc] * dataSrc[j*stepSrc] +
							dataSrc[(j + 1)*stepSrc] * dataSrc[(j + 1)*stepSrc]);
					}

					if (k == 1)
						dataSrc -= cols - 1, dataDst -= cols - 1;
				}
			}

			for (; rows--; dataSrc += stepSrc, dataDst += stepDst)
			{
				if (is_1d && cn == 1)
				{
					dataDst[0] = dataSrc[0] * dataSrc[0];
					if (cols % 2 == 0)
						dataDst[j1] = dataSrc[j1] * dataSrc[j1];
				}

				for (j = j0; j < j1; j += 2)
				{
					dataDst[j] = std::sqrt(dataSrc[j] * dataSrc[j] + dataSrc[j + 1] * dataSrc[j + 1]);
				}
			}
		}
	}

	static void divSpectrumsTest(cv::InputArray &_srcA, cv::InputArray &_srcB,
		cv::OutputArray &_dst, int flags, bool conjB)
	{
		cv::Mat srcA = _srcA.getMat(), srcB = _srcB.getMat();
		int depth = srcA.depth(), cn = srcA.channels(), type = srcA.type();
		int rows = srcA.rows, cols = srcA.cols;
		int j, k;

		CV_Assert(type == srcB.type() && srcA.size() == srcB.size());
		CV_Assert(type == CV_32FC1 || type == CV_32FC2 || type == CV_64FC1 || type == CV_64FC2);

		_dst.create(srcA.rows, srcA.cols, type);
		cv::Mat dst = _dst.getMat();

		bool is_1d = (flags & cv::DFT_ROWS) || (rows == 1 || (cols == 1 &&
			srcA.isContinuous() && srcB.isContinuous() && dst.isContinuous()));

		if (is_1d && !(flags & cv::DFT_ROWS))
			cols = cols + rows - 1, rows = 1;

		int ncols = cols*cn;
		int j0 = cn == 1;
		int j1 = ncols - (cols % 2 == 0 && cn == 1);

		if (depth == CV_32F)
		{
			const float* dataA = (const float*)srcA.data;
			const float* dataB = (const float*)srcB.data;
			float* dataC = (float*)dst.data;
			float eps = FLT_EPSILON; // prevent div0 problems

			size_t stepA = srcA.step / sizeof(dataA[0]);
			size_t stepB = srcB.step / sizeof(dataB[0]);
			size_t stepC = dst.step / sizeof(dataC[0]);

			if (!is_1d && cn == 1)
			{
				for (k = 0; k < (cols % 2 ? 1 : 2); k++)
				{
					if (k == 1)
						dataA += cols - 1, dataB += cols - 1, dataC += cols - 1;
					dataC[0] = dataA[0] / (dataB[0] + eps);
					if (rows % 2 == 0)
						dataC[(rows - 1)*stepC] = dataA[(rows - 1)*stepA] / (dataB[(rows - 1)*stepB] + eps);
					if (!conjB)
					for (j = 1; j <= rows - 2; j += 2)
					{
						double denom = (double)dataB[j*stepB] * dataB[j*stepB] +
							(double)dataB[(j + 1)*stepB] * dataB[(j + 1)*stepB] + (double)eps;

						double re = (double)dataA[j*stepA] * dataB[j*stepB] +
							(double)dataA[(j + 1)*stepA] * dataB[(j + 1)*stepB];

						double im = (double)dataA[(j + 1)*stepA] * dataB[j*stepB] -
							(double)dataA[j*stepA] * dataB[(j + 1)*stepB];

						dataC[j*stepC] = (float)(re / denom);
						dataC[(j + 1)*stepC] = (float)(im / denom);
					}
					else
					for (j = 1; j <= rows - 2; j += 2)
					{

						double denom = (double)dataB[j*stepB] * dataB[j*stepB] +
							(double)dataB[(j + 1)*stepB] * dataB[(j + 1)*stepB] + (double)eps;

						double re = (double)dataA[j*stepA] * dataB[j*stepB] -
							(double)dataA[(j + 1)*stepA] * dataB[(j + 1)*stepB];

						double im = (double)dataA[(j + 1)*stepA] * dataB[j*stepB] +
							(double)dataA[j*stepA] * dataB[(j + 1)*stepB];

						dataC[j*stepC] = (float)(re / denom);
						dataC[(j + 1)*stepC] = (float)(im / denom);
					}
					if (k == 1)
						dataA -= cols - 1, dataB -= cols - 1, dataC -= cols - 1;
				}
			}

			for (; rows--; dataA += stepA, dataB += stepB, dataC += stepC)
			{
				if (is_1d && cn == 1)
				{
					dataC[0] = dataA[0] / (dataB[0] + eps);
					if (cols % 2 == 0)
						dataC[j1] = dataA[j1] / (dataB[j1] + eps);
				}

				if (!conjB)
				for (j = j0; j < j1; j += 2)
				{
					double denom = (double)(dataB[j] * dataB[j] + dataB[j + 1] * dataB[j + 1] + eps);
					double re = (double)(dataA[j] * dataB[j] + dataA[j + 1] * dataB[j + 1]);
					double im = (double)(dataA[j + 1] * dataB[j] - dataA[j] * dataB[j + 1]);
					dataC[j] = (float)(re / denom);
					dataC[j + 1] = (float)(im / denom);
				}
				else
				for (j = j0; j < j1; j += 2)
				{
					double denom = (double)(dataB[j] * dataB[j] + dataB[j + 1] * dataB[j + 1] + eps);
					double re = (double)(dataA[j] * dataB[j] - dataA[j + 1] * dataB[j + 1]);
					double im = (double)(dataA[j + 1] * dataB[j] + dataA[j] * dataB[j + 1]);
					dataC[j] = (float)(re / denom);
					dataC[j + 1] = (float)(im / denom);
				}
			}
		}
		else
		{
			const double* dataA = (const double*)srcA.data;
			const double* dataB = (const double*)srcB.data;
			double* dataC = (double*)dst.data;
			double eps = DBL_EPSILON; // prevent div0 problems

			size_t stepA = srcA.step / sizeof(dataA[0]);
			size_t stepB = srcB.step / sizeof(dataB[0]);
			size_t stepC = dst.step / sizeof(dataC[0]);

			if (!is_1d && cn == 1)
			{
				for (k = 0; k < (cols % 2 ? 1 : 2); k++)
				{
					if (k == 1)
						dataA += cols - 1, dataB += cols - 1, dataC += cols - 1;
					dataC[0] = dataA[0] / (dataB[0] + eps);
					if (rows % 2 == 0)
						dataC[(rows - 1)*stepC] = dataA[(rows - 1)*stepA] / (dataB[(rows - 1)*stepB] + eps);
					if (!conjB)
					for (j = 1; j <= rows - 2; j += 2)
					{
						double denom = dataB[j*stepB] * dataB[j*stepB] +
							dataB[(j + 1)*stepB] * dataB[(j + 1)*stepB] + eps;

						double re = dataA[j*stepA] * dataB[j*stepB] +
							dataA[(j + 1)*stepA] * dataB[(j + 1)*stepB];

						double im = dataA[(j + 1)*stepA] * dataB[j*stepB] -
							dataA[j*stepA] * dataB[(j + 1)*stepB];

						dataC[j*stepC] = re / denom;
						dataC[(j + 1)*stepC] = im / denom;
					}
					else
					for (j = 1; j <= rows - 2; j += 2)
					{
						double denom = dataB[j*stepB] * dataB[j*stepB] +
							dataB[(j + 1)*stepB] * dataB[(j + 1)*stepB] + eps;

						double re = dataA[j*stepA] * dataB[j*stepB] -
							dataA[(j + 1)*stepA] * dataB[(j + 1)*stepB];

						double im = dataA[(j + 1)*stepA] * dataB[j*stepB] +
							dataA[j*stepA] * dataB[(j + 1)*stepB];

						dataC[j*stepC] = re / denom;
						dataC[(j + 1)*stepC] = im / denom;
					}
					if (k == 1)
						dataA -= cols - 1, dataB -= cols - 1, dataC -= cols - 1;
				}
			}

			for (; rows--; dataA += stepA, dataB += stepB, dataC += stepC)
			{
				if (is_1d && cn == 1)
				{
					dataC[0] = dataA[0] / (dataB[0] + eps);
					if (cols % 2 == 0)
						dataC[j1] = dataA[j1] / (dataB[j1] + eps);
				}

				if (!conjB)
				for (j = j0; j < j1; j += 2)
				{
					double denom = dataB[j] * dataB[j] + dataB[j + 1] * dataB[j + 1] + eps;
					double re = dataA[j] * dataB[j] + dataA[j + 1] * dataB[j + 1];
					double im = dataA[j + 1] * dataB[j] - dataA[j] * dataB[j + 1];
					dataC[j] = re / denom;
					dataC[j + 1] = im / denom;
				}
				else
				for (j = j0; j < j1; j += 2)
				{
					double denom = dataB[j] * dataB[j] + dataB[j + 1] * dataB[j + 1] + eps;
					double re = dataA[j] * dataB[j] - dataA[j + 1] * dataB[j + 1];
					double im = dataA[j + 1] * dataB[j] + dataA[j] * dataB[j + 1];
					dataC[j] = re / denom;
					dataC[j + 1] = im / denom;
				}
			}
		}

	}


	static void fftShiftTest(cv::InputOutputArray &_out)
	{
		cv::Mat out = _out.getMat();

		if (out.rows == 1 && out.cols == 1)
		{
			// trivially shifted.
			return;
		}

		std::vector<cv::Mat> planes;
		cv::split(out, planes);

		int xMid = out.cols >> 1;
		int yMid = out.rows >> 1;

		bool is_1d = xMid == 0 || yMid == 0;

		if (is_1d)
		{
			xMid = xMid + yMid;

			for (size_t i = 0; i < planes.size(); i++)
			{
				cv::Mat tmp;
				cv::Mat half0(planes[i], cv::Rect(0, 0, xMid, 1));
				cv::Mat half1(planes[i], cv::Rect(xMid, 0, xMid, 1));

				half0.copyTo(tmp);
				half1.copyTo(half0);
				tmp.copyTo(half1);
			}
		}
		else
		{
			for (size_t i = 0; i < planes.size(); i++)
			{
				// perform quadrant swaps...
				cv::Mat tmp;
				cv::Mat q0(planes[i], cv::Rect(0, 0, xMid, yMid));
				cv::Mat q1(planes[i], cv::Rect(xMid, 0, xMid, yMid));
				cv::Mat q2(planes[i], cv::Rect(0, yMid, xMid, yMid));
				cv::Mat q3(planes[i], cv::Rect(xMid, yMid, xMid, yMid));

				q0.copyTo(tmp);
				q3.copyTo(q0);
				tmp.copyTo(q3);

				q1.copyTo(tmp);
				q2.copyTo(q1);
				tmp.copyTo(q2);
			}
		}

		merge(planes, out);
	}

	static cv::Point2d weightedCentroidTest(cv::InputArray &_src,
		cv::Point &peakLocation, cv::Size weightBoxSize, double* response)
	{
		cv::Mat src = _src.getMat();

		int type = src.type();
		CV_Assert(type == CV_32FC1 || type == CV_64FC1);

		int minr = peakLocation.y - (weightBoxSize.height >> 1);
		int maxr = peakLocation.y + (weightBoxSize.height >> 1);
		int minc = peakLocation.x - (weightBoxSize.width >> 1);
		int maxc = peakLocation.x + (weightBoxSize.width >> 1);

		cv::Point2d centroid;
		double sumIntensity = 0.0;

		// clamp the values to min and max if needed.
		if (minr < 0)
		{
			minr = 0;
		}

		if (minc < 0)
		{
			minc = 0;
		}

		if (maxr > src.rows - 1)
		{
			maxr = src.rows - 1;
		}

		if (maxc > src.cols - 1)
		{
			maxc = src.cols - 1;
		}

		if (type == CV_32FC1)
		{
			const float* dataIn = (const float*)src.data;
			dataIn += minr*src.cols;
			for (int y = minr; y <= maxr; y++)
			{
				for (int x = minc; x <= maxc; x++)
				{
					centroid.x += (double)x*dataIn[x];
					centroid.y += (double)y*dataIn[x];
					sumIntensity += (double)dataIn[x];
				}

				dataIn += src.cols;
			}
		}
		else
		{
			const double* dataIn = (const double*)src.data;
			dataIn += minr*src.cols;
			for (int y = minr; y <= maxr; y++)
			{
				for (int x = minc; x <= maxc; x++)
				{
					centroid.x += (double)x*dataIn[x];
					centroid.y += (double)y*dataIn[x];
					sumIntensity += dataIn[x];
				}

				dataIn += src.cols;
			}
		}

		if (response)
			*response = sumIntensity;

		sumIntensity += DBL_EPSILON; // prevent div0 problems...

		centroid.x /= sumIntensity;
		centroid.y /= sumIntensity;

		return centroid;
	}
};


class PhaseCorrelationItems
{
public:

	/** @brief Test the phase correlation between two images.
	*/
	void test(cv::Mat &model, cv::Mat &query, cv::Point2d &shift) {

		double xshift_p_tot = 0, yshift_p_tot = 0;
		cv::Mat query64f, model64f;

		if (hann_.empty())
		{
			cv::createHanningWindow(hann_, model.size(), CV_64F);
		}

		model.convertTo(model64f, CV_64F);
		query.convertTo(query64f, CV_64F);

		shift = PhaseCorrelation::phaseCorrelateTest(model64f, query64f,
			hann_, NULL);
	}

private:

	cv::Mat hann_;
};



} // namespace measure
} // namespace CmnIP

#endif // CMNIP_MEASURE_PHASECORRELATION_HPP__
