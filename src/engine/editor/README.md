# Editor

This folder contains code relevant to editing, saving, and loading levels.

# Notes

We want to be able to construct 'entity types' as collections of components in
the editor, then instantiate them with small customisations.

when actually loading the level, we want it to be performant to add components
(i.e. no 'entity types', just components to add)

We want to be able to save 'entity types' and load them later, i.e. create
libraries of useful entities

## Entity type
Entity type is a list of components, with a create method passing in a *ECS.
The create method initialises the entity with all the values in the ECS.

The entity type defines a copy constructor, allowing the entity type to be
copied and modified.

## Entity type manager
The entity type manager holds a list of entity types. You can register entity
types with the manager under a string name, then request /delete them. This
pattern is to make sure that nobody changes an entity type - they can only
change copies of the entity type.

## Performance notes
The entity type / entity type manager system is NOT performant and shouldn't be
used for loading levels. It involves lots of copies in order to be very
expressive and robust. Performance considerations should still be taken in
order to make level editing a painless experience.
