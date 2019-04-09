#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <chrono>
#include "code/Config.h"
#include "code/Args.h"
#include "code/Types.h"
#include "code/Loaders.h"
#include "code/Noise.h"
#include "code/Distances.h"
#include "code/CML.h"
#include "code/Metrics.h"
#include "code/RaysGen.h"
#include "code/tools/Prints.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

int main(int argc, char *argv[]) {
    Config config;

    if (!loadArguments(argc, argv, config)) {
        return 1;
    }

    // Timers setup
    ms all = ms{0};
    ms load_image = ms{0};
    ms generate_rays = ms{0};
    ms calculate_dists = ms{0};
    ms add_noise = ms{0};
    ms calculate_cml = ms{0};

    auto all_start = Time::now();
    auto load_image_start = Time::now();

    // Load data
    std::cout << "Cargando datos..." << std::endl;
    std::vector<std::vector<unsigned int> > image = loadImage(config.imageFileName);

    load_image = std::chrono::duration_cast<ms>(Time::now() - load_image_start);

    if (image.size() > 0 && image[0].size() > 0) {
        std::cout << "Imagen de ";
        std::cout << image.size() << "x" << image[0].size();
        std::cout << " cargada." << std::endl;
    } else {
        std::cout << "Error! Imagen de dimension 0." << std::endl;
        return 2;
    }

    auto generate_rays_start = Time::now();

    // Se generan los rayos
    std::vector<std::pair<Point, Point> > rays;
    switch (config.rayType) {
        case 0:
            std::cout << "Generando rayos random" << std::endl;
            generateRandomRays(rays, config.rayN, image.size());
            break;
        case 1:
            std::cout << "Generando rayos rotados" << std::endl;
            generateRotatedRays(rays, config.rayN, image.size());
            break;
        case 2:
            std::cout << "Generando rayos en los laterales" << std::endl;
            generateLateralBordersRays(rays, config.rayN, image.size());
            break;
        case 3:
            std::cout << "Generando rayos en los bordes" << std::endl;
            generateAllBordersRays(rays, config.rayN, image.size());
            break;
    }
    std::cout << "# rayos: " << rays.size() << std::endl;

    generate_rays = std::chrono::duration_cast<ms>(Time::now() - generate_rays_start);

    auto calculate_dists_start = Time::now();

    std::vector<double> times(rays.size());

    // Discretize distances
    std::cout << "Discretizando distancias y simulando los tiempos" << std::endl;
    std::vector<std::vector<double> > distances = calculateDistances(image, rays, config.n, times);

    calculate_dists = std::chrono::duration_cast<ms>(Time::now() - calculate_dists_start);

    auto add_noise_start = Time::now();

    // Add and adapt noise
    std::cout << "Agrego ruido" << std::endl;
    addNoise(times, (config.noiseIntensity / 100.0) * 255.0 * config.n);
    adaptNoise(times);

    add_noise = std::chrono::duration_cast<ms>(Time::now() - add_noise_start);

    std::cout << "Size distancias: " << distances.size() << "x" << distances[0].size() << std::endl;
    if (distances.size() < distances[0].size()) {
        std::cout << "Tenes menos ecuaciones que incognitas!" << std::endl;
        return 2;
    }
    // prettyPrint(distances, config.n, rays);
    // prettyPrint(distances, config.n);

    auto calculate_cml_start = Time::now();

    // Reconstruct image from times and distances
    std::cout << "Calculando CML" << std::endl;
    std::cout << "Rayos: " << times.size() << std::endl;
    std::vector<std::vector<unsigned int> > generatedImage = reconstructImage(times, distances, config.eigenvalueCount,
                                                                              config.svd_path, config);

    calculate_cml = std::chrono::duration_cast<ms>(Time::now() - calculate_cml_start);

    std::ostringstream of;
    of << config.outputDirectory << "/reconstruccion-" << getFileName(config, true) << ".csv";
    std::cout << std::string(of.str()) << std::endl;
    std::ofstream fout(of.str());

    for (auto &fila : generatedImage) {
        for (int i = 0; i < fila.size(); i++) {
            unsigned int elem = fila[i];
            fout << elem;
            if (i != fila.size() - 1) {
                fout << ",";
            }
        }
        fout << "\n";
    }

    fout.close();

    all = std::chrono::duration_cast<ms>(Time::now() - all_start);

    std::ostringstream timef;
    timef << config.timeFileName << "/times-" << getFileName(config, true) << ".json";

    fout.open(timef.str(), std::ios::out | std::ios::trunc);
    fout << "{";
    fout << "\"load_image\":" << load_image.count() << ",";
    fout << "\"generate_rays\":" << generate_rays.count() << ",";
    fout << "\"calculate_dists\":" << calculate_dists.count() << ",";
    fout << "\"add_noise\":" << add_noise.count() << ",";
    fout << "\"calculate_cml\":" << calculate_cml.count() << ",";
    fout << "\"all\":" << all.count() << "}";
    fout.close();

    return 0;
}
