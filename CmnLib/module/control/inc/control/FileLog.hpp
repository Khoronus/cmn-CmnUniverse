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

#ifndef CMNLIB_CONTROL_FILELOG_HPP__
#define CMNLIB_CONTROL_FILELOG_HPP__

#include <time.h>

#include <string>
#include <iostream>
#include <fstream>


namespace CmnLib
{
namespace control
{

// Class to manage the log file or in the case output files
class Log
{
 public:

  static const int LOG_WRITE  = std::ios::out;
  static const int LOG_APPEND = std::ios::app;

  static const int EXIT_MSG_SIZE = 512;
  static const int MAX_EXIT_CODES = 3;

  // FILE LOG ERRORS
  static enum logErrors
  {
    LOG_NOERROR = 0,		// no errors
    LOG_NOFILENAME = 1,	// no filename set
    LOG_ERROR = 101		// general error
  };
  static enum logLevels 
  {
    LEVEL_0,       // buffer all log messages  
    QUIET_MODE     // do not print out any messages
  };

  /** Constructor
  */
  Log(const std::string filename, bool bAppend = false);

  /** Distruptor
  */
  Log::~Log();

  /** Get the error state
  */
  logErrors GetError()	{ return logError_; }
  /** Create file header
  */
  void Log::CreateFileHeader();
  /** Add string
  */
  void Log::operator+(std::string &msg);
  /** Add string
  */
  void Log::operator+(char *msg);

 private:
  /** Log filename
	  @remarks
		It may contains also the path
  */
  std::string filename_;
  /** Pointer to the current file
  */
  std::ofstream myfile_;
  /** level of output
  */
  enum logLevels logLevel_;	
  /** internal status (file is open or closed)
  */
  enum logStats logStat_;	
  /** memorize the internal errors of the file log
  */
  enum logErrors logError_;

};

const enum Log::logLevels L0 = Log::LEVEL_0;
const enum Log::logLevels LQUIET = Log::QUIET_MODE;

}  // namespace control
}  // namespace CmnLib

#endif /* CMNLIB_CONTROL_FILELOG_HPP__ */