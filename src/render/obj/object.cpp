#include <vector>

#include "triangle.cpp"

class Object {
public:

  // TODO: change this constructor to either copy or something else
  Object(std::vector<Triangle> triangles) {
    this->triangles = triangles;
  }

    bool contains(int x, int y) const {
    // Cycle through each triangle,
    //   if there is a hit then it is true
    //   else it is a false
    for (const Triangle& triangle : triangles) {
      if (triangle.contains(x, y)) {
        return true;
      }
    }
    return false;
  }

  bool contains(int camera_x, int camera_y, int camera_z, angle camera_roll, angle camera_pitch, int x, int y) const {
    // Cycle through each triangle,
    //   if there is a hit then it is true
    //   else it is a false
    for (const Triangle& triangle : triangles) {
      if (triangle.contains(camera_x, camera_y, camera_z, camera_roll, camera_pitch, x, y)) {
        return true;
      }
    }
    return false;
  }

private:
  std::vector<Triangle> triangles;
};
