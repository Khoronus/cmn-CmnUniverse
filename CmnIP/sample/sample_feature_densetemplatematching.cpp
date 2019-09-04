/**
* @file test_densetemplatematching.cpp
* @brief Test a simple dense template matching.
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

#include "draw/inc/draw/draw_headers.hpp"
#include "feature/inc/feature/feature_headers.hpp"

namespace
{


/** @brief Class to perform some simple operations over matrix
*/
class MatrixOperations
{
public:

	/** @brief Calculate the ratio between two matrix.

		@note The matrix are expected to be CV_32F
		@return Return 1 in case of success. 0 otherwise.
	*/
	static int ratio(const cv::Mat &a, const cv::Mat &b, cv::Mat &out)
	{
		if (a.size() != b.size()) return 0;
		if (a.type() != b.type() && a.type() != CV_32F) return 0;
		if (out.empty()) out = cv::Mat::zeros(a.size(), a.type());

		int w = a.cols, h = a.rows;
		//out = cv::Mat(a.size(), a.type(), cv::Scalar::all(0));
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				float va = a.at<float>(y, x);
				float vb = b.at<float>(y, x);
				//std::cout << va << " " << vb << std::endl;
				if (va != 0 && vb != 0)
				{
					out.at<float>(y, x) = (std::min)(va / vb, vb / va);
				} else {
					out.at<float>(y, x) = 0;
				}
			}
		}
		return 1;
	}

};


/** Example of use of a sample combine image
*/
void test()
{
	bool show = true;
	if (false)
	{
		// Example
		cv::Mat f(8, 8, CV_32FC1, cv::Scalar::all(0));
		for (int y = 0; y < f.rows; y++)
		for (int x = 0; x < f.rows; x++)
		f.at<float>(y, x) = (float)std::rand() / (float)RAND_MAX;

		cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
		CmnIP::draw::HeatMap::draw(f, m);
		cv::imshow("m", m);
		//cv::imwrite("m.png", m);
		cv::waitKey();
	}

	cv::Mat outputA, outputB, outputC;
	{
		cv::Mat src = cv::imread("..\\..\\data\\PatchFront1.jpg");
		cv::imshow("srcA", src);
		cv::Mat output;
		CmnIP::feature::Dense::linear10histo(src, show, output);
		cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
		CmnIP::draw::HeatMap::draw(output, m);
		cv::imshow("mF", m);
		//cv::imwrite("mF.png", m);
		//cv::waitKey();
		outputA = output;
		//cv::waitKey();
	}
	{
		cv::Mat src = cv::imread("..\\..\\data\\PatchLeft0.jpg");
		cv::imshow("srcB", src);
		cv::Mat output;
		CmnIP::feature::Dense::linear10histo(src, show, output);
		cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
		CmnIP::draw::HeatMap::draw(output, m);
		cv::imshow("mL", m);
		//cv::imwrite("mL.png", m);
		//cv::waitKey();
		outputB = output;
	}
	{
		cv::Mat src = cv::imread("..\\..\\data\\PatchLeft1.jpg");
		cv::imshow("srcC", src);
		cv::Mat output;
		CmnIP::feature::Dense::linear10histo(src, show, output);
		cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
		CmnIP::draw::HeatMap::draw(output, m);
		cv::imshow("mLB", m);
		//cv::imwrite("mLB.png", m);
		//cv::waitKey();
		outputC = output;	
	}
	//std::cout << "$$$ " << outputA << std::endl;
	//std::cout << "$$$ " << outputB << std::endl;
	//std::cout << "$$$ " << outputC << std::endl;

	cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
	MatrixOperations::ratio(outputA, outputB, outputB);
	MatrixOperations::ratio(outputA, outputC, outputC);
	//std::cout << outputB << std::endl << outputC << std::endl;
	CmnIP::draw::HeatMap::draw(outputB, m);
	cv::imshow("m+", m);
	//cv::imwrite("m+.png", m);
	CmnIP::draw::HeatMap::draw(outputC, m);
	cv::imshow("m-", m);
	//cv::imwrite("m-.png", m);
	cv::waitKey();
	cv::destroyAllWindows();
}



/** @brief Show a set of plot over the image.
*/
void test_multiple_areas()
{
	std::cout << "ESC to quit" << std::endl;
	cv::Mat src_in = cv::imread("..\\..\\data\\fish_left.jpg");
	if (src_in.empty()) {
		std::cout << "Unable to open the source file ../../data/fish_left.jpg" << std::endl;
		return;
	}
	cv::Mat src_ = src_in(cv::Rect(src_in.cols / 2, 0, src_in.cols / 2, src_in.rows));// src_;//
	cv::Mat model_in = cv::imread("..\\..\\data\\fish_front.jpg");
	if (model_in.empty()) {
		std::cout << "Unable to open the source file ../../data/fish_front.jpg" << std::endl;
		return;
	}
	cv::Mat model_ = model_in(cv::Rect(0, 0, model_in.cols / 2, src_.rows));// model_in;//

	cv::Mat m(src_in.size(), CV_32FC1, cv::Scalar::all(0));
	int kW = 150, kH = 150;
	cv::Mat a(kH, kW, CV_32FC1, cv::Scalar::all(1));

	for (int y_ = 0; y_ <= src_.rows - a.rows; y_ += a.rows)
	{
		for (int x_ = 0; x_ <= src_.cols - a.cols; x_ += a.cols)
		{
			cv::Mat src = src_(cv::Rect(x_, y_, kW, kH));
			cv::Mat src_clone = src_.clone();
			cv::rectangle(src_clone, cv::Rect(x_, y_, kW, kH), cv::Scalar(0, 0, 255), 3);
			cv::resize(src_clone, src_clone, cv::Size(512, 512));
			cv::imshow("src_clone", src_clone);
			for (int y = 0; y <= model_.rows - a.rows; y += a.rows)
			{
				for (int x = 0; x <= model_.cols - a.cols; x += a.cols)
				{
					cv::Mat model_clone = model_.clone();
					cv::rectangle(model_clone, cv::Rect(x, y, kW, kH), cv::Scalar(0, 0, 255), 3);
					cv::resize(model_clone, model_clone, cv::Size(512, 512));
					cv::imshow("model_clone", model_clone);
					cv::Mat model = model_(cv::Rect(x, y, kW, kH));

					cv::Mat outputA, outputB, outputC;
					CmnIP::feature::Dense::linear10histo(src, false, outputA);
					CmnIP::feature::Dense::linear10histo(model, false, outputB);
					cv::Mat m(512, 512, CV_8UC3, cv::Scalar::all(0));
					MatrixOperations::ratio(outputA, outputB, outputB);
					CmnIP::draw::HeatMap::draw(outputB, m);
					cv::imshow("m", m);
					if (cv::waitKey(10) == 27) return;
				}
			}
		}
	}
	cv::destroyAllWindows();
}



}  // namespace anonymous


/** Main function
*/
void main()
{
	test();
	test_multiple_areas();
}