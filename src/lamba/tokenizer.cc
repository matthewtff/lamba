#include "tokenizer.hh"

#include <algorithm>
#include <cctype>
#include <string>

namespace {

bool notDigit(const char ch) {
  return !std::isdigit(ch);
}

bool isNumber(const std::string& number) {
  return !number.empty() &&
      number.end() == std::find_if(number.begin(),
                                   number.end(),
                                   notDigit);
}

} // namespace

namespace lamba {

Tokenizer::Tokenizer() : is_comment_(false) {
}

bool Tokenizer::parse(const std::string& text) {
  clear();
  for (const char ch : text)
    processChar(ch);
  addToken();
  return !tokens_.empty();
}

// private

const Tokenizer::StringList Tokenizer::punctuators_ = {
  "(", ")", "/)", ".", ",", "=", "|", ";"
};

const Tokenizer::StringList Tokenizer::reserved_ = {
  "let", "type", "in"
};

void Tokenizer::addToken() {
  if (token_.empty())
    return;
  Token::Type type = Token::Type::Identificator;
  if (isReserved(token_))
    type = Token::Type::ReservedWord;
  else if (isPunctuator(token_))
    type = Token::Type::Punctuator;
  else if (isNumber(token_))
    type = Token::Type::Number;
  tokens_.emplace_back(token_, type, line_, position_);
  token_.clear();
}

void Tokenizer::checkNewLine(const char ch) {
  if (ch != '\n')
    return;
  ++line_;
  position_ = 0;
}

void Tokenizer::clear() {
  token_.clear();
  tokens_.clear();
  line_ = 0;
  position_ = 0;
  is_comment_ = false;
}

bool Tokenizer::isPunctuator(const char ch) const {
  return isPunctuator(std::string(1, ch));
}

bool Tokenizer::isPunctuator(const std::string& token) const {
  return punctuators_.end() != std::find(punctuators_.begin(),
                                         punctuators_.end(),
                                         token);
}

bool Tokenizer::isReserved(const std::string& token) const {
  return reserved_.end() != std::find(reserved_.begin(),
                                      reserved_.end(),
                                      token);
}

void Tokenizer::processChar(const char ch) {
  if (std::isspace(ch)) {
    addToken();
    checkNewLine(ch);
    return;
  }

  // For now we have only one punctuator consisting of 2 characters - '/)'
  // so it's a hack just until there are punctuators of 3 or more characters.
  const std::string possibleLambda = token_ + ch;
  if (isPunctuator(possibleLambda)) {
    token_ += ch;
    addToken();
    return;
  }
  
  if (isPunctuator(token_) || isPunctuator(ch))
    addToken();
  token_ += ch;
}

} // namespace lamba
