#pragma once

#include <imgui.h>
#include <magic_enum/magic_enum.hpp>

namespace Sindri
{
  static auto
  InputTextCallback(ImGuiInputTextCallbackData* data) -> int
  {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
      auto* str = static_cast<std::string*>(data->UserData);
      str->resize(data->BufTextLen);
      data->Buf = str->data();
    }
    return 0;
  }

  static auto
  InputTextString(const char*         label,
                  std::string&        str,
                  ImGuiInputTextFlags flags = 0) -> bool
  {
    return ImGui::InputText(label,
                            str.data(),
                            str.capacity() + 1,
                            ImGuiInputTextFlags_CallbackResize | flags,
                            InputTextCallback,
                            &str);
  }

  template<typename Enum>
  static auto
  ComboEnum(const char* label, Enum& current_value) -> bool
  {
    static_assert(std::is_enum_v<Enum>, "ComboEnum only works with enum types");

    int  currentIndex = static_cast<int>(current_value);
    bool changed = false;

    // Create a vector of enum names
    auto names = magic_enum::enum_names<Enum>();
    auto values = magic_enum::enum_values<Enum>();
    int  index = -1;

    // Find current index
    for (size_t i = 0; i < values.size(); ++i)
    {
      if (values[i] == current_value)
      {
        index = static_cast<int>(i);
        break;
      }
    }

    if (ImGui::BeginCombo(label, names[index].data()))
    {
      for (size_t i = 0; i < names.size(); ++i)
      {
        bool isSelected = (index == static_cast<int>(i));
        if (ImGui::Selectable(names[i].data(), isSelected))
        {
          current_value = values[i];
          changed = true;
        }
        if (isSelected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }

    return changed;
  }
}