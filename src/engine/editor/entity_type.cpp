#include "engine/ecs.hpp"
#include "entity_type.hpp"
#include <cstdlib>

EntityType::EntityType() {}

EntityType::~EntityType() {
#define X(TYPE, NAME)                                                          \
  if (NAME) {                                                                  \
    delete NAME;                                                               \
  }
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
}

EntityType::EntityType(const EntityType &t) {
#define X(TYPE, NAME) if (t.NAME != NULL) { \
  NAME = (TYPE*) malloc(sizeof(TYPE)); \
  *NAME = *t.NAME; \
}
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
}

EntityType &EntityType::operator=(EntityType other) {
  swap(*this, other);
  return *this;
}

void swap(EntityType &first, EntityType &second) {
  using std::swap;
#define X(TYPE, NAME) swap(first.NAME, second.NAME);
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
}

