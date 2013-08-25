#include "token.hh"

#include <string>

namespace lamba {

Token::Token(const std::string& token,
             const Type type,
             const LineNumber line,
             const LinePosition position)
    : token_(token), type_(type), line_(line), position_(position) {

}

std::string Token::getTypeString() const {
  switch (type_) {
    case Type::Comment:
      return "Comment";
    case Type::Identificator:
      return "Identificator";
    case Type::Number:
      return "Number";
    case Type::Punctuator:
      return "Punctuator";
    case Type::ReservedWord:
      return "ReservedWord";
  }
  return "Fatal";
}

} // namespace lamba
