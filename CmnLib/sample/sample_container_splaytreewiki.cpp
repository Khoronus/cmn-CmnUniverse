/**
 * @file sample_console_text.cpp
 * @brief Exmpla to show how is display the colored text.
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
 * @author  Ritecs Inc. - Alessandro Moro <alessandromoro.italy@ritecs.co.jp>
 * @bug No known bugs.
 * @version 1.1.0.0
 * 
 */

#include <iostream>
#include "container/inc/container/container_headers.hpp"
//#include "ts.hpp"

namespace
{

/** @brief Function to test the colored text.

	Function to test the colored text.
*/
void test()
{
	CmnLib::container::splay_tree<int> splay;
	splay.insert(5);
	std::cout << splay.find(5)->key << std::endl;
}

}	// namespace

#ifdef CMNLIB

CMNLIB_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Sample container splay tree wiki" << std::endl;
	test();
	return 0;
}

#endif