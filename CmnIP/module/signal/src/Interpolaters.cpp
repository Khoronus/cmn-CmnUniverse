#include "signal/inc/signal/signal_headers.hpp"

namespace CmnIP
{
namespace signal
{

float Interpolaters::Lerp(float v0, float v1, float t){
	return v0 + t * (v1 - v0);
}

float Interpolaters::Linear(float v0,float v1,float t) {
	return v0 + (v1 - v0) * t;
}

float Interpolaters::Cosine(float v0,float v1, float t) {
	float ft = t * 3.14;
	float f = (1 - cos(ft)) / 2;
	return v0 * (1 - f) + v1 * f;
}

float Interpolaters::Cubic(float v0, float v1, float v2, float v3, float t) {

	float a0, a1, a2, a3, t2;

	t2 = t * t;

	a0 = v3 - v2 - v0 + v1;
	a1 = v0 - v1 - a0;
	a2 = v2 - v0;
	a3 = v1;

	return (a0 * t * t2 + a1 * t2 + a2 * t + a3);
}

float Interpolaters::CatmullRom(float v0, float v1, float v2, float v3, float t) {
	float a0, a1, a2, a3, t2;

	t2 = t * t;

	a0 = -0.5 * v0 + 1.5 * v1 - 1.5 * v2 + 0.5 * v3;
	a1 = v0 - 2.5 * v1 + 2 * v2 - 0.5 * v3;
	a2 = -0.5 * v0 + 0.5 * v2;
	a3 = v1;

	return (a0 * t * t2 + a1 * t2 + a2 * t + a3);
}

float Interpolaters::Hermite(float v0, float v1, float v2, float v3, float t, float tension, float bias) {
	float m0, m1, t2, t3;
	float a0, a1, a2, a3;

	t2 = t * t;
	t3 = t2 * t;
	m0 = (v1 - v0) * (1 + bias) * (1 - tension) / 2;
	m0 += (v2 - v1) * (1 - bias) * (1 - tension) / 2;
	m1 = (v2 - v1) * (1 + bias) * (1 - tension) / 2;
	m1 += (v3 - v2) * (1 - bias) * (1 - tension) / 2;
	a0 = 2 * t3 - 3 * t2 + 1;
	a1 = t3 - 2 * t2 + t;
	a2 = t3 - t2;
	a3 = -2 * t3 + 3 * t2;

	return (a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2);
}

Interpolaters::Interpolaters()
{
}

Interpolaters::~Interpolaters()
{
}


} // namespace signal
} // namespace CmnIP
