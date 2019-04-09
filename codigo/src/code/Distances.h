#ifndef __DISTANCES_H__
#define __DISTANCES_H__

#include <vector>
#include "Types.h"

std::vector<std::vector<double> > calculateDistances(const std::vector<std::vector<unsigned int> > &image,
                                                     const std::vector<std::pair<Point, Point> > &rays, unsigned int n,
                                                     std::vector<double> &times);

#endif
