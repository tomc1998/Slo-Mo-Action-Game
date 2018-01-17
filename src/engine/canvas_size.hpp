/** This is a header file to define constant sizes. When rendering the
 * game we will render to a fixed screen size (i.e. 1066x600), then change
 * the GL viewport before making the draw calls. 
 *
 * These value are not only nice to have constants of, but are used for
 * transforming input coords to the viewport screen coords.
 *
 * 1066x600 is 16/9.
 * 800x600 is 4/3.
 */

#pragma once 

const i32 CANVAS_W = 1066;
const i32 CANVAS_H = 600;
const f32 CANVAS_ASPECT = CANVAS_W/CANVAS_H;
