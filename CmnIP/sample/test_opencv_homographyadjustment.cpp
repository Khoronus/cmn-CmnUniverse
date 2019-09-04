/* @file homographymatrix_adjustment.cpp
* @brief Main file with the example for the hog descriptor and visualization.
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


#include <iostream>
#include <fstream>
#include <vector>

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"

// ----------------------------------------------------------------------------
namespace
{

	/** @brief Load a set of points from a file.

	Load a set of points from a file.
	The points are organized as follow
	source_x source_y destination_x destination y
	*/
	int open_file_points_source_destination(const std::string &filename,
		std::vector< cv::Point2f > &v_points_src,
		std::vector< cv::Point2f > &v_points_dst)
	{
		std::ifstream myfile(filename);
		if (!myfile.is_open()) return 0;

		v_points_src.clear();
		v_points_dst.clear();

		while (!myfile.eof())
		{
			char buf[512];
			myfile.getline(buf, 512);
			if (std::strlen(buf) < 3) continue;

			int xs, ys, xd, yd;
			sscanf(buf, "%i %i %i %i", &xs, &ys, &xd, &yd);
			v_points_src.push_back(cv::Point2f(xs, ys));
			v_points_dst.push_back(cv::Point2f(xd, yd));
		}

		return 1;
	}

	/** @brief Function to test the transformation
	*/
	void test(const std::string &filename_img_perspective,
		const std::string &filename_homography_tv,
		const std::string &filename_points_source_destination,
		const std::string &filename_homography_fileout)
	{
		// Load the source images
		cv::Mat img_perspective = cv::imread(filename_img_perspective);
		if (img_perspective.empty()) {
			std::cout << "The image is empty!" << std::endl;
			return;
		}
		cv::Mat img_topview;
		cv::Mat img_finaltransformation;
		cv::Mat img_tmp;
		// Show the perspective image
		cv::resize(img_perspective, img_tmp,
			cv::Size(img_perspective.cols / 2, img_perspective.rows / 2));
		cv::imshow("img_perspective", img_tmp);
		// Load the source homography transformation
		cv::Mat mat_homography_tv;
		cv::FileStorage file(filename_homography_tv, cv::FileStorage::READ);
		file["t"] >> mat_homography_tv;
		std::cout << "mat_homography_tv: " << mat_homography_tv << std::endl;
		// Check that the transformation is correct
		// [!] The size (img_perspective.size()) defines how much of the is used.
		//     If too small, the result image is cut.
		cv::warpPerspective(img_perspective, img_topview, mat_homography_tv,
			img_perspective.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);
		// Resize to make the image stay in the screen
		cv::resize(img_topview, img_tmp,
			cv::Size(img_topview.cols / 2, img_topview.rows / 2));
		cv::imshow("img_topview", img_tmp);

		// Load the source and destination points
		std::vector< cv::Point2f > v_points_src;
		std::vector< cv::Point2f > v_points_dst;
		open_file_points_source_destination(filename_points_source_destination,
			v_points_src, v_points_dst);
		if (v_points_src.size() > 0 &&
			v_points_src.size() == v_points_dst.size()) {
			// Find the homography matrix
			// [!] Check for the other parameters
			cv::Mat homography_transformation =
				cv::findHomography(cv::Mat(v_points_src), cv::Mat(v_points_dst));
			// Perform the transformation
			cv::warpPerspective(img_topview, img_finaltransformation,
				homography_transformation, img_topview.size(), cv::INTER_LINEAR,
				cv::BORDER_CONSTANT);
			// Resize to make the image stay in the screen
			cv::resize(img_finaltransformation, img_tmp,
				cv::Size(img_topview.cols / 2, img_topview.rows / 2));
			cv::imshow("img_finaltransformation", img_tmp);

			// Merge the homography transformations
			cv::Mat homography_transformation_final = homography_transformation *
				mat_homography_tv;

			// Try the transformation
			cv::Mat img_verify_transformation;;
			cv::warpPerspective(img_perspective, img_verify_transformation,
				homography_transformation_final, img_topview.size(), cv::INTER_LINEAR,
				cv::BORDER_CONSTANT);
			// Resize to make the image stay in the screen
			cv::resize(img_verify_transformation, img_tmp,
				cv::Size(img_topview.cols / 2, img_topview.rows / 2));
			cv::imshow("img_verify_transformation", img_tmp);

			// Save the result
			if (filename_homography_fileout.size() > 3) {
				cv::FileStorage file(filename_homography_fileout,
					cv::FileStorage::WRITE);
				file << "homography" << homography_transformation_final;
			}

		}
		else {
			std::cout << "Unable to open the file: " <<
				filename_points_source_destination << std::endl;
		}

		cv::waitKey(0);
	}

} // namespace anonymous

// ----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//for (int i = 1; i < 5; i++)
	//{
	//	char buf[512];
	//	sprintf(buf, "..\\..\\Sample\\%i.jpg", i);
	//	cv::Mat m = cv::imread(buf);
	//	cv::Mat r = m(cv::Rect(170,50,940,940));
	//	sprintf(buf, "%i.jpg", i);
	//	cv::imwrite(buf, r);
	//}
	//return 0;
	//
	std::cout << "Homographt matrix adjustment" << std::endl;

	test("..\\..\\data\\homography\\img_perspective_0.jpg",
		"..\\..\\data\\homography\\HomoTop_0.txt",
		"..\\..\\data\\homography\\points0.txt",
		"HomoTransfFin_100.txt");
	test("..\\..\\data\\homography\\img_perspective_1.jpg",
		"..\\..\\data\\homography\\HomoTop_1.txt",
		"..\\..\\data\\homography\\points1.txt",
		"HomoTransfFin_101.txt");
	test("..\\..\\data\\homography\\img_perspective_2.jpg",
		"..\\..\\data\\homography\\HomoTop_2.txt",
		"..\\..\\data\\homography\\points1.txt",
		"HomoTransfFin_102.txt");
	test("..\\..\\data\\homography\\img_perspective_3.jpg",
		"..\\..\\data\\homography\\HomoTop_3.txt",
		"..\\..\\data\\homography\\points1.txt",
		"HomoTransfFin_103.txt");

	return 0;
}
