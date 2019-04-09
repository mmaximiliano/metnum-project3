#include "Args.h"

#include <iostream>
#include <string>

bool loadArguments(int argc, char *argv[], Config &config) {
    // Devolver true si se cargo bien, false si falta algo indispensable
    // Formato esperado: ./tp3 -i <image-path> -r <ray-type> <n> -s <size-n> -n <noise> -c <svd_path> -o <output-dir>

    if (argc < 16) {
        std::cout << "Los argumentos estan mal!" << std::endl;
        std::cout
                << "El formato es ./tp3 -i <image-path> -r <ray-type> <n> -s <size-n> -n <noise> -e <eigenvalue-min> -o <output-dir> -t <time-dir>"
                << std::endl;
        return false;
    }

    for (unsigned int i = 1; i < argc; i += 2) {
        std::string s = argv[i];

        switch (s[1]) {
            case 'i':
                config.imageFileName = argv[i + 1];
                break;
            case 'r':
                config.rayType = (RayType) std::stoi(argv[i + 1]);
                config.rayN = std::stoi(argv[i + 2]);
                i++;
                break;
            case 's':
                config.n = std::stoi(argv[i + 1]);
                break;
            case 'n':
                config.noiseIntensity = std::stod(argv[i + 1]);
                break;
            case 'o':
                config.outputDirectory = argv[i + 1];
                break;
            case 'e':
                config.eigenvalueCount = std::stoi(argv[i + 1]);
                break;
            case 'c':
                config.svd_path = argv[i + 1];
                break;
            case 't':
                config.timeFileName = argv[i + 1];
                break;
        }
    }

    return true;
}
