#include "grammar.hpp"

Grammar::Grammar(const std::vector<Rule>& rules,
                 const std::vector<char>& alphabet)
    : rules_(std::vector<Rule>(rules)),
      alphabet_(std::vector<char>(alphabet)) {}

std::vector<Rule> Grammar::GetRules() const { return rules_; }

void Grammar::AddNewRule(Rule new_rule) {
  rules_.emplace_back(std::move(new_rule));
}

std::vector<Rule> Grammar::GetRulesWithStartingState(char state) const {
  std::vector<Rule> answers;
  for (const auto& rule : rules_) {
    if (rule.GetStartState() == state) {
      answers.emplace_back(rule);
    }
  }
  return answers;
}

std::istream& operator>>(std::istream& input, Grammar& grammar) {
  size_t n;
  std::cout << "Input the number of rules: ";
  input >> n;
  if (n == 0) {
    std::cout << "The grammar is empty\n";
    return input;
  }
  Rule rule;
  std::cout << "Input the rules(example: S->aSb)\n";
  for (size_t i = 0; i < n; ++i) {
    std::cout << "Input the " << i + 1 << " rule: ";
    input >> rule;
    grammar.AddNewRule(rule);
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
  output << "Alphabet: ";
  for (const auto& symbol : grammar.alphabet_) {
    output << symbol << " ";
  }
  output << "\nRules: \n";
  for (const auto& rule : grammar.rules_) {
    output << rule << '\n';
  }
  return output;
}