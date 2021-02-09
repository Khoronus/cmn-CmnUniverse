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


#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include "cmnipcore/inc/cmnipcore/cmnipcore_headers.hpp"
#include "measure/inc/measure/measure_headers.hpp"

class Algorithm
{
public:

	virtual void foo() = 0;
};


class IdentifyRegionsCore : public Algorithm
{
public:

	virtual void get(const cv::Mat &image, std::vector< cv::Point > &points) = 0;

	virtual void foo() {}
};

class TemplateRegionsIdentifier : public IdentifyRegionsCore
{
public:

	static int get(const cv::Mat &image, const cv::Mat &model, float min_likelihood,
		std::vector< std::pair<cv::Point, float> > &points) {

		// check that the image data is not empty
		if (image.empty()) return 0;
		if (model.empty()) return 0;
		if (model.cols > image.cols || model.rows > image.rows) return 0;
		// Check that the image and model size are compatible.
		//if (image.size() < model.size()) return 0;
		// Capture the first frame to get the image dimension
		cv::Mat result;

		/// Create the result matrix
		int result_cols = image.cols - model.cols + 1;
		int result_rows = image.rows - model.rows + 1;

		result.create(result_cols, result_rows, CV_32FC1);

		// Do the Matching and Normalize
		cv::matchTemplate(image, model, result, 5);
		cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		//std::cout << "image: " << image.cols << " " << image.rows << std::endl;
		//std::cout << "model: " << model.cols << " " << model.rows << std::endl;
		//std::cout << "result: " << result.cols << " " << result.rows << std::endl;
		for (int y = 0; y < result_rows; y++)
		{
			for (int x = 0; x < result_cols; x++)
			{
				float p = result.at<float>(y, x);
				//std::cout << "p " << p << std::endl;
				if (p >= min_likelihood) {
					points.push_back(std::make_pair(cv::Point(x + model.cols / 2 - 1, y + model.rows / 2 - 1), p));
				}
			}
		}

		cv::imshow("result_window", result);
		return 1;
	}
};


namespace 
{

/** @brief Show a set of plot over the image.
*/
void test_regions()
{
	cv::Mat img_template_ = cv::imread("..\\..\\data\\fish_front.jpg");
	cv::Mat img_template = img_template_(cv::Rect(0, 0, img_template_.cols / 2, img_template_.rows));// src_;//
	img_template_ = img_template;
	cv::Mat reference_ = cv::imread("..\\..\\data\\fish_left.jpg");
	cv::Mat reference = reference_(cv::Rect(reference_.cols / 2, 0, reference_.cols / 2, reference_.rows));// src_;//
	reference_ = reference;

	std::ifstream myfile("..\\..\\data\\regions.txt");
	std::vector<std::pair<cv::Rect, cv::Rect>> vrect;
	while (!myfile.eof())
	{
		char buf[512];
		int x, y, w, h;
		myfile.getline(buf, 512);
		std::cout << "buf: " << buf << std::endl;
		if (std::strlen(buf) > 2) {
			sscanf(buf, "%i %i %i %i", &x, &y, &w, &h);
			if (x >= 0 && y >= 0 && (x + w) < img_template_.cols &&
				(y + h) < img_template_.rows) {
				vrect.push_back(std::make_pair(cv::Rect(x, y, w, h), cv::Rect(x, y, w, h)));
			}
		}
	}

	cv::Mat combo((std::max)(reference_.rows, img_template_.rows), reference_.cols + img_template_.cols,
		img_template_.type(), cv::Scalar::all(0));
	img_template_.copyTo(combo(cv::Rect(0, 0, img_template_.cols, img_template_.rows)));
	reference_.copyTo(combo(cv::Rect(img_template_.cols, 0, reference_.cols, reference_.rows)));
	cv::RNG rng(12345);
	for (auto it = vrect.begin(); it != vrect.end(); it++)
	{
		cv::Mat combo_copy = combo.clone();

		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//cv::Mat model_clone = model_.clone();
		//cv::rectangle(model_clone, it->first, color, 3);
		cv::rectangle(combo_copy, it->first, color, 5);
		//cv::resize(model_clone, model_clone, cv::Size(512, 512));
		//cv::imshow("model_clone", model_clone);
		cv::Mat img_template = img_template_(it->first);
		//cv::imshow("model", model);
		cv::Rect region_out;
		double likelihood;
		//genericcv::matching::TemplateMatching::region(src, model, 5, true, region_out,
		//	likelihood);
		std::vector< std::pair<cv::Point, float> > points;
		TemplateRegionsIdentifier::get(reference_, img_template, 0.9, points);
		std::cout << "Likelihood: " << points.size() << std::endl;
		for (auto it2 = points.begin(); it2 != points.end(); it2++)
		{
			//cv::line(combo_copy, cv::Point(it->first.x + it->first.width / 2, it->first.y + it->first.height / 2),
			//	cv::Point(it2->first.x + img_template_.cols, it2->first.y),
			//	cv::Scalar(255 - 255 * it2->second, 0, 255 * it2->second), 1);
			cv::circle(combo_copy, cv::Point(it2->first.x + img_template_.cols, it2->first.y), 1,
				cv::Scalar(255 - 255 * it2->second, 0, 255 * it2->second), 1);
		}
		//cv::Mat src_clone = src.clone();
		//cv::rectangle(src_clone, region_out, color, 3);
		//cv::rectangle(combo, cv::Rect(region_out.x + model_.cols, region_out.y, region_out.width, region_out.height),
		//	color, 5);
		//cv::resize(src_clone, src_clone, cv::Size(512, 512));
		//cv::imshow("src_clone", src_clone);
		cv::Mat tmp;
		cv::resize(combo_copy, tmp, cv::Size(1024, 512));
		cv::imshow("combo", tmp);

		//cv::imwrite("src_clone.png", src_clone);
		//cv::imwrite("model_clone.png", model_clone);
		//cv::imwrite("combo.png", combo);

		it->second = region_out;
		cv::waitKey(0);
	}

}


} // namespace anonymous

// ############################################################################

int main(int argc, char* argv[])
{
	std::cout << "Sample Matching Template" << std::endl;

	test_regions();
	return 0;
}
