/**
* @file FileLog.hpp
* @brief Header to call log file.
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
* @version 1.0.1.0
*
*/

#include "control/inc/control/FileLog.hpp"


//-----------------------------------------------------------------------------
CmnLib::control::Log::Log(const std::string filename, bool bAppend)
{
	filename_ = filename;
	logError_ = LOG_NOERROR;
	if (bAppend)
		myfile_.open(filename.c_str(), std::ios::app);
	else
		myfile_.open(filename.c_str());

	if (!myfile_.is_open())
		logError_ = LOG_NOFILENAME;
}
//-----------------------------------------------------------------------------
CmnLib::control::Log::~Log()
{
	/// time of the dat
	time_t t = time(0);
#ifdef WIN32
	struct tm *now = &tm();
	localtime_s(now, &t);
#else
	struct tm *now = localtime(&t);
#endif
	myfile_ << "[f] Closure Date: " << (now->tm_year + 1900) << "-" << 
		(now->tm_mon + 1) << "-" << now->tm_mday << " Time: " << 
		now->tm_hour << "-" << now->tm_min << "-" << now->tm_sec << std::endl;
	myfile_.close();
	myfile_.clear();
}
//-----------------------------------------------------------------------------
void CmnLib::control::Log::CreateFileHeader()
{
	logError_ = LOG_NOERROR;
	// start the sincronization
	myfile_ << "[n] New Log Information " << std::endl;
	myfile_ << "Filename: "<< filename_.c_str() << std::endl;

	/// time of the dat
	time_t t = time(0);
#ifdef WIN32
	struct tm *now = &tm();
	localtime_s(now, &t);
#else
	struct tm *now = localtime(&t);
#endif
	myfile_ << "Date: " << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) <<
		"-" << now->tm_mday << " Time: " << now->tm_hour << "-" << 
		now->tm_min << "-" << now->tm_sec << std::endl;
}
//-----------------------------------------------------------------------------
void CmnLib::control::Log::operator+(std::string &msg)
{
	myfile_ << msg << std::endl;
}
//-----------------------------------------------------------------------------
void CmnLib::control::Log::operator+(char *msg)
{
	myfile_ << msg << std::endl;
}
