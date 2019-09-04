#ifndef CMNIO_FILESIO_CONFIGLINE_HPP__
#define CMNIO_FILESIO_CONFIGLINE_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "cmnlibworld\inc\cmnlibworld\cmnlibworld_headers.hpp"

namespace CmnIO
{
namespace filesio
{

/** @brief Class to save the remap data information
*/
class ConfigLineIO
{
  public:

	  /** @brief It reads a file which is expected to contain
	             configuration information.

		  It reads a file which is expected to contain configuration 
		  information.
		  The file it is expected to be in the format:
		  key value
		  The "key" is one word. "value" can contains multiple words separated 
		  by spaces.
		  
		  @param[in] filename The file to read.
		  @param[out] params The parameters acquired.
		  @return Return true in case of success. False otherwise.
	  */
	  static bool readconfig_naive(const std::string &filename,
		  std::map<std::string, std::string> &params)
	  {
		  std::ifstream f(filename);
		  if (f.is_open())
		  {
			  while (!f.eof())
			  {
				  char buf[1024];
				  f.getline(buf, 1024);
				  CmnLib::text::stringTokenizer st(buf, ' ');
				  std::vector<std::string> words;
				  while (st.hasNext()) words.push_back(st.next());
				  std::string param;
				  if (words.size() > 1)
				  {
					  for (size_t i = 1; i < words.size() - 1; ++i) {
						  param += words[i] + " ";
					  }
					  param += words.back();
					  params[words[0]] = param;
				  }
			  }
			  return true;
		  }
		  return false;
	  }

};

} // namespace filesio
} // namespace CmnIO

#endif /* CMNIO_FILESIO_CONFIGLINE_HPP__ */