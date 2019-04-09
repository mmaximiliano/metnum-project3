#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

enum RayType {
    RANDOM_RAYS = 0,
    ROTATED_RAYS = 1,
    LATERAL_BORDER_RAYS = 2,
    ALL_BORDER_RAYS = 3
};

struct Config {
    std::string imageFileName;
    RayType rayType;
    unsigned int rayN;
    std::string svd_path = "NULL";
    unsigned int n;
    double noiseIntensity;
    std::string outputDirectory;
    unsigned int eigenvalueCount;
    std::string timeFileName;
};

#endif
