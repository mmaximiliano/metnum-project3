#include <iostream>

#include "code/Loaders.h"
#include "code/Metrics.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "El formato es ./comparar <imagen orginal> <imagen generada>" << std::endl;
        return 1;
    }

    std::cout << "Cargando datos..." << std::endl;
    std::vector<std::vector<unsigned int> > originalImage = loadImage(argv[1]);
    std::vector<std::vector<unsigned int> > generatedImage = loadImage(argv[2]);

    std::cout << "ECM: " << calculateECM(originalImage, generatedImage) << std::endl;
    std::cout << "PSNR: " << calculatePSNR(originalImage, generatedImage) << std::endl;
    std::cout << "RECMIQR: " << calculateRECMIQR(originalImage, generatedImage) << std::endl;

    return 0;
}