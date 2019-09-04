/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#include <iostream>
#include <ctype.h>


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/video/tracking.hpp"
//#include "opencv2/legacy/legacy.hpp"
#include "opencv2/video/background_segm.hpp"
#if CV_MAJOR_VERSION == 2
#include <opencv2/nonfree/nonfree.hpp>
#endif

namespace
{

	cv::Mat image;

	bool backprojMode = false;
	bool selectObject = false;
	int trackObject = 0;
	bool showHist = true;
	cv::Point origin;
	cv::Rect selection;
	int vmin = 10, vmax = 256, smin = 30;

	static void onMouse(int event, int x, int y, int, void*)
	{
		if (selectObject)
		{
			selection.x = MIN(x, origin.x);
			selection.y = MIN(y, origin.y);
			selection.width = std::abs(x - origin.x);
			selection.height = std::abs(y - origin.y);

			selection &= cv::Rect(0, 0, image.cols, image.rows);
		}

		switch (event)
		{
#if CV_MAJOR_VERSION == 3
		case CV_EVENT_LBUTTONDOWN:
#else if CV_MAJOR_VERSION == 4
		case cv::EVENT_LBUTTONDOWN:
#endif
			origin = cv::Point(x, y);
			selection = cv::Rect(x, y, 0, 0);
			selectObject = true;
			break;
#if CV_MAJOR_VERSION == 3
		case CV_EVENT_LBUTTONUP:
#else if CV_MAJOR_VERSION == 4
		case cv::EVENT_LBUTTONUP:
#endif
			selectObject = false;
			if (selection.width > 0 && selection.height > 0)
				trackObject = -1;
			break;
		}
	}

	static void help()
	{
		std::cout << "\nThis is a demo that shows mean-shift based tracking\n"
			"You select a color objects such as your face and it tracks it.\n"
			"This reads from video camera (0 by default, or the camera number"\
			" the user enters\n"
			"Usage: \n"
			"   ./camshiftdemo [camera number]\n";

		std::cout << "\n\nHot keys: \n"
			"\tESC - quit the program\n"
			"\tc - stop the tracking\n"
			"\tb - switch to/from backprojection view\n"
			"\th - show/hide object histogram\n"
			"\tp - pause video\n"
			"To initialize tracking, select the object with mouse\n";
	}

	const char* keys =
	{
		"{1|  | 0 | camera number}"
	};

}	// namespace anonymous


