//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_ARRIVALEVENT_H
#define CAFETERIASIMULATION_ARRIVALEVENT_H


#include "Event.h"

class Counter;

class ArrivalEvent : public Event {
private:
    Counter* counter;
public:
    ArrivalEvent (Counter* c) : counter(c) { }
    void handle ();
};


#endif //CAFETERIASIMULATION_ARRIVALEVENT_H
