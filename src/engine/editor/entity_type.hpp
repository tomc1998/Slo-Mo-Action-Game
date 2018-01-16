#pragma once

#include "engine/ecs.hpp"

/** This class groups together a list of components for usage with the
 * editor. This allows entity 'templates' to be created and saved, then
 * reused with minimal changes (i.e. changing position). These are
 * normally used through the entity_type_manager, which provides a method
 * of persisting entity types. 
 *
 * Any components inserted into this class will be deleted when this
 * class's destructor is called. */
class EntityType {
public:
  EntityType();
  ~EntityType();
  EntityType(const EntityType &t);
  EntityType &operator=(EntityType other);
  friend void swap(EntityType &first, EntityType &second);

#define X(TYPE, NAME) TYPE *NAME = NULL;
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
};
