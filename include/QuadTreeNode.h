#pragma once
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
  bool children;

public:
  explicit Node(const Quadrant &quadrant) noexcept;
  ~Node();
  void SpawnChildrenZone() noexcept;
};

template <typename DataT>
Node<DataT>::Node(const Quadrant &quadrant) noexcept
    : quadrant(quadrant), zones{nullptr, nullptr, nullptr, nullptr},
      children(false) {}

//Создает 4 потомственные зоны
template <typename DataT> void Node<DataT>::SpawnChildrenZone() noexcept {
  zones[nwZoneIndex] = new Node<DataT>(quadrant.CreateNwChildrenQuadrant());
  zones[neZoneIndex] = new Node<DataT>(quadrant.CreateNwChildrenQuadrant());
  zones[swZoneIndex] = new Node<DataT>(quadrant.CreateNwChildrenQuadrant());
  zones[seZoneIndex] = new Node<DataT>(quadrant.CreateNwChildrenQuadrant());
}
template <typename DataT> Node<DataT>::~Node() {
  for (auto &zone : zones) {
    delete zone;
  }
}

} // namespace QuadTree