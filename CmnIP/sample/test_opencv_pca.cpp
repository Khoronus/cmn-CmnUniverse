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

using namespace cv;
using namespace std;

#define usethis3

#ifdef usethis1

/*
* pca.cpp
*
*  Author:
*  Kevin Hughes <kevinhughes27[at]gmail[dot]com>
*
*  Special Thanks to:
*  Philipp Wagner <bytefish[at]gmx[dot]de>
*
* This program demonstrates how to use OpenCV PCA with a
* specified amount of variance to retain. The effect
* is illustrated further by using a trackbar to
* change the value for retained varaince.
*
* The program takes as input a text file with each line
* begin the full path to an image. PCA will be performed
* on this list of images. The author recommends using
* the first 15 faces of the AT&T face data set:
* http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
*
* so for example your input text file would look like this:
*
*        <path_to_at&t_faces>/orl_faces/s1/1.pgm
*        <path_to_at&t_faces>/orl_faces/s2/1.pgm
*        <path_to_at&t_faces>/orl_faces/s3/1.pgm
*        <path_to_at&t_faces>/orl_faces/s4/1.pgm
*        <path_to_at&t_faces>/orl_faces/s5/1.pgm
*        <path_to_at&t_faces>/orl_faces/s6/1.pgm
*        <path_to_at&t_faces>/orl_faces/s7/1.pgm
*        <path_to_at&t_faces>/orl_faces/s8/1.pgm
*        <path_to_at&t_faces>/orl_faces/s9/1.pgm
*        <path_to_at&t_faces>/orl_faces/s10/1.pgm
*        <path_to_at&t_faces>/orl_faces/s11/1.pgm
*        <path_to_at&t_faces>/orl_faces/s12/1.pgm
*        <path_to_at&t_faces>/orl_faces/s13/1.pgm
*        <path_to_at&t_faces>/orl_faces/s14/1.pgm
*        <path_to_at&t_faces>/orl_faces/s15/1.pgm
*
*/

///////////////////////
// Functions
static void read_imgList(const string& filename, vector<Mat>& images) {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line;
	while (getline(file, line)) {
		images.push_back(imread(line, 0));
	}
}

static  Mat formatImagesForPCA(const vector<Mat> &data)
{
	std::cout << data[0].cols << " " << data[0].rows << std::endl;
	Mat dst(static_cast<int>(data.size()), data[0].rows*data[0].cols, CV_32F);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		Mat image_row = data[i].clone().reshape(1, 1);

		//cv::imshow("Data", data[i]);
		//cv::imshow("image_row", image_row);
		Mat row_i = dst.row(i);
		image_row.convertTo(row_i, CV_32F);
		//cv::imshow("image_row2", image_row);
		//cv::imshow("row_i", row_i);
		//std::cout << row_i << std::endl;
		//cv::waitKey(0);
		//image_row = image_row / 255;
	}
	cv::Mat tmp;
	cv::resize(dst, tmp, cv::Size(1200, 200));
	cv::imshow("dst", tmp);
	//cv::waitKey(0);
	dst = dst / 255;
	return dst;
}

static Mat toGrayscale(InputArray _src) {
	Mat src = _src.getMat();
	// only allow one channel
	if (src.channels() != 1) {
		CV_Error(CV_StsBadArg, "Only Matrices with one channel are supported");
	}
	// create and return normalized image
	Mat dst;
	cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	return dst;
}

struct params
{
	Mat data;
	int ch;
	int rows;
	PCA pca;
	string winName;
};

static void onTrackbar(int pos, void* ptr)
{
	cout << "Retained Variance = " << pos << "%   ";
	cout << "re-calculating PCA..." << std::flush;

	double var = pos / 100.0;

	struct params *p = (struct params *)ptr;
	cv::Mat tmp = toGrayscale(p->data);
	cv::imshow("datapca", tmp);
	p->pca = PCA(p->data, cv::Mat(), CV_PCA_DATA_AS_ROW, var);

	Mat point = p->pca.project(p->data.row(0));
	Mat reconstruction = p->pca.backProject(point);
	reconstruction = reconstruction.reshape(p->ch, p->rows);
	reconstruction = toGrayscale(reconstruction);

	imshow("point", point);
	imshow(p->winName, reconstruction);
	std::cout << std::endl << " >>> " << std::endl;
	std::cout << p->data.cols << " " << p->data.rows << " " << p->pca.eigenvalues.cols << " " << p->pca.eigenvalues.rows << std::endl;
	cout << "done!   # of principal components: " << p->pca.eigenvectors.cols << " " << p->pca.eigenvectors.rows << endl;
	std::cout << "Eigenvalues: " << p->pca.eigenvalues << std::endl;
}


