#include "Metrics.h"
#include "tools/Lineal.h"
#include <math.h>
#include <algorithm>
#include <functional>

double calculatePSNR(const std::vector<std::vector<unsigned int> > &image,
                     const std::vector<std::vector<unsigned int> > &generatedImage) {
    double MAX2 = 255.0 * 255.0;
    return 10.0 * log10(MAX2 / calculateECM(image, generatedImage));
}


double calculateECM(const std::vector<std::vector<unsigned int> > &image,
                    const std::vector<std::vector<unsigned int> > &generatedImage) {
    int N = image.size() * image[0].size();
    return normaFcuadrada(image - generatedImage) / N;
}

double calculateRECMIQR(const std::vector<std::vector<unsigned int> > &image,
                        const std::vector<std::vector<unsigned int> > &generatedImage) {
    return sqrt(calculateECM(image, generatedImage)) / calculateIQR(generatedImage);
}

double calculateIQR(const std::vector<std::vector<unsigned int> > &A) {
    std::vector<unsigned int> v;

    for (auto &x : A) {
        for (auto y : x) {
            v.push_back(y);
        }
    }

    const unsigned int Q1 = v.size() / 4;
    const unsigned int Q2 = v.size() / 2;
    const unsigned int Q3 = Q1 + Q2;

    std::nth_element(v.begin(), v.begin() + Q3, v.end());

    return (double) (v[Q3] - v[Q1]);

}
