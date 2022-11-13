//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_TERMINATIONEVENT_H
#define CAFETERIASIMULATION_TERMINATIONEVENT_H


#include "Event.h"
#include "Counter.h"

class TerminationEvent : public Event {
private:
    Counter* counter;
public:
    TerminationEvent (Counter* c) : counter(c) { }
    void handle ();
};


#endif //CAFETERIASIMULATION_TERMINATIONEVENT_H
