#ifndef __LOADERS_H__
#define __LOADERS_H__

#include <vector>
#include <utility>
#include <string>
#include "Types.h"
#include "Config.h"

std::vector<std::vector<unsigned int> > loadImage(const std::string &filename);

std::vector<std::pair<Point, Point> > loadRays(const std::string &filename);

std::string getFileName(const Config config, bool noise);

#endif
