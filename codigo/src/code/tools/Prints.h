#ifndef __PRINTS_H__
#define __PRINTS_H__

#include <vector>
#include "../Types.h"

void print(const std::vector<double> &v);

void print(const std::vector<std::vector<double> > &m);

void prettyPrint(const std::vector<double> &v, int n);

void prettyPrint(const std::vector<std::vector<double> > &m, int n, std::vector<std::pair<Point, Point> > rays);

#endif
