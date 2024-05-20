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
Response<Event> computer_club::process_event(Event &event) {
  switch (event.type) {
    case 1:
      if (clients.find(event.name) != clients.end()) {
        return Response<Event>(Event{event.time, 13, "YouShallNotPass"});
      }
      if (event.time < start_time || end_time < event.time) {
        return Response<Event>(Event{event.time, 13, "NotOpenYet"});
      }
      clients[event.name] = Client(event.name);
      break;
    case 2:
      if (clients.find(event.name) == clients.end()) {
        return Response<Event>(Event{event.time, 13, "ClientUnknown"});
      }
      Table &table = tables[event.table_num]; // for code readability
      if (!table.is_free) {
        return Response<Event>(Event{event.time, 13, "PlaceIsBusy"});
      }
      Client &client = clients[event.name]; // for code readability
      if (client.curr_table != nullptr) {
        client.curr_table->leave(event.time, cost);
      }
      table.sit(event.time);
      client.curr_table = &table;
      break;
    case 3:
      break;
    case 4:
      break;
  }
}