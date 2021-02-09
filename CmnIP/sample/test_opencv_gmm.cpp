/* @file test_opencv_gmm.cpp
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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
//#include <opencv2/gpu/gpu.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/ml/ml.hpp>
#if CV_MAJOR_VERSION == 2
#include <opencv2/legacy/legacy.hpp>
#endif

namespace
{


bool IsNumber(double x)
{
	// This looks like it should always be true, 
	// but it's false if x is a NaN.
	return (x == x);
}

void gmm()
{
#if CV_MAJOR_VERSION == 2

	// 1. Prepare training vectors

	// 1.1 Create a list of sample points from a RGB image (some image structure, e.g. text on white background)
	//cv::Mat SampleImg = imread("W:\\01_data\\07_testimgs\\blobs_and_rectangles.png");
	cv::Mat SampleImg = cv::imread("..\\..\\data\\horses.jpg");
	if (SampleImg.empty()) return;
	int SampleImgHeight = SampleImg.rows;
	int SampleImgWidth = SampleImg.cols;
	std::vector<cv::Point> ListSamplePoints;
	for (int y = 0; y<SampleImgHeight; y++)
	{
		for (int x = 0; x<SampleImgWidth; x++)
		{
			// Get pixel color at that position
			cv::Vec3b bgrPixel = SampleImg.at<cv::Vec3b>(y, x);

			uchar b = bgrPixel.val[0];
			//uchar g = bgrPixel.val[1];
			//uchar r = bgrPixel.val[2];

			if (b == 0)
			{
				if (rand() % 2 == 0)
				{
					ListSamplePoints.push_back(cv::Point(x, y));

				} // (add to list of sample points?)

			} // if (color is not white)

		} // for (x)
	} // for (y)

	// 1.2 Write the just generated sample list points in <ListSamplePoints> to a matrix
	cv::Mat labels;
	int NrSamples = ListSamplePoints.size();
	cv::Mat samples(NrSamples, 2, CV_32FC1);
	for (int s = 0; s<NrSamples; s++)
	{
		cv::Point p = ListSamplePoints[s];

		samples.at<float>(s, 0) = (float)p.x;
		samples.at<float>(s, 1) = (float)p.y;
	}

	// Try out different nrs of GMM components to represent the sample distribution
	for (int NrGMMComponents = 1; NrGMMComponents <= 100; NrGMMComponents++)
	{
		// The number of samples must be bigger or equal to the number of the
		// number of GMM components
		if (NrGMMComponents > NrSamples) break;

		// 2. Prepare GMM training

		// 2.1 Set GMM parameters
		CvEMParams params;
		params.covs = NULL;
		params.means = NULL;
		params.weights = NULL;
		params.probs = NULL;
		params.nclusters = NrGMMComponents;
		params.cov_mat_type = CvEM::COV_MAT_GENERIC; // DIAGONAL, GENERIC, SPHERICAL
		params.start_step = CvEM::START_AUTO_STEP;
		params.term_crit.max_iter = 1500;
		params.term_crit.epsilon = 0.001;
		params.term_crit.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
		//params.term_crit.type     = CV_TERMCRIT_ITER;

		// 2.2 Estimate GMM params for all <NrGMMComponents> Gaussian Mixture Components
		CvEM em_model;
		em_model.train(samples, cv::Mat(), params, &labels);

		// 3. Visualize results

		// 3.1 Prepare visualization images
		cv::Mat img = cv::Mat::zeros(cv::Size(SampleImgWidth, SampleImgHeight), CV_8UC3);
		cv::Mat img2 = cv::Mat::zeros(cv::Size(SampleImgWidth, SampleImgHeight), CV_8UC3);

		char txt[500];
		sprintf_s(txt, "nr of gaussians: %d", NrGMMComponents);
		cv::putText(img, txt, cv::Point(10, 30), CV_FONT_HERSHEY_SIMPLEX, .75, CV_RGB(0, 255, 0));
		cv::putText(img2, txt, cv::Point(10, 30), CV_FONT_HERSHEY_SIMPLEX, .75, CV_RGB(0, 255, 0));

		// 3.2 Show classification for each pixel to which GMM component it belongs?
		if (false)
		{
			// Classify every image pixel
			// A single sample is a 1x2 float matrix
			cv::Mat sample(1, 2, CV_32FC1);
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					sample.at<float>(0) = (float)j;
					sample.at<float>(1) = (float)i;
					int response = cvRound(em_model.predict(sample));
					//Scalar c = colors[response];
					//circle( img, Point(j, i), 1, c*0.75, CV_FILLED );
				}
			}
		}

		// 3.3 Draw the samples
		for (int i = 0; i < NrSamples; i++)
		{
			float x = samples.at<float>(i, 0);
			float y = samples.at<float>(i, 1);
			cv::Point pt = cv::Point(x, y);
			cv::circle(img, pt, 1, CV_RGB(255, 0, 0), CV_FILLED);
		}

		// 3.4 Draw the cluster centers
		cv::Mat Means = em_model.getMeans();
		cv::Mat Weights = em_model.getWeights();
		std::vector<cv::Mat> covs;
		em_model.getCovs(covs);
		for (int i = 0; i<params.nclusters; i++)
		{
			double cx = Means.at<double>(i, 0);
			double cy = Means.at<double>(i, 1);
			double wi = Weights.at<double>(0, i);

			// Ups! Invalid cluster center!
			if (!IsNumber(cx))
			{
				continue;
			}

			circle(img, cv::Point(cx, cy), 5, CV_RGB(255, 255, 255), CV_FILLED);

			cv::Mat CurrCovMat = covs.at(i);
			double m11 = CurrCovMat.at<double>(0, 0);
			double m12 = CurrCovMat.at<double>(0, 1);

			double m21 = CurrCovMat.at<double>(1, 0);
			double m22 = CurrCovMat.at<double>(1, 1);

			// Get Eigenvectors + Eigenvalues of that covariance matrix
			cv::Mat eigenvalues;
			cv::Mat eigenvectors;
			cv::eigen(CurrCovMat, eigenvalues, eigenvectors);

			double eigenvec1_len = eigenvalues.at<double>(0, 0);
			double len1 = std::sqrt(eigenvec1_len) * 3;
			double eigenvec1_x = eigenvectors.at<double>(0, 0) * len1;
			double eigenvec1_y = eigenvectors.at<double>(1, 0) * len1;

			double eigenvec2_len = eigenvalues.at<double>(1, 0);
			double len2 = sqrt(eigenvec2_len) * 3;
			double eigenvec2_x = eigenvectors.at<double>(0, 1) * len2;
			double eigenvec2_y = eigenvectors.at<double>(1, 1) * len2;

			/*
			if ( (NrGMMComponents!=1) && ((len1>SampleImgHeight/2) || (len1>SampleImgWidth/2)) )
			{
			Logger::Access()->Log( "Yet another OpenCV EM algorithm error..." );
			continue;
			}
			*/

			// Show axes of ellipse
			line(img, cv::Point(cx, cy), cv::Point(cx + eigenvec1_x, cy + eigenvec1_y), CV_RGB(255, 255, 0));
			line(img, cv::Point(cx, cy), cv::Point(cx + eigenvec2_x, cy + eigenvec2_y), CV_RGB(0, 255, 0));

			// Show ellipse rotated into direction of eigenvec1
			double dx = eigenvec1_x;
			double dy = eigenvec1_y;
			double angle_rad = atan2(dy, dx);
			double angle_deg = angle_rad * (180.0 / CV_PI); // convert radians (0,2PI) to degree (0Åã,360Åã)
			cv::RotatedRect* myRotatedRect = new cv::RotatedRect(cvPoint(cx, cy), cvSize(len1, len2), angle_deg);
			if (myRotatedRect != nullptr)
			{
				int g = wi*255.0 * (i + 1);
				cv::Scalar s = CV_RGB(g, g, g);
				ellipse(img, *myRotatedRect, s);
				ellipse(img2, *myRotatedRect, s, -1);

				delete myRotatedRect;
			}
		}

		// 3.5 Save image
		char filename1[500];
		char filename2[500];
		sprintf_s(filename1, "visu1_sample_distribution_represented_with_%03d_gaussians.png", NrGMMComponents);
		sprintf_s(filename2, "visu2_sample_distribution_represented_with_%03d_gaussians.png", NrGMMComponents);
		//cv::imwrite(filename1, img);
		//cv::imwrite(filename2, img2);
		cv::imshow("img", img);
		cv::imshow("img2", img2);
		cv::waitKey();

	} // for (NrGMMComponents)

#else
	std::cout << "NOT IMPLEMENTED IN OPENCV3+" << std::endl;
#endif

}

} // namespace anonymous

// ############################################################################
// ############################################################################
// ############################################################################

/**	 Main code
*/
int main(int argc, char *argv[])
{
	gmm();
	return 0;
}
