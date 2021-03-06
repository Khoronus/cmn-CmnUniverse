/**
* @file test_container.cpp
* @brief Test how the container module works.
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
#include "container/inc/container/container_headers.hpp"

// Unnamed namespace
namespace
{

/** @brief Test the ContainerNearestKey
*/
void test_ContainerNearestKey() {
  std::map<double, double> m_data;
  m_data[400] = 1;
  m_data[800] = 2;
  m_data[1200] = 3;
  m_data[1500] = 4;
  double key = 300, tolerance = 100, value = 0;
  bool res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  m_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " << 
	  res << " value: " << value << std::endl;
  key = 300, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  m_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " << 
	  res << " value: " << value << std::endl;
  key = 700, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  m_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 1100, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  m_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 1300, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  m_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;


  std::vector < std::pair<double, double> > v_data;
  v_data.push_back(std::make_pair(400, 1));
  v_data.push_back(std::make_pair(800, 2));
  v_data.push_back(std::make_pair(1200, 3));
  v_data.push_back(std::make_pair(1500, 4));

  key = 300, tolerance = 100, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  v_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 300, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  v_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 700, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  v_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 1100, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  v_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
  key = 1300, tolerance = 1000, value = 0;
  res = CmnLib::container::ContainerNearestKey<double, double>::get_value(
	  v_data, key, tolerance, value);
  std::cout << "key: " << key << " tolerance: " << tolerance << " result: " <<
	  res << " value: " << value << std::endl;
}

/** @brief Test the ContainerCoreOperations
*/
void test_ContainerCoreOperations() {

    std::vector<float> features, v1, v2;
	std::vector< std::pair<float, float> > features_mM;

	// Set the features min and max
	for (int k = 0; k < 3; k++)
	{
		features.clear();
		for (int i = 0; i < 5; i++)
		{
			features.push_back( ((float)std::rand() / RAND_MAX) * 200);
		}
		CmnLib::container::ContainerCoreOperations<float>::container_minmax(features, 
			features_mM);
	}
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = features_mM.begin(); it != features_mM.end(); it++) {
#else
	for (std::vector< std::pair<float, float> >::const_iterator it = features_mM.begin(); it != features_mM.end(); it++) {
#endif
		std::cout << it->first << " " << it->second << std::endl;
	}

	// Split
	CmnLib::container::ContainerCoreOperations<float>::split(features_mM, 
		v1, v2);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v1.begin(); it != v1.end(); it++) {
#else
	for (std::vector<float>::const_iterator it = v1.begin(); it != v1.end(); it++) {
#endif
		std::cout << "v1: " << *it << std::endl;
	}
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = v2.begin(); it != v2.end(); it++) {
#else
	for (std::vector<float>::const_iterator it = v1.begin(); it != v1.end(); it++) {
#endif
		std::cout << "v2: " << *it << std::endl;
	}

	// Merge
	features_mM.clear();
	CmnLib::container::ContainerCoreOperations<float>::merge(v1, v2,
		features_mM);
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
	for (auto it = features_mM.begin(); it != features_mM.end(); it++) {
#else
	for (std::vector< std::pair<float, float> >::const_iterator it = features_mM.begin(); it != features_mM.end(); it++) {
#endif
		std::cout << it->first << " " << it->second << std::endl;
	}
}

/** Overload virtual method
*/
void test()	{
  std::cout << "Container" << std::endl;
  test_ContainerNearestKey();
  test_ContainerCoreOperations();
}

}  // namespace anonymous

CMNLIB_TEST_MAIN(&test, "MemoryLeakCPP.txt", "MemoryLeakC.txt");
