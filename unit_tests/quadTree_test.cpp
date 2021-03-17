#include "QuadTree.h"
#include "test_const.h"
#include "gtest/gtest.h"

const size_t deep = 14;

TEST(QuadTree, TestUodateWithCorrectPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::QuadTree<int> quadTree(deep, quadrant);
  quadTree.Update(nw, [](int& data){
    data = 5;
  });
}