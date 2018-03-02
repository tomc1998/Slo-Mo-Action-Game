#pragma once

#include "engine/editor/gui/gui.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "scrollable.hpp"
#include "engine/editor/input.hpp"
#include <cassert>

/** A scrollable container. Wrap any component in this to make it scrollable.
 * Wrapped containers will exist in the upper left, and scrolling will start at
 * the top to the bottom / left to the right. */
template <class T> class Scrollable {
public:
  T child;
  /** The amount we've scrolled on the x axis, in screen units */
  f32 scroll_x = 0.0f;
  /** The amount we've scrolled on the y axis, in screen units */
  f32 scroll_y = 0.0f;

  Scrollable(T child);

  /** Cannot be unconstrained */
  Rect update_paint(GuiContext &c, const BoxConstraints &rect,
                    const EditorInput &input);
};

template <class T> Scrollable<T>::Scrollable(T child) : child(child) {}

template <class T>
Rect Scrollable<T>::update_paint(GuiContext &c, const BoxConstraints &rect,
                                 const EditorInput &input) {
  assert(rect.size.x >= 0 && rect.size.y >= 0 &&
         "Painting scrollable unconstrained");
  c.p->push_clip(rect);
  Rect actual_child_size =
      child.update_paint(c, rect.translate(-scroll_x, -scroll_y).unconstrained(), input)
          .translate(scroll_x, scroll_y);
  c.p->pop_clip(NULL);

  return rect;
}
