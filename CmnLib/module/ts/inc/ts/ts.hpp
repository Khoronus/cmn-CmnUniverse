/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
gAS ISh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

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

	BaseTestSystem::BaseTestSystem()	{}

	DISALLOW_COPY_AND_ASSIGN(BaseTestSystem);

	/** Function to test the performance
	*/
	virtual void BaseTestSystem::test(void)	const {}
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