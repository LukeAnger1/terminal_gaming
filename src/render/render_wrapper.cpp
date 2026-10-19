#include <vector>

#include "camera.cpp"
#include "screen.cpp"
#include "obj/triangle.cpp"
#include "obj/object.cpp"

class render_wrapper {
public:
  render_wrapper() {

    // TODO: Clean this up some
    Triangle triangle{Point(10, 10, 0), Point(2, 1, 0), Point(100, 2, 0)};
    Object object{{triangle}};
    objects.push_back(object);
  }

  void add_object() {
    // TODO: Implement this or decide if we need this
  }

  void move_camera() {
    // TODO: Implement this later
  }

  void render() {
    // Update the frame buffer
    screen.update_screen([&objs = objects](int x, int y) {
      // Iterate through the triangles
      for (const Object& obj : objs) {
        // Check if the point is in the triangle
        if (obj.contains(x, y)) {

          // Short circuit to return 'h'
          return 'O';
        }
      }

      return ' ';
    });

    // Print the frame buffer
    screen.print_screen();
  }

private:
  std::vector<Object> objects;
  Screen screen;
  Camera camera;
};
