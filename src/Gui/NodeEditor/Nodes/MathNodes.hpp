#pragma once

#include <ImNodeFlow.h>

namespace Sindri
{
  class AddNode : public ImFlow::BaseNode
  {
  private:
    int m_valB = 0;

  public:
    AddNode()
    {
      setTitle("Add");
      setStyle(ImFlow::NodeStyle::red());
      ImFlow::BaseNode::addIN<int>(
        "In", 0, ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addOUT<int>("Out", nullptr)
        ->behaviour([this]() { return getInVal<int>("In") + m_valB; });
    }

    void
    draw() override
    {
      if (ImFlow::BaseNode::isSelected())
      {
        ImGui::SetNextItemWidth(100.f);
        ImGui::InputInt("##ValB", &m_valB);
        ImGui::Button("Hello");
      }
    }
  };
}