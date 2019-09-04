/* @file packunpack_images.hpp
 * @brief Class to pack or unpack a set of images.
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

#ifndef CMNIP_CODIFY_PACKUNPACKIMAGES_HPP__
#define CMNIP_CODIFY_PACKUNPACKIMAGES_HPP__


#include <vector>
#include <string>
#include <fstream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


namespace CmnIP
{
namespace codify
{


/** @brief Class to pack or unpack a collection of images.
*/
class PackUnpackImages
{
public:

	/** @brief Function to pack a set of images in a file.
	*/
	static int pack(const std::string &filename, 
		std::vector<cv::Mat> &container, int maxsize,
		bool append)
	{
		//std::ofstream myfile(filename, std::ios::binary);
		std::ofstream myfile;
		if (append) {
			myfile.open(filename.c_str(), std::ios::binary | std::ios::app);
		} else {
			myfile.open(filename.c_str(), std::ios::binary);
		}
		if (!myfile.is_open()) return 0;
		// Get the amount of data to memorize
		int size = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = container.begin(); it != container.end(); it++)
#else
		for (std::vector<cv::Mat>::const_iterator it = container.begin(); it != container.end(); it++)
#endif
		{
			size += it->cols * it->rows * it->channels();
			size += sizeof(int) * 3;
		}
		int fsize = filesize(filename.c_str());
		if (size + fsize > maxsize) return 0;
		// Create a memory block enough large to save the data
		char *memblock = new char[size];
		int pos = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = container.begin(); it != container.end(); it++)
#else
		for (std::vector<cv::Mat>::const_iterator it = container.begin(); it != container.end(); it++)
#endif
		{
			memcpy(&memblock[pos], &it->cols, sizeof(int)); pos += sizeof(int);
			memcpy(&memblock[pos], &it->rows, sizeof(int)); pos += sizeof(int);
			int channels = it->channels();
			memcpy(&memblock[pos], &channels, sizeof(int)); pos += sizeof(int);
			int s = sizeof(uchar) * it->cols * it->rows * 
				it->channels();
			memcpy(&memblock[pos], it->data, s);
			pos += s;
		}
		// Write the file
		myfile.write(memblock, size);
		myfile.close();
		myfile.clear();
		delete memblock;
		return 1;
	}


	/** @brief Function to pack a set of images in a file.
	*/
	static int pack(const std::string &filename,
		char *data, int sizedata, int sizemax,
		bool append)
	{
		//std::ofstream myfile(filename, std::ios::binary);
		std::ofstream myfile;
		if (append) {
			myfile.open(filename.c_str(), std::ios::binary | std::ios::app);
		}
		else {
			myfile.open(filename.c_str(), std::ios::binary);
		}
		if (!myfile.is_open()) return 0;
		// Get the amount of data to memorize
		int fsize = filesize(filename.c_str());
		if (fsize > sizemax) return 0;
		// Write the file
		myfile.write(data, sizedata);
		myfile.close();
		myfile.clear();
		return 1;
	}


	/** @brief Function to pack a set of images in a file.
	*/
	static int pack(const std::string &filename,
		std::vector<char> &data, int sizemax,
		bool append)
	{
		if (data.size() <= 0) return 0;

		//std::ofstream myfile(filename, std::ios::binary);
		std::ofstream myfile;
		if (append) {
			myfile.open(filename.c_str(), std::ios::binary | std::ios::app);
		}
		else {
			myfile.open(filename.c_str(), std::ios::binary);
		}
		if (!myfile.is_open()) return 0;
		// Get the amount of data to memorize
		int fsize = filesize(filename.c_str());
		if (fsize > sizemax) return 0;
		// Write the file
		myfile.write(&data[0], data.size());
		myfile.close();
		myfile.clear();
		return 1;
	}


	/** @brief Read from a binary file the memorized images.
	*/
	static int unpack(const std::string &filename, 
		std::vector<cv::Mat> &container)
	{
		container.clear();
		std::streampos size;
		char * memblock;

		std::ifstream file (filename.c_str(), 
			std::ios::in|std::ios::binary|std::ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			memblock = new char [size];
			file.seekg (0, std::ios::beg);
			file.read (memblock, size);
			file.close();
			//std::cout << "the entire file content is in memory";

			memblock2images(memblock, size, container);
			delete[] memblock;
		} else {
			//std::cout << "Unable to open file";
			return 0;
		}
		return 1;
	}


	/** @brief Read from a binary file the data.
	*/
	static int unpack(const std::string &filename,
		char* &data, int &size)
	{
		std::ifstream file (filename.c_str(), 
			std::ios::in|std::ios::binary|std::ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			data = new char [size];
			file.seekg (0, std::ios::beg);
			file.read (data, size);
			file.close();
			return 1;
		}
		return 0;
	}

private:

	/** @brief Function to get the file size.
	*/
	static std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	/** @brief This function convert a memory block in a collection of images.

		This function convert a memory block in a collection of images.
		The block of memory is expected to be allocated as follow:
		cols(4),rows(4),channels(4),data(n),cols(4)...
		where the number is equal to the number of bytes used to memorize the
		data.
		@param[in] data The block data.
		@param[in] size The amount of data passed.
		@param[out] container A vector with the images memorized.
	*/
	static void memblock2images(const char *memblock, int size,
		std::vector<cv::Mat> &container) {
		int pos = 0;
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		if (memblock == nullptr) return;
#else
		if (memblock == 0) return;
#endif
		while (pos < size) {
			int cols = 0, rows = 0, channels = 0;
			// copy the size
			memcpy(&cols, &memblock[pos], sizeof(int)); 
			pos += sizeof(int);
			//std::cout << cols << std::endl;
			memcpy(&rows, &memblock[pos], sizeof(int)); 
			pos += sizeof(int);
			//std::cout << rows << std::endl;
			memcpy(&channels, &memblock[pos], sizeof(int)); 
			pos += sizeof(int);
			int s = cols * rows * channels;
			// copy the memory block
			cv::Mat m;
			if (channels == 1) {
				m = cv::Mat(rows, cols, CV_8U);
			} else if (channels == 3) {
				m = cv::Mat(rows, cols, CV_8UC3);
			}
			if (!m.empty()) {
				memcpy(m.data, &memblock[pos], s);
				container.push_back(m);
			}
			pos += s;
		}
	}
};


} // namespace codify
} // namespace CmnIP

#endif /* CMNIP_CODIFY_PACKUNPACKIMAGES_HPP__ */
