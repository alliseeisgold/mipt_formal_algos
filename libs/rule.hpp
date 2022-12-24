#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "exceptions.hpp"

class Rule {
 public:
  Rule();
  explicit Rule(const std::string& rule);
  [[nodiscard]] char GetStartState() const;
  [[nodiscard]] std::string GetFinishState() const;
  bool operator<(const Rule& other) const;
  bool operator==(const Rule& other) const;
  friend std::istream& operator>>(std::istream& input, Rule& rule);
  friend std::ostream& operator<<(std::ostream& output, const Rule& rule);

 private:
  char start_state_;
  std::string finish_state_;
};
