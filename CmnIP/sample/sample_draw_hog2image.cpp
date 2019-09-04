/**
* @file sample_drawing_pairs.cpp
* @brief Example of the drawing of pairs of data.
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
* @version 1.0.0.1
*
*/

#include <iostream>

#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/legacy/legacy.hpp>
#endif

#include "draw/inc/draw/draw_headers.hpp"

namespace
{

	/** @brief Function to test the hog descriptor.

	@link http://www.juergenwiki.de/work/wiki/doku.php?id=public%3ahog_descriptor_computation_and_visualization#computing_the_hog_descriptor_using_opencv
	*/
	void test(const cv::Mat &img_src)
	{
#if CV_MAJOR_VERSION == 2
		// [!] Make a copy of the source image
		cv::Mat img_raw = img_src.clone();

		// Resize the image to match the HOG descriptor
		cv::resize(img_raw, img_raw, cv::Size(64, 128));
		cv::Mat img;
		cv::cvtColor(img_raw, img, CV_RGB2GRAY);

		// HOG Descriptor
		cv::HOGDescriptor d;
		// Size(128,64), //winSize
		// Size(16,16), //blocksize
		// Size(8,8), //blockStride,
		// Size(8,8), //cellSize,
		// 9, //nbins,
		// 0, //derivAper,
		// -1, //winSigma,
		// 0, //histogramNormType,
		// 0.2, //L2HysThresh,
		// 0 //gammal correction,
		// //nlevels=64
		//);

		// void HOGDescriptor::compute(const Mat& img, vector<float>& descriptors,
		//                             Size winStride, Size padding,
		//                             const vector<Point>& locations) const
		std::vector<float> descriptorsValues;
		std::vector<cv::Point> locations;
		d.compute(img, descriptorsValues, cv::Size(0, 0), cv::Size(0, 0),
			locations);

		std::cout << "HOG descriptor size is " << d.getDescriptorSize() << 
			std::endl;
		std::cout << "img dimensions: " << img.cols << " width x " << 
			img.rows <<	"height" << std::endl;
		std::cout << "Found " << descriptorsValues.size() << 
			" descriptor values" << std::endl;
		for (auto it = descriptorsValues.begin(); it != descriptorsValues.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Nr of locations specified : " << locations.size() <<
			std::endl;

		double image_rescale_times = 2;
		double hoglines_rescale_times = 3;
		cv::Mat hog_view = CmnIP::draw::HOG2Image::get_hogdescriptor_visual_image(
			img_raw, descriptorsValues, img_raw.size(), d.cellSize,
			image_rescale_times,
			hoglines_rescale_times, false);

		cv::imshow("hog_view", hog_view);
		cv::waitKey(0);
#else
		std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;
#endif
	}


} // namespace anonymous

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** @function main */
int main(int argc, const char* argv[])
{
	std::cout << "Test HOG" << std::endl;
	std::cout << "Last change: 2014/06/28" << std::endl;

	cv::Mat image(256, 256, CV_8UC3, cv::Scalar::all(0));
	cv::rectangle(image, cv::Rect(image.cols / 2 - 50, image.rows / 2 - 30,
		100, 60), cv::Scalar::all(255), 4);

	test(image);
	return 0;
}

#endif