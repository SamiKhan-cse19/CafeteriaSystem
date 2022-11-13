//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_RESTOCKEVENT_H
#define CAFETERIASIMULATION_RESTOCKEVENT_H


#include "FoodServer.h"

class RestockEvent : public Event {
private:
    FoodServer* server;
public:
    RestockEvent (FoodServer* s);
    void handle ();
};


#endif //CAFETERIASIMULATION_RESTOCKEVENT_H
