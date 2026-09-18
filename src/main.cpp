// CREDIT: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//   Sets up raw mode for terminal input and gameplay

#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include "utils/program_control.cpp"

int main() {
  enableRawMode();

  // Notify the user if in debug mode
  #if DEBUG==1
    std::cout << "In debug mode\n";
  #else
    std::cout << "Not in debug mode\n";
  #endif

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) endProgram("read");
    read(STDIN_FILENO, &c, 1);
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }

  return 0;
}
