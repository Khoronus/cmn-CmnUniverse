/**
* @file test_filelog.cpp
* @brief Example of logging class.
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

#include "ts/inc/ts/ts.hpp"
#include "cmnlibcore/inc/cmnlibcore/cmnlibcore_headers.hpp"
#include "control/inc/control/control_headers.hpp"

// Unnamed namespace
namespace
{

/** Overload virtual method
*/
void test()	{
	std::cout << "Example FileLog" << std::endl;
	CmnLib::control::Log log(std::string("SampleLog.txt"), 
		true);

	log.CreateFileHeader();
	std::string msg("This is a test");
	log + msg;

	// It does not save and display messages from lower level than set one.
	std::cout << "Create LogMS: " << 
		CmnLib::control::LogMS::ResetLogFile("SampleLogMS.txt") << std::endl;
	CmnLib::control::LogMS::ResetLogLevel(CmnLib::control::LogLevel::Debug);
	CmnLib::control::LogMS::Debug("hello, come va?\n");
	CmnLib::control::LogMS::Info("hello, come va?\n");
	CmnLib::control::LogMS::Error("hello, come va?\n");
	CmnLib::control::LogMS::Fatal("hello, come va?\n");
}

}  // namespace anonymous

CMNLIB_TEST_MAIN(&test, "MemoryLeakCPP.txt", "MemoryLeakC.txt");
