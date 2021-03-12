#pragma once
#include <iostream>
namespace QuadTree {

    typedef std::pair<double, double> Point;

    class Quadrant {
    private:
        Point nw; //Северо-восточная точка
        Point ne; //Северо-западная точка
        Point sw; //Юго-восточная точка
        Point se; //Юго-западная точка
    public:
        Quadrant(const Point& nw, const Point& ne, const Point& sw, const Point& se);

    };
}