#include "Eigenvectors.h"

#include "Lineal.h"
#include <cstdlib>
#include <thread>

void getRandomVector(std::vector<double> &v) {
    // TODO: fijar seed
    for (unsigned int i = 0; i < v.size(); i++) {
        // Numeros random
        v[i] = (std::rand() % 1000) / 1000.0;
    }

    v = normalizar(v);
}

double powerMethod(const std::vector<std::vector<double> > &A, std::vector<double> &v) {
    getRandomVector(v);

    for (unsigned int i = 0; i < MAX_ITERATIONS; i++) {
        v = normalizar(A * v);
    }
    return (v * (A * v)) / (v * v);
}

void reduceEigenvalues(std::vector<std::vector<double> > &B, std::vector<double> &v, double eigenvalue) {
    std::vector<std::thread> threads;

    unsigned int step = B.size() / THREAD_COUNT;
    unsigned int border = B.size() % THREAD_COUNT;

    auto partial_prod = [eigenvalue, &B, &v](unsigned int from, unsigned int to) -> void {
        for (unsigned int i = from; i < to; i++) {
            for (unsigned int j = 0; j < B.size(); j++) {
                B[i][j] -= eigenvalue * v[i] * v[j];
            }
        }
    };

    for (unsigned int i = 0; i < B.size() - border && step > 0; i += step) {
        threads.push_back(std::thread(partial_prod, i, i + step));
    }

    threads.push_back(std::thread(partial_prod, B.size() - border, B.size()));

    for (auto it = threads.begin(); it != threads.end(); it++) {
        it->join();
    }
}
