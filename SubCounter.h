//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_SUBCOUNTER_H
#define CAFETERIASIMULATION_SUBCOUNTER_H


#include "FoodServer.h"
#include "Customer.h"
#include <vector>

class Counter;

class SubCounter { // facility in MSQS
private:
    int id_;
    int level_;
    vector <FoodServer* > servers;
    Counter* counter_;
    SubCounter* next_;
public:
    SubCounter (int id, int lvl, int n, Counter* c, SubCounter* nxt);
    void initialize ();
    void arrivalHandler (Customer* cus);

private:
    FoodServer* getShortestQueueServer();

};


#endif //CAFETERIASIMULATION_SUBCOUNTER_H
