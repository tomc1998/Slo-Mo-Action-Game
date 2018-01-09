#include "engine/ecs.hpp"
#include "engine/color.hpp"
#include "engine/vec.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "paint_system.hpp"
#include "engine/renderer/vertex.hpp"
#include "globals.hpp"
#include <vector>

class SystemTilemapRenderer : public PaintSystem {
public:
  void handle_components(Globals &globals) {
    const auto& ecs = globals.ecs;
    const auto& paint_controller = globals.paint_controller;
    Color white = Color(1.0, 1.0, 1.0, 1.0);

    // Loop through and generate vertices for each tilemap
    for (const auto& tilemap : ecs->comp_tilemap) {
      paint_controller->draw_tilemap(tilemap, &white);
    }
  }
};
