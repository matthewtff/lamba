#include "tokenizer.hh"

#include <algorithm>
#include <cctype>
#include <string>

namespace lamba {

Tokenizer::Tokenizer() {
  clear();
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
  "(", ")", "\\", ".", ",", "|", ":", ";"
};

const Tokenizer::StringList Tokenizer::reserved_ = {
  "in", "is", "let", "type"
};

void Tokenizer::addToken() {
  if (token_.empty())
    return;
  Token::Type type = Token::Type::Identificator;
  if (isReserved(token_))
    type = Token::Type::ReservedWord;
  else if (isPunctuator(token_))
    type = Token::Type::Punctuator;
  tokens_.emplace_back(token_, type, position_);
  token_.clear();
}

void Tokenizer::checkNewLine(const char ch) {
  if (ch != '\n')
    return;
  ++position_.first;
  position_.second = 0;
}

void Tokenizer::clear() {
  token_.clear();
  tokens_.clear();
  position_ = std::make_pair(0, 0);
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
  /*const std::string possibleLambda = token_ + ch;
  if (isPunctuator(possibleLambda)) {
    token_ += ch;
    addToken();
    return;
  }*/
  
  if (isPunctuator(token_) || isPunctuator(ch))
    addToken();
  token_ += ch;
}

} // namespace lamba
