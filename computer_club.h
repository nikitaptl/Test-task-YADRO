#include "entities.h"
#include <unordered_map>
#include <queue>

#ifndef TEST_TASK_YADRO__COMPUTER_CLUB_H_
#define TEST_TASK_YADRO__COMPUTER_CLUB_H_

class Table {
  bool is_free;
  uint64_t total_revenue;
  Time total_time;
};

class Client {
  int name;
  Table *curr_table;
};

class computer_club {
 private:
  unsigned int table_num;
  unsigned int cost;
  Time start_time;
  Time end_time;
  std::unordered_map<std::string, Client> clients;
  Table *tables;
  std::queue<Client *> waiting;
 public:
  computer_club();
  computer_club(unsigned int table_num, unsigned int cost, Time start_time, Time end_time);
  Response<std::string> process_event();
};

#endif //TEST_TASK_YADRO__COMPUTER_CLUB_H_
