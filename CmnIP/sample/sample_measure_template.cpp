/**
* @file sample_matching_template.cpp
* @brief Sample for the template matching.
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
* @author  Ritecs Inc. - Alessandro Moro <alessandromoro.italy@ritecs.co.jp>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "measure/inc/measure/measure_headers.hpp"

namespace
{

void test()
{
	cv::Mat src = cv::imread("../../data/horses.jpg");
	cv::Mat model = src(cv::Rect(150,200,50,80)).clone();
	// Apply a simple blur to differ from the original
	cv::blur(model, model, cv::Size(3, 3));
	cv::imshow("model", model);
	cv::Rect region_out;
	double likelihood;
	commonip::measure::TemplateMatching::region(src, model, 5, true, region_out,
		likelihood);
	std::cout << "Likelihood: " << likelihood << std::endl;
	cv::waitKey();
}


} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample Matching Template" << std::endl;

	test();
	//test_multiple_areas();
	//test_regions();
}