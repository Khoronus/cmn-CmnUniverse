/**
* @file test_reportmessage.cpp
* @brief Example to report message.
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
#include <algorithm>
#include <memory>

#include "ts/inc/ts/ts.hpp"
#include "cmnlibcore/inc/cmnlibcore/cmnlibcore_headers.hpp"
#include "string/inc/string/string_headers.hpp"

class ReportMessageGeneric : public CmnLib::core::Singleton<ReportMessageGeneric>
{
public:

	static ReportMessageGeneric& getSingleton(void);
	static ReportMessageGeneric* getSingletonPtr(void);

	virtual void report(const std::string &msg) = 0;

};
//-----------------------------------------------------------------------------
template<> ReportMessageGeneric* CmnLib::core::Singleton<ReportMessageGeneric>::ms_Singleton = 0;
ReportMessageGeneric* ReportMessageGeneric::getSingletonPtr(void)
{
	return ms_Singleton;
}
//-----------------------------------------------------------------------------
ReportMessageGeneric& ReportMessageGeneric::getSingleton(void)
{
	return *ms_Singleton;
}

class ReportMessageConsole : public ReportMessageGeneric
{
public:

	void report(const std::string &msg)
	{
		std::cout << "rmc: " << msg << std::endl;
	}
};

class ReportMessageLog : public ReportMessageGeneric
{
public:

	void report(const std::string &msg)
	{
		std::cout << "rml: " << msg << std::endl;
	}
};

// Unnamed namespace
namespace
{

/** Overload virtual method
*/
void test()	{
	std::unique_ptr<ReportMessageGeneric> rmg = std::unique_ptr<ReportMessageGeneric>(new ReportMessageConsole());

	rmg->getSingletonPtr()->report("ciao");
}

}  // namespace anonymous

CMNLIB_TEST_MAIN(&test, "MemoryLeakCPP.txt", "MemoryLeakC.txt");
