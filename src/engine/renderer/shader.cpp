#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include "engine/renderer/shader.hpp"
#include "engine/util/io.hpp"

Shader::Shader(
    const char* vert_shader_path, 
    const char* frag_shader_path, 
    std::map<const GLchar*, GLuint> attrib_loc_bindings) {

  // Read the shader src, calculate line lengths
  std::vector<char*> vert_shader_src = load_file_by_lines(vert_shader_path);
  std::vector<char*> frag_shader_src = load_file_by_lines(frag_shader_path);
  std::vector<GLint> vert_shader_src_line_lengths, frag_shader_src_line_lengths;
  for (auto line : vert_shader_src) {
    vert_shader_src_line_lengths.push_back(strlen(line));
  }
  for (auto line : frag_shader_src) {
    frag_shader_src_line_lengths.push_back(strlen(line));
  }


  // Create shaders + attach source
  GLuint vert_shader, frag_shader;
  vert_shader = glCreateShader(GL_VERTEX_SHADER);
  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vert_shader, vert_shader_src.size(), 
      &(vert_shader_src[0]), &(vert_shader_src_line_lengths[0]));
  glShaderSource(frag_shader, frag_shader_src.size(), 
      &(frag_shader_src[0]), &(frag_shader_src_line_lengths[0]));

  // Compile the shaders
  glCompileShader(vert_shader);
  GLint success = 0;
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) { // Handle vert shader compilation errors
    GLint max_len = 0;
    glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &max_len);
    GLchar* err_log = new GLchar[max_len];
    glGetShaderInfoLog(vert_shader, max_len, &max_len, &err_log[0]);
    glDeleteShader(vert_shader);
    throw std::runtime_error(std::string("Failed to compile vertex shader: ") + err_log);
  }

  glCompileShader(frag_shader);
  success = 0;
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) { // Handle frag shader compilation errors
    GLint max_len = 0;
    glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &max_len);
    GLchar* err_log = new GLchar[max_len];
    glGetShaderInfoLog(frag_shader, max_len, &max_len, &err_log[0]);
    glDeleteShader(vert_shader);
    throw std::runtime_error(std::string("Failed to compile fragment shader: ") + err_log);
  }


  // Create the program & attach shaders
  program_id = glCreateProgram();
  glAttachShader(program_id, vert_shader);
  glAttachShader(program_id, frag_shader);

  // Bind attribute locations
  for (auto mapping : attrib_loc_bindings) {
    glBindAttribLocation(program_id, mapping.second, mapping.first);
  }

  GLint is_linked = 0;
  glGetProgramiv(program_id, GL_LINK_STATUS, (int*)&is_linked);
  if(is_linked == GL_FALSE) { // Handle link errors
    GLint max_len = 0;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_len);
    GLchar* err_log = new GLchar[max_len];
    glGetProgramInfoLog(program_id, max_len, &max_len, &err_log[0]);

    glDeleteProgram(program_id);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    throw std::runtime_error(std::string("Failed to link shader program: ") + err_log);
  }

  // Finally, detach the shaders before returning.
  glDetachShader(program_id, vert_shader);
  glDetachShader(program_id, frag_shader);
}
