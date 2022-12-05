#include <earley.hpp>

int main() {
  size_t n;
  std::cout << "Input the number of letters in the alphabet: ";
  std::cin >> n;
  if (n == 0) {
    std::cout << "The alphabet is empty";
    return 0;
  }
  std::cout << "Input the letters of the alphabet(example: { } [ ]): ";
  std::vector<char> alphabet(n);
  for (auto& letter : alphabet) {
    std::cin >> letter;
  }
  Grammar grammar;
  std::cin >> grammar;
  std::string word;
  std::cout << "\nInput the word(example: abba): ";
  std::cin >> word;
  Earley parser;
  if (parser.CanParse(grammar, word)) {
    std::cout << "\nYES! The word can be parsed";
  } else {
    std::cout << "\nNO! The word can not be parsed";
  }
  return 0;
}