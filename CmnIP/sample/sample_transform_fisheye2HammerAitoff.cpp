/* @file sample_imgproc_fisheye2perspective.cpp
 * @brief Test the fisheye to perspective transformation.
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "transform/inc/transform/transform_headers.hpp"
//#include "ts.hpp"


/** @WARNING IT CAUSES A CRASH!
             Copied just for backup
*/
class HammerAitoffSample
{
public:

	// Perform some Hammer-Aitoff transformation
	static void test()
	{
		std::string filename = "m0.yml";
		cv::Mat mapx, mapy;
		//RemapIO::load(filename, mapx, mapy);

		{
			cv::Mat m0 = cv::imread("..\\..\\data\\13510272-2014-11-30-162454.png");
			cv::Mat m1 = cv::imread("..\\..\\data\\13510272-2014-12-02-173029.png");
			// Get the info from image 0
			cv::Rect r(210, 190, 1840 - 210, 1840 - 210);
			m0 = m0(r);
			m1 = m1(r);
			cv::imshow("src0", m0);
			float radius_out0 = 774.99459, radius_out1 = 774.99459;
			float rdiff = ((std::min)(m0.cols / 2, m0.rows / 2) - radius_out0) / 2;
			m0 = m0(cv::Rect(rdiff, rdiff, m0.cols - rdiff * 2, m0.rows - rdiff * 2));
			m1 = m1(cv::Rect(rdiff, rdiff, m0.cols - rdiff * 2, m0.rows - rdiff * 2));
			cv::imshow("m0", m0);
			cv::imshow("m1", m1);

			cv::Mat mapx, mapy;
			CmnIP::transform::FishEye2HammerAitoff::HammerAitoff2Map(m0, mapx, mapy);
		}


		//cv::Mat out;
		//combine2fishimages(out);

		cv::Rect r(210, 190, 1840 - 210, 1840 - 210);
		std::vector<cv::Mat> vout;
		vout.push_back(cv::imread("..\\..\\data\\test7.png")(r));
		vout.push_back(cv::imread("..\\..\\data\\test8.png")(r));
		float radius_out0 = 774.99459, radius_out1 = 774.99459;
		float rdiff = ((std::min)(vout[0].cols / 2, vout[0].rows / 2) - radius_out0) / 2;

		//ExtractCore(out, vout);


		vout[0] = vout[0](cv::Rect(rdiff, rdiff, vout[0].cols - rdiff * 2, vout[0].rows - rdiff * 2));
		vout[1] = vout[1](cv::Rect(rdiff, rdiff, vout[1].cols - rdiff * 2, vout[1].rows - rdiff * 2));

		cv::imshow("vout[0]", vout[0]);
		cv::imshow("vout[1]", vout[1]);

		std::vector<cv::Mat> vHA;
		cv::Mat HA;
		//FishEyeTransform::HammerAitoff2Map(vout[0], mapx, mapy);
		//save(filename, mapx, mapy);
#if CV_MAJOR_VERSION == 3
		cv::remap(vout[0], HA, mapx, mapy, CV_INTER_LINEAR, 
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#else if CV_MAJOR_VERSION == 4
		cv::remap(vout[0], HA, mapx, mapy, cv::INTER_LINEAR, 
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#endif
		cv::imshow("vout0", HA);
		//FishEyeTransform::testHammerAitoff(vout[0], "HA0", HA);
		vHA.push_back(HA.clone());
#if CV_MAJOR_VERSION == 3
		cv::remap(vout[1], HA, mapx, mapy, CV_INTER_LINEAR, 
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#else if CV_MAJOR_VERSION == 4
		cv::remap(vout[1], HA, mapx, mapy, cv::INTER_LINEAR, 
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#endif
		cv::imshow("vout1", HA);
		//FishEyeTransform::testHammerAitoff(vout[1], "HA1", HA);
		vHA.push_back(HA);
		cv::Mat res;
		combineHA(vHA, res);
		cv::resize(res, res, cv::Size(res.cols / 2, res.rows / 2));
		cv::imshow("res", res);
		cv::waitKey();
	}

private:

	/** @brief Given 2 fish eye images, it compose a single image with the
	images side by side.

	Given 2 fish eye images, it compose a single image with the images side by
	side. The output image is used as demo for the processing and create a
	perspective view.
	*/
	static void combine2fishimages(cv::Mat &out)
	{
		std::vector<cv::Mat> images;
		images.push_back(cv::imread("..\\..\\data\\test7.png"));
		images.push_back(cv::imread("..\\..\\data\\test8.png"));
		int width = 1920, height = 1080;
		cv::Mat res(height, width, CV_8UC3, cv::Scalar::all(0));
		cv::resize(images[0], images[0], cv::Size(width / 2, height));
		cv::resize(images[1], images[1], cv::Size(width / 2, height));
		images[0].copyTo(res(cv::Rect(0, 0, width / 2, height)));
		images[1].copyTo(res(cv::Rect(width / 2, 0, width / 2, height)));
		cv::resize(res, res, cv::Size(res.cols / 2, res.rows / 2));
		cv::imshow("res", res);
		out = res;
	}

	/** @brief Given an image with 2 fish eyes image, extract the images and
	remove borders if necessary
	*/
	static void ExtractCore(cv::Mat &image, std::vector<cv::Mat> &vout)
	{
		// Split the image
		std::vector<cv::Mat> images;
		images.push_back(image(cv::Rect(0, 0, image.cols / 2, image.rows)));
		images.push_back(image(cv::Rect(image.cols / 2, 0, image.cols / 2, image.rows)));
		// change the image ratio size
		float ratio = (float)images[0].cols / (float)images[0].rows;
		cv::resize(images[0], images[0], cv::Size(images[0].cols / ratio, images[0].rows));
		cv::resize(images[1], images[1], cv::Size(images[1].cols / ratio, images[1].rows));

		std::vector<cv::Point2f> centers;
		centers.push_back(cv::Point2f(images[0].cols / 2, images[0].rows / 2));
		centers.push_back(cv::Point2f(images[1].cols / 2, images[1].rows / 2));
		float radius = 220;
		int thickness = 2;
		cv::Scalar color(0, 0, 255);
		size_t s = centers.size();
		for (size_t i = 0; i < s; ++i)
		{
			//cv::circle(images[i], centers[i], radius, color, thickness);
			vout.push_back(images[i](cv::Rect(centers[i].x - radius, centers[i].y - radius, radius * 2, radius * 2)));
		}
		cv::imshow("images0", images[0]);
		cv::imshow("images1", images[1]);
		cv::imshow("vout0", vout[0]);
		cv::imshow("vout1", vout[1]);

	}

	/** @brief Combine Hammer Atoff visualization
	*/
	static void combineHA(std::vector<cv::Mat> &images, cv::Mat &res)
	{
		// Smooth the connection areas between the images
		cv::Mat m0 = images[0];
		cv::Mat m1 = images[1];
		cv::Mat m2 = images[1];
		cv::Mat combo(m0.rows, m0.cols * 3, m0.type());
		m0.copyTo(combo(cv::Rect(0, 0, m0.cols, m0.rows)));
		m1.copyTo(combo(cv::Rect(m0.cols, 0, m1.cols, m1.rows)));
		m0.copyTo(combo(cv::Rect(m0.cols * 2, 0, m0.cols, m0.rows)));
		cv::Mat m = combo;
		//cv::TickMeter tm;
		//tm.start();
		int xkeypoint = m.cols / 3;
		//Smooth::horizontal(m, xkeypoint, 30, 50);
		xkeypoint = m.cols / 3 * 2;
		//Smooth::horizontal(m, xkeypoint, 30, 50);
		//tm.stop();
		//std::cout << "combineHA(ms): " << tm << std::endl;
		// Copy the most right to the left
		m(cv::Rect(xkeypoint, 0, 60, m.rows)).copyTo(m(cv::Rect(0, 0, 60, m.rows)));
		res = m(cv::Rect(m.cols / 6, 0, m.cols / 3 * 2, m.rows));
	}


};



namespace
{

/** @brief Test the fisheye to perspective transformation.
*/
void test(int argc, char *argv[])
{
	cv::Mat m0 = cv::imread("..\\..\\data\\13510272-2014-11-30-162454.png");
	cv::Mat m1 = cv::imread("..\\..\\data\\13510272-2014-12-02-173029.png");
	// Get the info from image 0
	cv::Rect r(210, 190, 1840 - 210, 1840 - 210);
	m0 = m0(r);
	m1 = m1(r);
	cv::imshow("src0", m0);
	float radius_out0 = 774.99459, radius_out1 = 774.99459;
	float rdiff = ((std::min)(m0.cols / 2, m0.rows / 2) - radius_out0) / 2;
	m0 = m0(cv::Rect(rdiff, rdiff, m0.cols - rdiff * 2, m0.rows - rdiff * 2));
	m1 = m1(cv::Rect(rdiff, rdiff, m0.cols - rdiff * 2, m0.rows - rdiff * 2));
	cv::imshow("m0", m0);
	cv::imshow("m1", m1);

	cv::Mat mapx, mapy;
	CmnIP::transform::FishEye2HammerAitoff::HammerAitoff2Map(m0, mapx, mapy);
#if CV_MAJOR_VERSION == 3
	cv::remap(m0, m1, mapx, mapy, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("m11", m1);
	cv::remap(m0, m1, mapx, mapy, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("m12", m1);
#else if CV_MAJOR_VERSION == 4
	cv::remap(m0, m1, mapx, mapy, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("m11", m1);
	cv::remap(m0, m1, mapx, mapy, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("m12", m1);
#endif

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
	std::cout << "Test point mapping" << std::endl;
	test(argc, argv);
	
	return 0;
}

#endif