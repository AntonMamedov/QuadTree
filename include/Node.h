#pragma once
#include "Quadrant.h"
#include <optional>

namespace QuadTree {

const size_t amountOfZone = 4;

const size_t nwZoneIndex = 0;
const size_t neZoneIndex = 1;
const size_t swZoneIndex = 2;
const size_t seZoneIndex = 3;

template <typename DataT> class Node {
private:
  Quadrant quadrant;
  Node<DataT> *zones[amountOfZone];
  DataT data;

private:
  void DestroyChildrenZones() noexcept;

public:
  explicit Node(const Quadrant &quadrant) noexcept;
  ~Node() noexcept;
  bool ChildrenZones();
  void SpawnChildrenZone() noexcept;
  std::optional<Node<DataT> *> GetNwZone();
  std::optional<Node<DataT> *> GetNeZone();
  std::optional<Node<DataT> *> GetSwZone();
  std::optional<Node<DataT> *> GetSeZone();
  std::optional<Node<DataT> *> ChoosingPath(const Point &point) noexcept;
  const Quadrant &GetQuadrant() const noexcept;
  DataT &Data();
};

template <typename DataT>
Node<DataT>::Node(const class Quadrant &quadrant) noexcept
    : quadrant(quadrant), zones{nullptr, nullptr, nullptr, nullptr} {}

template <typename DataT> Node<DataT>::~Node() noexcept {
  DestroyChildrenZones();
}

//Создает 4 потомственные зоны
template <typename DataT> void Node<DataT>::SpawnChildrenZone() noexcept {
  zones[nwZoneIndex] = new Node<DataT>(quadrant.CreateNwChildrenQuadrant());
  zones[neZoneIndex] = new Node<DataT>(quadrant.CreateNeChildrenQuadrant());
  zones[swZoneIndex] = new Node<DataT>(quadrant.CreateSwChildrenQuadrant());
  zones[seZoneIndex] = new Node<DataT>(quadrant.CreateSeChildrenQuadrant());
}

//Уничтожает поддерево теущего узла
template <typename DataT> void Node<DataT>::DestroyChildrenZones() noexcept {
  for (auto &zone : zones) {
    delete zone;
  }
}

//Возвращает квадрант
template <typename DataT>
const Quadrant &Node<DataT>::GetQuadrant() const noexcept {
  return quadrant;
}

//Возвращает ссылку на данные
template <typename DataT> DataT &Node<DataT>::Data() { return data; }

//Принимает на вход точку, определяет в каком подквадранте находится эта тчока
//В случае, если подквадрант существует, возвращает его, если нет - nullopt
template <typename DataT>
std::optional<Node<DataT> *>
Node<DataT>::ChoosingPath(const Point &point) noexcept {
  assert(quadrant[point] == true && "Point outside quadrant");
  const Point &center = quadrant.Center();
  if (point.first >= center.first && point.second <= center.second)
    return GetNwZone();
  else if (point.first >= center.first && center.second >= center.second)
    return GetNeZone();
  else if (point.first <= center.first && point.second <= center.second)
    return GetSwZone();
  else if (point.first <= center.first && point.second >= center.second)
    return GetSeZone();
}

//Проверка, есть ли у ноды наследники
template <typename DataT> bool Node<DataT>::ChildrenZones() {
  if (zones[nwZoneIndex] == nullptr)
    return false;
  else
    return true;
}

template <typename DataT>
std::optional<Node<DataT> *> Node<DataT>::GetNwZone() {
  if (zones[nwZoneIndex] == nullptr)
    return std::nullopt;
  else
    return {zones[nwZoneIndex]};
}

template <typename DataT>
std::optional<Node<DataT> *> Node<DataT>::GetNeZone() {
  if (zones[neZoneIndex] == nullptr)
    return std::nullopt;
  else
    return {zones[neZoneIndex]};
}

template <typename DataT>
std::optional<Node<DataT> *> Node<DataT>::GetSwZone() {
  if (zones[swZoneIndex] == nullptr)
    return std::nullopt;
  else
    return {zones[swZoneIndex]};
}

template <typename DataT>
std::optional<Node<DataT> *> Node<DataT>::GetSeZone() {
  if (zones[seZoneIndex] == nullptr)
    return std::nullopt;
  else
    return {zones[seZoneIndex]};
}

} // namespace QuadTree