#include "math.h"



float random(float a, float b) {
	float n = (float)rand() / RAND_MAX;
	float t = b - a;
	float r = a + n * t;
	return r;
}



int fibonacci(unsigned int index) {
	if (index <= 1)
		return index;
	return fibonacci(index - 1) + fibonacci(index - 2);
}



float cvtToRad(float ang) {
	return (ang * PI) / 90.0;
}