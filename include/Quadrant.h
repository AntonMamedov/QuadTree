#pragma once
#include <cassert>
#include <iostream>

namespace QuadTree {

typedef std::pair<double, double> Point;

//Класс, содержащий крайние и центральную точки квадранта
//Точки должны образовывать квадрат
//Класс воспринимается как множество точек, входящих в квадрант
class Quadrant final {
private:
  Point nw;     //Северо-восточная точка
  Point ne;     //Северо-западная точка
  Point sw;     //Юго-восточная точка
  Point se;     //Юго-западная точка
  Point center; //Центарльная точка
public:
  Quadrant(const Point &nw, const Point &ne, const Point &sw,
           const Point &se) noexcept;
  Quadrant(const Quadrant &other) noexcept = default;
  Quadrant(Quadrant &&other) noexcept = default;
  ~Quadrant() noexcept = default;
  const Point &NorthWest() const noexcept;
  const Point &SouthWest() const noexcept;
  const Point &NorthEast() const noexcept;
  const Point &SouthEast() const noexcept;
  const Point &Center() const noexcept;
  Point MidNorth() const noexcept;
  Point MidSouth() const noexcept;
  Point MidWest() const noexcept;
  Point MidEast() const noexcept;
  Quadrant CreateNwChildrenQuadrant() const noexcept;
  Quadrant CreateNeChildrenQuadrant() const noexcept;
  Quadrant CreateSwChildrenQuadrant() const noexcept;
  Quadrant CreateSeChildrenQuadrant() const noexcept;
  friend bool operator==(const Quadrant &left, const Quadrant &right);
  bool operator[](const Point &point) const noexcept;
};

//Создание квадранта из угловых точек
inline Quadrant::Quadrant(const Point &nw, const Point &ne, const Point &sw,
                          const Point &se) noexcept
    : nw(nw), ne(ne), sw(sw), se(se) {
  //Проверка того, образуют ли переданные значения квадрант
  assert(nw.second + ne.second == sw.second + se.second &&
         nw.first + sw.first == se.first + ne.first &&
         "The passed points do not form a square");
  center = Point((nw.first + sw.first) / 2, (nw.second + ne.second) / 2);
}

//Возвращает северо-западную точку
inline const Point &Quadrant::NorthWest() const noexcept { return nw; }

//Возвращает северо-западную точку
inline const Point &Quadrant::SouthWest() const noexcept { return sw; }

//Возвращает юго-западную точку точку
inline const Point &Quadrant::NorthEast() const noexcept { return ne; }

//Возвращает юго-восточную точку
inline const Point &Quadrant::SouthEast() const noexcept { return se; }

//Возвращает сентраьную точку
inline const Point &Quadrant::Center() const noexcept { return center; }

//Вычисляет центральную точку между северо-востоком и северо-западом
inline Point Quadrant::MidNorth() const noexcept {
  return Point(nw.first, (nw.second + ne.second) / 2);
  ;
}

//Вычисляет центральную точку между юго-востоком и юго-западом
inline Point Quadrant::MidSouth() const noexcept {
  return Point(sw.first, (sw.second + se.second) / 2);
  ;
}

//Вычисляет центральную точку между с и юго-западом и северо-западом
inline Point Quadrant::MidWest() const noexcept {
  return Point((nw.first + sw.first) / 2, nw.second);
}

//Вычисляет центральную точку между с и юго-востоком и северо-востоком
inline Point Quadrant::MidEast() const noexcept {
  return Point((ne.first + se.first) / 2, ne.second);
}

//Проверка вхождения точки в квадрант
//Если точка находится в множестве точек квадранта, возвращает true
inline bool Quadrant::operator[](const Point &point) const noexcept {
  return point.first <= nw.first && point.second >= nw.second &&
         point.first <= ne.first && point.second <= ne.second &&
         point.first >= sw.first && point.second >= sw.second &&
         point.first >= se.first && point.second <= se.second;
}

//Создает квадрант, составляющий 1/4 от размера родительского
//И находящийся в северо-западной зоне
inline Quadrant Quadrant::CreateNwChildrenQuadrant() const noexcept {
  return Quadrant(nw, MidNorth(), MidWest(), center);
}

//Создает квадрант, составляющий 1/4 от размера родительского
//И находящийся в северо-восточной зоне
inline Quadrant Quadrant::CreateNeChildrenQuadrant() const noexcept {
  return Quadrant(MidNorth(), ne, center, MidEast());
}

//Создает квадрант, составляющий 1/4 от размера родительского
//И находящийся в юго-западной зоне
inline Quadrant Quadrant::CreateSwChildrenQuadrant() const noexcept {
  return Quadrant(MidWest(), Center(), sw, MidSouth());
}

//Создает квадрант, составляющий 1/4 от размера родительского
//И находящийся в юго-восточной зоне
inline Quadrant Quadrant::CreateSeChildrenQuadrant() const noexcept {
  return Quadrant(center, MidEast(), MidSouth(), se);
}

inline bool operator==(const Quadrant &left, const Quadrant &right) {
  return left.center == right.center && left.nw == right.nw &&
         left.se == right.se;
}
} // namespace QuadTree
