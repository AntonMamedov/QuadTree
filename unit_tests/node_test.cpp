#include "Node.h"
#include "test_const.h"
#include "gtest/gtest.h"

TEST(Node, TestGetQuadrant) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  ASSERT_EQ(node->GetQuadrant(), quadrant);
  delete node;
}

TEST(Node, TestSpawnChildrenZone) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  ASSERT_EQ(node->ChildrenZones(), true);
  ASSERT_EQ(static_cast<bool>(node->GetNwZone()), true);
  ASSERT_EQ(static_cast<bool>(node->GetNeZone()), true);
  ASSERT_EQ(static_cast<bool>(node->GetSwZone()), true);
  ASSERT_EQ(static_cast<bool>(node->GetSeZone()), true);
  delete node;
}

TEST(Node, TestSpawnNwZone) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  ASSERT_EQ(node->ChildrenZones(), true);
  auto nwZone = node->GetNwZone();
  ASSERT_EQ(static_cast<bool>(nwZone), true);
  ASSERT_EQ(nwZone.value()->GetQuadrant(),
            QuadTree::Quadrant(nw, {n, center}, {center, w}, {center, center}));

  delete node;
}

TEST(Node, TestSpawnNeZone) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  ASSERT_EQ(node->ChildrenZones(), true);
  auto neZone = node->GetNeZone();
  ASSERT_EQ(static_cast<bool>(neZone), true);
  ASSERT_EQ(neZone.value()->GetQuadrant(),
            QuadTree::Quadrant({n, center}, ne, {center, center}, {center, e}));
  delete node;
}

TEST(Node, TestSpawnSwZone) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  ASSERT_EQ(node->ChildrenZones(), true);
  auto swZone = node->GetSwZone();
  ASSERT_EQ(static_cast<bool>(swZone), true);
  ASSERT_EQ(swZone.value()->GetQuadrant(),
            QuadTree::Quadrant({center, w}, {center, center}, sw, {s, center}));
  delete node;
}

TEST(Node, TestSpawnSeZone) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  ASSERT_EQ(node->ChildrenZones(), true);
  auto seZone = node->GetSeZone();
  ASSERT_EQ(static_cast<bool>(seZone), true);
  ASSERT_EQ(seZone.value()->GetQuadrant(),
            QuadTree::Quadrant({center, center}, {center, e}, {s, center}, se));
  delete node;
}

TEST(Node, TestChoizNorthWestPath) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  auto nwZone = node->ChoosingPath(nw);
  ASSERT_EQ(nwZone.value()->GetQuadrant(),
            QuadTree::Quadrant(nw, {n, center}, {center, w}, {center, center}));
  delete node;
}

TEST(Node, TestChoizNorthEastPath) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  auto neZone = node->ChoosingPath(ne);
  ASSERT_EQ(neZone.value()->GetQuadrant(),
            QuadTree::Quadrant({n, center}, ne, {center, center}, {center, e}));
  delete node;
}

TEST(Node, TestChoizSouthWestPath) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  auto swZone = node->ChoosingPath(sw);
  ASSERT_EQ(swZone.value()->GetQuadrant(),
            QuadTree::Quadrant({center, w}, {center, center}, sw, {s, center}));
  delete node;
}

TEST(Node, TestChoizSouthEastPath) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  auto node = new QuadTree::Node<int>(quadrant);
  node->SpawnChildrenZone();
  auto seZone = node->ChoosingPath(se);
  ASSERT_EQ(seZone.value()->GetQuadrant(),
            QuadTree::Quadrant({center, center}, {center, e}, {s, center}, se));
  delete node;
}
