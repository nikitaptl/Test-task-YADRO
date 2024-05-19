#include <iostream>
#include <fstream>
#include "InputValidator.h"

int main(int argc, char *argv[]) {
  InputValidator input_validator("../test_file.txt");
  if (!input_validator.is_open) {
    std::cout << "ERROR: can not open file" << std::endl;
  }

  unsigned int table_num;
  if (auto [is_correct, value] = input_validator.validateInt(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    table_num = value;
  }

  std::vector<std::string> times;
  if (auto [is_correct, value] = input_validator.validateTime(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    times = value;
  }
  std::cout << (input_validator.input_file ? "HERE" : "NO ^(");

  unsigned int cost;
  if (auto [is_correct, value] = input_validator.validateInt(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    cost = value;
  }

  std::vector<Event> events;
  input_validator.validateEvents();
  if(auto [is_correct, value] = input_validator.validateEvents(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  }
  else {
    events = value;
  }
  return 0;
}
