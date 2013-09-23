#ifndef lamba_token_hh
#define lamba_token_hh

#include <cstdint>
#include <string>
#include <utility>

namespace lamba {

class Token {
public:
  enum class Type {
    Comment,
    Identificator,
    Punctuator,
    ReservedWord
  };
  typedef std::pair<std::uint32_t, std::uint32_t> Position;

  Token(const std::string& token,
        const Type type,
        const Position position);

  std::string getToken() const { return token_; }
  Type getType() const { return type_; }
  std::string getTypeString() const;
  Position getPosition() const { return position_; }

private:
  const std::string token_;
  const Type type_;
  const Position position_;
}; // class Token

} // namespace lamba

#endif // lamba_token_hh
