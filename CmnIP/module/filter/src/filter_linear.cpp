/**
* @file filter_linear.cpp
* @brief Body of the classes to perform some filter linear.
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
* @version 1.0.0.0
*
*/


#include "filter/inc/filter/filter_linear.hpp"

namespace CmnIP
{
namespace filter
{

//-----------------------------------------------------------------------------
void FilterLinear::get_gabor(const cv::Mat &src, int kernel_size,
		int pos_sigma, int pos_lm, int pos_th, int pos_psi,
		cv::Mat &dest)
{
	cv::Mat src_f;
	src.convertTo(src_f, CV_32F, 1.0 / 255, 0);
	if (!kernel_size % 2)
	{
		kernel_size += 1;
	}

	double sig = pos_sigma;
	double lm = 0.5 + pos_lm / 100.0;
	double th = pos_th;
	double ps = pos_psi;
	cv::Mat kernel = mkKernel(kernel_size, sig, th, lm, ps);
	cv::filter2D(src_f, dest, CV_32F, kernel);
}
//-----------------------------------------------------------------------------
cv::Mat FilterLinear::mkKernel(int ks, double sig, double th, double lm,
	double ps)
{
	int hks = (ks - 1) / 2;
	double theta = th*CV_PI / 180;
	double psi = ps*CV_PI / 180;
	double del = 2.0 / (ks - 1);
	double lmbd = lm;
	double sigma = sig / ks;
	double x_theta;
	double y_theta;
	cv::Mat kernel(ks, ks, CV_32F);
	for (int y = -hks; y <= hks; y++)
	{
		for (int x = -hks; x <= hks; x++)
		{
			x_theta = x*del*cos(theta) + y*del*sin(theta);
			y_theta = -x*del*sin(theta) + y*del*cos(theta);
			kernel.at<float>(hks + y, hks + x) =
				(float)exp(-0.5*(pow(x_theta, 2) + pow(y_theta, 2)) /
				pow(sigma, 2))* cos(2 * CV_PI*x_theta / lmbd + psi);
		}
	}
	return kernel;
}
//-----------------------------------------------------------------------------
int FilterLinear::get_laplace(const cv::Mat &src, int kernel_size, int scale, 
	int delta, int ddepth, const cv::Size &blur_size, bool convert_scale, 
	cv::Mat &dst)
{
	if( src.empty() ) { return 0; }
	cv::Mat src_gray;
	if (src.channels() == 1) {
		src_gray = src;
	} else {
#if CV_MAJOR_VERSION == 3
		cv::cvtColor(src, src_gray, CV_RGB2GRAY);
#elif CV_MAJOR_VERSION == 4
		cv::cvtColor(src, src_gray, cv::COLOR_RGB2GRAY);
#endif
	}

	/// Remove noise by blurring with a Gaussian filter
	if (blur_size.width > 0 && blur_size.height > 0) {
		cv::GaussianBlur( src_gray, src_gray, blur_size, 
			0, 0, cv::BORDER_DEFAULT );
	}

	// Apply Laplace function
	cv::Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, 
		cv::BORDER_DEFAULT );
	if (convert_scale) {
		convertScaleAbs( dst, dst );
	}
	return 1;
}
//-----------------------------------------------------------------------------
int FilterLinear::filter2D(const cv::Mat src, const cv::Mat &kernel, 
	cv::Mat dst) {
	if (src.empty() || kernel.empty()) return 0;
	cv::Mat result;
	// Allocate if necessary
	result.create(src.size(), src.type());
	// Convolve imagem Gauss com filtro de Laplace
	cv::filter2D(src, dst, src.depth(), kernel);
	return 1;
}
//-----------------------------------------------------------------------------
void FilterLinear::create_kernel(cv::Size &size, double sigma, cv::Mat &kernel)
{
	kernel = cv::Mat(size,CV_64F);
	int rows = kernel.rows;
	int cols = kernel.cols;
	double halfSize = (double) size.width / 2.0; 
	for (int i=0; i<rows;i++)
		for (int j=0; j<cols;j++)
		{ 
			double x = (double)j - halfSize;
			double y = (double)i - halfSize;
			kernel.at<double>(i,j) = 
				(1.0 / (CV_PI*std::pow(sigma,4))) * 
				(1 - (x*x+y*y) / (sigma*sigma)) * 
				(pow(2.718281828, - (x*x + y*y) / 2 * sigma*sigma));
		}
}
//-----------------------------------------------------------------------------
void FilterLinear::create_gauss_filter(cv::Mat &kernel) {

	// Constroi kernel Gauss; todas entradas = 1/16
	cv::Mat kernelGauss(3, 3, CV_32F, cv::Scalar(0.0625));
  
	// Define matriz do filtro de Gauss
	kernelGauss.at<float>(0, 1) = 0.125;
	kernelGauss.at<float>(1, 0) = 0.125;
	kernelGauss.at<float>(1, 1) = 0.25;
	kernelGauss.at<float>(1, 2) = 0.125;
	kernelGauss.at<float>(2, 1) = 0.125;

	kernel = kernelGauss;
}
//-----------------------------------------------------------------------------
void FilterLinear::create_laplace_filter(cv::Mat &kernel) {

	// Constroi kernel Laplace; todas entradas = 0
	cv::Mat kernelLaplace(3, 3, CV_32F, cv::Scalar(0.0));
  
	// Define matriz do filtro de Laplace
	kernelLaplace.at<float>(0, 1) = -1.0;
	kernelLaplace.at<float>(1, 0) = -1.0;
	kernelLaplace.at<float>(1, 1) = +4.0;
	kernelLaplace.at<float>(1, 2) = -1.0;
	kernelLaplace.at<float>(2, 1) = -1.0;

	kernel = kernelLaplace;
}


}	// namespace filter
}	// namespace CmnIP
