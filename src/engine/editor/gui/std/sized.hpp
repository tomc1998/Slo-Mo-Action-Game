#pragma once

#include "engine/editor/gui/gui.hpp"
#include "sized.hpp"
#include <cassert>

/** A sized container. Will size the child to the given w / h. Useful inside
 * unconstrained components, like Scrollable. */
template <class T> class Sized {
public:
  T child;
  f32 w, h;

  Sized(T child, f32 w, f32 h);

  Rect update_paint(GuiContext &c, const BoxConstraints &rect,
                    const EditorInput &input);
};

template <class T>
Sized<T>::Sized(T child, f32 w, f32 h) : child(child), w(w), h(h) {}

template <class T>
Rect Sized<T>::update_paint(GuiContext &c, const BoxConstraints &rect,
                            const EditorInput &input) {
  assert((rect.size.x > w || rect.size.x == -1) &&
         (rect.size.y > h || rect.size.y == -1) && "Sized box overflowing");

  Rect r = rect;
  r.size.x = w;
  r.size.y = h;

  child.update_paint(c, r, input);

  return r;
}
