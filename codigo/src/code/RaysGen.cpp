#include "RaysGen.h"

#include <cstdlib>

enum Border {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

Point getBorderPoint(unsigned int index, Border border, unsigned int imageSize) {
    Point p;
    switch (border) {
        case UP:
            p = Point(0, index);
            break;
        case DOWN:
            p = Point(imageSize - 1, index);
            break;
        case LEFT:
            p = Point(index, 0);
            break;
        case RIGHT:
            p = Point(index, imageSize - 1);
            break;
    }
    return p;
}

Point getRandomPoint(unsigned int imageSize) {
    return getBorderPoint(std::rand() % imageSize, Border(std::rand() % 4), imageSize);
}

void generateRandomRays(std::vector<std::pair<Point, Point> > &rays, unsigned int n, unsigned int imageSize) {
    srand(0212); // Fecha de entrega del tp
    for (int i = 0; i < n; i++) {
        rays.push_back(std::pair<Point, Point> {
                getRandomPoint(imageSize),
                getRandomPoint(imageSize)
        });
    }
}

void
generateRotatedRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity, unsigned int imageSize) {
    for (int i = 0; i < imageSize; i += granularity) {
        // Borde superior con centro
        rays.push_back(std::pair<Point, Point> {
                Point(0, i),
                Point(imageSize - 1, imageSize - 1 - i)});

        // Borde inferior con centro
        rays.push_back(std::pair<Point, Point> {
                Point(imageSize - 1, i),
                Point(0, imageSize - 1 - i)});

        // Borde izquierdo con centro
        rays.push_back(std::pair<Point, Point> {
                Point(i, 0),
                Point(imageSize - 1 - i, imageSize - 1)});

        // Borde derecho con centro
        rays.push_back(std::pair<Point, Point> {
                Point(i, imageSize - 1),
                Point(imageSize - 1 - i, 0)});
    }
}

void
generateSideToSideRays(std::vector<std::pair<Point, Point> > &rays, Border from, Border to, unsigned int granularity,
                       unsigned int imageSize) {
    for (int i = 0; i < imageSize; i += granularity) {
        for (int j = 0; j < imageSize; j++) {
            // Borde derecho con izquierdo
            rays.push_back(std::pair<Point, Point> {
                    getBorderPoint(i, from, imageSize),
                    getBorderPoint(j, to, imageSize)});
        }
    }
}

void generateLateralBordersRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity,
                                unsigned int imageSize) {
    generateSideToSideRays(rays, LEFT, RIGHT, granularity, imageSize);
    generateSideToSideRays(rays, RIGHT, LEFT, granularity, imageSize);

    generateSideToSideRays(rays, LEFT, UP, granularity, imageSize);
    generateSideToSideRays(rays, RIGHT, UP, granularity, imageSize);
    generateSideToSideRays(rays, LEFT, DOWN, granularity, imageSize);
    generateSideToSideRays(rays, RIGHT, DOWN, granularity, imageSize);
}

void
generateAllBordersRays(std::vector<std::pair<Point, Point> > &rays, unsigned int granularity, unsigned int imageSize) {
    // Borde superior con borde inferior
    generateSideToSideRays(rays, UP, DOWN, granularity, imageSize);
    generateSideToSideRays(rays, DOWN, UP, granularity, imageSize);

    // Borde superior con borde izquierdo
    generateSideToSideRays(rays, UP, LEFT, granularity, imageSize);
    generateSideToSideRays(rays, LEFT, UP, granularity, imageSize);

    // Borde superior con borde derecho
    generateSideToSideRays(rays, UP, RIGHT, granularity, imageSize);
    generateSideToSideRays(rays, RIGHT, UP, granularity, imageSize);

    // Borde izquierdo con borde derecho
    generateSideToSideRays(rays, LEFT, RIGHT, granularity, imageSize);
    generateSideToSideRays(rays, RIGHT, LEFT, granularity, imageSize);

    // Borde izquierdo con borde inferior
    generateSideToSideRays(rays, LEFT, DOWN, granularity, imageSize);
    generateSideToSideRays(rays, DOWN, LEFT, granularity, imageSize);

    // Borde derecho con borde inferior
    generateSideToSideRays(rays, RIGHT, DOWN, granularity, imageSize);
    generateSideToSideRays(rays, DOWN, RIGHT, granularity, imageSize);
}