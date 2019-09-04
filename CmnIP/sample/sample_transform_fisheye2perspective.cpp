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


/** @brief Class to performs some operations over a remap matrix
*/
class RemapMatrixOperation
{
public:

	/** @brief It modifies the entries of a matrix with the average of a
	certain interval.

	It modifies the entries of a matrix with the average of a
	certain interval.
	The advantage to performs this operation is to obtain subpixel
	values to performs linear interpolation (or other interpolations)
	*/
	static void refine_matrix(int xmin, int ymin,
		int xmax, int ymax, cv::Mat &m, int frame)
	{
		cv::Mat mtmp = m.clone();
		for (int y = ymin; y < ymax; ++y)
		{
			for (int x = xmin; x < xmax; ++x)
			{
				float sum = 0;
				int count = 0;
				for (int y_ = y - frame; y_ <= y + frame; ++y_)
				{
					for (int x_ = x - frame; x_ <= x + frame; ++x_)
					{
						if (y_ >= 0 && y_ < mtmp.rows &&
							x_ >= 0 && x_ < mtmp.cols &&
							mtmp.at<float>(y_, x_) != 0)
						{
							++count;
							sum += mtmp.at<float>(y_, x_);
						}
					}
				}
				if (count > 0) m.at<float>(y, x) = sum / count;
			}
		}
	}

	/** @brief It modifies the entries of a matrix with the average of a
		certain interval.

		It modifies the entries of a matrix with the average of a
		certain interval.
		The advantage to performs this operation is to obtain subpixel
		values to performs linear interpolation (or other interpolations)

		@param[in] frame Frame size to compute the average.
		@param[in] mask Mask value not used.
		@param[out] m The refined matrix.
	*/
	static void refine_matrix(
		int xmin, int ymin,
		int xmax, int ymax, 
		int frame, float mask,
		cv::Mat &m)
	{
		cv::Mat mtmp = m.clone();
		for (int y = ymin; y < ymax; ++y)
		{
			for (int x = xmin; x < xmax; ++x)
			{
				float sum = 0;
				int count = 0;
				for (int y_ = y - frame; y_ <= y + frame; ++y_)
				{
					for (int x_ = x - frame; x_ <= x + frame; ++x_)
					{
						if (y_ >= 0 && y_ < mtmp.rows &&
							x_ >= 0 && x_ < mtmp.cols &&
							mtmp.at<float>(y_, x_) != mask)
						{
							++count;
							sum += mtmp.at<float>(y_, x_);
						}
					}
				}
				if (count > 0) m.at<float>(y, x) = sum / count;
			}
		}
	}


};


