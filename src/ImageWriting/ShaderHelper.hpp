#pragma once

#include <fstream>
#include <glad/glad.h>
#include <sstream>

namespace Sindri
{
  auto
  LoadFile(const std::string& path) -> std::string
  {
    std::ifstream     file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

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