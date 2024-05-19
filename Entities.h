#include <memory>

#ifndef TEST_TASK_YADRO__ENTITIES_H_
#define TEST_TASK_YADRO__ENTITIES_H_

class Time {
 public:
  uint16_t hours;
  uint16_t minutes;

  uint16_t get_minutes() {
    return hours * 60 + minutes;
  };
};

struct Event {
  Time time;
  uint16_t type;
  std::string name;
};

struct EventTable : public Event {
  unsigned int table_num;
};

template<typename T>
class Response {
 public:
  bool is_correct;
  T result;

  Response() {
    is_correct = false;
  }

  Response(T value) {
    is_correct = true;
    result = value;
  }
};

#endif //TEST_TASK_YADRO__ENTITIES_H_
