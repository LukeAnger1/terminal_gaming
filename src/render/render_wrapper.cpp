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
  render_wrapper() : screen(), camera() {}

  void add_object() {
    // TODO: Implement this or decide if we need this
  }

  void move_camera() {
    // TODO: Implement this later
  }

  void render() {
    // Update the frame buffer
    screen.update_screen(test_function);

    // Print the frame buffer
    screen.print_screen();
  }

private:
  Screen screen;
  Camera camera;
};
