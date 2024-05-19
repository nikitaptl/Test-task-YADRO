#include "Entities.h"
#include <iostream>
#include <memory>
#include <vector>
#include <format>
#include <regex>
#include <fstream>
#include <sstream>

#ifndef TEST_TASK_YADRO_INPUTVALIDATOR_H
#define TEST_TASK_YADRO_INPUTVALIDATOR_H

const std::string rg1 = "\\b([0-1][0-9]|2[0-3]):([0-5][0-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])\\b";
const std::string rg2 = "\\b([0-1][0-9]|2[0-3]):([0-5][0-9]) [1-4] [a-z0-9_-]+( [1-9]+[0-9]*)?\\b";

class InputValidator {
 public:
  std::ifstream input_file;
  bool is_open;
  unsigned int table_num;
  std::string error_message;

  InputValidator();
  InputValidator(const std::string &path);

  Response<unsigned int> validateInt();
  Response<std::vector<std::string>> validateTime();
  Response<std::vector<Event>> validateEvents();
  void stop();
  ~InputValidator();
};

#endif //TEST_TASK_YADRO_INPUTVALIDATOR_H
