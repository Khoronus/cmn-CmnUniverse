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


#include "string/inc/string/StringTokenizer.hpp"

namespace CmnLib
{
namespace text
{
//-----------------------------------------------------------------------------
stringTokenizer::stringTokenizer(std::string myMes, 
	char myCh, bool retDel) 
{
	message.clear();
	message = myMes;
	ch = myCh;
	delRet = retDel;
}
//-----------------------------------------------------------------------------
stringTokenizer::stringTokenizer(std::string myMes, 
	char myCh) 
{
	message.clear();
	message = myMes;
	ch = myCh;
	delRet = false;
}

//-----------------------------------------------------------------------------
stringTokenizer::stringTokenizer(std::string myMes) 
{
	message.clear();
	message = myMes;
	ch = ' ';
	delRet = false;
}
//-----------------------------------------------------------------------------
void stringTokenizer::setMessage(std::string newMessage) 
{
	message.clear();
	message = newMessage;
}
//-----------------------------------------------------------------------------
std::string stringTokenizer::next()
{
	std::string word;
	if (!delRet) 
	{
		processBlanks();
		int pos = (int)message.find(ch);
		if (pos != (int)std::string::npos) 
		{
			word = message.substr(0, pos);
			message = message.substr(pos);
		}
		else 
		{
			word = message;
			message = "";
		}
	}
	else
	{
		if (message[0] == ch) 
		{
			word = message.substr(0, 1);
			message = message.substr(1);
		}
		else
		{
			int pos = (int)message.find(ch);
			if (pos != (int)std::string::npos) 
			{
				word = message.substr(0, pos);
				message = message.substr(pos);
			}
			else 
			{
				word = message;
				message = "";
			}
		}
	}
	return word;
}
//-----------------------------------------------------------------------------
bool stringTokenizer::hasNext() const
{
	//cout << "lenght: " << message.length() << endl;
	return message.length() > 0;
}
//-----------------------------------------------------------------------------
void stringTokenizer::processBlanks() 
{
	while (message.length() > 0 && message[0] == ch)
		message = message.substr(1);
	return;
}
//-----------------------------------------------------------------------------
void stringTokenizer::to_vector(std::vector<std::string> &v)
{
	while (hasNext()) v.push_back(next());
}


} // namespace text
} // namespace CmnLib
