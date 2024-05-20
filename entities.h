#include <memory>
#include <format>

#ifndef TEST_TASK_YADRO__ENTITIES_H_
#define TEST_TASK_YADRO__ENTITIES_H_

struct Time {
  uint16_t hours;
  uint16_t minutes;

  Time() : hours(0), minutes(0) {}
  Time(uint16_t minutes) : hours(minutes / 60), minutes(minutes) {}
  Time(uint16_t hours, uint16_t minutes) : hours(hours), minutes(minutes) {}

  uint16_t get_minutes() const {
    return hours * 60 + minutes;
  };

  bool operator<(const Time &time) const {
    return get_minutes() < time.get_minutes();
  }

  bool operator==(const Time &time) const {
    return hours == time.hours && minutes == time.minutes;
  }

  bool operator<=(const Time &time) const {
    return get_minutes() <= time.get_minutes();
  }

  std::string to_string() const {
    return std::format("{:02d}:{:02d}", hours, minutes);
  }
};

struct Event {
  Time time;
  uint16_t type;
  std::string name;
  unsigned int table_num = 0;

  Event() = default;
  Event(Time time, uint16_t type, std::string name) : time(time), type(type), name(name) {};
  Event(Time time, uint16_t type, std::string name, unsigned int table_num)
      : time(time), type(type), name(name), table_num(table_num) {};
};

struct EventTable : public Event {
  unsigned int table_num;
};

template<typename T>
struct Response {
  bool is_correct;
  T result;

  Response() {
    is_correct = false;
    Time t1, t2;
  }

  Response(T value) {
    is_correct = true;
    result = value;
  }
};

#endif //TEST_TASK_YADRO__ENTITIES_H_
