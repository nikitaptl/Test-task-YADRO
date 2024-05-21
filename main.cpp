#include "input_validator.h"
#include "computer_club.h"

int main(int argc, char *argv[]) {
  std::string file_path;
  if (argc != 2) {
    file_path = "../test_file.txt";
  } else {
    file_path = argv[1];
  }
  input_validator input_validator(file_path);
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
  std::cout << times.first.to_string() << std::endl;
  if (auto [is_correct, value] = input_validator.validateEvents(); !is_correct) {
    std::cout << input_validator.error_message << std::endl;
    return 1;
  } else {
    events = value;
  }

  computer_club club(table_num, cost, times.first, times.second);
  for (auto event : events) {
    std::cout << event.to_string() << std::endl;
    if (auto [is_new, new_event] = club.process_event(event); is_new) {
      std::cout << new_event.to_string() << std::endl;
    }
  }
  std::cout << times.second.to_string() << std::endl;
  Table *tables = club.close();
  for (int i = 0; i < table_num; i++) {
    std::cout << std::format("{} {} {}", i + 1, tables[i].total_revenue, tables[i].total_time.to_string()) << std::endl;
  }
  return 0;
}
