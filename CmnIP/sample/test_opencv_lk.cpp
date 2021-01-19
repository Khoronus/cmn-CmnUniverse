/**
* @file sample_test_pca.cpp
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
#include <fstream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cmnipworld/inc/cmnipworld/cmnipworld_headers.hpp"


class LKTraker
{
public:

	void initialize()
	{
#if CV_MAJOR_VERSION == 3
		termcrit = cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 
			20, 0.03);
#elif CV_MAJOR_VERSION == 4
		termcrit = cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 
			20, 0.03);
#endif
		subPixWinSize = cv::Size(10, 10);
		winSize = cv::Size(31, 31);
		MAX_COUNT = 500;
		addRemovePt = false;
	}

	void track(cv::Mat &src, bool needToInit)
	{
		cv::Mat image = src.clone();
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(image, gray, CV_BGR2GRAY);
#elif CV_MAJOR_VERSION == 4
		cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
#endif

		if (needToInit)
		{
			// automatic initialization
			cv::goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, 
				cv::Mat());
			cornerSubPix(gray, points[1], subPixWinSize, cv::Size(-1, -1), 
				termcrit);
			addRemovePt = false;
		}
		else if (!points[0].empty())
		{
			std::vector<uchar> status;
			std::vector<float> err;
			if (prevGray.empty())
				gray.copyTo(prevGray);
			cv::calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
				3, termcrit, 0, 0.001);
			size_t i, k;
			for (i = k = 0; i < points[1].size(); i++)
			{
				if (addRemovePt)
				{
					if (cv::norm(point - points[1][i]) <= 5)
					{
						addRemovePt = false;
						continue;
					}
				}

				if (!status[i])
					continue;

				points[1][k++] = points[1][i];
				circle(image, points[1][i], 3, cv::Scalar(0, 255, 0), -1, 8);
			}
			points[1].resize(k);
		}

		if (addRemovePt && points[1].size() < (size_t)MAX_COUNT)
		{
			std::vector<cv::Point2f> tmp;
			tmp.push_back(point);
			cornerSubPix(gray, tmp, winSize, cv::Size(-1, -1), termcrit);
			points[1].push_back(tmp[0]);
			addRemovePt = false;
		}

		needToInit = false;
		imshow("LK Demo", image);
		std::swap(points[1], points[0]);
		cv::swap(prevGray, gray);

	}
private:

	cv::TermCriteria termcrit;
	cv::Size subPixWinSize, winSize;
	bool addRemovePt;
	cv::Point2f point;

	int MAX_COUNT;

	cv::Mat gray, prevGray, image;
	std::vector<cv::Point2f> points[2];
};


int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	// Estimate the flow of the image
	LKTraker lktraker;
	lktraker.initialize();

	cv::Mat img;
	bool needToInit = true;
	while (true)
	{
		cap >> img;
		if (img.empty()) break;
		// Lukas Kanade
		lktraker.track(img, needToInit);
		needToInit = false;
		cv::imshow("video capture", img);
		if (cv::waitKey(1) == 27) break;
	}
	return 0;
}
