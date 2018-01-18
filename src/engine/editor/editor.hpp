#pragma once
#include "entity_type_manager.hpp"

class ECS;
class Globals;
class Level;

/** An object with logic for rendering the game with editor overlay, and
 * editing the level. The level is stored internally (see the Level class).
 * This level can then be saved and loaded. 
 */
class Editor {
  /** The level we're editing currently. */
  Level* curr_level;
  EntityTypeManager entity_type_manager;

  /** The font to render the editor GUI with */
  FontHandle font;
  public:
    Editor(FontHandle font);
    ~Editor();
    /** Create a new level to edit. The previous level data will be destroyed. */
    void new_level();
    void load_curr_level_into_ecs(ECS& ecs) const;
    Editor& operator=(Editor& other) const;
    /** Call from the engine when you want to display the editor. Will process
     * inputs & render the editor of the current level (using the given
     * paintcontroller). */
    void update_render(Globals& globals);
};
