#pragma once

class GuiContext;
class Rect;
typedef Rect BoxConstraints;

/** Paint a panel at the given position. The box constraints cannot be
 * unconstrained. */
Rect paint_panel(GuiContext &c, const BoxConstraints& rect);
