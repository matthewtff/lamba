#ifndef lamba_token_hh
#define lamba_token_hh

#include <cstdint>
#include <string>

namespace lamba {

class Token {
public:
  enum class Type {
    Comment,
    Identificator,
    Number,
    Punctuator,
    ReservedWord
  };
  typedef std::uint32_t LineNumber;
  typedef std::uint32_t LinePosition;

  Token(const std::string& token,
        const Type type,
        const LineNumber line,
        const LinePosition position);

  std::string getToken() const { return token_; }
  Type getType() const { return type_; }
  std::string getTypeString() const;
  LineNumber getLineNumber() const { return line_; }
  LinePosition getLinePosition() const { return position_; }

private:
  const std::string token_;
  const Type type_;
  const LineNumber line_;
  const LinePosition position_;
}; // class Token

} // namespace lamba

#endif // lamba_token_hh
