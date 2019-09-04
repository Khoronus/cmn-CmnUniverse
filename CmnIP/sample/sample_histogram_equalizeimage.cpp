/**
* @file sample_numericsystem_numericsystem.cpp
* @brief Sample dynamic.
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

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram/inc/histogram/histogram_headers.hpp"

namespace
{

/** @brief It creates a matrix with probability values in a float container
*/
void create_float_mask()
{
	cv::Mat m(512, 512, CV_32F, cv::Scalar::all(0));
	float min_angle = CV_PI / 4, max_angle = CV_PI / 2, bin_angle = 0.1;
	float min_radius = 0, max_radius = 400, bin_radius = 0.1;
	for (float v = min_radius; v <= max_radius; v += bin_radius)
	{
		for (float a = min_angle; a <= max_angle; a += bin_angle)
		{
			float x = (std::cos)(a)* v + 256;
			float y = (std::sin)(a)* v + 256;
			float prob = (a - min_angle) / (max_angle - min_angle);
			if (y >= 0 && x >= 0 && x < m.cols && y < m.rows) {
				m.at<float>(y, x) = 1 - prob;
			}
		}
	}
	min_angle = 0;
	max_angle = CV_PI / 4;
	for (float v = min_radius; v <= max_radius; v += bin_radius)
	{
		for (float a = min_angle; a <= max_angle; a += bin_angle)
		{
			float x = (std::cos)(a)* v + 256;
			float y = (std::sin)(a)* v + 256;
			float prob = (a - min_angle) / (max_angle - min_angle);
			if (y >= 0 && x >= 0 && x < m.cols && y < m.rows) {
				m.at<float>(y, x) = prob;
			}
		}
	}
	cv::Mat t;
	cv::resize(m, t, cv::Size(1024, 1024));
	cv::imshow("m", m);
	m.convertTo(t, CV_8U, 256);
	cv::imshow("t", t);
	cv::imwrite("t.png", t);
	cv::waitKey();
}


//-----------------------------------------------------------------------------
void combine(const cv::Mat &img, const cv::Mat &ref, const cv::Mat &mprob,
	const cv::Mat &mprobneg, cv::Mat &out, bool copy)
{
	cv::Mat src = img;// .clone();
	if (copy) src = img.clone();

	cv::Mat result(img.size(), CV_32FC3);
	for (int y = 0; y < result.rows; y++)
	{
		for (int x = 0; x < result.cols; x++)
		{
			//std::cout << x << " " << y << " " << channelfloat.at<float>(y, x) << " " << mprob.at<float>(y, x) << " " <<
			//channelfloatadj.at<float>(y, x) << " " << mprobneg.at<float>(y, x) << std::endl;

			for (int c = 0; c < 3; ++c)
			{
				result.at<cv::Vec3f>(y, x)[c] = src.at<cv::Vec3b>(y, x)[c] * mprob.at<float>(y, x) +
					ref.at<cv::Vec3b>(y, x)[c] * mprobneg.at<float>(y, x);
			}
		}
	}
	result.convertTo(out, CV_8UC3);
}


