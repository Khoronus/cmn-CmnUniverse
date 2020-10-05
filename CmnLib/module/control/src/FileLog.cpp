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
