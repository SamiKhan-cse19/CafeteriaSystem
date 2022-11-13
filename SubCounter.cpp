//
// Created by Win10 on 11/13/2022.
//

#include "SubCounter.h"

SubCounter::SubCounter(int id, int numOfServers, Counter *c) : id_(id), counter(c) {
    // initialize servers vector
    this->servers = vector<FoodServer*>(numOfServers);
}

void SubCounter::arrivalHandler(Customer *cus) {
    /// choose server and admit customer

    // check for idle servers

    // check for shortest queue
}

void SubCounter::initialize() {
    /// call initialize on servers
    for (int i = 0; i < servers.size(); ++i) {
        servers[i] = new FoodServer();
    }
}
