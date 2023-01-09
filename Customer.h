//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_CUSTOMER_H
#define CAFETERIASIMULATION_CUSTOMER_H


#include <queue>
#include <utility>
using namespace std;

class SubCounter;

class Customer {
private:
    int id_;
    Customer* next_;
    double systemArrivalTime_;
    double serverArrivalTime_;
    double foodAmount_;
    double serviceTime_;
    queue<pair<SubCounter*, pair<double, double> > > path_;  // pair<sub-counter, pair<amount, service-time>>

public:
    Customer (int id);

    inline queue<pair<SubCounter*, pair<double, double> > >& path() { return path_; }
    inline double& foodAmount() { return foodAmount_; }
    inline double& serviceTime() { return serviceTime_; }
    inline int& id() { return id_; }
    inline double& systemArrivalTime() { return systemArrivalTime_; }
    inline double& serverArrivalTime() { return serverArrivalTime_; }
    inline Customer* next() { return next_; }

};


#endif //CAFETERIASIMULATION_CUSTOMER_H
