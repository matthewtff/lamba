#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "lamba/tokenizer.hh"

void printToken (const lamba::Token& token) {
  std::cout << token.getToken()
            << " : "
            << token.getTypeString()
            << std::endl;
}

void processFile (const std::string& file_name) {
  if (file_name.empty())
    return;
  std::ifstream input_file(file_name.c_str());
  if (!input_file)
    return;
  std::string input;
  std::string line;
  while (std::getline(input_file, line)) {
    input += line;
    input += '\r';
  }
  lamba::Tokenizer tokenizer;
  if (tokenizer.parse(input)) {
    const auto tokens = tokenizer.getTokens();
    std::for_each (tokens.begin(), tokens.end(), printToken);
  }
}

void processArgument(const char* argument) {
  if (!argument)
    return;
  const std::string arg(argument);
  if (arg == "--version")
    std::cout << "Version: 0.0.1 dev" << std::endl;
  else if (arg == "--help") {
    std::cout << "Available arguments:" << std::endl;
    std::cout << "  --help" << std::endl;
    std::cout << "  --version" << std::endl;
  } else
    processFile(arg);
}

int processArguments(int argc, char* argv[]) {
  for (int arg = 1; arg < argc; ++arg)
    processArgument(argv[arg]);
  return 0;
}

void printPrelude() {
  std::cout << "Lamba: ";
}

bool processExpression() {
  std::string expression;
  std::getline(std::cin, expression);
  const bool is_quit = expression == "quit";
  const bool is_empty = expression.empty();
  lamba::Tokenizer tokenizer;
  if (tokenizer.parse(expression)) {
    const auto tokens = tokenizer.getTokens();
    std::for_each (tokens.begin(), tokens.end(), printToken);
  } else {
    const auto position = tokenizer.getPosition();
    std::cout << "Error ["
              << position.first 
              << ","
              << position.second
              << "]" << std::endl;
  }
  return !is_quit && !is_empty;
}

int main(int argc, char* argv[]) {
  if (argc > 1)
    return processArguments(argc, argv);
  do {
    printPrelude();
  } while (processExpression());
  return 0;
}
