#include "signal/inc/signal/signal_headers.hpp"

namespace CmnIP
{
namespace signal
{

RandomNoise::RandomNoise()
{
	Size = 256;	
}

RandomNoise::~RandomNoise(){

}

void RandomNoise::Init1DArray(){	
	randomArray1D.resize(Size);
	for (int i = 0; i < Size; i++){
		float val = (float)(rand()) / RAND_MAX;
		randomArray1D[i] = val;
	}
}

void RandomNoise::Init2DArray(){
	randomArray2D.resize(Size);
	for (int i = 0; i < Size; i++){
		
		randomArray2D[i].resize(Size);
		for (int j = 0; j < Size; j++){
			float val = (float)(rand()) / RAND_MAX;
			randomArray2D[i][j] = val;
		}
	}
}

float RandomNoise::Get1D(float x){
	if (randomArray1D.size() == 0){
		Init1DArray();
	}
	int ix = (int)x % (Size - 1);

	return randomArray1D[ix];
}

float RandomNoise::Get2D(float x, float y){
	if (randomArray2D.size() == 0){		
		Init2DArray();
	}

	int ix = (int)x % (Size - 1);
	int iy = (int)y % (Size - 1);

	return randomArray2D[ix][iy];
}

} // namespace signal
} // namespace CmnIP
