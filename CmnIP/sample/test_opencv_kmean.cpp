/**
* @file sample_test_kmean.cpp
* @brief Sample test of the kmean clustering.
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

namespace
{

int test_kmean_points()
{
	std::cout << "This function show an example of kmean with a test of ";
	std::cout << "points." << std::endl;
	cv::Mat img(500, 500, CV_8UC3);
	cv::RNG rng(12345);

	for (;;)
	{
		int clusterCount = 10, sampleCount = 4000;
		cv::Mat points(sampleCount, 1, CV_32FC2), labels;

		clusterCount = MIN(clusterCount, sampleCount);
		cv::Mat centers(clusterCount, 1, points.type());

		/* generate random sample from multigaussian distribution */
		for (int k = 0; k < sampleCount; k++)
		{
			points.at<cv::Vec2f>(k, 0)[0] = rng.uniform(0, img.cols);
			points.at<cv::Vec2f>(k, 0)[1] = rng.uniform(0, img.rows);
		}

#if CV_MAJOR_VERSION == 3
		cv::kmeans(points, clusterCount, labels,
			cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			3, cv::KMEANS_PP_CENTERS, centers);
#elif CV_MAJOR_VERSION == 4
		cv::kmeans(points, clusterCount, labels,
			cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),
			3, cv::KMEANS_PP_CENTERS, centers);
#endif

		img = cv::Scalar::all(0);

		std::map<int, cv::Scalar> colors;
		for (int i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			cv::Point ipt = points.at<cv::Point2f>(i);
			cv::Scalar color(0, 0, 0);
			if (colors.find(clusterIdx) == colors.end()) {
				colors[clusterIdx] = cv::Scalar(rng.uniform(0, 255),
					rng.uniform(0, 255), rng.uniform(0, 255));
			}
#if CV_MAJOR_VERSION == 3
			cv::circle(img, ipt, 2, colors[clusterIdx], CV_FILLED, CV_AA);
#elif CV_MAJOR_VERSION == 4
			cv::circle(img, ipt, 2, colors[clusterIdx], cv::FILLED, 
				cv::LINE_AA);
#endif
		}

		cv::imshow("clusters", img);

		char key = (char)cv::waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}

	return 1;
}


int test_kmean()
{
	std::cout << "This function take a source image and it clusters the ";
	std::cout << "colors." << std::endl;
	cv::Mat src = cv::imread("../../data/horses.jpg");
	cv::Mat samples(src.rows * src.cols, 3, CV_32F);
	for (int y = 0; y < src.rows; y++)
	for (int x = 0; x < src.cols; x++)
	for (int z = 0; z < 3; z++)
		samples.at<float>(y + x*src.rows, z) = src.at<cv::Vec3b>(y, x)[z];


	int clusterCount = 5;
	cv::Mat labels;
	int attempts = 5;
	cv::Mat centers;
#if CV_MAJOR_VERSION == 3
	cv::kmeans(samples, clusterCount, labels, 
		cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 
			10000, 0.0001), attempts, cv::KMEANS_PP_CENTERS, centers);
#elif CV_MAJOR_VERSION == 4
	cv::kmeans(samples, clusterCount, labels, 
		cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 
			10000, 0.0001), attempts, cv::KMEANS_PP_CENTERS, centers);
#endif


	cv::Mat new_image(src.size(), src.type());
	for (int y = 0; y < src.rows; y++)
	for (int x = 0; x < src.cols; x++)
	{
		int cluster_idx = labels.at<int>(y + x*src.rows, 0);
		new_image.at<cv::Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
		new_image.at<cv::Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
		new_image.at<cv::Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);
	}
	cv::imshow("src", src);
	cv::imshow("clustered image", new_image);
	cv::waitKey(0);
	return 1;
}

} // namespace anonymous


int main(int argc, char* argv[])
{
	test_kmean_points();
	test_kmean();
	return 0;
}
