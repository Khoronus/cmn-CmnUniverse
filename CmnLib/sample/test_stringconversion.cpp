/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
“AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#include "ts/inc/ts/ts.hpp"
#include "commonlibrarycore/inc/commonlibrarycore/commonlibrarycore_headers.hpp"
#include "string/inc/string/string_headers.hpp"

// Unnamed namespace
namespace
{

/** Overload virtual method
*/
void test()	{
  std::cout << "StringConversion_Test" << std::endl;
  std::string prova = "ciao";
  std::wcout << commonlibrary::text::StringConversion::toUnicode(prova) << 
    std::endl;
}

}  // namespace anonymous

COMMONLIBRARY_TEST_MAIN(&test, "MemoryLeakCPP.txt", "MemoryLeakC.txt");
