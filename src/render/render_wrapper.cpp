#include <vector>

#include "camera.cpp"
#include "obj/object.cpp"
#include "obj/triangle.cpp"
#include "screen.cpp"

// Square parameters
//   TODO: Remove this later
#define SQUARE_WIDTH 10
#define SQUARE_OFFSET 10

static constexpr Point bottom_1{SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET};
static constexpr Point bottom_2{SQUARE_OFFSET, SQUARE_OFFSET,
                                SQUARE_OFFSET + SQUARE_WIDTH};
static constexpr Point bottom_3{SQUARE_OFFSET, SQUARE_OFFSET + SQUARE_WIDTH,
                                SQUARE_OFFSET};
static constexpr Point bottom_4{SQUARE_OFFSET, SQUARE_OFFSET + SQUARE_WIDTH,
                                SQUARE_OFFSET + SQUARE_WIDTH};
static constexpr Point top_1{SQUARE_OFFSET + SQUARE_WIDTH, SQUARE_OFFSET,
                             SQUARE_OFFSET};
static constexpr Point top_2{SQUARE_OFFSET + SQUARE_WIDTH, SQUARE_OFFSET,
                             SQUARE_OFFSET + SQUARE_WIDTH};
static constexpr Point top_3{SQUARE_OFFSET + SQUARE_WIDTH,
                             SQUARE_OFFSET + SQUARE_WIDTH, SQUARE_OFFSET};
static constexpr Point top_4{SQUARE_OFFSET + SQUARE_WIDTH,
                             SQUARE_OFFSET + SQUARE_WIDTH,
                             SQUARE_OFFSET + SQUARE_WIDTH};

static constexpr Triangle triangle_top_1{top_1, top_2, top_3};
static constexpr Triangle triangle_top_2{top_1, top_4, top_3};
static constexpr Triangle triangle_front_1{bottom_1, top_2, top_1};
static constexpr Triangle triangle_front_2{bottom_1, top_2, bottom_2};
static constexpr Triangle triangle_side_1{bottom_2, top_3, top_2};
static constexpr Triangle triangle_side_2{bottom_2, top_3, bottom_3};

#define SQUARE_WIDTH_2 10
#define SQUARE_OFFSET_2 20

static constexpr Point bottom2_1{SQUARE_OFFSET_2, SQUARE_OFFSET_2,
                                 SQUARE_OFFSET_2};
static constexpr Point bottom2_2{SQUARE_OFFSET_2, SQUARE_OFFSET_2,
                                 SQUARE_OFFSET_2 + SQUARE_WIDTH_2};
static constexpr Point bottom2_3{
    SQUARE_OFFSET_2, SQUARE_OFFSET_2 + SQUARE_WIDTH_2, SQUARE_OFFSET_2};
static constexpr Point bottom2_4{SQUARE_OFFSET_2,
                                 SQUARE_OFFSET_2 + SQUARE_WIDTH_2,
                                 SQUARE_OFFSET_2 + SQUARE_WIDTH_2};
static constexpr Point top2_1{SQUARE_OFFSET_2 + SQUARE_WIDTH_2, SQUARE_OFFSET_2,
                              SQUARE_OFFSET_2};
static constexpr Point top2_2{SQUARE_OFFSET_2 + SQUARE_WIDTH_2, SQUARE_OFFSET_2,
                              SQUARE_OFFSET_2 + SQUARE_WIDTH_2};
static constexpr Point top2_3{SQUARE_OFFSET_2 + SQUARE_WIDTH_2,
                              SQUARE_OFFSET_2 + SQUARE_WIDTH_2,
                              SQUARE_OFFSET_2};
static constexpr Point top2_4{SQUARE_OFFSET_2 + SQUARE_WIDTH_2,
                              SQUARE_OFFSET_2 + SQUARE_WIDTH_2,
                              SQUARE_OFFSET_2 + SQUARE_WIDTH_2};

static constexpr Triangle triangle_top2_1{top2_1, top2_2, top2_3};
static constexpr Triangle triangle_top2_2{top2_1, top2_4, top2_3};
static constexpr Triangle triangle_front2_1{bottom2_1, top2_2, top2_1};
static constexpr Triangle triangle_front2_2{bottom2_1, top2_2, bottom2_2};
static constexpr Triangle triangle_side2_1{bottom2_2, top2_3, top2_2};
static constexpr Triangle triangle_side2_2{bottom2_2, top2_3, bottom2_3};

class render_wrapper {
public:
  render_wrapper() {

    Object object{{triangle_top_1, triangle_top_2, triangle_front_1,
                   triangle_front_2, triangle_side_1, triangle_side_2},
                  'X'};

    Object object2{{triangle_top2_1, triangle_top2_2, triangle_front2_1,
                    triangle_front2_2, triangle_side2_1, triangle_side2_2},
                   'O'};

    objects.push_back(object);
    objects.push_back(object2);
  }

  void add_object() {
    // TODO: Implement this or decide if we need this
  }

  void move_camera(int dx, int dy, int dz, angle d_roll, angle d_pitch) {
    // TODO: Add in z movement
    camera.translate_camera_2d(dx, dy);

    camera.rotate_camera(d_roll, d_pitch);
  }

  void render() {
    // TODO: Add in logic to sort triangles based on distance
    //   Make sure the closest ones appear closer
    //   Make sure to drop the ones that are behind the camera

    // Update the frame buffer
    screen.update_screen([&objs = objects, &camera = camera](int x, int y) {
      // Iterate through the triangles
      for (const Object &obj : objs) {
        // Check if the point is in the triangle
        if (obj.contains(camera.get_x(), camera.get_y(), camera.get_z(),
                         camera.get_roll(), camera.get_pitch(), x, y)) {

          // Short circuit to return 'h'
          // TODO: Sort the objects
          //   There is currently no sorting, we need to add in sorting
          return obj.get_render_char();
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
