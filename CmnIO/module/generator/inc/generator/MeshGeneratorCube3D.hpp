#ifndef CMNIO_GENERATOR_MESHGENERATORCUBE3D_HPP__
#define CMNIO_GENERATOR_MESHGENERATORCUBE3D_HPP__

#include <fstream>
#include <iostream>
#include <string>

#include "cmnlibworld\inc\cmnlibworld\cmnlibworld_headers.hpp"

namespace CmnIO
{
namespace generator
{


/** @brief Class used to generate a simple mesh object CUBE
*/
class MeshGeneratorCube3D
{
public:

	/** @brief It creates a naive file with the cube vertex position.
	*/
	static bool create_naive(const std::string &filename)
	{
		std::ofstream f(filename);
		if (!f.is_open()) return false;

		f << "MeshNaive_v001" << std::endl;
		f << "x0 y0 z0 x1 y1 z1 x2 y2 z2 u0 v0 u1 v1 u2 v2" << std::endl;
		f << "-3 3 -3 -3 -3 -3 3 3 -3 0 0 0 1 1 0" << std::endl;
		f << "3 3 -3 -3 -3 -3 3 -3 -3 1 0 0 1 1 1" << std::endl;
		f << "-3 3 3 -3 -3 3 -3 3 -3 0 0 0 1 1 0" << std::endl;
		f << "-3 3 -3 -3 -3 3 -3 -3 -3 1 0 0 1 1 1" << std::endl;
		f << "-3 -3 3 -3 3 3 3 3 3 0 1 0 0 1 0" << std::endl;
		f << "-3 -3 3 3 3 3 3 -3 3 0 1 1 0 1 1" << std::endl;
		f << "3 -3 3 3 3 3 3 3 -3 0 1 0 0 1 0" << std::endl;
		f << "3 -3 3 3 3 -3 3 -3 -3 0 1 1 0 1 1" << std::endl;
		f << "-3 3 3 -3 3 -3 3 3 -3 0 1 0 0 1 0" << std::endl;
		f << "-3 3 3 3 3 -3 3 3 3 0 1 1 0 1 1" << std::endl;
		f << "-3 -3 -3 -3 -3 3 3 -3 -3 0 0 0 1 1 0" << std::endl;
		f << "3 -3 -3 -3 -3 3 3 -3 3 1 0 0 1 1 1" << std::endl;

		f.close();
		f.clear();
		return true;
	}

	///** @brief It creates a naive file with the cube vertex position.
	//*/
	//static bool create_naive(const std::string &filename,
	//	float size)
	//{
	//	std::ofstream f(filename);
	//	if (!f.is_open()) return false;

	//	f << -size << " " << size << " " << -size << " " <<
	//		-size << " " << -size << " " << -size << " " <<
	//		size << " " << size << " " << -size << " 0 0 0 1 1 0" << std::endl;

	//	f << size << " " << size << " " << -size << " " <<
	//		-size << " " << -size << " " << -size << " " <<
	//		size << " " << -size << " " << -size << " 1 0 0 1 1 1" << std::endl;
	//	f << "-3 3 3 -3 -3 3 -3 3 -3 0 0 0 1 1 0" << std::endl;
	//	f << "-3 3 -3 -3 -3 3 -3 -3 -3 1 0 0 1 1 1" << std::endl;
	//	f << "-3 -3 3 -3 3 3 3 3 3 0 1 0 0 1 0" << std::endl;
	//	f << "-3 -3 3 3 3 3 3 -3 3 0 1 1 0 1 1" << std::endl;
	//	f << "3 -3 3 3 3 3 3 3 -3 0 1 0 0 1 0" << std::endl;
	//	f << "3 -3 3 3 3 -3 3 -3 -3 0 1 1 0 1 1" << std::endl;
	//	f << "-3 3 3 -3 3 -3 3 3 -3 0 1 0 0 1 0" << std::endl;
	//	f << "-3 3 3 3 3 -3 3 3 3 0 1 1 0 1 1" << std::endl;
	//	f << "-3 -3 -3 -3 -3 3 3 -3 -3 0 0 0 1 1 0" << std::endl;
	//	f << "3 -3 -3 -3 -3 3 3 -3 3 1 0 0 1 1 1" << std::endl;

	//	f.close();
	//	f.clear();
	//	return true;
	//}

};


} // namespace generator
} // namespace CmnIO


#endif /* MESHGENERATORCUBE3D_HPP__ */