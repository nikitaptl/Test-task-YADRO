#include "input_validator.h"
#include "computer_club.h"

int main(int argc, char *argv[]) {
  input_validator input_validator("../test_file.txt");
  if (!input_validator.is_open) {
    std::cout << "ERROR: can not open file" << std::endl;
  }

  unsigned int table_num;
  if (auto [is_correct, value] = input_validator.validate_int(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    table_num = value;
  }

  std::pair<Time, Time> times;
  if (auto [is_correct, value] = input_validator.validateTime(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    times = value;
  }

  unsigned int cost;
  if (auto [is_correct, value] = input_validator.validate_int(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    cost = value;
  }

  std::vector<Event> events;
  if(auto [is_correct, value] = input_validator.validateEvents(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  }
  else {
    events = value;
  }
  return 0;
}
