#include "computer_club.h"

computer_club::computer_club() : table_num(10),
                                 cost(70),
                                 start_time(Time{0, 0}),
                                 end_time(Time{23, 0}) {
  tables = new Table[table_num];
};

computer_club::computer_club(unsigned int table_num, unsigned int cost, Time start_time, Time end_time) : table_num(
    table_num),
                                                                                                          cost(cost),
                                                                                                          start_time(
                                                                                                              start_time),
                                                                                                          end_time(
                                                                                                              end_time) {
  tables = new Table[table_num];
};
Response<std::string> computer_club::process_event() {
}