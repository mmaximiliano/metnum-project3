#include "Distances.h"
#include <math.h>
#include <iostream>


std::vector<std::vector<double> > calculateDistances(const std::vector<std::vector<unsigned int> > &image,
                                                     const std::vector<std::pair<Point, Point> > &rays, unsigned int n,
                                                     std::vector<double> &times) {
    std::vector<double> dRows(n * n);
    std::vector<std::vector<double> > d(rays.size(), dRows);

    int df = image.size() / n;
    int dc = image[0].size() / n;

    for (int i = 0; i < rays.size(); i++) {
        //std::cout << "Rays x1: " << rays[i].first.x << " y1: " << rays[i].first.y << " x2: " << rays[i].second.x << " y2: " << rays[i].second.y << std::endl;
        double deltaX = int(rays[i].second.x) - int(rays[i].first.x);
        if (abs(deltaX) > EPSILON) {
            double deltaY = int(rays[i].second.y) - int(rays[i].first.y);

            // Calculo la recta
            double pendiente = deltaY / deltaX;
            double ordenaOrigen = rays[i].first.y - pendiente * rays[i].first.x;
            // std::cout << "m " << pendiente << std::endl;
            // std::cout << "b " << ordenaOrigen << std::endl;

            // Calculo el rango de x donde pasa la recta
            int greaterX = rays[i].first.x < rays[i].second.x ? rays[i].second.x : rays[i].first.x;
            int smallerX = rays[i].first.x > rays[i].second.x ? rays[i].second.x : rays[i].first.x;
            for (int x = smallerX; x < greaterX; x++) {

                bool y1Entero = false;
                bool y2Entero = false;

                double y1 = pendiente * x + ordenaOrigen;
                double y2 = pendiente * (x + 1) + ordenaOrigen;

                // Se rompe el floor sino. Ej: y1 = -0.0000001, floor(y1) = -1
                if (abs(y1 - int(y1)) < EPSILON) {
                    y1 = int(y1);
                    y1Entero = true;
                } else {
                    y1 = floor(y1);
                }
                if (abs(y2 - int(y2)) < EPSILON) {
                    y2 = int(y2);
                    y2Entero = true;
                } else {
                    y2 = floor(y2);
                }

                // Sino recorrio un valor de y entero
                if (abs(int(y1) - int(y2)) < EPSILON) {
                    d[i][int(y1 / df) * n + int(x / df)]++;
                    times[i] += image[int(y1)][x] + 1;
                } else {

                    int greaterY = 0;

                    // Esto esa para los casos como el de f(x) = x. Porque si dejo incluido el borde de y
                    // superior cuento que el rayo pasa por dos cuadrados de y por cada x cuando en realidad
                    // pasa por uno solo. Despues lo podemos emprolijar. Ej:
                    // 1   0   0   0
                    // 1   1   0   0
                    // 0   1   1   0
                    // 0   0   1   1
                    // Cuando deberia ser:
                    // 1   0   0   0
                    // 0   1   0   0
                    // 0   0   1   0
                    // 0   0   0   1

                    if (y1 < y2) {
                        greaterY = y2;
                        if (y2Entero) {
                            greaterY--;
                        }
                    } else {
                        greaterY = y1;
                        if (y1Entero) {
                            greaterY--;
                        }
                    }
                    int smallerY = y1 > y2 ? y2 : y1;

                    // Si recorrio mas de un valor de y
                    for (int y = int(smallerY); y <= int(greaterY); y++) {
                        d[i][(y / df) * n + (x / df)]++;
                        times[i] += image[int(y)][x] + 1;
                    }
                }
            }
            // Caso borde para el ultimo x
            double y = pendiente * greaterX + ordenaOrigen;
            if (abs(y - int(y)) < EPSILON) {
                y = int(y);
            } else {
                y = floor(y);
            }
            d[i][int(y / df) * n + int(greaterX / df)]++;
            times[i] += image[y][greaterX] + 1;
        } else {
            // Caso en el que no sea una recta de un eje cartesiano
            int greaterY = rays[i].first.y < rays[i].second.y ? rays[i].second.y : rays[i].first.y;
            int smallerY = rays[i].first.y > rays[i].second.y ? rays[i].second.y : rays[i].first.y;
            for (int y = smallerY; y <= greaterY; y++) {
                d[i][(y / df) * n + (rays[i].first.x / df)]++;
                times[i] += image[y][rays[i].first.x] + 1;
            }
        }
    }
    return d;
}
