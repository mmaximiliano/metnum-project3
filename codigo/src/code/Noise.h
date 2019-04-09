#ifndef __NOISE_H__
#define __NOISE_H__

#include <vector>

void addNoise(std::vector<double> &times, double noiseIntensity);

void adaptNoise(std::vector<double> &times);

#endif

