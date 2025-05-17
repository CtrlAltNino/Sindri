#include "pch.hpp"

#include "Helpers/UI.hpp"
#include "ProceduralTexture.hpp"
#include "Sindri.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <chrono>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <iostream>

namespace Sindri
{
  SindriApp::SindriApp()
  {
    if (!Init())
    {
      std::cerr << "[Error] Failed to initialize SindriApp.\n";
    }

    mTextureSettings.mSeed = mRandomDevice();
    mScripts = GetLuaScripts();
  }

  SindriApp::~SindriApp()
  {
    Shutdown();
  }

  auto
  SindriApp::Init() -> bool
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
      std::cerr << "[SDL] Initialization Error: " << SDL_GetError() << "\n";
      return false;
    }

    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER,
                "0"); // optional: disable ES fallback
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    mWindow = SDL_CreateWindow(mTitle.c_str(),
                               mWidth,
                               mHeight,
                               SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!mWindow)
    {
      std::cerr << "[SDL] Failed to create window: " << SDL_GetError() << "\n";
      return false;
    }

    // SDL3: Third argument is now a const char* driver name (or nullptr)
    mContext = SDL_GL_CreateContext(mWindow);

    // Check if the OpenGL context was created successfully.
    if (mContext == nullptr)
    {
      std::cerr << "[SDL] Failed to create context: " << SDL_GetError() << "\n";
      return false;
    }

    SDL_GL_MakeCurrent(mWindow, mContext);
    SDL_GL_SetSwapInterval(1); // Disable VSync (uncapped framerate)

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(mWindow, mContext);
    ImGui_ImplOpenGL3_Init("#version 450");

    mRunning = true;
    return true;
  }

  void
  SindriApp::Shutdown()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(mContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  void
  SindriApp::Run()
  {
    if (!mRunning)
    {
      std::cerr << "[SindriApp] Cannot run main loop; init failed.\n";
      return;
    }

    MainLoop();
  }

  void
  SindriApp::MainLoop()
  {
    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    while (mRunning)
    {
      auto  now = clock::now();
      float deltaTime = std::chrono::duration<float>(now - lastTime).count();
      lastTime = now;
      mFps = 1.0f / deltaTime;
      mMsPerFrame = deltaTime * 1000.0f;
      SDL_GetWindowSize(mWindow, &mCurrentWindowWidth, &mCurrentWindowHeight);

      HandleEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      // Demo window for testing
      // ImGui::ShowDemoWindow();
      MainWindow();

      Render();

      // SDL_Delay(1); // prevent CPU spinlock
    }
  }

  void
  SindriApp::HandleEvents()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL3_ProcessEvent(&event);
      switch (event.type)
      {
        case SDL_EVENT_QUIT: mRunning = false; break;
        default: break;
      }
    }
  }

  void
  SindriApp::Render()
  {
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(mWindow);
  }

  void
  SindriApp::MainWindow()
  {
    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(
      ImVec2((float)mCurrentWindowWidth / 2, (float)mCurrentWindowHeight));

    // Create a full-screen ImGui window
    ImGui::Begin("SettingsWindow", nullptr, windowFlags);
    ImGui::Text("General");
    ImGui::Separator();

    ImGui::Text("FPS: %.1f", mFps);
    ImGui::Text("Frame Time: %.2f ms", mMsPerFrame);
    if (ImGui::Checkbox("VSync", &mVsync))
    {
      SDL_GL_SetSwapInterval(mVsync ? 1 : 0);
    }

    ImGui::Spacing();
    ImGui::Text("Options");
    ImGui::Separator();

    ImGui::InputScalar("Seed", ImGuiDataType_U32, &mTextureSettings.mSeed);

    ImGui::SameLine();
    if (ImGui::Button("Randomize Seed"))
    {
      mTextureSettings.mSeed = mRandomDevice();
    }

    ComboEnum("Texture Dimension", mTextureSettings.mDimensions);
    ComboEnum("Output Format", mTextureSettings.mOutputFormat);
    ComboEnum("Texture Format", mTextureSettings.mBitDepth);

    switch (mTextureSettings.mDimensions)
    {
      using enum TextureDimension;
      case Texture1D:
        ImGui::InputInt("Resolution",
                        glm::value_ptr(mTextureSettings.mResolution));
        break;
      case Texture2D:
        ImGui::InputInt2("Resolution",
                         glm::value_ptr(mTextureSettings.mResolution));
        break;
      case Texture3D:
        ImGui::InputInt3("Resolution",
                         glm::value_ptr(mTextureSettings.mResolution));
        break;
    }

    ImGui::Spacing();
    ImGui::Text("Lua Scripts");
    ImGui::Separator();

    LuaScriptSelector();

    ImGui::Spacing();
    ImGui::Text("Stack");
    ImGui::Separator();

    // Composition
    {
      mCompositionStack.RenderSettings();
    }

    if (mCompositionStack.GetEntries().empty())
    {
      ImGui::BeginDisabled();
    }

    ImGui::Spacing();
    ImGui::Separator();

    if (ImGui::Button("Generate"))
    {
      GenerateTexture();
    }

    if (mCompositionStack.GetEntries().empty())
    {
      ImGui::EndDisabled();
    }

    // You can add buttons, sliders, etc. here
    ImGui::End();

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(ImVec2((float)mCurrentWindowWidth / 2, 0));
    ImGui::SetNextWindowSize(
      ImVec2((float)mCurrentWindowWidth / 2, (float)mCurrentWindowHeight));

    ImGui::Begin("PreviewWindow", nullptr, windowFlags);
    ImGui::Text("Texture Preview");
    ImGui::Separator();

    // Texture size you want to display (e.g. width, height in pixels or UV
    // scale)
    ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x,
                         ImGui::GetContentRegionAvail().x);

    static bool interpolatePreviewTexture = false;

    if (ImGui::Checkbox("Interpolate", &interpolatePreviewTexture))
    {
      mTexture->SetInterpolatePreview(interpolatePreviewTexture);
    }
    // Note: cast GLuint to void* to pass as ImTextureID
    if (mTexture && mTexture->GetIsUploaded())
    {
      ImGui::Image((ImTextureID)mTexture->GetTextureId(), size);
    }

    // You can add buttons, sliders, etc. here
    ImGui::End();
  }

  void
  SindriApp::GenerateTexture()
  {
    if (!mTexture)
    {
      mTexture = std::make_shared<ProceduralTexture>();
    }

    switch (mTextureSettings.mDimensions)
    {
      case TextureDimension::Texture1D:
        mTexture->Reserve(mTextureSettings.mResolution.x);
        break;
      case TextureDimension::Texture2D:
        mTexture->Reserve(mTextureSettings.mResolution.x,
                          mTextureSettings.mResolution.y);
        break;
      case TextureDimension::Texture3D:
        mTexture->Reserve(mTextureSettings.mResolution.x,
                          mTextureSettings.mResolution.y,
                          mTextureSettings.mResolution.z);
        break;
    }

    mNoiseGenerator.FillTexture(mCompositionStack, mTextureSettings, *mTexture);
  }

  auto
  SindriApp::GetLuaScripts() -> std::vector<std::filesystem::path>
  {
    std::vector<std::filesystem::path> scripts;
    for (const auto& entry : std::filesystem::directory_iterator("lua"))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".lua")
      {
        scripts.push_back(entry.path()); // relative name
      }
    }
    return scripts;
  }

  void
  SindriApp::LuaScriptSelector()
  {
    // Combo Box
    if (ImGui::BeginCombo("Lua Script",
                          mSelectedScriptIndex >= 0 &&
                              mSelectedScriptIndex < mScripts.size()
                            ? mScripts[mSelectedScriptIndex].string().c_str()
                            : "Select..."))
    {
      for (int i = 0; i < mScripts.size(); ++i)
      {
        bool isSelected = (mSelectedScriptIndex == i);
        if (ImGui::Selectable(mScripts[i].string().c_str(), isSelected))
        {
          mSelectedScriptIndex = i;
        }
        if (isSelected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }

    ImGui::SameLine();

    // Add Button
    if (ImGui::Button("Add to Stack"))
    {
      if (mSelectedScriptIndex >= 0 && mSelectedScriptIndex < mScripts.size())
      {
        // std::string selectedScript = mScripts[mSelectedScriptIndex];
        mCompositionStack.Add(mScripts[mSelectedScriptIndex]);
        // TODO: Do something with the selected script
        // std::cout << "Selected: " << selectedScript << std::endl;
      }
    }

    ImGui::SameLine();

    if (ImGui::Button("Refresh"))
    {
      mSelectedScriptIndex = 0;
      mScripts = GetLuaScripts();
    }
  }
}