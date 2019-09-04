/* @file sample_imgproc_codify_data.cpp
 * @brief Test the data codification over an image.
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
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */


#include "cmnipcontainer/inc/cmnipcontainer/cmnipcontainer_headers.hpp"

namespace
{

void test()
{
	CmnIP::cmnipcontainer::IndexTiming h2;
	h2.clear();
	h2.add(3, 10);
	h2.display();
	h2.add(5, 15);
	h2.display();
	h2.add(10, 16);
	h2.display();
	h2.add(17, 20);
	h2.display();
	h2.add(3, 21);
	h2.display();
}

}  // namespace anonymous


/** Main function
*/
void main()
{
	std::cout << "Class to manage timer index. It requires check and debug" << 
		std::endl;
	test();
}