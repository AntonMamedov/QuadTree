#include "../include/Quadrant.h"
#include "test_const.h"
#include "gtest/gtest.h"

TEST(Quadrant, TestConstructorAndGetFuncs) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  ASSERT_EQ(nw, quadrant.NorthWest());
  ASSERT_EQ(ne, quadrant.NorthEast());
  ASSERT_EQ(sw, quadrant.SouthWest());
  ASSERT_EQ(se, quadrant.SouthEast());
}

TEST(Quadrant, TestGetCenter) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point center;
  ASSERT_EQ(center, quadrant.Center());
}

TEST(Quadrant, TestMidNorth) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midNorth(nw.first, (nw.second + ne.second) / 2);
  ASSERT_EQ(midNorth, quadrant.MidNorth());
}

TEST(Quadrant, TestMidSouth) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midSouth(sw.first, (sw.second + se.second) / 2);
  ASSERT_EQ(midSouth, quadrant.MidSouth());
}

TEST(Quadrant, TestMidWest) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midWest((sw.first + nw.first) / 2, sw.second);
  ASSERT_EQ(midWest, quadrant.MidWest());
}

TEST(Quadrant, TestMidEast) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midEast((se.first + ne.first) / 2, se.second);
  ASSERT_EQ(midEast, quadrant.MidEast());
}

TEST(Quadrant, TestNorthWestChildren) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant nwChildren(nw, {n, center}, {center, w}, {center, center});
  ASSERT_EQ(quadrant.CreateNwChildrenQuadrant(), nwChildren);
}

TEST(Quadrant, TestNorthEastChildren) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant neChildren({n, center}, ne, {center, center}, {center, e});
  ASSERT_EQ(quadrant.CreateNeChildrenQuadrant(), neChildren);
}

TEST(Quadrant, TestSouthWestChildren) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant swChildren({center, w}, {center, center}, sw, {s, center});
  ASSERT_EQ(quadrant.CreateSwChildrenQuadrant(), swChildren);
}

TEST(Quadrant, TestSouthEastChildren) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant seChildren({center, center}, {center, e}, {s, center}, se);
  ASSERT_EQ(quadrant.CreateSeChildrenQuadrant(), seChildren);
}

TEST(Quadrant, TestingPointsIncludedInTheQuadrant) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(89, 36);
  const QuadTree::Point p2(0, 179);
  const QuadTree::Point p3(88, -164);
  const QuadTree::Point p4(-65, 99);
  const QuadTree::Point p5(-78, -168);
  const QuadTree::Point p6(center, center);
  ASSERT_EQ(true, quadrant[p1]);
  ASSERT_EQ(true, quadrant[p2]);
  ASSERT_EQ(true, quadrant[p3]);
  ASSERT_EQ(true, quadrant[p4]);
  ASSERT_EQ(true, quadrant[p5]);
  ASSERT_EQ(true, quadrant[p6]);
}

TEST(Quadrant, TestBorderNorthPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(90, 36);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestBorderSouthPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-90, 36);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestBorderWestPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-78, -180);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestBorderEastPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-78, 180);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestOutNorthPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(91, 180);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestOuntSouthPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-91, 180);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestingOutWestPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(80, -181);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestingOutEastPoint) {
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(91, 181);
  ASSERT_EQ(false, quadrant[p1]);
}
