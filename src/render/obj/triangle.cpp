#include "point.cpp"

#pragma once

class Triangle {
public:
  Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {

#if DEBUG == 1

#endif
  }

  // Check if the screen point (x, y) is inside the triangle (z is ignored)
  //   Idea: walk around the edges a->b, b->c, c->a. If the point is on the
  //   same side of all three edges, it is inside.
  bool contains(int x, int y) const {
    int side_ab = edge(a, b, x, y);
    int side_bc = edge(b, c, x, y);
    int side_ca = edge(c, a, x, y);

    // Inside if all sides agree (all >= 0 or all <= 0)
    //   Checking both lets the corners be listed in either winding order
    //   0 means the point is exactly on an edge, which counts as inside
    bool all_positive = side_ab >= 0 && side_bc >= 0 && side_ca >= 0;
    bool all_negative = side_ab <= 0 && side_bc <= 0 && side_ca <= 0;

    return all_positive || all_negative;
  }

private:
  // Which side of the line from -> to is the point (x, y) on?
  //   This is the 2D cross product of (to - from) and (point - from)
  //   > 0: left side, < 0: right side, 0: on the line
  static int edge(const Point &from, const Point &to, int x, int y) {
    int edge_x = to.get_x() - from.get_x();
    int edge_y = to.get_y() - from.get_y();
    int point_x = x - from.get_x();
    int point_y = y - from.get_y();

    return edge_x * point_y - edge_y * point_x;
  }

  Point a, b, c;
};
