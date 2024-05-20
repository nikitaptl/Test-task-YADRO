#include "computer_club.h"

computer_club::computer_club() : table_num(10),
                                 cost(70),
                                 start_time(Time{0, 0}),
                                 end_time(Time{23, 0}),
                                 free_tables(10) {
  tables = new Table[table_num];
};

computer_club::computer_club(unsigned int table_num, unsigned int cost, Time start_time, Time end_time) : table_num(
    table_num),
                                                                                                          cost(cost),
                                                                                                          start_time(
                                                                                                              start_time),
                                                                                                          end_time(
                                                                                                              end_time),
                                                                                                          free_tables(
                                                                                                              table_num) {
  tables = new Table[table_num];
};

computer_club::~computer_club() {
  delete[] tables;
}

Response<Event> computer_club::process_event(Event &event) {
  switch (event.type) {
    Client *client; // for code readability
    Table *table;
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
      table = &tables[event.table_num - 1];
      if (!table->is_free) {
        return Response<Event>(Event{event.time, 13, "PlaceIsBusy"});
      }
      client = &clients[event.name];
      if (client->curr_table != nullptr) {
        client->curr_table->leave(event.time, cost);
        free_tables++;
      }
      client->curr_table = table;
      table->sit(event.time);
      free_tables--;
      break;
    case 3:
      if (free_tables != 0) {
        return Response<Event>(Event{event.time, 13, "ICanWaitNoLonger!"});
      }
      if (waiting.size() > table_num) {
        return Response<Event>(Event{event.time, 11, event.name});
      }
      waiting.push(&clients[event.name]);
      break;
    case 4:
      if (clients.find(event.name) == clients.end()) {
        return Response<Event>(Event{event.time, 13, "ClientUnknown"});
      }
      client = &clients[event.name];
      if (client->curr_table != nullptr) {
        table = client->curr_table;
        table->leave(event.time, cost);
        free_tables++;
        if (waiting.size() != 0) {
          std::string name_waiting = waiting.front()->name;
          waiting.front()->curr_table = table;
          waiting.pop();
          table->sit(event.time);
          free_tables--;
          clients.erase(event.name);
          return Response<Event>(Event{event.time, 12, name_waiting, (unsigned int) (table - tables)});
        }
      }
      clients.erase(event.name);
      break;
  }
  return Response<Event>();
}

Table *computer_club::close() {
  for (unsigned int i = 0; i < table_num; i++) {
    if (!tables[i].is_free) {
      tables[i].leave(end_time, cost);
    }
  }
  return tables;
}