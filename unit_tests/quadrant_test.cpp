#include "../include/Quadrant.h"
#include "gtest/gtest.h"

const double n = 90;
const double w = -180;
const double s = -90;
const double e = 180;
const double center = 0;

TEST(Quadrant, TestСonstructorAndGetFuncs) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  ASSERT_EQ(nw, quadrant.NorthWest());
  ASSERT_EQ(ne, quadrant.NorthEast());
  ASSERT_EQ(sw, quadrant.SouthWest());
  ASSERT_EQ(se, quadrant.SouthEast());
}

TEST(Quadrant, TestGetCenter) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point center;
  ASSERT_EQ(center, quadrant.Center());
}

TEST(Quadrant, TestMidNorth) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midNorth(nw.first, (nw.second + ne.second) / 2);
  ASSERT_EQ(midNorth, quadrant.MidNorth());
}

TEST(Quadrant, TestMidSouth) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midSouth(sw.first, (sw.second + se.second) / 2);
  ASSERT_EQ(midSouth, quadrant.MidSouth());
}

TEST(Quadrant, TestMidWest) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midWest((sw.first + nw.first) / 2, sw.second);
  ASSERT_EQ(midWest, quadrant.MidWest());
}

TEST(Quadrant, TestMidEast) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point midEast((se.first + ne.first) / 2, se.second);
  ASSERT_EQ(midEast, quadrant.MidEast());
}

TEST(Quadrant, TestNorthWestChildren) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant nwChildren(nw, {n, center}, {center, w}, {center, center});
  ASSERT_EQ(quadrant.CreateNwChildrenQuadrant(), nwChildren);
}

TEST(Quadrant, TestNorthEastChildren) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant neChildren({n, center}, ne, {center, center}, {center, e});
  ASSERT_EQ(quadrant.CreateNeChildrenQuadrant(), neChildren);
}

TEST(Quadrant, TestSouthWestChildren) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant swChildren({center, w}, {center, center}, sw, {s, center});
  ASSERT_EQ(quadrant.CreateSwChildrenQuadrant(), swChildren);
}

TEST(Quadrant, TestSouthEastChildren) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  QuadTree::Quadrant seChildren({center, center}, {center, e}, {s, center}, se);
  ASSERT_EQ(quadrant.CreateSeChildrenQuadrant(), seChildren);
}

TEST(Quadrant, TestingPointsIncludedInTheQuadrant) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
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

TEST(Quadrant, TestingBorderИorthPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(90, 36);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestingBorderSouthPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-90, 36);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestingBorderWestPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-78, -180);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestingBorderEastPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-78, 180);
  ASSERT_EQ(true, quadrant[p1]);
}

TEST(Quadrant, TestingOutNorthPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(91, 180);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestingOutSouthPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(-91, 180);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestingOutWestPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(80, -181);
  ASSERT_EQ(false, quadrant[p1]);
}

TEST(Quadrant, TestingOutEastPoint) {
  const QuadTree::Point nw(n, w);
  const QuadTree::Point ne(n, e);
  const QuadTree::Point sw(s, w);
  const QuadTree::Point se(s, e);
  QuadTree::Quadrant quadrant(nw, ne, sw, se);
  const QuadTree::Point p1(91, 181);
  ASSERT_EQ(false, quadrant[p1]);
}
