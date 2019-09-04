#include "signal/inc/signal/signal_headers.hpp"

namespace CmnIP
{
namespace signal
{

float T [] = { 0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a };

int SimplexNoise::b2Param(int N, int B){
	return N >> B & 1;
}

int SimplexNoise::b4Param(int i, int j, int k, int B){
	return T[b2Param(i, B) << 2 | b2Param(j, B) << 1 | b2Param(k, B)];
}

float SimplexNoise::noise(float x, float y, float z){
	float s = (x + y + z) / 3;
	i = (int)floor(x + s);
	j = (int)floor(y + s);
	k = (int)floor(z + s);
	s = (i + j + k) / 6.0f;
	u = x - i + s;
	v = y - j + s;
	w = z - k + s;

	A[0] = A[1] = A[2] = 0;
	int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
	int lo = u< w ? u< v ? 0 : 1 : v< w ? 1 : 2;

	return SimplexNoise::K(hi) + SimplexNoise::K(3 - hi - lo) + SimplexNoise::K(lo) + SimplexNoise::K(0);
}

float SimplexNoise::K(int a){
	float s = (A[0] + A[1] + A[2]) / 6.0f;
	float x = u - A[0] + s;
	float y = v - A[1] + s;
	float z = w - A[2] + s;
	float t = 0.6 - x * x - y * y - z * z;
	int h = (int)Shuffle(i + A[0], j + A[1], k + A[2]);

	A[a]++;

	if (t < 0)
	{
		return 0;
	}


	// calculate the gradients
	int b5 = h >> 5 & 1, b4 = h >> 4 & 1, b3 = h >> 3 & 1, b2 = h >> 2 & 1, b = h & 3;
	float p = b == 1 ? x : b == 2 ? y : z, q = b == 1 ? y : b == 2 ? z : x, r = b == 1 ? z : b == 2 ? x : y;
	p = (b5 == b3 ? -p : p); q = (b5 == b4 ? -q : q); r = (b5 != (b4 ^ b3) ? -r : r);
	t *= t;
	return (float)(8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r)));
}

float SimplexNoise::Shuffle(int i, int j, int k){
	return SimplexNoise::b4Param(i, j, k, 0) 
		+ SimplexNoise::b4Param(j, k, i, 1) + SimplexNoise::b4Param(k, i, j, 2) + b4Param(i, j, k, 3) + b4Param(j, k, i, 4) + b4Param(k, i, j, 5) + SimplexNoise::b4Param(i, j, k, 6) + SimplexNoise::b4Param(j, k, i, 7);
}

float SimplexNoise::Get1D(float x){
	return SimplexNoise::noise(x, 0, 0 );
}

float SimplexNoise::Get2D(float x, float y){
	return SimplexNoise::noise(x, y, 0);
}

SimplexNoise::SimplexNoise()
{
}


SimplexNoise::~SimplexNoise()
{
}

} // namespace signal
} // namespace CmnIP
