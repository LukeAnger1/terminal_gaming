#include <vector>

#include "../camera.cpp"
#include "point.cpp"
#include "triangle.cpp"

class Object {
public:
  // TODO: change this constructor to either copy or something else

  // IMPORTANT TODO: Make sure the camera pointer is properly intiailized!!
  // Object(std::vector<Triangle> triangles) {
  //   this->triangles = triangles;
  //   this->render_char = 'O';
  //   this->center = get_center();
  // }

  // Object(std::vector<Triangle> triangles, char render_char) {
  //   this->triangles = triangles;
  //   this->render_char = render_char;
  //   this->center = get_center();
  // }

  Object(std::vector<Triangle> triangles, const Camera &camera,
         char render_char) {
    this->triangles = triangles;
    this->render_char = render_char;
    this->center = get_center();
    this->camera = &camera;
  }

  int get_distance_squared_to_camera() const {
    int camera_x = camera->get_x();
    int camera_y = camera->get_y();
    int camera_z = camera->get_z();

    int our_x = center.get_x();
    int our_y = center.get_y();
    int our_z = center.get_z();

    return (camera_x - our_x) * (camera_x - our_x) +
           (camera_y - our_y) * (camera_y - our_y) +
           (camera_z - our_z) * (camera_z - our_z);
  }

  bool operator<(const Object &other) const {

    // Get our distance to camera center
    int our_distance_squared = get_distance_squared_to_camera();

    // Get other distance to camera center
    int other_distance_squared = other.get_distance_squared_to_camera();

    return our_distance_squared < other_distance_squared;
  }

  bool contains(int x, int y) const {
    // Cycle through each triangle,
    //   if there is a hit then it is true
    //   else it is a false
    for (const Triangle &triangle : triangles) {
      if (triangle.contains(x, y)) {
        return true;
      }
    }
    return false;
  }

  bool contains(int camera_x, int camera_y, int camera_z, angle camera_roll,
                angle camera_pitch, int x, int y) const {
    // Cycle through each triangle,
    //   if there is a hit then it is true
    //   else it is a false
    for (const Triangle &triangle : triangles) {
      if (triangle.contains(camera_x, camera_y, camera_z, camera_roll,
                            camera_pitch, x, y)) {
        return true;
      }
    }
    return false;
  }

  char get_render_char() const { return this->render_char; }

private:
  Point get_center() {
    // Gets the center point from the loaded in triangles
    //   Does not check if the triangles are loaded in
    int sum_x = 0, sum_y = 0, sum_z = 0, count = 0;

    for (const Triangle &triangle : triangles) {
      Point center_point = triangle.get_center();

      sum_x += center_point.get_x();
      sum_y += center_point.get_y();
      sum_z += center_point.get_z();
      count++; // TODO: Change this to the length of triangles
    }

    Point output{sum_x / count, sum_y / count, sum_z / count};

    return output;
  }

  std::vector<Triangle> triangles;
  char render_char;
  Point center;
  Camera const *camera;
};
