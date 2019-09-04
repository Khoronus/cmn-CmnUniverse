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
#include <fstream>

#include <opencv2/highgui/highgui.hpp>

#include "cmnipcontainer/inc/cmnipcontainer/cmnipcontainer_headers.hpp"
//#include "ts.hpp"

namespace
{
// ############################################################################


void test()
{
	cv::Mat img0(512, 512, CV_8UC3, cv::Scalar::all(0));
	cv::Mat img1(512, 512, CV_8UC3, cv::Scalar::all(0));
	cv::Mat img2(512, 512, CV_8UC3, cv::Scalar::all(0));

	CmnIP::cmnipcontainer::ImagePointsAssociation ipa;

	for (int i = 0; i < 4; i++)
	{
		ipa.setPoint(0, 4, std::make_pair(0, 1), i, 
			cv::Point2f(std::rand() % img0.cols, std::rand() % img0.rows));
		ipa.setPoint(1, 4, std::make_pair(1, 0), i, 
			cv::Point2f(std::rand() % img0.cols, std::rand() % img0.rows));
	}
	for (int i = 0; i < 4; i++)
	{
		ipa.setPoint(0, 4, std::make_pair(0, 2), i,
			cv::Point2f(std::rand() % img0.cols, std::rand() % img0.rows));
		ipa.setPoint(2, 4, std::make_pair(2, 0), i,
			cv::Point2f(std::rand() % img0.cols, std::rand() % img0.rows));
	}

	ipa.save("", "ImagePointsAssociation_Sample.txt");
	
	ipa.load("", "ImagePointsAssociation_Sample.txt");


	cv::Mat img0points(512, 512, CV_8UC3, cv::Scalar::all(0));
	ipa.toImage(0, 1.0, 1.0, img0points);
	cv::imshow("img0points", img0points);
	cv::Mat img1points(512, 512, CV_8UC3, cv::Scalar::all(0));
	ipa.toImage(1, 1.0, 1.0, img1points);
	cv::imshow("img1points", img1points);
	cv::Mat img2points(512, 512, CV_8UC3, cv::Scalar::all(0));
	ipa.toImage(2, 1.0, 1.0, img2points);
	cv::imshow("img2points", img2points);
	cv::waitKey();

}


} // namespace anonymous

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	test();
	return 0;
}

#endif