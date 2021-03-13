#include "../include/Quadrant.h"
#include "gtest/gtest.h"

TEST(Quadrant, TestСonstructorAndGetFuncs) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  ASSERT_EQ(nw, quadrant.NorthWest());
  ASSERT_EQ(ne, quadrant.NorthEast());
  ASSERT_EQ(sw, quadrant.SouthWest());
  ASSERT_EQ(se, quadrant.SouthEast());
}

TEST(Quadrant, TestGetCenter) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point center;
  ASSERT_EQ(center, quadrant.Center());
}

TEST(Quadrant, TestMidNorth) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midNorth(nw.first, (nw.second + ne.second) / 2);
  ASSERT_EQ(midNorth, quadrant.MidNorth());
}

TEST(Quadrant, TestMidSouth) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midSouth(sw.first, (sw.second + se.second) / 2);
  ASSERT_EQ(midSouth, quadrant.MidSouth());
}

TEST(Quadrant, TestMidWest) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midWest((sw.first + nw.first) / 2, sw.second);
  ASSERT_EQ(midWest, quadrant.MidWest());
}

TEST(Quadrant, TestMidEast) {
  const QuadTree::Point nw(90, -180);
  const QuadTree::Point ne(90, 180);
  const QuadTree::Point sw(-90, -180);
  const QuadTree::Point se(-90, 180);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midEast((se.first + ne.first) / 2, se.second);
  ASSERT_EQ(midEast, quadrant.MidEast());
}