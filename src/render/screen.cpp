#include <array>
#include <iostream>

#include "../utils/program_control.cpp"

#define SCREEN_WIDTH 5
#define SCREEN_HEIGHT 5
#define SCREEN_REP_WIDTH (SCREEN_WIDTH + 1)
#define SCREEN_CHARACTERS (SCREEN_HEIGHT * (SCREEN_REP_WIDTH))

#define NOT_SET_CHAR '0'
#define RETURN '\n'

class Screen {
public:
  Screen() : screen_data(SCREEN_CHARACTERS, NOT_SET_CHAR) {

    // Initialize the screen to have returns in the correct spot
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
      set_char(SCREEN_WIDTH, y, RETURN);
    }
  }

  void set_char(int x, int y, char c) {
    // x goes along the width, more positive x goes right
    // y goes along the height, more positive y goes down

    check_x_y(x, y);

    screen_data[y * SCREEN_REP_WIDTH + x] = c;
  }

  char get_char(int x, int y) {

    check_x_y(x, y);

    return screen_data[y * SCREEN_REP_WIDTH + x];
  }

  void print_screen() { std::cout << screen_data; }

private:
  std::string screen_data;

  void check_x_y(int x, int y) {
// Make sure x and y are in a good range when debugging
#if DEBUG == 1
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
      std::cout << "x=" << x << "\ny=" << y << "\n";
      exit(1);
    }
#endif
  }
};
