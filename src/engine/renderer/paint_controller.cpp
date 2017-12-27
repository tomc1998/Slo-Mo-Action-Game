#include "engine/renderer/vertex.hpp"
#include "engine/renderer/paint_controller.hpp"

PaintController::PaintController(PaintBuffer* _buffer) {
  buffer = _buffer;
}

void PaintController::fill_rect(f32 x, f32 y, f32 w, f32 h, Color* color) {
  Vertex v[] = {
    Vertex(Vec2(x, y), color),
    Vertex(Vec2(x+w, y), color),
    Vertex(Vec2(x+w, y+h), color),

    Vertex(Vec2(x, y), color),
    Vertex(Vec2(x, y+h), color),
    Vertex(Vec2(x+w, y+h), color)
  };
  buffer->buffer(v, 6);
}
