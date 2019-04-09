#ifndef __AUTOVECTORES_H__
#define __AUTOVECTORES_H__

#include <vector>

#define MAX_ITERATIONS 100

double powerMethod(const std::vector<std::vector<double> > &A, std::vector<double> &v);

void reduceEigenvalues(std::vector<std::vector<double> > &B, std::vector<double> &v, double eigenvalue);

#endif
