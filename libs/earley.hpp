#pragma once

#include <set>

#include "grammar.hpp"

class Earley {
 public:
  bool CanParse(const Grammar& grammar, const std::string& word);
  void Build(const Grammar& grammar, const std::string& word);
  void Predict(size_t situation_set_number, const Grammar& grammar);
  void Scan(size_t situation_set_number, char symbol);
  void Complete(size_t situation_set_number);

 private:
  struct Situation {
   public:
    Situation(Rule rule, size_t cposition, size_t sposition)
        : rule(std::move(rule)),
          current_position(cposition),
          start_position(sposition) {}
    [[nodiscard]] bool Completed() const {
      return current_position == rule.GetFinishState().size();
    }
    [[nodiscard]] char GetCurrentSymbol() const {
      return rule.GetFinishState()[current_position];
    }
    bool operator<(const Situation& other) const {
      if (rule == other.rule) {
        if (current_position == other.current_position) {
          return start_position < other.start_position;
        }
        return current_position < other.current_position;
      }
      return rule < other.rule;
    }
    Rule rule;
    size_t current_position;
    size_t start_position;
  };
  std::vector<std::set<Situation>> sets_;
};
