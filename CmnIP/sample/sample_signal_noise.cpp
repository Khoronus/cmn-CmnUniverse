/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "signal/inc/signal/signal_headers.hpp"
//#include "ts.hpp"

namespace
{

/** Test the functions
*/
void test()
{
	// Random
	{
		cv::Mat m = cv::Mat::zeros(512, 512, CV_8U);
		CmnIP::signal::RandomNoise gen = CmnIP::signal::RandomNoise();
		for (int y = 0; y < m.rows; y++)
		{
			for (int x = 0; x < m.cols; x++)
			{
				m.at<uchar>(y, x) = (uchar)(gen.Get2D(x, y) * 255);
			}
		}
		cv::imshow("RandomNoise", m);
	}
	// Value
	{
		cv::Mat m = cv::Mat::zeros(512, 512, CV_8U);
		CmnIP::signal::ValueNoise gen = CmnIP::signal::ValueNoise();
		for (int y = 0; y < m.rows; y++)
		{
			for (int x = 0; x < m.cols; x++)
			{
				float f = gen.Get2D(x, y);
				//std::cout << f << std::endl;
				m.at<uchar>(y, x) = (uchar)(f * 255);
			}
		}
		cv::imshow("ValueNoise", m);
	}
	// Perlin
	{
		cv::Mat m = cv::Mat::zeros(512, 512, CV_8U);
		CmnIP::signal::PerlinNoise gen = CmnIP::signal::PerlinNoise();
		for (float y = 0; y < m.rows; y++)
		{
			for (float x = 0; x < m.cols; x++)
			{
				float f = gen.Get2D(x, y);
				//std::cout << f << std::endl;
				m.at<uchar>(y, x) = (uchar)(f * 255);
			}
		}
		cv::imshow("PerlinNoise", m);
	}
	// Simplex
	{
		cv::Mat m = cv::Mat::zeros(512, 512, CV_8U);
		CmnIP::signal::SimplexNoise gen = CmnIP::signal::SimplexNoise();
		for (float y = 0; y < m.rows; y++)
		{
			for (float x = 0; x < m.cols; x++)
			{
				float f = gen.Get2D(x, y);
				//std::cout << f << std::endl;
				m.at<uchar>(y, x) = (uchar)(f * 255);
			}
		}
		cv::imshow("SimplexNoise", m);
	}
	// Worley (cell noise)
	{
		cv::Mat m = cv::Mat::zeros(512, 512, CV_8U);
		CmnIP::signal::WorleyNoise gen = CmnIP::signal::WorleyNoise();
		for (int y = 0; y < m.rows; y++)
		{
			for (int x = 0; x < m.cols; x++)
			{
				float f = gen.Get2D(x, y);
				//std::cout << f << std::endl;
				m.at<uchar>(y, x) = (uchar)(f * 255);
			}
		}
		cv::imshow("WorleyNoise", m);
	}

	cv::waitKey();
}

}	// namespace

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Test signal texture generation with random noise" << 
		std::endl;
	test();
}

#endif