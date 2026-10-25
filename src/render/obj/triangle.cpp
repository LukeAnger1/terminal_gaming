#include "point.cpp"

#pragma once

// This macro for how close the detection has to be
//   Adding this in because when the triangle is viewed to be a line,
//     it glitches into a line
#define EPS_EDGE_DETECTION .25

class Triangle {
public:
  constexpr Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {

#if DEBUG == 1

#endif
  }

  bool contains(int x, int y) const {
    int side_ab = edge(a, b, x, y);
    int side_bc = edge(b, c, x, y);
    int side_ca = edge(c, a, x, y);

    bool all_positive = side_ab >= EPS_EDGE_DETECTION && side_bc >= EPS_EDGE_DETECTION && side_ca >= EPS_EDGE_DETECTION;
    bool all_negative = side_ab <= -EPS_EDGE_DETECTION && side_bc <= -EPS_EDGE_DETECTION && side_ca <= -EPS_EDGE_DETECTION;

    return all_positive || all_negative;
  }

private:
  // sign says what side of the line, 0 means on the line
  static int edge(const Point &from, const Point &to, int x, int y) {
    int edge_x = to.get_x() - from.get_x();
    int edge_y = to.get_y() - from.get_y();
    int point_x = x - from.get_x();
    int point_y = y - from.get_y();

    return edge_x * point_y - edge_y * point_x;
  }

  Point a, b, c;
};
