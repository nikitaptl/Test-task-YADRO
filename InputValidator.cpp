#include "InputValidator.h"

InputValidator::InputValidator() {
  input_file = std::ifstream("test_file.txt");
  is_open = input_file.is_open();
}

InputValidator::InputValidator(const std::string &path) {
  input_file = std::ifstream(path);
  is_open = input_file.is_open();
}

Response<unsigned int> InputValidator::validateInt() {
  std::string str;
  std::getline(input_file, str);
  if (!input_file) {
    error_message = "ERROR: the file is empty or the input data is insufficient";
    return Response<unsigned int>();
  }
  try {
    table_num = std::stoul(str);
  }
  catch (const std::invalid_argument &e) {
    error_message = std::format("{}\nERROR: invalid integer argument ({})", str, e.what());
    return Response<unsigned int>();
  }
  catch (const std::out_of_range &e) {
    error_message = std::format("{}\nERROR: out of range ({})", str, e.what());
    return Response<unsigned int>();
  }
  return Response<unsigned int>(table_num);
}

Response<std::vector<std::string>> InputValidator::validateTime() {
  std::string str;
  std::getline(input_file, str);
  if (!input_file) {
    error_message = "ERROR: the file is empty or the input data is insufficient";
    return Response<std::vector<std::string>>();
  }
  if (std::regex regex(rg1); !std::regex_match(str, regex)) {
    error_message = "ERROR: invalid time format";
    return Response<std::vector<std::string>>();
  } else {
    std::vector<std::string> result;
    result.reserve(4);
    for(int i = 0; i < str.size(); i += 3) {
      result.push_back(str.substr(i, 2));
    }
    return Response<std::vector<std::string>>{result};
  }
}

Response<std::vector<Event>> InputValidator::validateEvents() {
  if (!input_file) {
    error_message = "ERROR: file is empty";
    return Response<std::vector<Event>>();
  }
  std::vector<Event> result;
  std::regex regex(rg2);
  std::string str;
  std::getline(input_file, str);
  std::istringstream iss;
  std::vector<std::string> parts;
  parts.reserve(4);
  while (input_file) {
    if(!std::regex_match(str, regex)) {
      error_message = "ERROR: invalid event format";
      return Response<std::vector<Event>>();
    }
    iss = std::istringstream(str);
    std::string part;
    while(iss >> part) {
      parts.push_back(part);
    }
    Time time{(uint16_t)std::stoul(parts[0].substr(0, 2)), (uint16_t)std::stoul(parts[0].substr(3, 2))};
    uint8_t type = std::stoul(parts[1]);
    std::string name = parts[2];
    Event event;
    if(parts.size() == 4) {
      if(type != 2) {
        error_message = "ERROR: invalid event format";
        return Response<std::vector<Event>>();
      }
      unsigned int table = std::stoul(parts[4]);
      if(table > table_num) {
        error_message = "ERROR: incorrect table number in event";
        return Response<std::vector<Event>>();
      }
      event = EventTable{time, type, name, table};
    }
    else {
      event = Event{time, type, name};
    }
    result.push_back(event);
    parts.clear();
  }
}

void InputValidator::stop() {
  input_file.close();
}

InputValidator::~InputValidator() {
  stop();
}