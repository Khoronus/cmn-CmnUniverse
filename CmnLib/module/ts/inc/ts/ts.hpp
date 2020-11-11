/**
* @file ts.hpp
* @brief Header to test classes.
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

#ifndef CMNLIB_TS_TS_HPP__
#define CMNLIB_TS_TS_HPP__

#if _DEBUG
#define CMNLIB
#define CL_MEMORY_MANAGER
#endif

#include "cmnlibcore/inc/cmnlibcore/memory.hpp"

namespace CmnLib
{
namespace ts
{

/** Base class to perform the test
*/
class BaseTestSystem
{
public:

	BaseTestSystem()	{}

	DISALLOW_COPY_AND_ASSIGN(BaseTestSystem);

	/** Function to test the performance
	*/
	virtual void test(void)	const {}
};

/** Class used to test if the program has memory leak
*/
class TestSystem
{
public:

	TestSystem()	{}

	DISALLOW_COPY_AND_ASSIGN(TestSystem);

	~TestSystem()	{
#ifdef CL_MEMORY_MANAGER
		//Memory::getSingletonPtr()->GenerateReport(memory_filename_.c_str());
		//MemoryLeakTrackerC::getSingletonPtr()->report_mem_leak(memoryc_filename_);
		Memory::getSingletonPtr()->GenerateReport(memory_filename_);
		MemoryLeakTrackerC::getSingletonPtr()->report_mem_leak(memoryc_filename_);
#endif
	}

	/** Set where to save the result of C memory leak detector
	*/
	void set_memoryc_filename(const std::string &filename)	{
		//memoryc_filename_ = filename;
		sprintf(memoryc_filename_, "%s", filename.c_str());
	}

	/** Set where to save the result of C++ memory leak detector
	*/
	void set_memory_filename(const std::string &filename)	{
		//memory_filename_ = filename;
		sprintf(memory_filename_, "%s", filename.c_str());
	}

	/** Run the testing system
	*/
	void test( const BaseTestSystem &base_test_system)	{
		base_test_system.test();
	}

	/** Run the testing system
	*/
	void test( void (*func)(void) )	{
		func();
	}


private:

#ifdef CL_MEMORY_MANAGER
	/** @brief Memorize the leak caused by C++ code
	*/
	static Memory memory_;

	/** *brief Memorize the leak caused by C code
	*/
	static MemoryLeakTrackerC memoryc_;
#endif

	/** @brief Filename for the C++ memory leak  tracker
	*/
	//std::string memory_filename_;
	char memory_filename_[512];

	/** @brief Filename for the C memory leak tracker
	*/
	//std::string memoryc_filename_;
	char memoryc_filename_[512];

};

// Declare static vars
#ifdef CL_MEMORY_MANAGER
Memory TestSystem::memory_;
MemoryLeakTrackerC TestSystem::memoryc_;
#endif

}	// namespace ts
}	// namespace CmnLib

#endif
