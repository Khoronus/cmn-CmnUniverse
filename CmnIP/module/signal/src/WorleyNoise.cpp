#include "signal/inc/signal/signal_headers.hpp"

namespace CmnIP
{
namespace signal
{

float WorleyNoise::CombinerFunction1(float ar[]){
	return ar[0];
}

float WorleyNoise::CombinerFunction2(float ar[]){
	return ar[1] - ar[0];
}

float WorleyNoise::CombinerFunction3(float ar[]){
	return ar[2] - ar[0];
}

float WorleyNoise::EuclidianDistanceFunc(cv::Point3f p1, cv::Point3f p2){
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)
		+ (p1.z - p2.z) * (p1.z - p2.z);
}

float WorleyNoise::ManhattanDistanceFunc(cv::Point3f p1, cv::Point3f p2){
	return abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z);
}
float ChebyshevDistanceFunc(cv::Point3f p1, cv::Point3f p2){
	cv::Point3f diff = cv::Point3f();
	diff.x = p1.x - p2.x;
	diff.y = p1.y - p2.y;
	diff.z = p1.z - p2.z;

	return std::max(std::max(abs(diff.x), abs(diff.y)), abs(diff.z));
}

long WorleyNoise::probLookup(long value){
	value = value & 0xffffffff;
	if (value < 393325350) return 1 & 0xffffffff;
	if (value < 1022645910) return 2 & 0xffffffff;
	if (value < 1861739990) return 3 & 0xffffffff;
	if (value < 2700834071) return 4 & 0xffffffff;
	if (value < 3372109335) return 5 & 0xffffffff;
	if (value < 3819626178) return 6 & 0xffffffff;
	if (value < 4075350088) return 7 & 0xffffffff;
	if (value < 4203212043) return 8 & 0xffffffff;
	return 9 & 0xffffffff;
}

void WorleyNoise::insert(float ar[], float value){
	float temp;

	int arraySize = sizeof(ar);

	for (int i = arraySize - 1; i >= 0; i--)
	{
		if (value > ar[i]) break;
		temp = ar[i];
		ar[i] = value;
		if (i + 1 < arraySize) ar[i + 1] = temp;
	}
}

long WorleyNoise::lcgRandom(long lastValue){
	return (((1103515245 & 0xffffffff) * lastValue + (12345 & 0xffffffff)) % 0x100000000) & 0xffffffff;
}

long WorleyNoise::hash(long i, long j, long k){
	return ((((((WorleyNoise::OFFSET_BASIS ^ (i & 0xffffffff)) * WorleyNoise::FNV_PRIME) ^ (j & 0xffffffff)) * WorleyNoise::FNV_PRIME)
		^ (k & 0xffffffff)) * WorleyNoise::FNV_PRIME) & 0xffffffff;

}

float WorleyNoise::noise(cv::Point3f input){
	float value = 0;

	long lastRandom;
	long numberFeaturePoints;
	cv::Point3f randomDiff = cv::Point3f();
	randomDiff.x = 0;
	randomDiff.y = 0;
	randomDiff.z = 0;
	cv::Point3f featurePoint = cv::Point3f();
	featurePoint.x = 0;
	featurePoint.y = 0;
	featurePoint.z = 0;
	int cubeX, cubeY, cubeZ;

	int distanceArraySize = sizeof(WorleyNoise::DistanceArray);

	for (int i = 0; i < distanceArraySize; i++)
	{
		WorleyNoise::DistanceArray[i] = 6666;
	}

	int evalCubeX = (int)(floor(input.x));
	int evalCubeY = (int)(floor(input.y));
	int evalCubeZ = (int)(floor(input.z));

	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
			for (int k = -1; k < 2; ++k)
			{
				cubeX = evalCubeX + i;
				cubeY = evalCubeY + j;
				cubeZ = evalCubeZ + k;

				//2. Generate a reproducible random number generator for the cube
				lastRandom = lcgRandom(hash((cubeX + WorleyNoise::Seed) & 0xffffffff, (cubeY)& 0xffffffff, (cubeZ)& 0xffffffff));
				//3. Determine how many feature points are in the cube
				numberFeaturePoints = probLookup(lastRandom);
				//4. Randomly place the feature points in the cube
				for (int l = 0; l < numberFeaturePoints; ++l)
				{
					lastRandom = lcgRandom(lastRandom);
					randomDiff.x = lastRandom / 0x100000000;

					lastRandom = lcgRandom(lastRandom);
					randomDiff.y = lastRandom / 0x100000000;

					lastRandom = WorleyNoise::lcgRandom(lastRandom);
					randomDiff.y = lastRandom / 0x100000000;

					featurePoint.x = randomDiff.x + cubeX;
					featurePoint.y = randomDiff.y + cubeY;
					featurePoint.z = randomDiff.z + cubeZ;


					//5. Find the feature point closest to the evaluation point. 
					//This is done by inserting the distances to the feature points into a sorted list
					float v = WorleyNoise::EuclidianDistanceFunc(input, featurePoint);
					WorleyNoise::insert(WorleyNoise::DistanceArray, v);
				}
				//6. Check the neighboring cubes to ensure their are no closer evaluation points.
				// This is done by repeating steps 1 through 5 above for each neighboring cube
			}

	float color = WorleyNoise::CombinerFunction1(WorleyNoise::DistanceArray);
	if (color < 0) color = 0;
	if (color > 1) color = 1;

	return color;
}


float WorleyNoise::Get1D(float x) {
	cv::Point3f p1 = cv::Point3f();
	p1.x = x;
	p1.y = 0;
	p1.z = 0;

	return WorleyNoise::noise(p1);
}
float WorleyNoise::Get2D(float x, float y){
	cv::Point3f p1 = cv::Point3f();

	p1.x = x;
	p1.y = y;
	p1.z = 0;

	return WorleyNoise::noise(p1);
}

WorleyNoise::WorleyNoise()
{
	DistanceFunction = 0;
	CombineDistanceFunction = 0;
	Seed = 3221;

	OFFSET_BASIS = 2166136261;
	FNV_PRIME = 16777619;
}


WorleyNoise::~WorleyNoise()
{
}


} // namespace signal
} // namespace CmnIP
