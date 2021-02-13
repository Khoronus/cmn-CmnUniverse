/**
* @file sample_filesio.cpp
* @brief Sample files IO.
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
* @version 0.1.0.0
*
*/

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "filesio/inc/files/filesio_headers.hpp"

// ############################################################################

/** @brief Test VertexIO
*/
void test_vertexIO() {

	std::vector<std::pair<cv::Point2f, cv::Point3f> > v_xyxyz =
	{ {cv::Point2f(0, 1), cv::Point3f(0, 1, 2)} };
	std::string fname = "test_vertexIO.txt", header;
	// write
	CmnIO::filesio::VertexIONaive::write(fname, "test",
		v_xyxyz);
	// read
	CmnIO::filesio::VertexIONaive::read(fname, header,
		v_xyxyz);

	for (auto& it : v_xyxyz) {
		std::cout << it.first << " " << it.second << std::endl;
	}
}

// ############################################################################

int main(int argc, char* argv[])
{
	test_vertexIO();
	
	return 0;
}


