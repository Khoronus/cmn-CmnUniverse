/**
* @file test_opencv_poissonblending.cpp
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
* @author 
* @link http://blog.livedoor.jp/tmako123-programming/archives/38713988.html
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define LOOP_MAX 10000
#define EPS 2.2204e-016
#define NUM_NEIGHBOR 4

using namespace cv;

int quasi_poisson_solver(Mat &img_src, Mat &img_dst, Mat &img_mask, int channel, int offset[]){
	int i, j, loop, neighbor, count_neighbors, ok;
	float error, sum_f, sum_vpq, fp;
	int naddr[NUM_NEIGHBOR][2] = { { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };
	cv::Mat img_new = (cv::Mat_<double>(img_dst.rows, img_dst.cols));
	for (i = 0; i<img_dst.rows; i++){
		for (j = 0; j<img_dst.cols; j++){
			img_new.at<double>(i, j) = (double)img_dst.at<Vec3b>(i, j)[channel];
		}
	}
	for (loop = 0; loop<LOOP_MAX; loop++){
		ok = 1;
		printf("%d\n", loop);
		for (i = 0; i<img_mask.rows; i++){
			for (j = 0; j<img_mask.cols; j++){
				if ((int)img_mask.at<Vec3b>(i, j)[0]>0){
					sum_f = 0.0;
					sum_vpq = 0.0;
					count_neighbors = 0;
					for (neighbor = 0; neighbor<NUM_NEIGHBOR; neighbor++){
						if (i + offset[0] + naddr[neighbor][0] >= 0
							&& j + offset[1] + naddr[neighbor][1] >= 0
							&& i + offset[0] + naddr[neighbor][0]<img_dst.rows
							&&j + offset[1] + naddr[neighbor][1]<img_dst.cols){
							sum_f += img_new.at<double>(i + offset[0] + naddr[neighbor][0], j + offset[1] + naddr[neighbor][1]);
							sum_vpq += (float)img_src.at<Vec3b>(i, j)[channel]
								- (float)img_src.at<Vec3b>(i + naddr[neighbor][0], j + naddr[neighbor][1])[channel];
							count_neighbors++;
						}
					}
					fp = (sum_f + sum_vpq) / (float)count_neighbors;
					error = fabs(fp - img_new.at<double>(i + offset[0], j + offset[1]));
					if (ok&&error>EPS*(1 + fabs(fp))){
						ok = 0;
					}
					img_new.at<double>(i + offset[0], j + offset[1]) = fp;
				}
			}
		}
		if (ok){
			break;
		}
	}
	for (i = 0; i<img_dst.rows; i++){
		for (j = 0; j<img_dst.cols; j++){
			if (img_new.at<double>(i, j)>255){
				img_new.at<double>(i, j) = 255.0;
			}
			else if (img_new.at<double>(i, j)<0){
				img_new.at<double>(i, j) = 0.0;
			}
			img_dst.at<Vec3b>(i, j)[channel] = (uchar)img_new.at<double>(i, j);
		}
	}
	return 1;
}

int poisson(){
	cv::Mat source = imread("..\\..\\data\\cat.png");
	cv::Mat destination = imread("..\\..\\data\\girl.png");
	cv::Mat mask = imread("..\\..\\data\\mask.png");
	int offset[2] = { 0, 0 };


	imshow("destination", destination);
	imshow("mask", mask);
	imshow("source", source);
	cv::waitKey(0);

	int i;
	for (i = 0; i<3; i++){
		quasi_poisson_solver(source, destination, mask, i, offset);
	}
	imwrite("destination.png", destination);
	imshow("destination", destination);
	cv::waitKey(0);

	return 1;
}

int main()
{
	poisson();
	return 0;
}