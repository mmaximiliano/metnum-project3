#include "Noise.h"
#include "tools/Lineal.h"
#include <random>

void addNoise(std::vector<double> &times, double noiseIntensity) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, noiseIntensity);

    for (int i = 0; i < times.size(); i++) {
        times[i] += distribution(generator);
    }
}

void adaptNoise(std::vector<double> &times) {
    for (int i = 0; i < times.size(); i++) {
        if (times[i] < 1) {
            times[i] = 1;
        }
    }
}
