#ifndef lamba_parser_hh
#define lamba_parser_hh

#include <memory>
#include <string>

#include "constructions.hh"
#include "tokenizer.hh"

namespace lamba {

class Parser {
public:
  std::string parse(const std::string& text);

  enum class Punctuator {
    OpeningBracket,
    ClosingBracket,
    Lambda,
    Pipe,
    Colon,
    Period,
    Semicolon,
    Unknown
  };

private:
  typedef Tokenizer::Tokens::const_iterator TokenIterator;

  std::string errorMessage(TokenIterator token);
  TokenIterator parseDefenition(TokenIterator token);
  TokenIterator parseLambda(TokenIterator token);
  TokenIterator processToken(TokenIterator token);
  void resetError();
  void setError(const char* message);
  TokenIterator showIdentificator(TokenIterator token);
  std::string tokenizerError() const;

  Tokenizer tokenizer_;
  Context context_;

  std::unique_ptr<Lambda> current_lambda_;

  bool is_error_;
  std::string error_message_;
}; // class Parser

} // namespace lamba

#endif // lamba_parser_hh
