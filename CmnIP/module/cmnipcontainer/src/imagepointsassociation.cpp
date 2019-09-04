/**
 * @file point_association.cpp
 * @brief Class to manage the association of points.
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

#include "cmnipcontainer/inc/cmnipcontainer/imagepointsassociation.hpp"

namespace CmnIP
{
namespace cmnipcontainer
{

//-----------------------------------------------------------------------------
bool ImagePointsAssociation::save(const std::string &path, 
	const std::string &filename_)	{
	std::string path_ = "";
	if (path.size() > 0) {
		if (path[path.size() - 1] == '\\' || path[path.size() - 1] == '/') {
			path_ = path;
		} else {
#if WIN32
			path_ = path + '\\';
#else
			path_ = path + '/';
#endif
		}
	}
	// Save the points
	std::string filename = path_ + filename_;
	if (path_.length() < 3) filename = filename_;
	if (ipmpc_.save(filename)) return true;

	return false;
}
//-----------------------------------------------------------------------------
bool ImagePointsAssociation::load(const std::string &path,
	const std::string &filename_)	{
	std::string path_ = "";
	if (path.size() > 0) {
		if (path[path.size() - 1] == '\\' || path[path.size() - 1] == '/') {
			path_ = path;
		} else {
#if WIN32
			path_ = path + '\\';
#else
			path_ = path + '/';
#endif
		}
	}
	// Load the points
	std::string filename = path_ + filename_;
	if (path_.length() < 3) filename = filename_;
	if (ipmpc_.load(filename, 1.0f, 1.0f)) return true;

	return false;
}
//-----------------------------------------------------------------------------
bool ImagePointsAssociation::load(const std::string &path,
	const std::string &filename_, const std::string &version)	{
	std::string path_ = "";
	if (path.size() > 0) {
		if (path[path.size() - 1] == '\\' || path[path.size() - 1] == '/') {
			path_ = path;
		} else {
#if WIN32
			path_ = path + '\\';
#else
			path_ = path + '/';
#endif
		}
	}
	// Load the points
	std::string filename = path_ + filename_;
	if (path_.length() < 3) filename = filename_;
	if (version == std::string("version_0"))
	{
		if (ipmpc_.load(filename, 1.0f, 1.0f)) return true;
	} else if (version == std::string("version_1")) {
		if (ipmpc_.load_ver1(filename, 1.0f, 1.0f)) return true;
	}

	return false;
}

}	// namespace cmnipcontainer
}	// namespace CmnIP