///////////////////////
// Main
int main(int argc, char** argv)
{
	// Get the path to your CSV.
	string imgList = string("..\\..\\data\\image_list.txt");

	// vector to hold the images
	vector<Mat> images;

	// Read in the data. This can fail if not valid
	try {
		read_imgList(imgList, images);
	}
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << imgList << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	// Quit if there are not enough images for this demo.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}

	// Reshape and stack images into a rowMatrix
	Mat data = formatImagesForPCA(images);

	// perform PCA
	PCA pca(data, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a cmn value for retainedVariance

	// Demonstration of the effect of retainedVariance on the first image
	Mat point = pca.project(data.row(0)); // project into the eigenspace, thus the image becomes a "point"
	Mat reconstruction = pca.backProject(point); // re-create the image from the "point"
	reconstruction = reconstruction.reshape(images[0].channels(), images[0].rows); // reshape from a row vector into image shape
	reconstruction = toGrayscale(reconstruction); // re-scale for displaying purposes

	// init highgui window
	string winName = "Reconstruction | press 'q' to quit";
	namedWindow(winName, WINDOW_NORMAL);

	// params struct to pass to the trackbar handler
	params p;
	p.data = data;
	p.ch = images[0].channels();
	p.rows = images[0].rows;
	p.pca = pca;
	p.winName = winName;

	// create the tracbar
	int pos = 95;
	createTrackbar("Retained Variance (%)", winName, &pos, 100, onTrackbar, (void*)&p);

	// display until user presses q
	imshow(winName, reconstruction);

	int key = 0;
	while (key != 'q')
		key = waitKey();

	return 0;
}

#endif




#ifdef usethis2


Mat normalize(const Mat& src) {
	Mat srcnorm;
	normalize(src, srcnorm, 0, 255, NORM_MINMAX, CV_8UC1);
	return srcnorm;
}



//
int main(int argc, char *argv[]) {
	vector<Mat> db;

	// load greyscale images (these are from http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html)
	//for (int i = 0; i < 100; i++)
	//{
	//	char buf[1024];
	//	sprintf(buf, "C:\\workspace\\programs\\development\\ccpp\\samples_norepo\\GenericCV\\vs2013\\sample\\1_%i.png", i);
	//	cv::Mat m = cv::imread(buf, 0);
	//	if (m.empty()) continue;
	//	db.push_back(m);
	//}
	db.push_back(imread("..\\..\\data\\att_faces\\s1\\1.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s1\\2.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s1\\3.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s1\\4.pgm", 0));

	db.push_back(imread("..\\..\\data\\att_faces\\s2\\1.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s2\\2.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s2\\3.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s2\\4.pgm", 0));

	db.push_back(imread("..\\..\\data\\att_faces\\s3\\1.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s3\\2.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s3\\3.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s3\\4.pgm", 0));

	db.push_back(imread("..\\..\\data\\att_faces\\s4\\1.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s4\\2.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s4\\3.pgm", 0));
	db.push_back(imread("..\\..\\data\\att_faces\\s4\\4.pgm", 0));

	int total = db[0].rows * db[0].cols;

	// build matrix (column)
	Mat mat(total, db.size(), CV_32FC1);
	for (int i = 0; i < db.size(); i++) {
		Mat X = mat.col(i);
		db[i].reshape(1, total).col(0).convertTo(X, CV_32FC1, 1 / 255.);
	}

	// Change to the number of principal components you want:
	int numPrincipalComponents = 16;

	// Do the PCA:
	PCA pca(mat, Mat(), CV_PCA_DATA_AS_COL, numPrincipalComponents);

	// Create the Windows:
	namedWindow("avg", 1);
	namedWindow("pc1", 1);
	namedWindow("pc2", 1);
	namedWindow("pc3", 1);
	namedWindow("pc4", 1);

	// Mean face:
	imshow("avg", pca.mean.reshape(1, db[0].rows));

	std::cout << pca.eigenvalues.cols << " " << pca.eigenvalues.rows << std::endl;
	std::cout << pca.eigenvalues << std::endl;

	std::cout << "Eigenvalues: " << pca.eigenvalues.rows << " " << pca.eigenvalues.cols << std::endl;
	std::cout << "Eigenvectors: " << pca.eigenvectors.rows << " " << pca.eigenvectors.cols << std::endl;
	//Store the eigenvalues and eigenvectors
	vector<Point2d> eigen_vecs(pca.eigenvalues.rows);
	vector<double> eigen_val(pca.eigenvalues.rows);
	for (int i = 0; i < pca.eigenvalues.rows; ++i)
	{
		eigen_vecs[i] = Point2d(pca.eigenvectors.at<double>(i, 0),
			pca.eigenvectors.at<double>(i, 1));

		eigen_val[i] = pca.eigenvalues.at<double>(0, i);
		std::cout << eigen_vecs[i] << " -> " << eigen_val[i] << std::endl;
	}


	// First three eigenfaces:
	for (int i = 0; i < numPrincipalComponents; i++)
	{
		std::cout << i << "...";
		char buf[256];
		sprintf(buf, "pc%i", i);
		imshow(buf, normalize(pca.eigenvectors.row(i)).reshape(1, db[0].rows));
		std::cout << "done" << std::endl;
	}
	// Show the windows:
	waitKey(0);
}


#endif


#ifdef usethis3


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace
{
	double getOrientation(std::vector<cv::Point> &pts, cv::Mat &img)
	{
		if (pts.size() == 0) return false;

		//Construct a buffer used by the pca analysis
		cv::Mat data_pts = cv::Mat(pts.size(), 2, CV_64FC1);
		for (int i = 0; i < data_pts.rows; ++i)
		{
			data_pts.at<double>(i, 0) = pts[i].x;
			data_pts.at<double>(i, 1) = pts[i].y;
		}


		//Perform PCA analysis
#if CV_MAJOR_VERSION == 3
		cv::PCA pca_analysis(data_pts, cv::Mat(), CV_PCA_DATA_AS_ROW);
#elif CV_MAJOR_VERSION == 4
		cv::PCA pca_analysis(data_pts, cv::Mat(), cv::PCA::DATA_AS_ROW);
#endif

		//Store the position of the object
		cv::Point pos = cv::Point(pca_analysis.mean.at<double>(0, 0),
			pca_analysis.mean.at<double>(0, 1));

		//Store the eigenvalues and eigenvectors
		std::vector<cv::Point2d> eigen_vecs(2);
		std::vector<double> eigen_val(2);
		for (int i = 0; i < 2; ++i)
		{
			eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
				pca_analysis.eigenvectors.at<double>(i, 1));

			eigen_val[i] = pca_analysis.eigenvalues.at<double>(0, i);
		}

		// Draw the principal components
		circle(img, pos, 3, CV_RGB(255, 0, 255), 2);
		cv::line(img, pos, pos + 0.02 * cv::Point(eigen_vecs[0].x * eigen_val[0], eigen_vecs[0].y * eigen_val[0]), CV_RGB(255, 255, 0));
		cv::line(img, pos, pos + 0.02 * cv::Point(eigen_vecs[1].x * eigen_val[1], eigen_vecs[1].y * eigen_val[1]), CV_RGB(0, 255, 255));

		return std::atan2(eigen_vecs[0].y, eigen_vecs[0].x);
	}
}

