#ifndef __LINEAL_H__
#define __LINEAL_H__

#include <vector>

#define THREAD_COUNT 7

double norma1(const std::vector<double> &v);

double norma2(const std::vector<double> &v);

double norma2cuadrada(const std::vector<double> &v);

double normaFcuadrada(const std::vector<std::vector<double> > &M);

double normaF(const std::vector<std::vector<double> > &M);

std::vector<double> normalizar(const std::vector<double> &v);

std::vector<double> operator*(double x, const std::vector<double> &v);

std::vector<double> mul(const std::vector<std::vector<double> > &M, const std::vector<double> &v);

double operator*(const std::vector<double> &v1, const std::vector<double> &v2);

std::vector<double> operator*(const std::vector<std::vector<double> > &M, const std::vector<double> &v);

std::vector<std::vector<double> >
operator-(const std::vector<std::vector<double> > &M, const std::vector<std::vector<double> > &A);

std::vector<std::vector<double> >
operator-(const std::vector<std::vector<unsigned int> > &M, const std::vector<std::vector<unsigned int> > &A);

std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &w);

void operator+=(std::vector<double> &v, const std::vector<double> &w);

std::vector<std::vector<double> > transpose(const std::vector<std::vector<double> > &M);

#endif
