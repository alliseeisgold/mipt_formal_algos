#pragma once

#include "rule.hpp"

const std::string kSeparator = "->";

class Grammar {
 public:
  Grammar() = default;
  Grammar(const std::vector<Rule>& rules, const std::vector<char>& alphabet);
  [[nodiscard]] std::vector<Rule> GetRules() const;
  void AddNewRule(Rule new_rule);
  [[nodiscard]] std::vector<Rule> GetRulesWithStartingState(char state) const;
  friend std::istream& operator>>(std::istream& input, Grammar& grammar);
  friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

 private:
  std::vector<Rule> rules_;
  std::vector<char> alphabet_;
};