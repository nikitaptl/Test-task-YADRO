#include "entities.h"
#include <unordered_map>
#include <queue>
#include <cmath>

#ifndef TEST_TASK_YADRO__COMPUTER_CLUB_H_
#define TEST_TASK_YADRO__COMPUTER_CLUB_H_

struct Table {
  bool is_free = true;
  uint64_t total_revenue = 0;
  Time total_time = Time{0, 0};
  Time curr_time;

  void sit(Time time) {
    is_free = false;
    curr_time = time;
  }

  void leave(Time time, unsigned int cost) {
    total_revenue += std::ceil(double(time.get_minutes() - curr_time.get_minutes()) / 60) * cost;
    total_time = Time(total_time.get_minutes() - curr_time.get_minutes() +
        time.get_minutes());
    is_free = true;
  }
};

struct Client {
  std::string name;
  Table *curr_table = nullptr;

  Client() = default;
  Client(std::string name) : name(name) {}
};

class computer_club {
 private:
  unsigned int table_num;
  unsigned int free_tables;
  unsigned int cost;
  Time start_time;
  Time end_time;
  std::unordered_map<std::string, Client> clients;
  Table *tables;
  std::queue<Client *> waiting;
 public:
  computer_club();
  computer_club(unsigned int table_num, unsigned int cost, Time start_time, Time end_time);
  Response<Event> process_event(Event &event);
  Table *close();
};

#endif //TEST_TASK_YADRO__COMPUTER_CLUB_H_
