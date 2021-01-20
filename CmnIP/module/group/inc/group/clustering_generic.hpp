/**
* @file clustering.hpp
* @brief Perform a phase correlation matching.
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
* @oauthor Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNIP_GROUP_CLUSTERINGGENERIC_HPP__
#define CMNIP_GROUP_CLUSTERINGGENERIC_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <list>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "opencv2/core/core.hpp"
//#include "opencv2/core/opengl_interop.hpp"
//#include "opencv2/contrib/contrib.hpp"

namespace CmnIP
{
namespace group
{

	/** @brief Traits for retrieving class name

	Traits for retrieving class name
	@link: http://stackoverflow.com/questions/1055452/c-get-name-of-type-in-template
	http://gestface.googlecode.com/svn-history/r108/trunk/pipeit/include/prj_definitions.h
	*/
	template<typename T>
	class TypeParseTraits{
	public:
		static const std::string name(){
			return typeid(T).name();
		}
	};

#define REGISTER_PARSE_TYPE(X) \
	template<> class TypeParseTraits< X > \
	{ public: static const std::string name(){ return #X; } };


#define kPatchSize cv::Size(32,32)

	template <typename _Ty, typename _kTy = int>
	class AbstractContainer
	{
	public:

		virtual void add(_Ty &item) = 0;

		virtual void add(const _Ty &item) = 0;

		virtual void add(_Ty &item, _kTy &key) = 0;

		virtual void add(const _Ty &item, _kTy &key) = 0;

		virtual void remove(const _Ty &item) = 0;

		virtual bool exist(const _Ty &item) = 0;

		virtual size_t size() const = 0;

		virtual int item(int idx, _Ty &item) = 0;
	};


	template <typename _Ty, typename _kTy = int>
	class DataContainer : public AbstractContainer<_Ty, _kTy>
	{
	public:

		std::list< _Ty > container_;

		void add(_Ty &item) {
			container_.push_back(std::move(item));
		}

		void add(const _Ty &item) {
			container_.push_back(item);
		}

		void add(_Ty &item, _kTy &key) {
			container_.push_back(std::move(item));
		}

		void add(const _Ty &item, _kTy &key) {
			container_.push_back(item);
		}

		void remove(const _Ty &item) {
			container_.remove(item);
		}

		void clear() {
			container_.clear();
		}

		bool exist(const _Ty &item) {
			//std::list<T>::iterator findIter = std::find(container_.begin(), 
			//	container_.end(), 1);
			//return findIter != container_.end() ? true : false;
			for (auto it = container_.begin(); it != container_.end(); it++) {
				if (*it == item) return true;
			}
			return false;
		}

		size_t size() const {
			return container_.size();
		}

		int item(int idx, _Ty &item) {
			if (idx >= 0 && idx < container_.size()) {
				//std::list<_Ty>::iterator it = container_.begin();
				auto it = container_.begin();
				item = *(std::next(it, idx));
				return 1;
			}
			return 0;
		}
	};

	template <typename _Ty, typename _kTy = int>
	class DataContainerMultimap : public AbstractContainer<_Ty, _kTy>
	{
	public:

		std::multimap< _kTy, _Ty> container_;

		void add(_Ty &item) {
		}

		void add(const _Ty &item) {
		}

		void add(_Ty &item, _kTy &key) {
			container_.insert(std::make_pair(key, item));
		}

		void add(const _Ty &item, _kTy &key) {
			container_.insert(std::make_pair(key, item));
		}

		void remove(const _Ty &item) {
		}

		bool exist(const _Ty &item) {
			return false;
		}

		size_t size() const {
			return container_.size();
		}

		int item(int idx, _Ty &item) {
			if (idx >= 0 && idx < container_.size()) {

				auto it = container_.begin();
				for (int i = 0; i <= idx; i++)
				{
					if (i == idx) {
						item = it->second;
						return 1;
					}
					if (it != container_.end())	it++;
				}
			}
			return 0;
		}

		int item_by_key(int key, _Ty &item) {
			auto it = container_.find(key);
			if (it != container_.end())
			{
				item = it->second;
				return 1;
			}
			return 0;
		}


		void keys(std::vector<_kTy> &keys) {
			keys.clear();
			for (auto it = container_.begin(), end = container_.end();
				it != end; it = container_.upper_bound(it->first))
			{
				keys.push_back(it->first);
			}
		}

		void items(_kTy &key,
			std::pair<typename std::multimap< _kTy, _Ty>::iterator,
			typename std::multimap< _kTy, _Ty>::iterator> &ret) {
			ret = container_.equal_range(key);
		}
	};


	/** @brief Contains the reference to a frame
	*/
	class AbstractFrame
	{
	public:

		AbstractFrame() : pImg_(nullptr) {}

		cv::Point3d position() {
			return position_;
		}
		void set_position(const cv::Point3d &position) {
			position_ = position;
		}

		cv::Point3d orientation() {
			return orientation_;
		}
		void set_orientation(const cv::Point3d &orientation) {
			orientation_ = orientation;
		}

		const cv::Mat* pImg() const {
			return pImg_;
		}
		void set_pImg(const cv::Mat* pImg) {
			pImg_ = pImg;
		}

		/** @brief Analyze the frame
		*/
		virtual void analyze() = 0;

	protected:

		const cv::Mat* pImg_;

		cv::Point3d position_;

		cv::Point3d orientation_;
	};

	/** @brief Contains the reference to a frame
	*/
	class ApproximateFrame : public AbstractFrame
	{
	public:

		ApproximateFrame() : AbstractFrame() {}

		void analyze() {
			create_patch();
		}

		const cv::Mat& patch() const {
			return patch_;
		}

	private:

		/** @brief It defines a small patch image to display the original one.
		*/
		cv::Mat patch_;

		/** @brief Create a small patch of the original image if possible.
		*/
		void create_patch() {
			if (pImg_ != nullptr) {
				if (!pImg_->empty()) {
					if (pImg_->channels() == 3) {
#if CV_MAJOR_VERSION == 3
						cv::cvtColor(*pImg_, patch_, CV_BGR2GRAY);
#elif CV_MAJOR_VERSION == 4
						cv::cvtColor(*pImg_, patch_, cv::COLOR_BGR2GRAY);
#endif
						cv::resize(patch_, patch_, kPatchSize);
					}
					else {
						cv::resize(*pImg_, patch_, kPatchSize);
					}
				}
			}
		}
	};

	/** @brief Collect the images that belong to the same area
	*/
	class ClusterImages
	{
	public:

		ClusterImages(size_t univoque_key) : univoque_key_(univoque_key) {}

		std::vector< ApproximateFrame* >& container() {
			return container_;
		}

		std::vector< ApproximateFrame* > container_;

		void add(ApproximateFrame* af) {
			container_.push_back(af);
		}

		int univoque_key() const {
			return univoque_key_;
		}

		void set_univoque_key(int univoque_key) {
			univoque_key_ = univoque_key;
		}

		cv::Point3d position() {
			return position_;
		}
		void set_position(const cv::Point3d &position) {
			position_ = position;
		}

		cv::Point3d orientation() {
			return orientation_;
		}
		void set_orientation(const cv::Point3d &orientation) {
			orientation_ = orientation;
		}

		cv::Point3d size() {
			return size_;
		}
		void set_size(const cv::Point3d &size) {
			size_ = size;
		}

		void estimate_position() {
			position_ = cv::Point3d(0, 0, 0);
			for (auto it = container_.begin(); it != container_.end(); it++)
			{
				position_ += (*it)->position();
			}
			size_t s = container_.size();
			if (s > 0) {
				position_.x /= s; position_.y /= s; position_.z /= s;
			}
		}

		void estimate_size() {
			size_t s = container_.size();
			size_ = cv::Point3d(0, 0, 0);
			if (s > 0) {
				cv::Point3d pmin = container_[0]->position();
				cv::Point3d pmax = container_[0]->position();
				for (size_t i = 0; i < s; i++)
				{
					pmin.x = (std::min)(pmin.x, container_[i]->position().x);
					pmin.y = (std::min)(pmin.y, container_[i]->position().y);
					pmin.z = (std::min)(pmin.z, container_[i]->position().z);
					pmax.x = (std::max)(pmax.x, container_[i]->position().x);
					pmax.y = (std::max)(pmax.y, container_[i]->position().y);
					pmax.z = (std::max)(pmax.z, container_[i]->position().z);
				}
				size_.x = pmax.x - pmin.x;
				size_.y = pmax.y - pmin.y;
				size_.z = pmax.z - pmin.z;
			}
		}

		cv::Rect bounding_box_2d() {
			return cv::Rect(cv::Point(position_.x - size_.x / 2,
				position_.y - size_.y / 2),
				cv::Point(position_.x + size_.x / 2,
				position_.y + size_.y / 2));
		}

	private:

		size_t univoque_key_;

		cv::Point3d position_;
		cv::Point3d orientation_;
		cv::Point3d size_;

	};


	/** @brief It defines a clustering method
	*/
	enum ClusteringMode
	{
		kClusterizeMode_kmean = 0
	};

	/** @brief
	*/
	template<typename T>
	class AbstractCluster
	{
	public:

		AbstractCluster() {}

		virtual int clusterize(ClusteringMode mode,
			std::map<std::string, double> &params) = 0;

		DataContainer<T>* container() {
			return container_;
		}

		void set_container(const DataContainer<T> *container) {
			container_ = container;
		}
	protected:

		const DataContainer<T> *container_;
	};


	// Register the entities
	REGISTER_PARSE_TYPE(DataContainerMultimap<ApproximateFrame*>);


	/** @brief Perform the clustering of the data.
	*/
	class GenericCluster : public AbstractCluster<ApproximateFrame*>
	{
	public:

		GenericCluster() {}

		int clusterize(ClusteringMode mode,
			std::map<std::string, double> &params) {
			if (mode == kClusterizeMode_kmean) {
				int clusterCount = 1, attempts = 1;
				if (params.find("#clusters") != params.end()) {
					clusterCount = (int)params["#clusters"];
					attempts = (int)params["attempts"];
				}
				return apply(clusterCount, attempts);
			}
			return 0;
		}

		void structurize(DataContainerMultimap<ApproximateFrame*> &dcm) {
			size_t s = container_->size();
			for (size_t i = 0; i < s; i++)
			{
				int cluster_idx = labels_.at<int>(i, 0);
				ApproximateFrame *af = nullptr;
				if (const_cast< DataContainer<ApproximateFrame*>* >(container_)->item(i, af)) {
					dcm.add(af, cluster_idx);
				}
			}
		}

	protected:

		cv::Mat labels_;
		cv::Mat centers_;

		int apply(int clusterCount, int attempts)
		{
			size_t s = container_->size();
			cv::Mat samples(s, 3, CV_32F);
			int idx = 0;
			for (auto it = container_->container_.begin();
				it != container_->container_.end(); it++)
			{
				samples.at<float>(idx, 0) = (*it)->position().x;
				samples.at<float>(idx, 1) = (*it)->position().y;
				samples.at<float>(idx, 2) = (*it)->position().z;
				++idx;
			}
#if CV_MAJOR_VERSION == 3
			cv::kmeans(samples, clusterCount, labels_,
				cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000,
					0.0001), attempts, cv::KMEANS_PP_CENTERS, centers_);
#elif CV_MAJOR_VERSION == 4
			cv::kmeans(samples, clusterCount, labels_,
				cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 10000,
					0.0001), attempts, cv::KMEANS_PP_CENTERS, centers_);
#endif

			for (size_t i = 0; i < s; i++)
			{
				int cluster_idx = labels_.at<int>(i, 0);
				float x = centers_.at<float>(cluster_idx, 0);
				float y = centers_.at<float>(cluster_idx, 1);
				float z = centers_.at<float>(cluster_idx, 2);
				std::cout << "xyz(" << cluster_idx << "): " << x << " " << y << " " << z << std::endl;
			}
			return 1;
		}

	};

	/** @brief It contains all the clusters
	*/
	class ClusterCollectors
	{
	public:

		ClusterCollectors() {}

		DataContainerMultimap<ClusterImages*> container_;

		void structurize(DataContainerMultimap<ApproximateFrame*> &container) {

			std::vector<int> keys;
			container.keys(keys);
			for (auto it = keys.begin(); it != keys.end(); it++)
			{
				std::cout << "keys: " << *it << std::endl;
				std::pair <std::multimap<int, ApproximateFrame*>::iterator,
					std::multimap<int, ApproximateFrame*>::iterator> ret;
				container.items(*it, ret);

				ClusterImages *ci = new ClusterImages(*it);
				for (auto it2 = ret.first; it2 != ret.second; it2++)
				{
					ci->add(it2->second);
				}
				ci->estimate_position();
				ci->estimate_size();
				container_.add(ci, *it);
			}
		}

		int get(int idx, ClusterImages* &item) {
			return container_.item_by_key(idx, item);
		}

		void get(std::vector< int > &keys) {
			container_.keys(keys);
		}
	};


	class PlotImageCluster
	{
	public:

		static void plot(cv::Mat &dst, cv::Point &offset,
			DataContainerMultimap<ApproximateFrame*> &container) {

			size_t s = container.size();
			for (size_t i = 0; i < s; i++)
			{
				ApproximateFrame *af = nullptr;
				if (container.item(i, af))
				{
					std::cout << af->position() << std::endl;
					cv::Mat img;
#if CV_MAJOR_VERSION == 3
					cv::cvtColor(af->patch(), img, CV_GRAY2BGR);
#elif CV_MAJOR_VERSION == 4
					cv::cvtColor(af->patch(), img, cv::COLOR_GRAY2BGR);
#endif
					cv::Rect r(cv::Point(af->position().x - 16, af->position().y - 16) + offset,
						cv::Point(af->position().x + 16, af->position().y + 16) + offset);
					img.copyTo(dst(r));
					//char buf[256];
					//sprintf(buf, "%5.3f", (*it)->likelihood());
					//cv::putText(dst, buf, cv::Point(af->position().x + 16, af->position().y + 16),
					//	0, 0.5, cv::Scalar(0, 0, 255));
				}
			}
		}


		static void plot(cv::Mat &dst, cv::Point &offset,
			ClusterCollectors &cluster_collectors) {

			std::vector< int > indexes;
			cluster_collectors.get(indexes);
			for (auto it = indexes.begin(); it != indexes.end(); it++)
			{
				ClusterImages* item = nullptr;
				cluster_collectors.get(*it, item);
				// Get the images
				std::vector< ApproximateFrame* > images = item->container();
				for (auto it2 = images.begin(); it2 != images.end(); it2++)
				{
					cv::Mat img;
#if CV_MAJOR_VERSION == 3
					cv::cvtColor((*it2)->patch(), img, CV_GRAY2BGR);
#elif CV_MAJOR_VERSION == 4
					cv::cvtColor((*it2)->patch(), img, cv::COLOR_GRAY2BGR);
#endif
					cv::Rect r(cv::Point((*it2)->position().x - 16, (*it2)->position().y - 16) + offset,
						cv::Point((*it2)->position().x + 16, (*it2)->position().y + 16) + offset);
					img.copyTo(dst(r));
					char buf[256];
					sprintf(buf, "%i", item->univoque_key());
					cv::putText(dst, buf, cv::Point(item->position().x, item->position().y) + offset,
						0, 0.5, cv::Scalar(0, 0, 255));

					// Draw a bounding box
					r = item->bounding_box_2d();
					cv::rectangle(dst, cv::Rect(r.tl() + offset, r.br() + offset), cv::Scalar(0, 255));
				}
			}
		}

	};



	template <typename _Ty>
	class GenericDataContainer
	{
	public:

		std::list< std::unique_ptr<_Ty> > container_;

		void add(std::unique_ptr<_Ty> &item) {
			container_.push_back(std::move(item));
		}

		void add(_Ty *item) {
			std::unique_ptr<_Ty> elem(item);
			container_.push_back(std::move(elem));
		}

		size_t size() const {
			return container_.size();
		}

		int item(int idx, _Ty &item) {
			if (idx >= 0 && idx < container_.size()) {
				//std::list<std::unique_ptr<_Ty> >::iterator it = container_.begin();
				auto it = container_.begin();
				item = **(std::next(it, idx));
				return 1;
			}
			return 0;
		}
	};


} // namespace group
} // namespace CmnIP

#endif // CMNIP_GROUP_CLUSTERINGGENERIC_HPP__
