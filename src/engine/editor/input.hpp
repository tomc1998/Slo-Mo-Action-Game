#pragma once

/**
 * A singleton class for editor input. This is separate to the normal in-game
 * input state, as we don't need keybindings for this, and we want the game
 * input state to remain relatively bloat-free. 
 *
 * See instance member to get an instance of this editor input.
 */
class EditorInput {
  private:
    EditorInput();

  public:
    static EditorInput* instance;

    /** This should be called from the glfw input callback function. */
    void key_input(int key, int scancode, int action, int mods);

    /** This should be called from the glfw input callback function. Should be
     * transformed onto the viewport.*/
    void cursor_pos_input(double xpos, double ypos);

    /** This should be called from the glfw input callback function. */
    void mouse_input(int button, int action, int mods);
};
