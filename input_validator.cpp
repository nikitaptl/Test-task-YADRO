#include "input_validator.h"
const std::string INVALID_TIME_FORMAT = "ERROR: invalid time format";
const std::string INVALID_EVENT_FORMAT = "ERROR: invalid event format";
const std::string INVALID_FILE_FORMAT = "ERROR: the file is empty or the input data is insufficient";

input_validator::input_validator() {
  input_file = std::ifstream("test_file.txt");
  is_open = input_file.is_open();
}

input_validator::input_validator(const std::string &path) {
  input_file = std::ifstream(path);
  is_open = input_file.is_open();
}

Response<unsigned int> input_validator::validate_int() {
  std::string str;
  std::getline(input_file, str);
  if (!input_file) {
    error_message = INVALID_FILE_FORMAT;
    return Response<unsigned int>();
  }
  try {
    table_num = std::stoul(str);
  }
  catch (const std::invalid_argument &e) {
    error_message = str + "\nERROR: invalid integer argument (" + e.what() + ")";
    return Response<unsigned int>();
  }
  catch (const std::out_of_range &e) {
    error_message = str + "\nERROR: out of range (" + e.what() + ")";
    return Response<unsigned int>();
  }
  return Response<unsigned int>(table_num);
}

Response<std::pair<Time, Time>>
input_validator::validateTime() {
  std::string str;
  std::getline(input_file, str);
  if (!input_file) {
    error_message = INVALID_FILE_FORMAT;
    return Response<std::pair<Time, Time>>
        ();
  }
  if (std::regex regex(rg1); !std::regex_match(str, regex)) {
    error_message = INVALID_TIME_FORMAT;
    return Response<std::pair<Time, Time>>
        ();
  }
  std::pair<Time, Time> result{Time{(uint16_t) std::stoul(str.substr(0, 2)), (uint16_t) std::stoul(str.substr(3, 2))},
                               Time{(uint16_t) std::stoul(str.substr(6, 2)), (uint16_t) std::stoul(str.substr(9, 2))}};
  if (result.second < result.first) {
    error_message = INVALID_TIME_FORMAT;
    return Response<std::pair<Time, Time>>
        ();
  }
  return Response(result);
}

Response<std::vector<Event>>
input_validator::validateEvents() {
  std::string str;
  std::getline(input_file, str);
  if (!input_file) {
    error_message = INVALID_FILE_FORMAT;
    return Response<std::vector<Event>>
        ();
  }
  std::vector<Event> result;
  std::vector<std::string> parts; // for parts of event
  parts.reserve(4);

  std::regex regex(rg2);
  std::istringstream iss;
  // We also need to check if events go sequentially
  Time previous_time = Time{0, 0};
  while (input_file) {
    if (!std::regex_match(str, regex)) {
      error_message = INVALID_EVENT_FORMAT;
      return Response<std::vector<Event>>();
    }
    iss = std::istringstream(str);
    for (std::string part; iss >> part;) {
      parts.push_back(part);
    }
    Time time{(uint16_t) std::stoul(parts[0].substr(0, 2)), (uint16_t) std::stoul(parts[0].substr(3, 2))};
    if (time < previous_time) {
      error_message = INVALID_EVENT_FORMAT;
      return Response<std::vector<Event>>
          ();
    }
    uint16_t type = std::stoul(parts[1]);
    std::string name = parts[2];
    Event event;
    if (parts.size() == 4) {
      if (type != 2) {
        error_message = INVALID_EVENT_FORMAT;
        return Response<std::vector<Event>>
            ();
      }
      unsigned int table = std::stoul(parts[3]);
      if (table > table_num) {
        error_message = INVALID_EVENT_FORMAT;
        return Response<std::vector<Event>>
            ();
      }
      event = Event{time, type, name, table};
    } else {
      event = Event{time, type, name};
    }
    result.push_back(event);
    parts.clear();
    previous_time = time;
    std::getline(input_file, str);
  }
  return result;
}

void input_validator::stop() {
  input_file.close();
}

input_validator::~input_validator() {
  stop();
}