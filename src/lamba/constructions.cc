#include "constructions.hh"

#include <string>

namespace lamba {

std::string Top::toString() const {
  if (identifier_.empty())
    return "<top:err>";
  std::string result = identifier_;
  result += ":";
  result += type_;
  return result;
}

Top::Pointer Lambda::argument() const {
  if (inner_context_.empty())
    return createEmpty();
  return *inner_context_.begin();
}

std::string Lambda::toString() const {
  Top::Pointer arg(argument());
  if (!arg)
    return "<lamba:err>";
  std::string result = "/)";
  result += arg->getIdentifier();
  result += " ";
  for (const Top::Pointer top : body_)
    result += top->toString();
  return result;
}

} // namespace lamba
