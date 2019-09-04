#ifndef CMNIO_FILESIO_FISHEYELENSCORRECTIONIO_HPP__
#define CMNIO_FILESIO_FISHEYELENSCORRECTIONIO_HPP__

#include <fstream>
#include <iostream>

namespace CmnIO
{
namespace filesio
{


/** @brief Class to Save or Load the information about the
fish eye lens correction.

Class to Save or Load the information about the
fish eye lens correction.
*/
class FishEyeLensCorrectionIO
{
public:

	/** @brief Open the file descriptor with the correction information.

	Open the file descriptor with the correction information.
	@param[in] filename The file with the correction values.
	It contains two header file.
	*/
	static bool save_cam_keys_correction(const std::string &filename,
		std::vector< std::map< int, std::pair<float, float> > >  &corrections)
	{
		std::ofstream f(filename);
		if (!f.is_open()) return false;

		f << "FishEye AzimuthCorrection v001" << std::endl;
		f << "id angle_on_lens correction_value" << std::endl;
		for (auto it : corrections)
		{
			for (auto it2 : it)
			{
				f << it2.first << " " << it2.second.first << " " << it2.second.second << std::endl;
			}
		}
		f.close();
		f.clear();
		return true;
	}


	/** @brief Open the file descriptor with the correction information.

	Open the file descriptor with the correction information.
	@param[in] filename The file with the correction values.
	It contains two header file.
	*/
	static bool load_cam_keys_correction(const std::string &filename,
		std::map<int, std::map<float, float> > &cam_correction)
	{
		std::ifstream f(filename);
		if (!f.is_open()) return false;
		char buf[1024];
		// Skip the first two lines which describes the file
		f.getline(buf, 1024);
		f.getline(buf, 1024);
		//std::map<int, std::map<float, float> > cam_correction;
		while (!f.eof())
		{
			f.getline(buf, 1024);
			int idx = 0;
			float key = 0, value = 0;
			if (strlen(buf) > 3)
			{
				sscanf(buf, "%i %f %f", &idx, &key, &value);
				cam_correction[idx][key] = value;
			}
		}
		f.close();
		f.clear();
		return true;

	}
};

} // namespace filesio
} // namespace CmnIO


#endif /* CMNIO_FILESIO_FISHEYELENSCORRECTIONIO_HPP__ */