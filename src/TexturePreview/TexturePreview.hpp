#pragma once

#include "IGpuPreviewTexture.hpp"
#include "ITextureBuffer.hpp"
#include "ITexturePreview.hpp"
#include "TextureSettings/TextureSettings.hpp"

namespace Sindri
{
  struct Framebuffer
  {
    GLuint  fbo = 0;
    GLuint  colorTexture = 0;
    GLsizei width = 0;
    GLsizei height = 0;
  };

  struct Mesh
  {
    GLuint  vao = 0;
    GLuint  vbo = 0;
    GLuint  ebo = 0;
    GLsizei indexCount = 0;
  };

  class TexturePreview : public ITexturePreview
  {
  private:
    TextureDimension mCachedDimension = TextureDimension::Texture2D;
    std::shared_ptr<TextureSettings>    mTextureSettings;
    std::shared_ptr<ITextureBuffer>     mTexture;
    std::shared_ptr<IGpuPreviewTexture> mGpuPreviewTexture;
    Framebuffer                         mFramebuffer;
    Mesh                                mCubeMesh;
    GLuint                              m3DPreviewShader = 0;
    glm::mat4                           mModelMatrix = glm::mat4(1.0F);
    float                               mDensityFactor = 0.6F;
    float                               mStepSize = 0.005F;
    int                                 mMaxSteps = 580;
    float                               mRotationSpeed = 0.2F;

    void
    SetupShader();

    void
    SetupCubeMesh();

    void
    SetupFramebuffer(glm::vec2 resolution);

    void
    DestroyFramebuffer();

    void
    ResizeFramebuffer(glm::vec2 resolution);

    void
    Render2DPreview(glm::vec2 resolution);

    void
    Render3DPreview(glm::vec2 resolution, float deltaTime);

  public:
    TexturePreview(std::shared_ptr<TextureSettings>    textureSettings,
                   std::shared_ptr<ITextureBuffer>     texture,
                   std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture);

    ~TexturePreview();

    void
    Init() override;

    void
    Render(glm::vec2 resolution, float deltaTime) override;

    void
    RenderSettings() override;
  };
}