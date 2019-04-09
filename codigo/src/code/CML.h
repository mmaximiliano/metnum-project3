#ifndef __CML_H__
#define __CML_H__

#include <vector>
#include <string>
#include "Config.h"
#include "Loaders.h"

std::vector<std::vector<unsigned int> >
reconstructImage(const std::vector<double> &times, std::vector<std::vector<double> > &distances,
                 unsigned int eigenvalueCount, std::string svd_path, Config config);

#endif
