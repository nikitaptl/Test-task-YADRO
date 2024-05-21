#include "entities.h"
#include <iostream>
#include <memory>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>

#ifndef TEST_TASK_YADRO_INPUTVALIDATOR_H
#define TEST_TASK_YADRO_INPUTVALIDATOR_H

const std::string rg1 = "\\b([0-1][0-9]|2[0-3]):([0-5][0-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])\\b";
const std::string rg2 = "\\b([0-1][0-9]|2[0-3]):([0-5][0-9]) [1-4] [a-z0-9_-]+( [1-9]+[0-9]*)?\\b";

class input_validator {
 private:
  std::ifstream input_file;
  unsigned int table_num;
 public:
  bool is_open;
  std::string error_message;

  input_validator();
  input_validator(const std::string &path);

  Response<unsigned int> validate_int();
  Response<std::pair<Time, Time>> validateTime();
  Response<std::vector<Event>> validateEvents();
  void stop();
  ~input_validator();
};

#endif //TEST_TASK_YADRO_INPUTVALIDATOR_H