namespace
{

/** @brief Test the fisheye to perspective transformation.
*/
void test(int argc, char *argv[])
{
	//cv::Mat image = cv::imread("..\\..\\data\\fish_left.jpg");
	cv::Mat image = cv::imread("..\\..\\data\\fish_front.jpg");
	//cv::Mat image = cv::imread("..\\..\\data\\14135931-2016-01-11-165358.jpg");
	if (image.empty()) std::cout << "Empty" << std::endl;

	cv::Mat map_x_p, map_y_p, map_x_f, map_y_f, out, out2;
	std::vector< std::pair< cv::Point3f, cv::Point2f > > points_lens, points_plane;
	bool bSetup = true;
	
	//float wsize = 1, hsize = 1, zoom = 1;
	//float xrot = -0.8, yrot = 0.0, zrot = 0.5;
	//float wsize = 1.1, hsize = 1.1, zoom = 5.0;
	//float xrot = 0.0, yrot = 0.0, zrot = 0.0;//0.0;
	//float xmodifier = 1.05, ymodifier = 1.11;
	//float wsize = 5, hsize = 5, zoom = 5.0;
	//float xrot = -0.35, yrot = 0.0, zrot = 0.0;//0.0;
	//float xmodifier = 1.05, ymodifier = 1.19;
	//bool bContinue = true;

	float wsize = 5, hsize = 5, zoom = 5.0;
	float xrot = 0, yrot = 0.0, zrot = 0.0;//0.0;
	float xmodifier = 1.0, ymodifier = 1.0;
	bool bContinue = true;

	// Fisheye 2 Perspective transformation
	CmnIP::transform::FishEye2Perspective pm2;
	//int kW = 1536, kH = 1536; 
	//int kW = 2000, kH = 2000; 
	//int kW = 512, kH = 512; 
	//int kW = 400, kH = 400; 
	int kW = 960, kH = 960; 

	// If true, it performs some matrix interpolation
	bool do_refine_matrix = false;

	// save the current matrix information
	bool do_save_matrix = false;
	int num_saved_matrix = 0;
	float mask_val = -1.0f;

	while (bContinue)
	{
		if (bSetup)
		{
			std::cout << wsize << " " << hsize << " " << xrot << " " << yrot << " " << zrot << " " << xmodifier << " " << ymodifier << std::endl;
			bSetup = false;
			// Try to perform an image transformation
			pm2.initialize(image.size(), cv::Size(kW, kH));
			//pm2.cam2world(image, 1.0f, 1.0f, 1.0f, cv::Point3f(0.0,0.0,0), true, 
			//	points_lens, points_plane);
			wsize = hsize = zoom;
			pm2.create_perspective(wsize, hsize, 1.0, 
				cv::Point3f(xrot, yrot, zrot), true,
				xmodifier, ymodifier
		#ifdef POINTMAPPING2DEBUG_
				, image,
				points_lens, points_plane
		#endif
				);
			pm2.create_fisheye2perspective_LUT(map_x_p, map_y_p);

			if (do_refine_matrix) {
				RemapMatrixOperation::refine_matrix(0, 0, map_x_p.cols, map_x_p.rows, 5, mask_val, map_x_p);
				RemapMatrixOperation::refine_matrix(0, 0, map_x_p.cols, map_y_p.rows, 5, mask_val, map_y_p);
			}
			
			pm2.create_perspective2fisheye_LUT(map_x_f, map_y_f);
			
			if (do_refine_matrix) {
				RemapMatrixOperation::refine_matrix(0, 0, map_x_f.cols, map_x_f.rows, 5, mask_val, map_x_f);
				RemapMatrixOperation::refine_matrix(0, 0, map_y_f.cols, map_y_f.rows, 5, mask_val, map_y_f);
			}

			// Save the map in a file
			if (do_save_matrix)
			{
				std::cout << "save matrix...";
				do_save_matrix = false;
				// write Mat objects to the freakin file
				cv::FileStorage fs("fish2perspective_map_" + std::to_string(num_saved_matrix) + ".txt", cv::FileStorage::WRITE);
				if (!fs.isOpened())	fs.open("fish2perspective_map_" + std::to_string(num_saved_matrix) + ".txt", cv::FileStorage::WRITE);
				fs << "map_x_p" << map_x_p;
				fs << "map_y_p" << map_y_p;
				fs << "map_x_f" << map_x_f;
				fs << "map_y_f" << map_y_f;
				fs.release();
				++num_saved_matrix;
				std::cout << "done" << std::endl;
			}
		}

		// Remap
#if CV_MAJOR_VERSION == 3
		cv::remap(image, out, map_x_p, map_y_p, CV_INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		//pm2.transform(image, cv::Rect(0, 0, image.cols, image.rows), out);
		cv::Mat tmp = cv::Mat(out.size(), CV_8U, cv::Scalar::all(255));
		cv::remap(tmp, out2, map_x_f, map_y_f, CV_INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		//pm2.transform(tmp, cv::Rect(0, 0, image.cols, image.rows), out2);
#else if CV_MAJOR_VERSION == 4
		cv::remap(image, out, map_x_p, map_y_p, cv::INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		//pm2.transform(image, cv::Rect(0, 0, image.cols, image.rows), out);
		cv::Mat tmp = cv::Mat(out.size(), CV_8U, cv::Scalar::all(255));
		cv::remap(tmp, out2, map_x_f, map_y_f, cv::INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		//pm2.transform(tmp, cv::Rect(0, 0, image.cols, image.rows), out2);
#endif

		// Detect edges using Threshold
		cv::Mat threshold_output;
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::threshold( out2, threshold_output, 50, 255, cv::THRESH_BINARY );
		std::vector<std::vector<cv::Point> > points, hull;
		points.push_back(std::vector<cv::Point>() );
		hull.push_back(std::vector<cv::Point>() );
		for (int y = 0; y < threshold_output.rows; y++)
		{
			for (int x = 0; x < threshold_output.cols; x++)
			{
				if (threshold_output.at<uchar>(y,x) != 0) {
					points[0].push_back(cv::Point(x, y));
					hull[0].push_back(cv::Point());
				}
			}
		}
		convexHull( cv::Mat(points[0]), hull[0], false );
		/// Draw contours + hull results
		cv::Mat drawing = image.clone();
		cv::Scalar color = cv::Scalar( 0, 255, 0 );
		drawContours( drawing, hull, 0, color, 3, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );

		// Display
		cv::imshow("out", out);
		cv::imshow("outc", drawing);
		cv::imwrite("out.jpg", out);
		cv::resize(out, out, cv::Size(kW,kH));
		cv::resize(drawing, drawing, cv::Size(kW,kH));
		//cv::resize(out2, out2, cv::Size(512,512));
		//cv::imshow("outb", out2);

		cv::Mat m(kH, kW*2, CV_8UC3);
		drawing.copyTo(m(cv::Rect(0,0,kW,kH)));
		out.copyTo(m(cv::Rect(kW,0,kW,kH)));
		cv::imshow("result", m);
		cv::imwrite("result.jpg", m);

		char c = cv::waitKey();
		switch(c)
		{
		case 'q':
		case 27:
			bContinue = false;
			break;
		case '+':
			if (zoom > 0.5) { 
				if (zoom > 1.9) {
				  zoom -= 1; 
				}else {
				  zoom -= 0.1;	
				}
				bSetup = true; 
			}
			break;
		case '-':
			if (zoom < 50.0) {
				if (zoom > 1.1) {
				  zoom += 1; 
				}else {
				  zoom += 0.1;	
				}
				bSetup = true; 
			}
			break;
		case '4':
			xrot += 0.05; bSetup = true;//if (xrot > 1.0) { zoom -= 1; bSetup = true; }
			break;
		case '6':
			xrot -= 0.05; bSetup = true;//if (zoom < 5.0) { zoom += 1; bSetup = true; }
			break;
		case '1':
			yrot += 0.01; bSetup = true;//if (zoom > 1.0) { zoom -= 1; bSetup = true; }
			break;
		case '3':
			yrot -= 0.01; bSetup = true;//if (zoom < 5.0) { zoom += 1; bSetup = true; }
			break;
		case '2':
			zrot += 0.05; bSetup = true;//if (zoom > 1.0) { zoom -= 1; bSetup = true; }
			break;
		case '8':
			zrot -= 0.05; bSetup = true;//if (zoom < 5.0) { zoom += 1; bSetup = true; }
			break;
		case 't':
			xmodifier -= 0.01; bSetup = true;
			break;
		case 'y':
			xmodifier += 0.01; bSetup = true;
			break;
		case 'g':
			ymodifier -= 0.01; bSetup = true;
			break;
		case 'h':
			ymodifier += 0.01; bSetup = true;
			break;
		case 'r':
			do_refine_matrix = true; bSetup = true;
			break;
		case 'n':
			do_refine_matrix = false; bSetup = true;
			break;
		case 's':
			do_save_matrix = true; bSetup = true;
			break;
		}
	}
}

/** @brief Check the fish 2 perspective mapping.
*/
int check_mapping()
{
	// Lead the map in a file
	// write Mat objects to the freakin file
	cv::Mat map_x_p, map_y_p, map_x_f, map_y_f;
	cv::FileStorage fs("fish2perspective_map_4.txt", cv::FileStorage::READ);
	if (!fs.isOpened())	return 0;
	fs["map_x_p"] >> map_x_p;
	fs["map_y_p"] >> map_y_p;
	fs["map_x_f"] >> map_x_f;
	fs["map_y_f"] >> map_y_f;
	fs.release();

	bool do_refine_matrix = true;
	float mask_val = -1.0f;
	if (do_refine_matrix) {
		RemapMatrixOperation::refine_matrix(0, 0, map_x_p.cols, map_x_p.rows, 5, mask_val, map_x_p);
		RemapMatrixOperation::refine_matrix(0, 0, map_x_p.cols, map_y_p.rows, 5, mask_val, map_y_p);
	}

	if (do_refine_matrix) {
		RemapMatrixOperation::refine_matrix(0, 0, map_x_f.cols, map_x_f.rows, 5, mask_val, map_x_f);
		RemapMatrixOperation::refine_matrix(0, 0, map_y_f.cols, map_y_f.rows, 5, mask_val, map_y_f);
	}


	//cv::Mat image = cv::imread("..\\..\\data\\FishEye.jpg"), img_perspective, img_fisheye;
	cv::Mat image = cv::imread("E:\\images_biblio\\frame_1_28.jpg"), img_perspective, img_fisheye;

	const clock_t begin_time = clock();
#if CV_MAJOR_VERSION == 3
	cv::remap(image, img_perspective, map_x_p, map_y_p, CV_INTER_LINEAR,
		cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::remap(img_perspective, img_fisheye, map_x_f, map_y_f, CV_INTER_LINEAR,
		cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#else if CV_MAJOR_VERSION == 4
	cv::remap(image, img_perspective, map_x_p, map_y_p, cv::INTER_LINEAR,
		cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::remap(img_perspective, img_fisheye, map_x_f, map_y_f, cv::INTER_LINEAR,
		cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
#endif
	// do something
	std::cout << "ct: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

	// check the coordinate position
	// Fish2Perspective
	int x = 700, y = 680;
	std::cout << "Fish2Perspective " << x << " " << y << " " << 
		map_x_f.at<float>(y,x) << " " << map_y_f.at<float>(y,x) << std::endl;
	std::cout << "Perspective2Fish " << x << " " << y << " " << 
		map_x_p.at<float>(y,x) << " " << map_y_p.at<float>(y,x) << std::endl;

	// Try to remap the images
	cv::Mat mp(map_y_p.size(), CV_8UC3, cv::Scalar::all(0));
	cv::Mat mf(map_y_f.size(), CV_8UC3, cv::Scalar::all(0));
	cv::Mat instancesp(map_y_p.size(), CV_8U, cv::Scalar::all(0));
	cv::Mat instancesf(map_y_f.size(), CV_8U, cv::Scalar::all(0));
	int w = map_x_f.cols, h = map_y_f.rows;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int x_ = map_x_f.at<float>(y,x);
			int y_ = map_y_f.at<float>(y,x);
			if (x_ >= 0 && y_ >= 0) {
				if (instancesp.at<uchar>(y_, x_) == 0) {
					instancesp.at<uchar>(y_, x_) = 1;
					mp.at<cv::Vec3b>(y_, x_) = image.at<cv::Vec3b>(y, x);
				}
			}
		}
	}

	w = map_x_p.cols;
	h = map_y_p.rows;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int x_ = map_x_p.at<float>(y,x);
			int y_ = map_y_p.at<float>(y,x);
			if (x_ >= 0 && y_ >= 0) {
				if (instancesf.at<uchar>(y_, x_) == 0) {
					instancesf.at<uchar>(y_, x_) = 1;
					mf.at<cv::Vec3b>(y_, x_) = img_perspective.at<cv::Vec3b>(y, x);
				}
			}
		}
	}

	cv::imshow("img_perspective", img_perspective);
	cv::imshow("img_fisheye", img_fisheye);
	cv::imshow("mp", mp);
	cv::imshow("mf", mf);
	cv::waitKey();

	return 0;
}

}	// namespace

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	//check_mapping();
	//return 0;
	std::cout << "Test point mapping" << std::endl;

	test(argc, argv);
	return 0;
}

#endif