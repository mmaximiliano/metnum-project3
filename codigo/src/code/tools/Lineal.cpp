#include "Lineal.h"

#include <cmath>
#include <thread>

double norma1(const std::vector<double> &v) {
    double norma = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) {
        norma += std::abs(v[i]);
    }
    return norma;
}

double norma2(const std::vector<double> &v) {
    return sqrt(norma2cuadrada(v));
}

double norma2cuadrada(const std::vector<double> &v) {
    double norma = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) {
        norma += v[i] * v[i];
    }
    return norma;
}

double normaFcuadrada(const std::vector<std::vector<double> > &M) {
    double acc = 0.0;
    for (auto &v : M) {
        acc += norma2cuadrada(v);
    }

    return acc;
}

double normaF(const std::vector<std::vector<double> > &M) {
    return sqrt(normaFcuadrada(M));
}

std::vector<double> normalizar(const std::vector<double> &v) {
    double normaDeV = norma2(v);

    std::vector<double> res;
    for (unsigned int i = 0; i < v.size(); i++) {
        res.push_back(v[i] / normaDeV);
    }

    return res;
}

std::vector<double> operator*(double x, const std::vector<double> &v) {
    std::vector<double> w;

    for (double vi:v) {
        w.push_back(x * vi);
    }

    return w;
}

double operator*(const std::vector<double> &v1, const std::vector<double> &v2) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v1.size(); i++) {
        sum += v1[i] * v2[i];
    }

    return sum;
}

std::vector<double> operator*(const std::vector<std::vector<double> > &M, const std::vector<double> &v) {
    std::vector<double> res(M.size());

    std::vector<std::thread> threads;

    unsigned int step = M.size() / THREAD_COUNT;
    unsigned int border = M.size() % THREAD_COUNT;

    auto partial_prod = [](const std::vector<std::vector<double> > *M, const std::vector<double> *v,
                           std::vector<double> *res,
                           unsigned int from, unsigned int to) -> void {
        for (unsigned int i = from; i < to; i++) {
            double sum = 0.0;
            for (unsigned int j = 0; j < (*M)[i].size(); j++) {
                sum += (*M)[i][j] * (*v)[j];
            }

            (*res)[i] = sum;
        }
    };

    for (unsigned int i = 0; i < M.size() - border && step > 0; i += step) {
        threads.push_back(std::thread(partial_prod, &M, &v, &res, i, i + step));
    }

    threads.push_back(std::thread(partial_prod, &M, &v, &res, M.size() - border, M.size()));

    for (auto it = threads.begin(); it != threads.end(); it++) {
        it->join();
    }

    return res;
}

std::vector<double> mul(const std::vector<std::vector<double> > &M, const std::vector<double> &v) {
    std::vector<double> res;
    for (unsigned int i = 0; i < M.size(); i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < M[i].size(); j++) {
            sum += M[i][j] * v[j];
        }

        res.push_back(sum);
    }

    return res;
}

std::vector<std::vector<double> >
operator-(const std::vector<std::vector<double> > &M, const std::vector<std::vector<double> > &A) {
    std::vector<std::vector<double> > res(M.size());
    for (auto &v : M) {
        auto i = &v - &M[0];
        for (auto &e : v) {
            auto j = &e - &v[0];
            res[i].push_back(e - A[i][j]);
        }
    }

    return res;
}

std::vector<std::vector<double> >
operator-(const std::vector<std::vector<unsigned int> > &M, const std::vector<std::vector<unsigned int> > &A) {
    std::vector<std::vector<double> > res(M.size());
    for (auto &v : M) {
        auto i = &v - &M[0];
        for (auto &e : v) {
            auto j = &e - &v[0];
            res[i].push_back((double) e - (double) A[i][j]);
        }
    }

    return res;
}

std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &w) {
    std::vector<double> res(v.size());
    for (auto &e : v) {
        auto i = &e - &v[0];
        res[i] = e + w[i];
    }

    return res;
}

void operator+=(std::vector<double> &v, const std::vector<double> &w) {
    for (int i = 0; i < v.size(); i++) {
        v[i] += w[i];
    }
}

std::vector<std::vector<double> > transpose(const std::vector<std::vector<double> > &M) {
    //std::vector<double> matRows(M.size());
    std::vector<std::vector<double> > Mt(M.at(0).size(), std::vector<double>(M.size()));

    std::vector<std::thread> threads;

    unsigned int step = M[0].size() / THREAD_COUNT;
    unsigned int border = M[0].size() % THREAD_COUNT;

    auto partial_prod = [&M, &Mt](unsigned int from, unsigned int to) -> void {
        for (unsigned int i = from; i < to; i++) {
            for (unsigned int j = 0; j < M.size(); j++) {
                Mt[i][j] = M[j][i];
            }
        }
    };

    for (unsigned int i = 0; i < M[0].size() - border && step > 0; i += step) {
        threads.push_back(std::thread(partial_prod, i, i + step));
    }

    threads.push_back(std::thread(partial_prod, M[0].size() - border, M[0].size()));

    for (auto &e : threads) {
        e.join();
    }

    return Mt;
}

