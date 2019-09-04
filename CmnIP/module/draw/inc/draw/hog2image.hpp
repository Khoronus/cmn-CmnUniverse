/**
* @file pairs.hpp
* @brief Header of the pairs visualization.
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

#ifndef CMNIP_DRAW_HOG2IMAGE_HPP__
#define CMNIP_DRAW_HOG2IMAGE_HPP__

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace CmnIP
{
namespace draw
{

/** @brief Class to display the HOG descriptor

@link http://www.juergenwiki.de/work/wiki/doku.php?id=public%3ahog_descriptor_computation_and_visualization#computing_the_hog_descriptor_using_opencv
*/
class HOG2Image
{
public:

	// HOGDescriptor visual_imagealizer
	// adapted for arbitrary size of feature sets and training images
	static cv::Mat get_hogdescriptor_visual_image(cv::Mat& origImg,
		std::vector<float>& descriptorValues,
		cv::Size winSize,
		cv::Size cellSize,
		int scaleFactor,
		double viz_factor,
		bool verbose)
	{
		cv::Mat visual_image;
		resize(origImg, visual_image, cv::Size(origImg.cols*scaleFactor,
			origImg.rows*scaleFactor));

		int gradientBinSize = 9;
		// dividing 180Åã into 9 bins, how large (in rad) is one bin?
		float radRangeForOneBin = 3.14 / (float)gradientBinSize;

		// prepare data structure: 9 orientation / gradient strenghts for each cell
		int cells_in_x_dir = winSize.width / cellSize.width;
		int cells_in_y_dir = winSize.height / cellSize.height;
		int totalnrofcells = cells_in_x_dir * cells_in_y_dir;
		float*** gradientStrengths = new float**[cells_in_y_dir];
		int** cellUpdateCounter = new int*[cells_in_y_dir];
		for (int y = 0; y<cells_in_y_dir; y++)
		{
			gradientStrengths[y] = new float*[cells_in_x_dir];
			cellUpdateCounter[y] = new int[cells_in_x_dir];
			for (int x=0; x<cells_in_x_dir; x++)
			{
				gradientStrengths[y][x] = new float[gradientBinSize];
				cellUpdateCounter[y][x] = 0;

				for (int bin = 0; bin<gradientBinSize; bin++)
					gradientStrengths[y][x][bin] = 0.0;
			}
		}

		// nr of blocks = nr of cells - 1
		// since there is a new block on each cell (overlapping blocks!) but the last one
		int blocks_in_x_dir = cells_in_x_dir - 1;
		int blocks_in_y_dir = cells_in_y_dir - 1;

		// compute gradient strengths per cell
		int descriptorDataIdx = 0;
		int cellx = 0;
		int celly = 0;

		for (int blockx = 0; blockx<blocks_in_x_dir; blockx++)
		{
			for (int blocky = 0; blocky<blocks_in_y_dir; blocky++)
			{
				// 4 cells per block ...
				for (int cellNr = 0; cellNr<4; cellNr++)
				{
					// compute corresponding cell nr
					int cellx = blockx;
					int celly = blocky;
					if (cellNr == 1) celly++;
					if (cellNr == 2) cellx++;
					if (cellNr == 3)
					{
						cellx++;
						celly++;
					}

					for (int bin = 0; bin<gradientBinSize; bin++)
					{
						float gradientStrength = descriptorValues[descriptorDataIdx];
						descriptorDataIdx++;

						gradientStrengths[celly][cellx][bin] += gradientStrength;

					} // for (all bins)


					// note: overlapping blocks lead to multiple updates of this sum!
					// we therefore keep track how often a cell was updated,
					// to compute average gradient strengths
					cellUpdateCounter[celly][cellx]++;

				} // for (all cells)


			} // for (all block x pos)
		} // for (all block y pos)


		// compute average gradient strengths
		for (int celly = 0; celly<cells_in_y_dir; celly++)
		{
			for (int cellx = 0; cellx<cells_in_x_dir; cellx++)
			{

				float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];

				// compute average gradient strenghts for each gradient bin direction
				for (int bin = 0; bin<gradientBinSize; bin++)
				{
					gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
				}
			}
		}


		if (verbose) {
			std::cout << "descriptorDataIdx = " << descriptorDataIdx <<
				std::endl;
		}

		// draw cells
		for (int celly = 0; celly<cells_in_y_dir; celly++)
		{
			for (int cellx = 0; cellx<cells_in_x_dir; cellx++)
			{
				int drawX = cellx * cellSize.width;
				int drawY = celly * cellSize.height;

				int mx = drawX + cellSize.width / 2;
				int my = drawY + cellSize.height / 2;

				cv::rectangle(visual_image,
					cv::Point(drawX*scaleFactor, drawY*scaleFactor),
					cv::Point((drawX + cellSize.width)*scaleFactor,
					(drawY + cellSize.height)*scaleFactor),
					CV_RGB(100, 100, 100),
					1);

				// draw in each cell all 9 gradient strengths
				for (int bin = 0; bin<gradientBinSize; bin++)
				{
					float currentGradStrength = gradientStrengths[celly][cellx][bin];

					// no line to draw?
					if (currentGradStrength == 0)
						continue;

					float currRad = bin * radRangeForOneBin + radRangeForOneBin / 2;

					float dirVecX = cos(currRad);
					float dirVecY = sin(currRad);
					float maxVecLen = cellSize.width / 2;
					float scale = viz_factor; // just a visual_imagealization scale,
					// to see the lines better

					// compute line coordinates
					float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
					float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
					float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
					float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

					// draw gradient visual_imagealization
					cv::line(visual_image,
						cv::Point(x1*scaleFactor, y1*scaleFactor),
						cv::Point(x2*scaleFactor, y2*scaleFactor),
						CV_RGB(0, 0, 255),
						1);

				} // for (all bins)

			} // for (cellx)
		} // for (celly)


		// don't forget to free memory allocated by helper data structures!
		for (int y = 0; y<cells_in_y_dir; y++)
		{
			for (int x = 0; x<cells_in_x_dir; x++)
			{
				delete[] gradientStrengths[y][x];
			}
			delete[] gradientStrengths[y];
			delete[] cellUpdateCounter[y];
		}
		delete[] gradientStrengths;
		delete[] cellUpdateCounter;

		return visual_image;
	}

};


} // namespace draw
} // namespace CmnIP

#endif /* CMNIP_DRAW_HOG2IMAGE_HPP__ */
