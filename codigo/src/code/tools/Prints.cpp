#include "Prints.h"

#include <iostream>

void print(const std::vector<double> &v) {
    std::cout << "[";

    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];

        if (i < v.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << "]";
}

void print(const std::vector<std::vector<double> > &m) {
    std::cout << "[" << std::endl;

    for (int i = 0; i < m.size(); i++) {
        // std::cout << "\t";
        print(m[i]);

        if (i < m.size() - 1) {
            std::cout << ",";
        }
        // std::cout << std::endl;
    }

    // std::cout << "]";
}

void prettyPrint(const std::vector<double> &v, int n) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if ((i + 1) % n == 0) {
            std::cout << std::endl;
        } else if (i < v.size() - 1) {
            std::cout << "   ";
        }
    }
}

void prettyPrint(const std::vector<std::vector<double> > &m, int n, std::vector<std::pair<Point, Point> > rays) {
    for (int i = 0; i < m.size(); i++) {
        std::cout << "Rays " << i << " x1: " << rays[i].first.x << " y1: " << rays[i].first.y << " x2: "
                  << rays[i].second.x << " y2: " << rays[i].second.y << std::endl;
        prettyPrint(m[i], n);

        if (i < m.size() - 1) {
            std::cout << std::endl;
        }
    }
}
