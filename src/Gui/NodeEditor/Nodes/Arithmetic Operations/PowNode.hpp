// SubtractNode_variant.h
#include "ImNodeFlow.h" // adjust path as needed
#include <cmath>
#include <string>
#include <variant>

using Scalar = std::variant<int, float, double>;

class PowNode : public ImFlow::BaseNode
{
public:
  PowNode()
  {
    setTitle("Pow");
    setStyle(ImFlow::NodeStyle::green());
    getStyle()->bg = IM_COL32(46, 52, 64, 255);
    getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

    // add two inputs and one output all typed as the Variant "Scalar"
    addIN<Scalar>("A", Scalar{ 0 }, ImFlow::ConnectionFilter::SameType());
    addIN<Scalar>("B", Scalar{ 0 }, ImFlow::ConnectionFilter::SameType());

    // output behaviour: compute the sum and return a Scalar (we return a double
    // for precision)
    addOUT<Scalar>("Result")->behaviour(
      [this]() -> Scalar
      {
        const auto& a = getInVal<Scalar>("A");
        const auto& b = getInVal<Scalar>("B");

        double res = std::visit(
          [](auto&& lhs, auto&& rhs) -> double
          {
            return std::pow(static_cast<double>(lhs), static_cast<double>(rhs));
          },
          a,
          b);

        return Scalar{ res }; // stored as the double alternative in the variant
      });
  }

  void
  draw() override
  {
    // Show a simple readout of the computed result (not required — behaviour is
    // where outputs are computed)
    const auto& a = getInVal<Scalar>("A");
    const auto& b = getInVal<Scalar>("B");
    double      res = std::visit(
      [](auto&& lhs, auto&& rhs)
      { return std::pow(static_cast<double>(lhs), static_cast<double>(rhs)); },
      a,
      b);
    ImGui::Text("Result: %g", res);
  }
};
