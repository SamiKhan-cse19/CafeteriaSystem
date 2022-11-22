//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_EVALUATIONEVENT_H
#define CAFETERIASIMULATION_EVALUATIONEVENT_H


#include "Event.h"

class FoodServer;

class EvaluationEvent : public Event {
private:
    FoodServer* server;
public:
    EvaluationEvent (FoodServer* s);
    void handle ();
};


#endif //CAFETERIASIMULATION_EVALUATIONEVENT_H
