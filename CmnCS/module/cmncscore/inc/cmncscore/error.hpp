/**
* @file error.hpp
* @brief Contains classes to manage errors.
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
* @version 1.1.1.0
*
*/

#ifndef CMNCS_CMNCSCORE_ERROR_HPP__
#define CMNCS_CMNCSCORE_ERROR_HPP__

#include "libdefine.hpp"

#ifdef USE_OPENCV

#include <iostream>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

/** Redirect the opencv error
    http://stackoverflow.com/questions/17567808/how-to-suppress-opencv-error-message
*/
static int handleErrorCalib( int status, const char* func_name,
			const char* err_msg, const char* file_name,
			int line, void* userdata )
{
	//Do nothing -- will suppress console output
	return 0;   //Return value is not used
}

#endif

#endif // CMNCS_CMNCSCORE_ERROR_HPP__
