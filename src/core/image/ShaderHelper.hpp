#pragma once

#include <fstream>
#include <glad/glad.h>
#include <sstream>

namespace Sindri
{
  /**
   * @brief Helper function to load a text based file.
   *
   * @param path Path to the file.
   * @return std::string Content of the imported file.
   */
  auto
  LoadFile(const std::string& path) -> std::string
  {
    std::ifstream     file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

  /**
   * @brief Compiles an OpenGL shader.
   *
   * @param type The type of shader (Vertex, Geometry, Fragment, etc.).
   * @param src The source code of the shader.
   * @return GLuint The OpenGL ID of the shader.
   */
  auto
  CompileShader(GLenum type, const char* src) -> GLuint
  {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char log[1024];
      glGetShaderInfoLog(shader, 1024, nullptr, log);
      fprintf(stderr, "Shader compile error: %s\n", log);
    }

    return shader;
  }

  /**
   * @brief Compiles an OpenGL shader program.
   *
   * @param vertexSrc Source of a the vertex shader.
   * @param fragmentSrc Source of a fragment shader.
   * @return GLuint The OpenGL ID of the compiled shader program.
   */
  auto
  CompileShaderProgram(const char* vertexSrc, const char* fragmentSrc) -> GLuint
  {
    GLuint vert = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint frag = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
      char log[1024];
      glGetProgramInfoLog(program, 1024, nullptr, log);
      fprintf(stderr, "Shader link error: %s\n", log);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
  }
}