//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_DEPARTUREEVENT_H
#define CAFETERIASIMULATION_DEPARTUREEVENT_H


#include "Event.h"

class FoodServer;

class DepartureEvent : public Event {
private:
    FoodServer* server;
public:
    DepartureEvent (FoodServer* s);
    void handle ();
};


#endif //CAFETERIASIMULATION_DEPARTUREEVENT_H
