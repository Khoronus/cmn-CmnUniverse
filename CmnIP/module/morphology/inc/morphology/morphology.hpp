/**
* @file morphology.hpp
* @brief Header of all the files related to the algorithm
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
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__
#define CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "opencv2/legacy/legacy.hpp"

namespace CmnIP
{
namespace morphology
{

/** Simple morphology operations
*/
class Morphology
{
public:

  /**  @function Erosion  */
  static void Erosion( const cv::Mat &src, cv::Mat &dst,
	  int type = 2, int size = 2);

  /** @function Dilation */
  static void Dilation( const cv::Mat &src, cv::Mat &dst,
	  int type = 2, int size = 2 );

};


} // namespace morphology
} // namespace CmnIP

#endif /* CMNIP_MORPHOLOGY_MORPHOLOGY_HPP__ */
