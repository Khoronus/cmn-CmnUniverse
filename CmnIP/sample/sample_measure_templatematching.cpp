/**
* @file sample_matching_template.cpp
* @brief Sample for the template matching.
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
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "measure/inc/measure/measure_headers.hpp"

namespace
{

/** @brief Show a set of plot over the image.
*/
void test_multiple_areas()
{
	//cv::Mat src = cv::imread("../../data/scene_000.png");
	//cv::Mat model = src(cv::Rect(150,200,200,250));
	cv::Mat src_ = cv::imread("..\\..\\data\\fish_left.jpg");
	cv::Mat src =  src_(cv::Rect(src_.cols / 2, 0, src_.cols / 2, src_.rows));// src_;//
	//cv::Mat model = cv::imread("../../data/1_patch.jpg");
	cv::Mat model_in = cv::imread("..\\..\\data\\fish_front.jpg");
	cv::Mat model_ = model_in(cv::Rect(0, 0, model_in.cols / 2, src_.rows));// model_in;//

	cv::Mat m(src.size(), CV_32FC1, cv::Scalar::all(0));
	int kW = 150, kH = 150;
	cv::Mat a(kH, kW, CV_32FC1, cv::Scalar::all(1));

	for (int y = 0; y <= model_.rows - a.rows; y += a.rows)
	{
		for (int x = 0; x <= model_.cols - a.cols; x += a.cols)
		{
			cv::Mat model_clone = model_.clone();
			cv::rectangle(model_clone, cv::Rect(x, y, kW, kH), cv::Scalar(0,0,255), 3);
			cv::imshow("model_clone", model_clone);
			//cv::Mat src = src_(cv::Rect(src_.cols / 2, y, src_.cols / 2, a.rows + 1));
			cv::Mat model = model_(cv::Rect(x, y, kW, kH));
			cv::imshow("model", model);
			cv::Rect region_out;
			double likelihood;
			CmnIP::measure::TemplateMatching::region(src, model, 5, true, region_out,
				likelihood);
			std::cout << "Likelihood: " << likelihood << std::endl;
			if (likelihood > -0.4) {
				cv::imshow("src", src);
				cv::waitKey(10);
				cv::Mat tmp(m.size(), CV_32FC1, cv::Scalar::all(0));
				a.copyTo(tmp(region_out));
				m += tmp;

				double minVal, maxVal;
				cv::minMaxLoc(m, &minVal, &maxVal);
				cv::normalize(m, tmp, maxVal);
				cv::resize(tmp, tmp, cv::Size(m.cols / 2, m.rows / 2));
				cv::imshow("m", tmp);
			}
			cv::Mat src_clone = src.clone();
			cv::rectangle(src_clone, region_out, cv::Scalar(0, 0, 255), 3);
			cv::imshow("src_clone", src_clone);

			//cv::imwrite("src_clone.png", src_clone);
			//cv::imwrite("model_clone.png", model_clone);

			if (cv::waitKey() == 27) return;
		}
	}
	cv::destroyAllWindows();
}


/** @brief Show a set of plot over the image.
*/
void test_regions()
{
	cv::Mat src_ = cv::imread("..\\..\\data\\fish_left.jpg");
	cv::Mat src = src_(cv::Rect(src_.cols / 2, 0, src_.cols / 2, src_.rows));// src_;//
	cv::Mat model_ = cv::imread("..\\..\\data\\fish_front.jpg");

	std::ifstream myfile("..\\..\\data\\regions.txt");
	if (!myfile.is_open()) {
		std::cout << "Unable to find the file regions.txt" << std::endl;
		std::cout << "The file contains the coordinate of rectangular areas" << std::endl;
		std::cout << "File format " << std::endl;
		std::cout << "TL_X TL_Y BR_X BR_Y" << std::endl;
		return;
	}
	std::vector<std::pair<cv::Rect, cv::Rect>> vrect;
	while (!myfile.eof())
	{
		char buf[512];
		int x, y, w, h;
		myfile.getline(buf, 512);
		std::cout << "buf: " << buf << std::endl;
		if (std::strlen(buf) > 2) {
			sscanf(buf, "%i %i %i %i", &x, &y, &w, &h);
			if (x >= 0 && y >= 0 && (x + w) < src.cols &&
				(y + h) < src.rows) {
				vrect.push_back(std::make_pair(cv::Rect(x, y, w, h), cv::Rect(x, y, w, h)));
			}
		}
	}

	cv::Mat combo((std::max)(model_.rows, src.rows), model_.cols + src.cols,
		src.type(), cv::Scalar::all(0));
	model_.copyTo(combo(cv::Rect(0, 0, model_.cols, model_.rows)));
	src.copyTo(combo(cv::Rect(model_.cols, 0, src.cols, src.rows)));

	cv::RNG rng(12345);
	for (auto it = vrect.begin(); it != vrect.end(); it++)
	{
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::Mat model_clone = model_.clone();
		cv::rectangle(model_clone, it->first, color, 3);
		cv::rectangle(combo, it->first, color, 5);
		cv::resize(model_clone, model_clone, cv::Size(512, 512));
		cv::imshow("model_clone", model_clone);
		cv::Mat model = model_(it->first);
		cv::imshow("model", model);
		cv::Rect region_out;
		double likelihood;
		CmnIP::measure::TemplateMatching::region(src, model, 5, true, region_out,
			likelihood);
		std::cout << "Likelihood: " << likelihood << std::endl;
		cv::Mat src_clone = src.clone();
		cv::rectangle(src_clone, region_out, color, 3);
		cv::rectangle(combo, cv::Rect(region_out.x + model_.cols, region_out.y, region_out.width, region_out.height), 
			color, 5);
		cv::resize(src_clone, src_clone, cv::Size(512, 512));
		cv::imshow("src_clone", src_clone);
		cv::Mat tmp;
		cv::resize(combo, tmp, cv::Size(1024, 512));
		cv::imshow("combo", tmp);

		//cv::imwrite("src_clone.png", src_clone);
		//cv::imwrite("model_clone.png", model_clone);
		cv::imwrite("combo.png", combo);

		it->second = region_out;
		if (cv::waitKey(0) == 27) break;
	}


	// Salve the regions detected
	if (false)
	{
		std::ofstream myfile_out("regions_sd.txt");
		//cv::Mat cpy = curr.clone();
		// rescale the features
		for (auto it = vrect.begin(); it != vrect.end(); it++)
		{
			myfile_out << it->first.x << " " << it->first.y << " " <<
				it->first.width << " " << it->first.height << " " <<
				it->second.x << " " << it->second.y << " " << it->second.width <<
				" " << it->second.height << std::endl;
		}
		//cv::imshow("cpy", cpy);
		myfile_out.close();
		myfile_out.clear();
	}

	cv::destroyAllWindows();
}


void test()
{
	cv::Mat src = cv::imread("../../data/out_front.jpg");
	cv::Mat model = src(cv::Rect(150,200,200,250));
	cv::imshow("model", model);
	cv::Rect region_out;
	double likelihood;
	CmnIP::measure::TemplateMatching::region(src, model, 5, true, region_out,
		likelihood);
	std::cout << "Likelihood: " << likelihood << std::endl;
	cv::waitKey();
	cv::destroyAllWindows();
}


} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample Matching Template" << std::endl;

	test();
	test_multiple_areas();
	test_regions();
	
	return 0;
}
