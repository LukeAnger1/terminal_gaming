// CREDIT: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//   Sets up raw mode for terminal input and gameplay

#include <ctype.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "render/screen.cpp"
#include "render/render_wrapper.cpp"
#include "utils/program_control.cpp"

int main() {
  enableRawMode();

// Notify the user if in debug mode
#if DEBUG == 1
  std::cout << "In debug mode\n";
#else
  // std::cout << "Not in debug mode\n";
#endif

  // Render wrapper for rendering graphics
  render_wrapper render_wrapper;

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
      endProgram("read");
    read(STDIN_FILENO, &c, 1);

    // TODO: Add in macros for the change in camera to easily change
    // TODO: Change the x/y/z into a custom type that is a float
    // TODO: Clear the screen between calls
    // TODO: Add in logic to get the proper screen size for the terminal

    // Move the camera translare around with wasd
    if (c == 'a') {
      render_wrapper.move_camera(-1, 0, 0, 0, 0);
    }
    if (c == 'd') {
      render_wrapper.move_camera(1, 0, 0, 0, 0);
    }
    if (c == 'w') {
      render_wrapper.move_camera(0, -1, 0, 0, 0);
    }
    if (c == 's') {
      render_wrapper.move_camera(0, 1, 0, 0, 0);
    }

    // Move the camera rotate with ijkl
    if (c == 'i') {
      render_wrapper.move_camera(0, 0, 0, -.01, 0);
    }
    if (c == 'j') {
      render_wrapper.move_camera(0, 0, 0, .01, 0);
    }
    if (c == 'k') {
      render_wrapper.move_camera(0, 0, 0, 0, -.01);
    }
    if (c == 'l') {
      render_wrapper.move_camera(0, 0, 0, 0, .01);
    }

    render_wrapper.render();

    if (c == 'q')
      break;
  }

  return 0;
}
