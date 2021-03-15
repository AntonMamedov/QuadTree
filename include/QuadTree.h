#include "Node.h"
#include <functional>
#include <stack>
namespace QuadTree {
template <typename DataT> class QuadTree {
private:
  Node<DataT> *root;
  size_t deep;

private:
  std::optional<Node<DataT> *> GoToTheLastLevel(const Point &point,
                                                Node<DataT> *current,
                                                size_t currentDeep);

public:
  explicit QuadTree(size_t deep);
  void Update(const Point &point, std::function<void(DataT &data)>);
  void Update(const Point &point,
              std::function<void(DataT &data, const Quadrant &)>);
};

template <typename DataT>
QuadTree<DataT>::QuadTree(size_t deep) : deep(deep), root(nullptr) {}

//Создает новую ноду, соотвутствущую указанной точке и вызывает в этой ноде
// callback Если нода уже созданна, то просто вызывается callback
template <typename DataT>
void QuadTree<DataT>::Update(const Point &point,
                             std::function<void(DataT &)> handler) {
  std::optional<Node<DataT> *> current = GoToTheLastLevel(point, root, 0);
  if (current) {
    handler(current.value()->Data());
  }
}
template <typename DataT>
void QuadTree<DataT>::Update(const Point &point,
                             std::function<void(DataT &, const Quadrant &)>) {}
template <typename DataT>
std::optional<Node<DataT> *>
QuadTree<DataT>::GoToTheLastLevel(const Point &point, Node<DataT> *current,
                                  size_t currentDeep) {
  if (current->GetQuadrant()[point]) {
    for (size_t i = currentDeep; i < deep; i++) {
      if (!current->ChildrenZones())
        current->ChildrenSpawn();
      current = current->ChoosingPath(point);
    }
    return current;
  } else
    return std::nullopt;
}

} // namespace QuadTree