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
#include "utils/program_control.cpp"

int main() {
  enableRawMode();

// Notify the user if in debug mode
#if DEBUG == 1
  std::cout << "In debug mode\n";
#else
  // std::cout << "Not in debug mode\n";
#endif

  // Testing rendering a screen
  Screen screen;
  screen.set_char(0, 0, 'a');
  screen.set_char(1, 0, 'b');
  screen.set_char(2, 0, 'c');
  screen.print_screen();

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
      endProgram("read");
    read(STDIN_FILENO, &c, 1);
    if (iscntrl(c)) {
      // printf("%d\r\n", c);
    } else {
      // printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q')
      break;
  }

  return 0;
}
