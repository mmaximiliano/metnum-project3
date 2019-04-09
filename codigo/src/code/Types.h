#ifndef __TYPES_H__
#define __TYPES_H__

struct Point {
    unsigned int x;
    unsigned int y;

    Point() : x(0), y(0) {}

    Point(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
};

#define EPSILON 0.000001

#endif
