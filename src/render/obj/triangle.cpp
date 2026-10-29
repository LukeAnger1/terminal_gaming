#include <cmath>

#pragma once

#include "point.cpp"
#include "triangle.cpp"

// TODO: Change this to use the angle from camera
typedef float angle;

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

    bool all_positive = side_ab >= EPS_EDGE_DETECTION &&
                        side_bc >= EPS_EDGE_DETECTION &&
                        side_ca >= EPS_EDGE_DETECTION;
    bool all_negative = side_ab <= -EPS_EDGE_DETECTION &&
                        side_bc <= -EPS_EDGE_DETECTION &&
                        side_ca <= -EPS_EDGE_DETECTION;

    return all_positive || all_negative;
  }

  bool contains(int camera_x, int camera_y, int camera_z, angle camera_roll,
                angle camera_pitch, int x, int y) const {
    // Translate the points based on the camera
    int dx = x - camera_x;
    int dy = y - camera_y;
    int dz = -camera_z;

    // Rotate the points based on the camera
    //   Undo pitch (about the y axis)
    int x1 = cos(camera_pitch) * dx + sin(camera_pitch) * dz;
    int y1 = dy;
    int z1 = -sin(camera_pitch) * dx + cos(camera_pitch) * dz;
    //   Undo roll (about the x axis)
    int depth = x1;
    int right = cos(camera_roll) * y1 + sin(camera_roll) * z1;
    int up = -sin(camera_roll) * y1 + cos(camera_roll) * z1;

    return contains(right, up);
  }

  Point get_center() const {
    int x = (a.get_x() + b.get_x() + c.get_x()) / 3;
    int y = (a.get_y() + b.get_y() + c.get_y()) / 3;
    int z = (a.get_z() + b.get_z() + c.get_z()) / 3;

    return Point{x, y, z};
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
