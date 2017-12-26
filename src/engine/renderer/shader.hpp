#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

/** A class to represent a GLSL shader program. */
class Shader {
  private:
    GLuint program_id;

  public:
    /** 
     * Create a shader from the vertex shader path and the fragment shader
     * path. This will load in the GLSL files, and compile them into a Shader.
     *
     * If there are errors in the shader or loading the file, this will throw a
     * runtime error & print the error to stdout. Don't catch this, the point
     * is to crash the program and provide diagnostics - not to provide a way
     * to handle the issue.
     *
     * @param[in] vert_shader_path The path to the vertex shader.
     * @param[in] frag_shader_path The path to the fragment shader.
     * @param[in] attrib_loc_bindings A mapping of vertex attribute names to
     *                                attribute locations to bind to.
     */
    Shader(
        const char* vert_shader_path, 
        const char* frag_shader_path, 
        std::map<const GLchar*, GLuint> attrib_loc_bindings);
};
