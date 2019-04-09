#include "Loaders.h"

#include <fstream>
#include <sstream>

std::vector<std::vector<unsigned int> > loadImage(const std::string &filename) {
    // Imagen final
    std::vector<std::vector<unsigned int> > image;

    // Archivo a cargar
    std::ifstream fin(filename);

    // Row a parsear
    std::string row;
    // Itero las filas (separas por newLines)
    while (std::getline(fin, row)) {
        std::istringstream rowStream(row);

        // Pixel a parsear
        std::string pixel;
        std::vector<unsigned int> parsedRow;
        // Recorro la fila, separada por comas, y me guardo cada elemento
        while (std::getline(rowStream, pixel, ',')) {
            parsedRow.push_back(std::stoi(pixel));
        }

        image.push_back(parsedRow);
    }

    return image;
}

std::vector<std::pair<Point, Point> > loadRays(const std::string &filename) {
    std::vector<std::pair<Point, Point> > rays;
    return rays;
}

std::string getFileName(const Config config, bool noise) {
    std::stringstream ss;
    ss << "n_" << config.n << "_rayType_" << config.rayType << "_rayN_"
       << config.rayN << "_e_" << config.eigenvalueCount;
    if (noise) {
        ss << "_noise_" << config.noiseIntensity;
    }
    return ss.str();
}
