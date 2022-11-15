//
// Created by Win10 on 11/13/2022.
//

#include "SubCounter.h"
#include "Scheduler.h"

SubCounter::SubCounter(int id, int lvl, int n, Counter *c, SubCounter *nxt) : id_(id), counter_(c), next_(nxt) {
    // initialize servers vector
    this->servers = vector<FoodServer*>(n);
    for (int i = 0; i < servers.size(); ++i) {
        servers[i] = new FoodServer(i, 0.0, 12.0, 4.0, 3.0, 5.0, 8.0, 1.0, 4.0);
    }
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
