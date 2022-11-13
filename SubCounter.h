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
    vector <FoodServer* > servers;
    Counter* counter;
public:
    SubCounter (int id, int numOfServers, Counter* c);
    void initialize ();
    void arrivalHandler (Customer* cus);

};


#endif //CAFETERIASIMULATION_SUBCOUNTER_H
