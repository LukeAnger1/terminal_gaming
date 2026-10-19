#include <vector>

#include "camera.cpp"
#include "screen.cpp"
#include "obj/triangle.cpp"

// TODO: Remove this
//   This is a test function to develop the render
char test_function(int x, int y) {
  return x<3? 'a':'b';
}

class render_wrapper {
public:
  render_wrapper() {

    // TODO: Remove this test triangle
    triangles.push_back(Triangle(Point(10, 10, 0), Point(2, 1, 0), Point(100, 2, 0)));
  }

  void add_object() {
    // TODO: Implement this or decide if we need this
  }

  void move_camera() {
    // TODO: Implement this later
  }

  void render() {
    // Update the frame buffer
    screen.update_screen([&tris = triangles](int x, int y) {
      // Iterate through the triangles
      for (const auto& triangle : tris) {
        // Check if the point is in the triangle
        if (triangle.contains(x, y)) {

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
  std::vector<Triangle> triangles; // TODO: Update this for generic objs?
  Screen screen;
  Camera camera;
};
