#pragma once
#include <exception>

class IncorrectInputError : public std::exception {
  const char *what() const noexcept override {
    return "Incorrect format of rule";
  }
};

class StartStateError : public std::exception {
  const char *what() const noexcept override {
    return "Start state too long or too short (supports only N->finish format)";
  }
};