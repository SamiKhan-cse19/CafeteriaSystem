//
// Created by Win10 on 11/13/2022.
//

#include <iostream>
#include <fstream>
#include "SubCounter.h"
#include "Scheduler.h"
#include "FoodServer.h"
#include "Counter.h"


SubCounter::SubCounter(int id, int lvl, double prob, double unit, double minA, double maxA, int n, Counter *c, vector<SubCounter*>* nxt) : id_(id), level_(lvl), probability_(prob), counter_(c), next_(nxt), foodUnit_(unit), minAmount_(minA), maxAmount_(maxA) {
    // initialize servers vector
    this->servers = vector<FoodServer*>(n);
    for (int i = 0; i < servers.size(); ++i) {
        servers[i] = new FoodServer(i, maxAmount_, 40.0, 4.0, 13.0, 5.0, 7.0, this);

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
    return to_string(counter_->id()) + "-" + to_string(level_) + "-" + to_string(id_);
}

void SubCounter::departureHandler(Customer *cus) {
    if (cus -> path().empty()) {
        // customer has finished service
        return;
    }
    pair<SubCounter*, pair<double, double> > psas = cus -> path().front();
    cus -> path().pop();
    SubCounter* nextSubCounter = psas.first;
    double amount = psas.second.first;
    double serviceTime = psas.second.second;
    cus -> foodAmount() = amount;
    cus -> serviceTime() = serviceTime;
    nextSubCounter -> arrivalHandler(cus);
}

double SubCounter::getCustomerAmount() {
    double u = (double)rand() / RAND_MAX;
    double l = minAmount_ / foodUnit_;
    double h = maxAmount_ / foodUnit_;
    return foodUnit_ * floor(l + (h - l + 1) * u );
}

void SubCounter::terminationHandler() {
    for (auto s : servers) {
        s -> terminationHandler();
    }
}

void SubCounter::report() {
    cout << "Sub-counter: " << id() << endl;
    for (auto s : servers) {
        s -> report();
    }

}

double SubCounter::getCustomerServiceTime() {
    FoodServer* server = servers[0];
    return server -> getCustomerServiceTime();
}

void SubCounter::setMinLevel(bool l) {
    for (auto s : servers) {
        if (l == 0) s -> minLevel() = maxAmount_;
        else s -> minLevel() = 2 * maxAmount_;
    }
}

void SubCounter::setEvaluationInterval(double i) {
    for (auto s : servers)
        s -> evaluationInterval() = i;
}
