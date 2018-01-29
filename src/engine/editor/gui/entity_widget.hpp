#pragma once
#include <string>
#include "engine/editor/entity_type.hpp"

class GuiContext;
class EditorInput;
class Rect;

/** A widget which renders an entity in a little box, with its name below. */
class EntityWidget {
public:
  /** A reference to the entity type we're rendering */
  const EntityType *entity_type;
  /** The name of the entity type we're rendering. Limited to 32 chars because
   * fuck it - std::string requires move constructors for certain stl
   * containers, this is more efficient and simpler. */
  char entity_name[32];

  EntityWidget(const EntityType *entity_type, const char* entity_name);
  void update_paint(GuiContext &c, const Rect &rect, const EditorInput &input);
};
