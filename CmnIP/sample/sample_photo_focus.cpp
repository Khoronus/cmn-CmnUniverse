/**
* @file sample_numericsystem_numericsystem.cpp
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
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "photo/inc/photo/photo_headers.hpp"

namespace
{

void test()
{
	cv::Mat img_normal = cv::imread("../../data/focus_normal.png");
	cv::Mat img_outoffocus = cv::imread("../../data/focus_outoffocus.png");
	if (img_normal.empty() || img_outoffocus.empty()) {
		std::cout << "Images not found" << std::endl;
		return;
	}
	std::cout << "modifiedLaplacian: " << CmnIP::photo::Focus::modifiedLaplacian(img_normal) << " " <<
		CmnIP::photo::Focus::modifiedLaplacian(img_outoffocus) << std::endl;
	std::cout << "normalizedGraylevelVariance: " << CmnIP::photo::Focus::normalizedGraylevelVariance(img_normal) << " " <<
		CmnIP::photo::Focus::normalizedGraylevelVariance(img_outoffocus) << std::endl;
	std::cout << "tenengrad: " << CmnIP::photo::Focus::tenengrad(img_normal, 5) << " " <<
		CmnIP::photo::Focus::tenengrad(img_outoffocus, 5) << std::endl;
	std::cout << "varianceOfLaplacian: " << CmnIP::photo::Focus::varianceOfLaplacian(img_normal) << " " <<
		CmnIP::photo::Focus::varianceOfLaplacian(img_outoffocus) << std::endl;
}

} // namespace anonymous

// ############################################################################

void main()
{
	std::cout << "Sample Photo Focus" << std::endl;

	test();
}


