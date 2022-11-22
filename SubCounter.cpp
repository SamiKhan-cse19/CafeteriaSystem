//
// Created by Win10 on 11/13/2022.
//

#include <iostream>
#include <fstream>
#include "SubCounter.h"
#include "Scheduler.h"
#include "FoodServer.h"
#include "Counter.h"


SubCounter::SubCounter(int id, int lvl, double prob, int n, Counter *c, vector<SubCounter*>* nxt) : id_(id), level_(lvl), probability_(prob), counter_(c), next_(nxt) {
    // initialize servers vector
    this->servers = vector<FoodServer*>(n);
    for (int i = 0; i < servers.size(); ++i) {
        servers[i] = new FoodServer(i, 0.0, 12.0, 4.0, 3.0, 5.0, 8.0, 1.0, 4.0, this);

//        // for testing purpose
//        cout<<*servers[i]<<endl;
    }

//    // for testing purposes
//    cout<<"Sub-counter: "<<id<<" "<<", level: "<<level_<<endl;
//    cout<<"Probability: "<<probability_<<endl;
//    cout<<"Number of Servers: "<<n<<endl;
//    if(next_) {
//        cout << "Next Sub-counter: { ";
//        for (auto sc: *next_) {
//            cout << sc->id_ << " ";
//        }
//        cout << "}"<< endl;
//    }
}

void SubCounter::initialize() {
    /// call initialize on servers
    for (int i = 0; i < servers.size(); ++i) {
        servers[i] -> initialize();
    }
}

void SubCounter::arrivalHandler(Customer *cus) {
    /// choose server and admit customer

    // find idle servers or server with the shortest queue
    FoodServer* server = getShortestQueueServer();
    cus -> serverArrivalTime() = Scheduler :: now();
    server ->arrivalHandler(cus);
}

FoodServer *SubCounter::getShortestQueueServer() {
    // get pointer to the server with the shortest number of customers
    // in case of tie, return leftmost one
    int sid = 0;
    for (int i = 0; i < servers.size(); ++i) {
        if (servers[i] -> status() + servers[i] -> queueLength()
            < servers[sid] -> status() + servers[sid] -> queueLength()) {
            sid = i;
        }
    }
    return servers[sid];
}

string SubCounter::getAddress() {
    return "(" + to_string(id_) +","+ to_string(level_) +","+ to_string(counter_->id()) + ")";
}

void SubCounter::departureHandler(Customer *cus) {

    if(!next_) {
        return;
    }

    double u = (double)rand() / RAND_MAX;
    double s = 0.0;
    for (int j = 0; j < next_->size(); ++j) {
        if (u < s + next_->at(j)->probability()) {
            next_->at(j)->arrivalHandler(cus);
            break;
        }
        s += next_->at(j)->probability();
    }
}
