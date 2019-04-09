#ifndef __RAYSGEN_H__
#define __RAYSGEN_H__

#include <vector>
#include "Types.h"

// Genera n rayos
void generateRandomRays(std::vector<std::pair<Point, Point> > &rays, unsigned int n, unsigned int imageSize);

// Genera 4 * imageSize/granularity rayos (con algunos repetidos)
void generateRotatedRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity, unsigned int imageSize);

// Genera rayos desde los bordes derecho e izquierdo
// Genera 6 * imagesize^2 / granularity rayos (con repetidos)
void generateLateralBordersRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity,
                                unsigned int imageSize);

// Genera rayos entre todos los bordes
// Genera 12 * imagesize^2 / granularity rayos (con repetidos)
void
generateAllBordersRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity, unsigned int imageSize);

#endif
