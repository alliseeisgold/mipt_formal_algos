#include "rule.hpp"

#include "grammar.hpp"

Rule::Rule() : start_state_{' '} {};

Rule::Rule(const std::string& rule) {
  size_t sep_pos = rule.find(kSeparator);
  if (sep_pos == std::string::npos) {
    throw IncorrectInputError();
  }
  std::string start_state = rule.substr(0, sep_pos);
  if (start_state.size() > 1 || start_state.empty()) {
    throw StartStateError();
  }
  start_state_ = start_state[0];
  finish_state_ = rule.substr(sep_pos + kSeparator.size());
}

char Rule::GetStartState() const { return start_state_; }

std::string Rule::GetFinishState() const { return finish_state_; }

bool Rule::operator<(const Rule& other) const {
  if (start_state_ == other.start_state_) {
    return finish_state_ < other.finish_state_;
  }
  return start_state_ < other.start_state_;
}

bool Rule::operator==(const Rule& other) const {
  return (!(*this < other) && !(other < *this));
}

std::istream& operator>>(std::istream& input, Rule& rule) {
  std::string new_rule;
  input >> new_rule;
  rule = Rule(new_rule);
  return input;
}

std::ostream& operator<<(std::ostream& output, const Rule& rule) {
  output << rule.start_state_ << kSeparator << rule.finish_state_;
  return output;
}
