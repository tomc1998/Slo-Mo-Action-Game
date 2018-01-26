#pragma once
#include <string>

class GuiContext;
class EditorInput;
class Rect;
class EntityType;

/** A widget which renders an entity in a little box, with its name below. */
class EntityWidget {
public:
  /** A reference to the entity type we're rendering */
  EntityType* entity_type;
  /** The name of the entity type we're rendering */
  std::string* entity_name;

  EntityWidget(EntityType* entity_type, std::string* entity_name);
  void update_paint(GuiContext &c, const Rect &rect, const EditorInput &input);
};