int main(int argc, const char** argv)
{
	help();

	cv::Rect trackWindow;
	int hsize = 16;
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;
	cv::CommandLineParser parser(argc, argv, keys);


	// Camera manager
	cv::VideoCapture vc(0);

	// Image and Histogram containers and vars
	cv::Mat frame, hsv, hue, mask, hist,
		histimg = cv::Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;

	// Bars and window
	cv::namedWindow("Histogram", 0);
	cv::namedWindow("CamShift Demo", 0);
	cv::setMouseCallback("CamShift Demo", onMouse, 0);
	cv::createTrackbar("Vmin", "CamShift Demo", &vmin, 256, 0);
	cv::createTrackbar("Vmax", "CamShift Demo", &vmax, 256, 0);
	cv::createTrackbar("Smin", "CamShift Demo", &smin, 256, 0);


	int iFrameNum = 0;
	bool bContinue = true;
	while (bContinue)
	{
		if (!paused)
		{
			vc >> frame;
			if (frame.empty())
				continue;
		}

		frame.copyTo(image);

		if (!paused)
		{
#if CV_MAJOR_VERSION == 3
			cvtColor(image, hsv, CV_BGR2HSV);
#else if CV_MAJOR_VERSION == 4
			cvtColor(image, hsv, cv::COLOR_BGR2HSV);
#endif

			if (trackObject)
			{
				int _vmin = vmin, _vmax = vmax;

				inRange(hsv, cv::Scalar(0, smin, MIN(_vmin, _vmax)),
					cv::Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = { 0, 0 };
				hue.create(hsv.size(), hsv.depth());
				mixChannels(&hsv, 1, &hue, 1, ch, 1);

				if (trackObject < 0)
				{
					cv::Mat roi(hue, selection), maskroi(mask, selection);
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
#if CV_MAJOR_VERSION == 3
					normalize(hist, hist, 0, 255, CV_MINMAX);
#else if CV_MAJOR_VERSION == 4
					normalize(hist, hist, 0, 255, cv::NORM_MINMAX);
#endif

					trackWindow = selection;
					trackObject = 1;

					histimg = cv::Scalar::all(0);
					int binW = histimg.cols / hsize;
					cv::Mat buf(1, hsize, CV_8UC3);
					for (int i = 0; i < hsize; i++)
						buf.at<cv::Vec3b>(i) = cv::Vec3b(
						cv::saturate_cast<uchar>(i*180. / hsize), 255, 255);
#if CV_MAJOR_VERSION == 3
					cvtColor(buf, buf, CV_HSV2BGR);
#else if CV_MAJOR_VERSION == 4
					cvtColor(buf, buf, cv::COLOR_HSV2BGR);
#endif

					for (int i = 0; i < hsize; i++)
					{
						int val = cv::saturate_cast<int>(hist.at<float>(i) *
							histimg.rows / 255);
						rectangle(histimg, cv::Point(i*binW, histimg.rows),
							cv::Point((i + 1)*binW, histimg.rows - val),
							cv::Scalar(buf.at<cv::Vec3b>(i)), -1, 8);
					}
				}

				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				backproj &= mask;
#if CV_MAJOR_VERSION == 3
				cv::RotatedRect trackBox = CamShift(backproj, trackWindow,
					cv::TermCriteria(CV_TERMCRIT_EPS |
						CV_TERMCRIT_ITER, 10, 1));
#else if CV_MAJOR_VERSION == 4
				cv::RotatedRect trackBox = CamShift(backproj, trackWindow,
					cv::TermCriteria(cv::TermCriteria::EPS |
						cv::TermCriteria::MAX_ITER, 10, 1));
#endif
				if (trackWindow.area() <= 1)
				{
					int cols = backproj.cols, rows = backproj.rows,
						r = (MIN(cols, rows) + 5) / 6;
					trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
						trackWindow.x + r, trackWindow.y + r) &
						cv::Rect(0, 0, cols, rows);
				}

#if CV_MAJOR_VERSION == 3
				if (backprojMode) {
					cvtColor(backproj, image, CV_GRAY2BGR);
			}
				//ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
				cv::rectangle(image, trackBox.boundingRect(),
					cv::Scalar(0, 0, 255), 3, CV_AA);
#else if CV_MAJOR_VERSION == 4
				if (backprojMode) {
					cvtColor(backproj, image, cv::COLOR_GRAY2BGR);
				}
				//ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
				cv::rectangle(image, trackBox.boundingRect(),
					cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
#endif

				/// Find the center box of the face
				cv::Point RectCenter(trackBox.boundingRect().x +
					trackBox.boundingRect().width / 2,
					trackBox.boundingRect().y +
					trackBox.boundingRect().height / 2);
				cv::Rect rFace(RectCenter.x - MIN(
					trackBox.boundingRect().width / 2,
					trackBox.boundingRect().height / 2),
					RectCenter.y - MIN(
					trackBox.boundingRect().width / 2,
					trackBox.boundingRect().height / 2),
					MIN(trackBox.boundingRect().width,
					trackBox.boundingRect().height),
					MIN(trackBox.boundingRect().width,
					trackBox.boundingRect().height));
#if CV_MAJOR_VERSION == 3
				cv::rectangle(image, rFace, cv::Scalar(0, 255, 255), 3, 
					CV_AA);
#else if CV_MAJOR_VERSION == 4
				cv::rectangle(image, rFace, cv::Scalar(0, 255, 255), 3, 
					cv::LINE_AA);
#endif

				std::vector< cv::Point2f > v_point;
				int _h = 2, _w = 2;
				//int w = (trackBox.boundingRect().x + trackBox.boundingRect().width) / _w;
				//int h = (trackBox.boundingRect().y + trackBox.boundingRect().height) / _h;

				int w = rFace.width / _w;
				int h = rFace.height / _h;

				for (int i = 0; i < _h; i++)
				{
					for (int j = 0; j < _w; j++)
					{
						v_point.push_back(cv::Point2f(
							trackBox.boundingRect().x + j * w,
							trackBox.boundingRect().y + i * h));
					}
				}

				char buf_tmp[256];
				sprintf(buf_tmp, "image_%i.jpg", iFrameNum);
				//cv::imwrite(buf_tmp, image);
				iFrameNum++;

			}
		} else if (trackObject < 0) {
			paused = false;
		}

		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			cv::Mat roi(image, selection);
			bitwise_not(roi, roi);
		}

		imshow("CamShift Demo", image);
		imshow("Histogram", histimg);

		char c = (char)cv::waitKey(10);
		if (c == 27)
			break;
		switch (c)
		{
		case 'b':
			backprojMode = !backprojMode;
			break;
		case 'c':
			trackObject = 0;
			histimg = cv::Scalar::all(0);
			break;
		case 'h':
			showHist = !showHist;
			if (!showHist)
				cv::destroyWindow("Histogram");
			else
				cv::namedWindow("Histogram", 1);
			break;
		case 'p':
			paused = !paused;
			break;
		case 'q':
			bContinue = false;
			break;
		default:
			;
		}
	}

	return 0;
}
