#include <iostream>
#include <string>

#include "lamba/tokenizer.hh"

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
  }
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
    for (const lamba::Token& token : tokenizer.getTokens()) {
      std::cout << token.getToken()
                << " : "
                << token.getTypeString()
                << std::endl;
    }
  } else {
    std::cout << "Error ["
              << tokenizer.getLine()
              << ","
              << tokenizer.getPosition()
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
