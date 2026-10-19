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

private:
  std::vector<Triangle> triangles;
};
