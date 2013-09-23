#include "parser.hh"

#include <sstream>
#include <string>

namespace {

using lamba::Token;
using lamba::Parser;

Parser::Punctuator tokenToPunctuator(const Token& token) {
  if (token.getType() != Token::Type::Punctuator)
    return Parser::Punctuator::Unknown;
  if (token.getToken() == "(")
    return Parser::Punctuator::OpeningBracket;
  else if (token.getToken() == ")")
    return Parser::Punctuator::ClosingBracket;
  else if (token.getToken() == "/)")
    return Parser::Punctuator::Lambda;
  else if (token.getToken() == "|")
    return Parser::Punctuator::Pipe;
  else if (token.getToken() == ".")
    return Parser::Punctuator::Period;
  else if (token.getToken() == ";")
    return Parser::Punctuator::Semicolon;
  return Parser::Punctuator::Unknown;
}


} // namespace

namespace lamba {

std::string Parser::parse(const std::string& text) {
  resetError();
  if (!tokenizer_.parse(text))
    return tokenizerError();
  
  TokenIterator token = tokenizer_.begin();

  while (token != tokenizer_.cend()) {
    token = processToken(token);
    if (is_error)
      return errorMessage(token);
  }

  return "ok\n";
}

std::string Parser::errorMessage(TokenIterator token) {
  std::stringstream result(error_message_);
  result << " on " << token->getLinePosition() << std::endl;
  return result.str();
}

TokenIterator Parser::parseDefenition(TokenIterator token) {
  if (token->getToken() != "let") {
    setError("Defenition expected");
    return token;
  }
  ++token;
  if (token->getType() != Token::Type::Identificator) {
    setError("Identificator expected");
    return token;
  }
  std::string identificator = token->getToken();
  ++token;
  if (token->getType() != Token::Type::ReservedWord ||
      token->getToken() != "is") {
    setError("Reserved word 'is' expected");
    return token;
  }
  token = 
}

TokenIterator Parser::parseLambda(TokenIterator token) {
}

Parser::TokenIterator Parser::processToken(TokenIterator token) {
  if (token->getType() == Token::Type::Comment)
    return ++token;
  if (token->getType() == Token::Type::Identificator)
    return showIdentificator(token);
  if (token->getType() == Token::Type::Punctuator) {
    token = parseLambda(token);
    if (current_lambda_)
    return token;
  }
  if (token->getType() == Token::Type::ReservedWord)
    return parseDefinition(token);
}

void Parser::resetError() {
  is_error = false;
  error_message_.clear();
}

void Parser::setError(const char* message) {
  error_message_ = message;
  is_error = true;
}

Parser::TokenIterator Parser::showIdentificator(TokenIterator token) {
  const Token& identificator = *token;
  ++token;
  const Punctuator punctuator = tokenToPunctuator(token);
  if (punctuator != Punctuator::Period) {
    setError("Period expected");
    return token;
  }
  for (const Top::Pointer top : context_) {
    if (top->getIdentifier() == identificator.getToken())
      std::cout << top->toString() << std::endl;
  }
  return ++token;
}

std::string Parser::tokenizerError() const {
  std::string result = "Error [";
  result += tokenizer_.getLine();
  result += ",";
  result += tokenizer_.getPosition();
  result += "]\n";
  return result;
}

} // namespace lamba
