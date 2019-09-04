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


#include "container/inc/container/container_headers.hpp"
//#include "ts.hpp"

namespace
{

/** @brief Function to test the colored text.

	Function to test the colored text.
*/
int test()
{
	CmnLib::container::SplayTree st;
	int vector[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	CmnLib::container::splay *root;
	root = NULL;
	const int length = 10;
	int i;
	for (i = 0; i < length; i++)
		root = st.Insert(vector[i], root);
	std::cout << "\nInOrder: \n";
	st.InOrder(root);
	int input, choice;
	while (1)
	{
		std::cout << "\nSplay Tree Operations\n";
		std::cout << "1. Insert " << std::endl;
		std::cout << "2. Delete" << std::endl;
		std::cout << "3. Search" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter value to be inserted: ";
			std::cin >> input;
			root = st.Insert(input, root);
			std::cout << "\nAfter Insert: " << input << std::endl;
			st.InOrder(root);
			break;
		case 2:
			std::cout << "Enter value to be deleted: ";
			std::cin >> input;
			root = st.Delete(input, root);
			std::cout << "\nAfter Delete: " << input << std::endl;
			st.InOrder(root);
			break;
		case 3:
			std::cout << "Enter value to be searched: ";
			std::cin >> input;
			root = st.Search(input, root);
			std::cout << "\nAfter Search " << input << std::endl;
			st.InOrder(root);
			break;

		case 4:
			exit(1);
		default:
			std::cout << "\nInvalid type! \n";
		}
	}
	std::cout << "\n";
	return 0;
}

}	// namespace

#ifdef CMNLIB

CMNLIB_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	std::cout << "Sample container splay tree naive" << std::endl;
	test();
	return 0;
}

#endif