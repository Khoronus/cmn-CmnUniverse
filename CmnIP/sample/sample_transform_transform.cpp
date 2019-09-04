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


#include "transform/inc/transform/transform_headers.hpp"

namespace
{

/** Example of use of a sample combine image
*/
void test()
{
	cv::Mat src = cv::imread("..\\..\\data\\horses.jpg");
	cv::Mat dst;
	CmnIP::transform::Transform::dft(src, dst);
	cv::imshow("src", src);
	cv::imshow("DFT", dst);
	cv::Mat gray;
#if CV_MAJOR_VERSION == 3
	cv::cvtColor(src, gray, CV_BGR2GRAY);
#else if CV_MAJOR_VERSION == 4
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
#endif
	CmnIP::transform::Transform::dct(gray, dst);
	cv::imshow("DCT", dst);
	cv::waitKey();
}

}  // namespace anonymous


/** Main function
*/
void main()
{
  test();
}