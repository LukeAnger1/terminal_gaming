class Point {
public:
  constexpr Point(int x, int y, int z) : x(x), y(y), z(z) {}

  // bool operator==(const Point &other) {
    // NOTE: I dont think I do this becasue the compiler auto generates checks
    // for values in the class
    // return (this->x == other.x) && (this->y);
  // }

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_z() const { return z; }

private:
  int x, y, z;
};