int main()
{
	// Read the image
	Mat bw, img = imread("..\\..\\data\\pca_test1.jpg"); // "pca_test2.jpg"
	//Mat bw, img = imread("..\\..\\data\\imgang.png"); // "pca_test2.jpg"
	//Mat bw, img = imread("C:\\moro\\programs\\sample\\TrafficLight\\vs2013\\code\\idx0.png"); // "pca_test2.jpg"

	// Convert it to greyscale
	cv::cvtColor(img, bw, COLOR_BGR2GRAY);

	// Apply thresholding
#if CV_MAJOR_VERSION == 3
	cv::threshold(bw, bw, 150, 255, CV_THRESH_BINARY);
#elif CV_MAJOR_VERSION == 4
	cv::threshold(bw, bw, 150, 255, cv::THRESH_BINARY);
#endif

	// Find all objects of interest
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
#if CV_MAJOR_VERSION == 3
	cv::findContours(bw, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
#elif CV_MAJOR_VERSION == 4
	cv::findContours(bw, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
#endif

	// For each object
	for (size_t i = 0; i < contours.size(); ++i)
	{
		// Calculate its area
		double area = cv::contourArea(contours[i]);

		// Ignore if too small or too large
		if (area < 1e2 || 1e5 < area) continue;

		// Draw the contour
		cv::drawContours(img, contours, i, CV_RGB(255, 0, 0), 2, 8, hierarchy, 0);

		// Get the object orientation
		getOrientation(contours[i], img);
	}

	cv::imshow("Image", img);
	char key;
	while (true)
	{
		key = cv::waitKey(1);

		if (key == 'q' || key == 27) break;
	}

	return 0;
}

#endif
