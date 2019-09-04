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

#ifndef CMNLIB_STRING_STRINGTOKENIZER_HPP__
#define CMNLIB_STRING_STRINGTOKENIZER_HPP__

#include <string>
#include <iostream>
#include <vector>

namespace CmnLib
{
namespace text
{

/** String tokenizer
*/
class stringTokenizer 
{
 public:

  /** Construptor
  */
  stringTokenizer(std::string myMes, char myCh, bool retDel);
  /** Construptor
  */
  stringTokenizer(std::string myMes, char myCh);
  /** Construptor
  */
  stringTokenizer(std::string myMes);
  /** Set the message to split
  */
  void setMessage(std::string newMessage);
  /** Get the next word
  */
  std::string next();
  /** String contains a next word
  */
  bool hasNext() const;

  /** @brief It fill a container with words
  */
  void to_vector(std::vector<std::string> &v);
 private:
  /** Process the blank intervals
  */
  void processBlanks();
  
  /** @brief Message to split 
  */
  std::string message;
  /** @brief Blank char
  */
  char ch;
  /** @brief Return value once finished
  */
  bool delRet;
};

}  // namespace text
}  // namespace CmnLib

#endif