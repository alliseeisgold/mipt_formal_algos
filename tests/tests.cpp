#include <string>
#include <vector>

#include "earley.hpp"
#include "gtest/gtest.h"

bool TestBrackets(std::vector<char> alphabet, std::vector<Rule> rules,
                  std::string word) {
  Grammar grammar(rules, alphabet);
  Earley parser;
  return parser.CanParse(grammar, word);
}

TEST(BRACKETS, CAN_PARSE) {
  std::vector<char> alphabet = {'(', ')'};
  std::vector<Rule> rules = {Rule("A->S"), Rule("S->(S)S"), Rule("S->S(S)"),
                             Rule("S->")};
  EXPECT_TRUE(TestBrackets(alphabet, rules, "(()(()))()"));
}

TEST(BRACKETS, CAN_NOT_PARSE) {
  std::vector<char> alphabet = {'{', '}'};
  std::vector<Rule> rules = {Rule("A->S"), Rule("S->{S}S"), Rule("S->S{S}"),
                             Rule("S->")};
  EXPECT_FALSE(TestBrackets(alphabet, rules, "{{}}}"));
}

bool TestPalindromWords(std::string word) {
  std::vector<char> alphabet;
  alphabet.emplace_back(' ');
  for (char letter = 'a'; letter <= 'z'; letter++) {
    alphabet.emplace_back(letter);
  }
  std::vector<Rule> rules;
  rules.emplace_back("U->S");
  rules.emplace_back("S->");
  for (const auto& letter : alphabet) {
    std::string finish = std::string(1, letter);
    rules.emplace_back("S->" + finish);
    finish += "S" + std::string(1, letter);
    rules.emplace_back("S->" + finish);
  }
  Grammar grammar(rules, alphabet);
  Earley parser;
  return parser.CanParse(grammar, word);
}

TEST(PALINDROM_WORDS, CAN_PARSE) {
  std::string word = "arozaupalanalapuazora";
  EXPECT_TRUE(TestPalindromWords(word));
}

TEST(PALINDROM_WORDS, CAN_NOT_PARSE) {
  EXPECT_FALSE(TestPalindromWords("kukareku"));
}

TEST(APELLIDO, CAN_NOT_PARSE) { EXPECT_FALSE(TestPalindromWords("akhtyamov")); }

TEST(NOTHING, SPACES) { EXPECT_TRUE(TestPalindromWords("    ")); }

TEST(NOTHING2, SPACES_N_LETTERS) { EXPECT_TRUE(TestPalindromWords("a    a")); }

TEST(NOTHING3, SPACES_N_TRASH) { EXPECT_FALSE(TestPalindromWords("**    -")); }

void TestExceptions(std::string rule) { ASSERT_ANY_THROW(Rule varname(rule)); }
TEST(EXCEPTIONS, EMPTY_START_STATE) { TestExceptions("->aSb"); }
TEST(EXCEPTIONS, TOO_LONG_START_STATE) { TestExceptions("S*->aSb"); }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
