//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_SUBCOUNTER_H
#define CAFETERIASIMULATION_SUBCOUNTER_H


#include "FoodServer.h"
#include "Customer.h"
#include <vector>
using namespace std;

class Counter;

class SubCounter { // facility in MSQS
private:
    int id_;
    int level_;
    double probability_;
    vector <FoodServer* > servers;
    Counter* counter_;
    vector<SubCounter*>* next_;
public:
    SubCounter (int id, int lvl, double prob, int n, Counter* c, vector<SubCounter*>* nxt);
    void initialize ();
    void arrivalHandler (Customer* cus);
    void departureHandler (Customer* cus);

    inline int& id() { return id_; }
    inline int& level() { return level_; }
    inline double& probability() { return probability_; }

    string getAddress();

private:
    FoodServer* getShortestQueueServer();

};


#endif //CAFETERIASIMULATION_SUBCOUNTER_H
