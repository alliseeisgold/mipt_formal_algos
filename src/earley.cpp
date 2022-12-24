#include "earley.hpp"

bool Earley::CanParse(const Grammar& grammar, const std::string& word) {
  Build(grammar, word);
  Rule rule = grammar.GetRules()[0];
  Situation situation(rule, 1, 0);
  return sets_[word.size()].find(situation) != sets_[word.size()].end();
}

void Earley::Build(const Grammar& grammar, const std::string& word) {
  sets_.clear();
  sets_.resize(word.size() + 1);
  Rule rule = grammar.GetRules()[0];
  sets_[0].emplace(rule, 0, 0);
  ssize_t cur_size = -1;
  while (cur_size != sets_[0].size()) {
    cur_size = sets_[0].size();
    Predict(0, grammar);
    Complete(0);
  }
  for (size_t i = 1; i < word.size() + 1; ++i) {
    Scan(i - 1, word[i - 1]);
    cur_size = -1;
    while (cur_size != sets_[i].size()) {
      cur_size = sets_[i].size();
      Predict(i, grammar);
      Complete(i);
    }
  }
}

void Earley::Predict(size_t set_number, const Grammar& grammar) {
  for (const auto& situation : sets_[set_number]) {
    char start = situation.GetCurrentSymbol();
    for (const auto& rule : grammar.GetRulesWithStartingState(start)) {
      sets_[set_number].emplace(rule, 0, set_number);
    }
  }
}

void Earley::Scan(size_t set_number, char symbol) {
  for (const auto& situation : sets_[set_number]) {
    if (situation.GetCurrentSymbol() == symbol) {
      sets_[set_number + 1].emplace(situation.rule,
                                    situation.current_position + 1,
                                    situation.start_position);
    }
  }
}

void Earley::Complete(size_t set_number) {
  for (const auto& situation : sets_[set_number]) {
    if (situation.Completed()) {
      for (const auto& item : sets_[situation.start_position]) {
        if (item.GetCurrentSymbol() == situation.rule.GetStartState()) {
          sets_[set_number].emplace(item.rule, item.current_position + 1,
                                    item.start_position);
        }
      }
    }
  }
}