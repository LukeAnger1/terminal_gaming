// CREDIT: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//   Sets up raw mode for terminal input and gameplay

#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream>

struct termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

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
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
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

// #include <SFML/Graphics.hpp>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen())
//     {
//         while (const std::optional event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }
// }

// #include "user_input/BufferToggle.hpp"

// int main() {

//     // BEGIN CREDIT: https://cplusplus.com/forum/general/29137/
//     BufferToggle bt;
//     std::getchar(); //waits for you to press enter before proceeding to the next instruction
//     bt.off();
//     std::getchar(); //processes next instruction as soon as you type a character (no enter)
//     bt.on();
//     std::getchar(); //waits for you to press enter before proceeding to the next instructionhttps://cplusplus.com/forum/general/29137/
//     // END CREDIT
// }
