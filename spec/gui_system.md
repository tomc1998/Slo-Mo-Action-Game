# The GUI system
What follows is a description of the GUI system for the editor. It's clear
we need a GUI system, as doing things through simply popups and
keybindings is simply infeasible given the complexity of the engine
layout.

## Widget system
There will be no widget base class, as the naive implementation would give.
Most functionality will be achieved through templates - that is, IF templates
are needed.

Conceptually there are 2 widget types - atomic widgets, and container
widgets. 

Atomic widgets are items like checkboxes, or text boxes - things
which only take data and produce a visual representation. These will probably
not (and probably should not) feature type parameters.

Container widgets are items like scrollboxes, or floating windows - they
have a visual representation and data, but they also need to contain user
defined widgets. These container widgets will normally be templated with
the child / children values.

## Painting widgets
All widgets define the same `update_paint` method. This is called to check
for input, then update & paint the widget. It takes a paint controller,
rectangle to draw in, and an input object, and is responsible for updating its
own state based on the input. It is also responsible for positioning / updating
/ painting child widgets.

## Character input buffer
Some elements of the GUI need to support text input. The EditorInput struct
will provide a character buffer, which is essentially a queue of characters
entered by the user in that frame (probably just a statically sized array, no
need to go crazy with heap allocation here).

Widgets can choose to read characters from the buffer. They will probably
do this if 'focused' (determined by that widget). Doing so will NOT consume
the characters (the buffer should remain unmodified for all other widgets).

## Helper paint methods
Sometimes you might want to paint a complex structure which needs to retain no
state and not react to any input. In this case, instead of creating a
widget, you can just create a function which takes in a paint_controller and
a size. This is useful for stuff like window or panel backgrounds - you might
need to draw a panel background many times, but having to create a 'panel'
object and specify children etc is cumbersome.
