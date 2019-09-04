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

#endif /* CMNCS_CMNCSCORE_ERROR_HPP__ */
