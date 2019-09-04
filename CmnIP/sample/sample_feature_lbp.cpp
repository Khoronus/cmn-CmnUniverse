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

#include <opencv2/opencv.hpp>

#include "feature/inc/feature/feature_headers.hpp"
#include "group/inc/group/group_headers.hpp"



int main(int argc, const char *argv[]) {
	int deviceId = 0;
	if (argc > 1)
		deviceId = atoi(argv[1]);

	cv::VideoCapture cap(deviceId);

	if (!cap.isOpened()) {
		std::cerr << "Capture Device ID " << deviceId << "cannot be opened." << std::endl;
		return -1;
	}

	// initial values
	int radius = 1;
	int neighbors = 8;

	// windows
#if CV_MAJOR_VERSION == 3
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("lbp", CV_WINDOW_AUTOSIZE);
#else if CV_MAJOR_VERSION == 4
	cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("lbp", cv::WINDOW_AUTOSIZE);
#endif

	// matrices used
	cv::Mat frame; // always references the last frame
	cv::Mat dst; // image after preprocessing
	cv::Mat lbp; // lbp image

	// just to switch between possible lbp operators
	std::vector<std::string> lbp_names;
	lbp_names.push_back("Extended LBP"); // 0
	lbp_names.push_back("Fixed Sampling LBP"); // 1
	lbp_names.push_back("Variance-based LBP"); // 2
	int lbp_operator = 0;

	CmnIP::group::ImageSplit is;

	bool running = true;
	while (running) {
		cap >> frame;

		if (frame.empty()) continue;

#if CV_MAJOR_VERSION == 3
		cv::cvtColor(frame, dst, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
		cv::cvtColor(frame, dst, cv::COLOR_BGR2GRAY);
#endif
		cv::GaussianBlur(dst, dst, cv::Size(7, 7), 5, 3, cv::BORDER_CONSTANT); // tiny bit of smoothing is always a good idea
		// comment the following lines for original size
		//cv::resize(frame, frame, cv::Size(), 0.5, 0.5);
		//cv::resize(dst, dst, cv::Size(), 0.5, 0.5);
		//
		switch (lbp_operator) {
		case 0:
			CmnIP::feature::LBP::ELBP(dst, lbp, radius, neighbors); // use the extended operator
			break;
		case 1:
			CmnIP::feature::LBP::OLBP(dst, lbp); // use the original operator
			break;
		case 2:
			CmnIP::feature::LBP::VARLBP(dst, lbp, radius, neighbors);
			break;
		}

		// now to show the patterns a normalization is necessary
		// a simple min-max norm will do the job...
		cv::normalize(lbp, lbp, 0, 255, cv::NORM_MINMAX, CV_8UC1);

		is.split(lbp, lbp.cols, lbp.rows, 16, 16);

		for (auto it = is.rois_img_.begin(); it != is.rois_img_.end(); it++)
		{
			cv::Mat d = CmnIP::feature::LBPHistogram::histogram(it->second, 256, 1);
			//std::cout << d << std::endl;
			double minVal = 0, maxVal = 0;
			cv::minMaxLoc(d, &minVal, &maxVal);
			//std::cout << it->first.first << " " << it->first.second << " " << maxVal << std::endl;
		}

		cv::Mat d = CmnIP::feature::LBPHistogram::histogram(lbp, 256, 1);

		cv::imshow("original", frame);
		cv::imshow("lbp", lbp);

		char key = (char)cv::waitKey(20);

		// exit on escape
		if (key == 27)
			running = false;

		// to make it a bit interactive, you can increase and decrease the parameters
		switch (key) {
		case 'q': case 'Q':
			running = false;
			break;
			// lower case r decreases the radius (min 1)
		case 'r':
			radius -= 1;
			radius = std::max(radius, 1);
			std::cout << "radius=" << radius << std::endl;
			break;
			// upper case r increases the radius (there's no real upper bound)
		case 'R':
			radius += 1;
			radius = std::min(radius, 32);
			std::cout << "radius=" << radius << std::endl;
			break;
			// lower case p decreases the number of sampling points (min 1)
		case 'p':
			neighbors -= 1;
			neighbors = std::max(neighbors, 1);
			std::cout << "sampling points=" << neighbors << std::endl;
			break;
			// upper case p increases the number of sampling points (max 31)
		case 'P':
			neighbors += 1;
			neighbors = std::min(neighbors, 31);
			std::cout << "sampling points=" << neighbors << std::endl;
			break;
			// switch between operators
		case 'o': case 'O':
			lbp_operator = (lbp_operator + 1) % 3;
			std::cout << "Switched to operator " << lbp_names[lbp_operator] << std::endl;
			break;
		case 's': case 'S':
			imwrite("original.jpg", frame);
			imwrite("lbp.jpg", lbp);
			std::cout << "Screenshot (operator=" << lbp_names[lbp_operator] << ",radius=" << radius << ",points=" << neighbors << ")" << std::endl;
			break;
		default:
			break;
		}
	}
	return 0; // success
}