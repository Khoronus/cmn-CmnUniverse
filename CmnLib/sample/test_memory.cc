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

#include <vector>
#include <map>

#include "ts/inc/ts/ts.hpp"
#include "cmnlibcore/inc/cmnlibcore/cmnlibcore_headers.hpp"

// Unnamed namespace
namespace
{

/** Derivate class to test the memory allocation performance
*/
class MemoryPerformance : public CmnLib::ts::BaseTestSystem
{
public:

	MemoryPerformance()	{}

	/** Overload virtual method
	*/
	void test()	const	{
		int *data = NULLPTR;
		CmnLib::memory::MemoryManager<int>::AllocateVector(data, 10, __FILE__, __LINE__);
		CmnLib::memory::MemoryManager<int>::DeallocateVector(data);

		int *p1 = static_cast<int*>(malloc(10));  
		int *p2 = static_cast<int*>(calloc(10, sizeof(int)));
		char *p3 = static_cast<char*>(calloc(15, sizeof(char)));
		float *p4 = static_cast<float*>(malloc(16));
		free(p2);
	}
};

/** Overload virtual method
*/
void test()	{
	int *data = NULLPTR;
	CmnLib::memory::MemoryManager<int>::AllocateVector(data, 10, __FILE__, __LINE__);
	//CmnLib::memory::MemoryManager<int>::DeallocateVector(data);

	int *p1 = static_cast<int*>(malloc(10));  
	int *p2 = static_cast<int*>(calloc(10, sizeof(int)));
	char *p3 = static_cast<char*>(calloc(15, sizeof(char)));
	float *p4 = static_cast<float*>(malloc(16));
	free(p2);

	int *data2 = new int[123];

	std::vector<std::string> words = {"hello"};

	std::map<std::string, std::string> words_v2 = { {"key0", "value0"}, {"key1", "value1"} };
}

}  // namespace anonymous

///** Test a simple main
//*/
//void main()
//{
//	{
//		MemoryPerformance memory_performance;
//		CmnLib::ts::TestSystem test_system;
//		std::string cpp_filename = "MemoryLeakCPP.txt";
//		std::string c_filename = "MemoryLeakC.txt";
//		test_system.set_memoryc_filename(c_filename);
//		test_system.set_memory_filename(cpp_filename);
//		//test_system.test(memory_performance);
//		test_system.test(&test);
//	}
//}

CMNLIB_TEST_MAIN(&test, "MemoryLeakCPP.txt", "MemoryLeakC.txt");
