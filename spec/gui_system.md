# The GUI system

What follows is a description of the GUI system for the editor. It's clear
we need a GUI system, as doing things through simply popups and
keybindings is simply infeasible given the complexity of the engine
layout.

## Component system
There will be no component base class, as the naive implementation would give.
Most functionality will be achieved through templates - that is, IF templates
are needed.

Conceptually there are 2 component types - atomic components, and container
components. 

Atomic components are items like checkboxes, or text boxes - things
which only take data and produce a visual representation. These will probably
not (and probably should not) feature type parameters.

Container components are items like scrollboxes, or floating windows - they
have a visual representation and data, but they also need to contain user
defined components. These container components will normally be templated with
the child / children values.

## Painting components
All components define the same `update_paint` method. This is called to check
for input, then update & paint the component. It takes a paint controller,
rectangle to draw in, and an input object, and is responsible for updating its
own state based on the input. It is also responsible for positioning / updating
/ painting child components.

## Character input buffer
Some elements of the GUI need to support text input. The EditorInput struct
will provide a character buffer, which is essentially a queue of characters
entered by the user in that frame (probably just a statically sized array, no
need to go crazy with heap allocation here).

Components can choose to read characters from the buffer. They will probably
do this if 'focused' (determined by that component). Doing so will NOT consume
the characters (the buffer should remain unmodified for all other components).

