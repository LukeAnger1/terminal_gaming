#include "obj/triangle.cpp"

typedef float angle;

class Camera {
public:
  Camera(int x, int y, int z, angle roll, angle pitch)
      : x(x), y(y), z(z), roll(roll), pitch(pitch) {}

  Camera(int x, int y, int z) : x(x), y(y), z(z), roll(0), pitch(0) {}

  Camera() : x(0), y(0), z(0), roll(0), pitch(0) {}

  void translate_camera_2d(int dx, int dy) {
    x += dx;
    y += dy;
  }

  void rotate_camera(const float& d_roll, const float& d_pitch) {
    roll += d_roll;
    pitch += d_pitch;
  }

private:
  // Controls the position of the camera
  int x, y, z;

  // Controls the direction of the camera
  //   Based on the layout
  //   https://www.researchgate.net/publication/279291928/figure/fig1/AS:292533185462272@1446756754388/Orientation-of-the-head-in-terms-of-pitch-roll-and-yaw-movements-describing-the-three.png
  //   roll rotates about the x axis, pitch about the y axis
  //   Camera points in the positive x axis direction
  angle roll, pitch;
};
