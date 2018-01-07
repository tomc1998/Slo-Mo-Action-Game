#pragma once

class FontChar {
  /** The uvs in the font texture of this character */
  f32 uvs[4];

  /** The width of the character */
  u32 width;

  /** The height of the character */
  u32 height;

  /** The x offset from the current cursor position when drawing the character
   */
  i32 x_offset;

  /** The y offset from the top of the cell height when drawing the character */
  i32 y_offset;

  /** How far the cursor should move in the x position when drawing the
   * character */
  i32 x_advance;
};
