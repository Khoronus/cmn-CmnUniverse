#include "signal/inc/signal/signal_headers.hpp"

namespace CmnIP
{
namespace signal
{

ValueNoise::ValueNoise()
{
	Size = 256;
}


ValueNoise::~ValueNoise()
{
}


void ValueNoise::Init1DArray(){
	randomArray1D.resize(Size);
	for (int i = 0; i < Size; i++){
		float val = (float)(rand()) / RAND_MAX;
		randomArray1D[i] = val;
	}
}

void ValueNoise::Init2DArray(){
	randomArray2D.resize(Size);
	for (int i = 0; i < Size; i++){

		randomArray2D[i].resize(Size);
		for (int j = 0; j < Size; j++){
			float val = (float)(rand()) / RAND_MAX;
			randomArray2D[i][j] = val;
		}
	}
}

float ValueNoise::Get1D(float x){
	if (randomArray1D.size() == 0){
		Init1DArray();
	}

	Interpolaters interp = Interpolaters();

	int ix = (int)x % (Size - 1);
	float t = x - ix;
	float val = interp.Linear(randomArray1D[ix], randomArray1D[ix + 1], t);
		
	return val;
}

float ValueNoise::Get2D(float x, float y){
	if (randomArray2D.size() == 0){
		Init2DArray();
	}

	Interpolaters interp = Interpolaters();

	int ix = (int)x % (Size - 1);
	int iy = (int)y % (Size - 1);

	float tx = x - ix;
	float ty = y - iy;

	/// Random values at the corners of the cell
	float rx0 = ix & (Size - 1);
	float rx1 = (ix + 1) & (Size - 1);
	float ry0 = iy & (Size - 1);
	float ry1 = (iy + 1) & (Size - 1);

	float sx = tx * tx * (3 - (2 * tx));
	float sy = ty * ty * (3 - (2 * ty));

	float p00 = randomArray2D[rx0][ry0];
	float p01 = randomArray2D[rx0][ry1];
	float p10 = randomArray2D[rx1][ry0];
	float p11 = randomArray2D[rx1][ry1];

	float pl0 = interp.Linear(p00, p10, sx);
	float pl1 = interp.Linear(p01, p11, sx);

	return interp.Linear(pl0, pl1, sy);
}


} // namespace signal
} // namespace CmnIP
