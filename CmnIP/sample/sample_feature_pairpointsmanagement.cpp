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

#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>

#include "string/inc/string/string_headers.hpp"
#include "feature/inc/feature/feature_headers.hpp"
//#include "ts.hpp"

namespace
{
// ############################################################################


/** @brief Function to read a file with the features information.
*/
int openRawFeatureFile(const std::string &filename,
	std::vector< std::vector< std::pair< cv::Point2f, cv::Point2f > > > &v_v_points) {
	std::ifstream myfile(filename.c_str());
	if (!myfile.is_open()) return 0;

	v_v_points.clear();
	while (!myfile.eof())
	{
		char buf[4096];
		myfile.getline(buf, 4096);
		if (std::strlen(buf) <= 3) continue;
		CmnLib::text::stringTokenizer st(buf);

		std::vector<float> v_values;
		while(st.hasNext())
		{
			std::string word = st.next();
			if (std::strlen(word.c_str()) >= 1) {
				v_values.push_back((float)std::atof(word.c_str()));
			}
		}

		std::vector< std::pair< cv::Point2f, cv::Point2f > > v_pairs;
		// Analyze the row
		size_t num_pairs = v_values.size();
		for (int i = 0; i < num_pairs; i+= 4)
		{
			cv::Point2f s(v_values[i], v_values[i+1]);
			cv::Point2f d(v_values[i+2], v_values[i+3]);

			v_pairs.push_back( std::make_pair( s, d ) );
		}

		v_v_points.push_back( v_pairs );
	}

	return 1;
}


/** @brief Visualize the features over a cv::Mat
*/
void visualizeFeatures(
	std::vector< std::vector< std::pair< cv::Point2f, cv::Point2f > > > &v_v_points) {
	
	int s = v_v_points.size();
	for (int i = 0; i < s; i++)
	{
		cv::Mat m(480,640,CV_8UC3,cv::Scalar::all(0));

		// Draw the features
#if _MSC_VER && !__INTEL_COMPILER && (_MSC_VER > 1600)
		for (auto it = v_v_points[i].begin(); it != v_v_points[i].end(); it++)
#else
		for (std::vector< std::pair< cv::Point2f, cv::Point2f > >::const_iterator it = v_v_points[i].begin(); it != v_v_points[i].end(); it++)
#endif
		{
			cv::line(m, it->first, it->second, cv::Scalar(0,255));
		}

		std::vector< double > features;
		CmnIP::feature::PairPointManagement<cv::Point2f, double>::points2features(
			v_v_points[i], features);

		for (std::vector< double >::const_iterator it = features.begin();
			it != features.end(); it++) {
				std::cout << *it << " ";
		}
		std::cout << std::endl;

		cv::imshow("m", m);
		if (cv::waitKey(0) > 0) break;
	}

}

/** @brief Test the raw features reading and sample pair of points analysis.
*/
void test()
{
	std::vector< std::vector< std::pair< cv::Point2f, cv::Point2f > > > v_v_points;
	for (int i = 0; i < 10; i++)
	{
		std::vector< std::pair< cv::Point2f, cv::Point2f > > v;
		for (int j = 0; j < 20; j++)
		{
			cv::Point2f a(std::rand() % 512, std::rand() % 512);
			cv::Point2f b(std::rand() % 512, std::rand() % 512);
			v.push_back(std::make_pair(a, b));
		}
		v_v_points.push_back(v);
	}
	//std::string filename = "..\\..\\data\\features.txt";
	//if (!openRawFeatureFile(filename, v_v_points)) {
	//	std::cout << "Unable to open the file: " << filename << 
	//		std::endl;
	//	return;
	//}
	visualizeFeatures(v_v_points);
}

} // namespace anonymous

#ifdef CmnLib

cmnLIBRARY_TEST_MAIN(&test, "data\\MemoryLeakCPP.txt", "data\\MemoryLeakC.txt");

#else

/** main
*/
int main(int argc, char *argv[])
{
	test();
	return 0;
}

#endif