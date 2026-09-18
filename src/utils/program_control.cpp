#include <ctype.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#pragma once

void endProgram(const char *s) {
  perror(s);
  exit(1);
}

// Sets up the user input to listen from terminal clicking
// CREDIT: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//   Sets up raw mode for terminal input and gameplay
struct termios orig_termios;

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    endProgram("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    endProgram("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

  // TODO: Look into what this flag does,
  //   currently causes weird indent on the screen output
  // raw.c_oflag &= ~(OPOST);

  raw.c_cflag |= (CS8);

  // NOTE: Flag notes below
  //   ECHO flag makes sure the arrow keys arent typed to terminal
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    endProgram("tcsetattr");
}
