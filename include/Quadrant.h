#pragma once
#include <iostream>

namespace QuadTree {

    typedef std::pair<double, double> Point;

    class Quadrant {
    private:
        Point nw;    //Северо-восточная точка
        Point ne;    //Северо-западная точка
        Point sw;    //Юго-восточная точка
        Point se;    //Юго-западная точка
        Point center;//Центарльная точка
    public:
        Quadrant(const Point &nw, const Point &ne, const Point &sw, const Point &se);
        Quadrant(const Quadrant &other) = default;
        Quadrant(Quadrant &&other) = default;
        ~Quadrant() = default;
        const Point &NorthWest() const;
        const Point &SouthWest() const;
        const Point &NorthEast() const;
        const Point &SouthEast() const;
        const Point &Center() const;
        Point MidNorth() const;
        Point MidSouth() const;
        Point MidWest() const;
        Point MidEast() const;

        Quadrant &operator=(const Quadrant &quad) = default;
        Quadrant &operator=(Quadrant &&quad) = default;
        bool operator[](const Point &point) const;
    };

    //Создание квадранта из угловых точек
    inline Quadrant::Quadrant(const Point &nw, const Point &ne, const Point &sw, const Point &se)
        : nw(nw), ne(ne), sw(sw), se(se) {
        center = Point((nw.first + sw.first) / 2, (nw.second + ne.second) / 2);
    }

    //Возвращает северо-западную точку
    inline const Point &Quadrant::NorthWest() const {
        return nw;
    }

    //Возвращает северо-западную точку
    inline const Point &Quadrant::SouthWest() const {
        return sw;
    }

    //Возвращает юго-западную точку точку
    inline const Point &Quadrant::NorthEast() const {
        return ne;
    }

    //Возвращает юго-восточную точку
    inline const Point &Quadrant::SouthEast() const {
        return se;
    }

    //Возвращает сентраьную точку
    inline const Point &Quadrant::Center() const {
        return center;
    }

    //Вычисляет центральную точку между северо-востоком и северо-западом
    inline Point Quadrant::MidNorth() const {
        return Point(nw.first, (nw.second + ne.second) / 2);
        ;
    }

    //Вычисляет центральную точку между юго-востоком и юго-западом
    inline Point Quadrant::MidSouth() const {
        return Point(sw.first, (sw.second + se.second) / 2);
        ;
    }

    //Вычисляет центральную точку между с и юго-западом и северо-западом
    inline Point Quadrant::MidWest() const {
        return Point((nw.first + sw.first) / 2, nw.second);
        ;
    }

    //Вычисляет центральную точку между с и юго-востоком и северо-востоком
    inline Point Quadrant::MidEast() const {
        return Point((ne.first + se.first) / 2, ne.second);
    }

    //Проверка вхождения точки в квадрант
    //Если точка находится в множестве точек квадранта, возвращает true
    inline bool Quadrant::operator[](const Point &point) const {
        return point.first <= nw.first && point.second >= nw.second &&
               point.first <= ne.first && point.second <= ne.second &&
               point.first >= sw.first && point.second >= sw.second &&
               point.first >= se.first && point.second <= se.second;
    }

}// namespace QuadTree
