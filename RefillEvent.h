//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_REFILLEVENT_H
#define CAFETERIASIMULATION_REFILLEVENT_H


#include "FoodServer.h"

class RefillEvent : public Event {
private:
    FoodServer* server;
public:
    RefillEvent (FoodServer* s);
    void handle ();
};


#endif //CAFETERIASIMULATION_REFILLEVENT_H
