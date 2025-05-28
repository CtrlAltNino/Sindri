#include "pch.hpp"

#include "ImageWriting/ShaderHelper.hpp"
#include "TexturePreview.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Sindri
{
  TexturePreview::TexturePreview(
    std::shared_ptr<TextureSettings>    textureSettings,
    std::shared_ptr<ITextureBuffer>     texture,
    std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture)
    : mTextureSettings(std::move(textureSettings))
    , mTexture(std::move(texture))
    , mGpuPreviewTexture(std::move(gpuPreviewTexture))
  {
  }

  TexturePreview::~TexturePreview()
  {
    DestroyFramebuffer();
  }

  void
  TexturePreview::SetupShader()
  {
    std::string vertexSource = LoadFile("shaders/raymarch.vert");
    std::string fragmentSource = LoadFile("shaders/raymarch.frag");

    m3DPreviewShader =
      CompileShaderProgram(vertexSource.c_str(), fragmentSource.c_str());
  }

  void
  TexturePreview::SetupCubeMesh()
  {
    const float vertices[] = {
      // Positions
      -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1,
      -1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1,
    };

    const uint32_t indices[] = { // Front
                                 0,
                                 1,
                                 2,
                                 2,
                                 3,
                                 0,
                                 // Right
                                 1,
                                 5,
                                 6,
                                 6,
                                 2,
                                 1,
                                 // Back
                                 5,
                                 4,
                                 7,
                                 7,
                                 6,
                                 5,
                                 // Left
                                 4,
                                 0,
                                 3,
                                 3,
                                 7,
                                 4,
                                 // Bottom
                                 4,
                                 5,
                                 1,
                                 1,
                                 0,
                                 4,
                                 // Top
                                 3,
                                 2,
                                 6,
                                 6,
                                 7,
                                 3
    };

    glCreateVertexArrays(1, &mCubeMesh.vao);
    glCreateBuffers(1, &mCubeMesh.vbo);
    glCreateBuffers(1, &mCubeMesh.ebo);

    glNamedBufferStorage(mCubeMesh.vbo, sizeof(vertices), vertices, 0);
    glNamedBufferStorage(mCubeMesh.ebo, sizeof(indices), indices, 0);

    glVertexArrayVertexBuffer(
      mCubeMesh.vao, 0, mCubeMesh.vbo, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(mCubeMesh.vao, mCubeMesh.ebo);

    // Vertex attribute: position (location = 0)
    glEnableVertexArrayAttrib(mCubeMesh.vao, 0);
    glVertexArrayAttribFormat(mCubeMesh.vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(mCubeMesh.vao, 0, 0);

    mCubeMesh.indexCount = sizeof(indices) / sizeof(indices[0]);
  }

  void
  TexturePreview::SetupFramebuffer(glm::vec2 resolution)
  {
    // Framebuffer fb;
    mFramebuffer.width = resolution.x;
    mFramebuffer.height = resolution.y;

    // Create color texture
    glCreateTextures(GL_TEXTURE_2D, 1, &mFramebuffer.colorTexture);
    glTextureStorage2D(mFramebuffer.colorTexture,
                       1,
                       GL_RGBA8,
                       mFramebuffer.width,
                       mFramebuffer.height);

    // Set texture parameters (optional, adjust as needed)
    glTextureParameteri(
      mFramebuffer.colorTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(
      mFramebuffer.colorTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(
      mFramebuffer.colorTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(
      mFramebuffer.colorTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Create framebuffer
    glCreateFramebuffers(1, &mFramebuffer.fbo);
    glNamedFramebufferTexture(
      mFramebuffer.fbo, GL_COLOR_ATTACHMENT0, mFramebuffer.colorTexture, 0);

    // Check completeness
    if (glCheckNamedFramebufferStatus(mFramebuffer.fbo, GL_FRAMEBUFFER) !=
        GL_FRAMEBUFFER_COMPLETE)
    {
      // Handle error appropriately in your app
      fprintf(stderr, "Framebuffer is incomplete!\n");
      glDeleteFramebuffers(1, &mFramebuffer.fbo);
      glDeleteTextures(1, &mFramebuffer.colorTexture);
    }
  }

  void
  TexturePreview::DestroyFramebuffer()
  {
    if (mFramebuffer.fbo)
    {
      glDeleteFramebuffers(1, &mFramebuffer.fbo);
      mFramebuffer.fbo = 0;
    }
    if (mFramebuffer.colorTexture)
    {
      glDeleteTextures(1, &mFramebuffer.colorTexture);
      mFramebuffer.colorTexture = 0;
    }
    mFramebuffer.width = 0;
    mFramebuffer.height = 0;
  }

  void
  TexturePreview::ResizeFramebuffer(glm::vec2 resolution)
  {
    if (resolution.x == mFramebuffer.width &&
        resolution.y == mFramebuffer.height)
      return; // No need to resize

    SetupFramebuffer(resolution);
    return;

    mFramebuffer.width = resolution.x;
    mFramebuffer.height = resolution.y;

    // Reallocate storage for the existing texture
    glTextureStorage2D(
      mFramebuffer.colorTexture, 1, GL_RGBA8, resolution.x, resolution.y);

    // You can re-attach the texture just to be safe (optional but safe)
    glNamedFramebufferTexture(
      mFramebuffer.fbo, GL_COLOR_ATTACHMENT0, mFramebuffer.colorTexture, 0);

    // Check again for completeness
    if (glCheckNamedFramebufferStatus(mFramebuffer.fbo, GL_FRAMEBUFFER) !=
        GL_FRAMEBUFFER_COMPLETE)
    {
      fprintf(stderr, "Resized framebuffer is incomplete!\n");
    }
  }

  void
  TexturePreview::Render2DPreview(glm::vec2 resolution)
  {
    ImGui::Image((ImTextureID)mGpuPreviewTexture->GetTextureId(),
                 ImVec2(resolution.x, resolution.y));
  }

  void
  TexturePreview::Render3DPreview(glm::vec2 resolution, float deltaTime)
  {
    // TODO: Resize if resolution changed compared to the framebuffer
    ResizeFramebuffer(resolution);

    // Bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer.fbo);
    glViewport(0, 0, resolution.x, resolution.y);

    // Clear with transparent background
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader
    glUseProgram(m3DPreviewShader);

    static glm::vec3 cameraPos = glm::vec3(3.5F, 1.5F, 3.5F);
    static glm::vec3 target = glm::vec3(0, 0, 0);
    static glm::vec3 forward = glm::normalize(target - cameraPos);
    static glm::vec3 right =
      glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    static glm::vec3 cameraUp = glm::cross(forward, right);

    glm::mat4 view = glm::lookAt(cameraPos, target, cameraUp);

    // Setup static camera matrices
    /*glm::mat4 view = glm::lookAtRH(cameraPos,                  // Eye position
                                   glm::vec3(0.0F),            // Look at origin
                                   glm::vec3(0.0F, 1.0F, 0.0F) // Up vector
    );*/

    glm::mat4 projection =
      glm::perspective(glm::radians(45.0f),
                       static_cast<float>(mFramebuffer.width) /
                         static_cast<float>(mFramebuffer.height),
                       0.01f,
                       40.0f);

    // Upload uniforms
    GLint locModel = glGetUniformLocation(m3DPreviewShader, "uModel");
    GLint locView = glGetUniformLocation(m3DPreviewShader, "uView");
    GLint locProj = glGetUniformLocation(m3DPreviewShader, "uProjection");
    GLint locTex = glGetUniformLocation(m3DPreviewShader, "uVolume");
    GLint locStepSize = glGetUniformLocation(m3DPreviewShader, "uStepSize");
    GLint locCameraPos = glGetUniformLocation(m3DPreviewShader, "uCameraPos");
    GLint locDensityFactor =
      glGetUniformLocation(m3DPreviewShader, "uDensityFactor");
    GLint locMaxSteps = glGetUniformLocation(m3DPreviewShader, "uMaxSteps");

    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_3D,
                  mGpuPreviewTexture->GetTextureId()); // Bind your 3D texture
    glUseProgram(m3DPreviewShader); // Use your shader program
    glUniform1i(locTex, 0);

    mModelMatrix =
      glm::rotate(mModelMatrix, mRotationSpeed * deltaTime, glm::vec3(0, 1, 0));

    glUniform1i(locMaxSteps, mMaxSteps);
    glUniform1f(locStepSize, mStepSize);
    glUniform1f(locDensityFactor, mDensityFactor);
    glUniform3fv(locCameraPos, 1, glm::value_ptr(cameraPos));
    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mModelMatrix));
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw mesh
    glBindVertexArray(mCubeMesh.vao);
    glDrawElements(GL_TRIANGLES, mCubeMesh.indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Reset state
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Image((ImTextureID)mFramebuffer.colorTexture,
                 ImVec2(resolution.x, resolution.y),
                 ImVec2(0, 1),
                 ImVec2(1, 0));
  }

  void
  TexturePreview::Init()
  {
    SetupShader();
    SetupCubeMesh();
    SetupFramebuffer({ 512, 512 });
  }

  void
  TexturePreview::Render(glm::vec2 resolution, float deltaTime)
  {
    switch (mTextureSettings->Dimensions)
    {
      case TextureDimension::Texture1D: break;
      case TextureDimension::Texture2D: Render2DPreview(resolution); break;
      case TextureDimension::Texture3D:
        Render3DPreview(resolution, deltaTime);
        break;
    }
  }

  void
  TexturePreview::RenderSettings()
  {
    static bool interpolatePreviewTexture =
      mGpuPreviewTexture->GetInterpolatePreview();

    if (ImGui::Checkbox("Interpolate", &interpolatePreviewTexture))
    {
      mGpuPreviewTexture->SetInterpolatePreview(interpolatePreviewTexture);
    }

    if (mTextureSettings->Dimensions == TextureDimension::Texture3D)
    {
      ImGui::SliderFloat("Density factor", &mDensityFactor, 0.0F, 4.0F, "%.2F");
      ImGui::SliderFloat("Step Size", &mStepSize, 0.000001F, 0.1F, "%.4F");
      ImGui::SliderInt("Max steps", &mMaxSteps, 1, 2048);
      ImGui::SliderFloat("Rotation speed", &mRotationSpeed, 0.0F, 2.0F, "%.2F");
    }
  }
}