// Test the  light condition equalization with probability mask
void blending_and_probabiliy_mask()
{
	std::string path = "../../data";
	std::string folder = "/LightCondition4";

	//cv::Mat ref = cv::imread(path + folder + "/1.jpg");
	cv::Mat ref = cv::imread(path + folder + "/01.png");
	if (ref.empty()) return;
	char buf[1024];
	sprintf(buf, "/02");
	cv::Mat src = cv::imread(path + folder + buf + ".png");
	//cv::Mat src = cv::imread("red.png");
	if (src.empty()) return;

	// Make the source red
	for (int y = 0; y < src.rows; ++y)
	{
		for (int x = 0; x < src.cols; ++x)
		{
			for (int c = 0; c < 2; ++c)
			{
				src.at<cv::Vec3b>(y, x)[c] = 0;
			}
		}
	}

	cv::imshow("src", src);


	cv::Mat mprob(src.size(), CV_32F, cv::Scalar::all(1));
	cv::Mat mprobneg(src.size(), CV_32F, cv::Scalar::all(0));
	// Set the probability region
	float ymin = 0, ymax = mprob.rows, xmin = 0, xmax = 1000;
	for (int y = ymin; y < ymax; y++)
	{
		float prob = (float)(y - ymin) / (float)(ymax - ymin);
		for (int x = xmin; x < xmax; x++)
		{
			mprob.at<float>(y, x) = prob;
			mprobneg.at<float>(y, x) = 1 - prob;
		}
	}

	cv::Mat src_copy = src.clone();
	cv::Mat out;
	CmnIP::histogram::EqualizeImage::color(src, ref, 0, out, false);
	CmnIP::histogram::EqualizeImage::color(src, ref, 1, out, false);
	CmnIP::histogram::EqualizeImage::color(src, ref, 2, out, false);
	cv::imshow("ref", ref);
	cv::imshow("result", out);
	cv::imwrite("result_ref.png", ref);
	cv::imwrite("result_src.png", src);
	cv::imwrite("result001.png", out);
	cv::waitKey();

	src = src_copy.clone();
	CmnIP::histogram::EqualizeImage::color(src, ref, mprob, mprobneg, 0, out, false);
	CmnIP::histogram::EqualizeImage::color(src, ref, mprob, mprobneg, 1, out, false);
	CmnIP::histogram::EqualizeImage::color(src, ref, mprob, mprobneg, 2, out, false);
	cv::imshow("ref", ref);
	cv::imshow("result", out);
	cv::imshow("mprob", mprob);
	cv::imshow("mprobneg", mprobneg);
	cv::imwrite("result002.png", out);
	cv::imwrite("mprob.png", mprob * 255);
	cv::imwrite("mprobneg.png", mprobneg * 255);

	combine(src, ref, mprob, mprobneg, out, false);
	cv::imshow("out", out);
	cv::imwrite("result003.png", out);
	cv::waitKey();

}





int example_light_equalization() {
	// http://sourceforge.net/p/emgucv/opencv_contrib/ci/bbda6c6322de94742c3798368aa763845cee2478/tree/modules/
	std::string path = "../../data";
	std::string folder = "/LightCondition5";
	// Apply some filters on the image
	for (int i = 1; i <= 4; i++)
	{
		cv::Mat tmp;
		int iAdd = 0;
		cv::Mat ref = cv::imread(path + folder + "/1.jpg");
		if (ref.empty()) {
			std::cout << "Unable to open the reference file" << std::endl;
			return 0;
		}
		char buf[1024];
		sprintf(buf, "/%i", i);
		cv::Mat src = cv::imread(path + folder + buf + ".jpg");
		if (src.empty()) {
			std::cout << "Unable to open the source file" << std::endl;
			return 0;
		}
		cv::resize(src, tmp, cv::Size(512, 512));
		cv::Mat result(tmp.rows, tmp.cols * 7, tmp.type());
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));
		cv::resize(ref, tmp, cv::Size(512, 512));
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));

		cv::imshow("src", src);
		cv::Mat out;
		//src = out.clone();
		CmnIP::histogram::EqualizeImage::adjust_intensity(src, ref, out, true);
		cv::resize(out, tmp, cv::Size(512, 512));
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));
		cv::imshow("intensity", out);
		cv::imwrite(path + folder + buf + "intensity_ref.jpg", out);
		cv::Mat src_clone = src.clone();
		CmnIP::histogram::EqualizeImage::color(src, ref, 0, out, false);
		CmnIP::histogram::EqualizeImage::color(src, ref, 1, out, false);
		CmnIP::histogram::EqualizeImage::color(src, ref, 2, out, false);
		src = src_clone.clone();
		cv::resize(out, tmp, cv::Size(512, 512));
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));
		cv::imshow("color_ref", out);
		cv::imwrite(path + folder + buf + "color_ref.jpg", out);
		CmnIP::histogram::EqualizeImage::equalize_intensity(src, out);
		cv::resize(out, tmp, cv::Size(512, 512));
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));
		cv::imshow("intensity", out);
		cv::imwrite(path + folder + buf + "intensity.jpg", out);
		CmnIP::histogram::EqualizeImage::rgbclahe(src, out);
		cv::resize(out, tmp, cv::Size(512, 512));
		tmp.copyTo(result(cv::Rect(tmp.cols * iAdd++, 0, tmp.cols, tmp.rows)));
		cv::imshow("rgbclahe", out);
		cv::imwrite(path + folder + buf + "rgbclahe.jpg", out);
		cv::imwrite(path + folder + buf + "panel.jpg", result);
	}
	return 1;
}


void test()
{
	std::cout << "create_float_mask" << std::endl;
	create_float_mask();
	std::cout << "blending_and_probabiliy_mask" << std::endl;
	blending_and_probabiliy_mask();
	std::cout << "example_light_equalization" << std::endl;
	//example_light_equalization();
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample Histogram Equalization" << std::endl;

	test();
}


