#ifndef lamba_tokenizer_hh
#define lamba_tokenizer_hh

#include <list>
#include <string>

#include "token.hh"

namespace lamba {

class Tokenizer {
public:
  typedef std::list<std::string> StringList;
  typedef std::list<Token> Tokens;

  Tokenizer();
  bool parse(const std::string& text);
  const Tokens getTokens() const { return tokens_; }
  Token::LineNumber getLine() const { return line_; }
  Token::LinePosition getPosition() const { return position_; }

private:
  void addToken();
  void checkNewLine(const char ch);
  void clear();
  bool isPunctuator(const char ch) const;
  bool isPunctuator(const std::string& token) const;
  bool isReserved(const std::string& token) const;
  void processChar(const char ch);

  static const StringList punctuators_;
  static const StringList reserved_;
  std::string token_;
  Tokens tokens_;

  Token::LineNumber line_;
  Token::LinePosition position_;

  bool is_comment_;
}; // class Tokenizer

} // namespace lamba

#endif // lamba_tokenizer_hh
