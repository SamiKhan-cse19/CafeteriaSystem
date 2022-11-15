//
// Created by Win10 on 11/13/2022.
//

#include "Counter.h"
#include "Customer.h"
#include <cstdlib>
#include <cmath>

int Counter :: customerArrived_ = 0;

Counter::Counter(int id) : id_(id), a_(this), t_(this){
    customerArrived_ = 0;
}

double Counter :: exponential(double mean) {

    double r = (double)rand()/(RAND_MAX+1);
    double ex = -mean * log (r);
    return ex;

}

void Counter :: initialize () {
    /// initialize the state variables
    allowArrival_ = true;

    /// instantiate sub-counters (bottom-up)
//    [
//        [Rice, Bread],
//        [Dessert],
//        [Fish, Chicken, Meat],
//        [Raita],
//        [Dal]
//    ]
    // level 4
    SubCounter* dal = new SubCounter(0, 3, 1, this, nullptr);

    // level 3
    SubCounter* raita = new SubCounter(1, 3, 1, this, nullptr);

    // level 2
    SubCounter* fish = new SubCounter(0, 2, 1, this, nullptr);
    SubCounter* chicken = new SubCounter(1, 2, 1, this, nullptr);
    SubCounter* meat = new SubCounter(2, 2, 1, this, nullptr);

    // level 1
    SubCounter* dessert = new SubCounter(0, 1, 1, this, nullptr);

    // level 0
    SubCounter* rice = new SubCounter(0, 0, 1, this, nullptr);
    SubCounter* bread = new SubCounter(1, 0, 1, this, nullptr);

    /// initialize sub-counters and prababilities
    subCounters = vector<vector<SubCounter*> >(
            { { rice, bread },
               { dessert },
               { fish, chicken, meat },
               { raita },
               { dal } }
               );
    probabilities = vector<vector<double> >(
            { { 0.7, 0.3 },
              { 0.9 },
              { 0.2, 0.4, 0.4 },
              { 0.4 },
              { 0.7 } }
            );

    for (auto vs : subCounters) {
        for (auto sc : vs) {
            sc -> initialize();
        }
    }

    /// trigger first arrival event
    double t = exponential(arrivalMean_);
    /// trace file output
    a_.activate(t);

    /// trigger termination event
    t_.activate(150.0); // 150 min or 2:30 hrs
}

void Counter::arrivalHandler() {
    // check if termination event has occurred - no more arrivals
    if (!allowArrival_) {
        return;
    }
    /// customers arrival in batches

    // determine batch size (Discrete Random)
    int batchSize = discreteRandom();

    for ( int i = 0; i < batchSize; i ++ ) {
        // instantiate new customer
        Customer *newCustomer = new Customer(customerArrived_ ++);

        /// send customer to first sub-counter
        double u = (double)rand() / RAND_MAX;
        double s = 0.0;
        for (int j = 0; j < probabilities[0].size(); ++j) {
            if (u < s + probabilities[0][j]) {
                subCounters[0][j] ->arrivalHandler(newCustomer);
                break;
            }
            s += probabilities[0][j];
        }
    }

    // trigger next arrival event
    double t = exponential(arrivalMean_);
    /// trace file output
    a_.activate(t);
}

int Counter::discreteRandom() {
    // for determining batch size (number of customers arriving at a time)
    double u = (double)rand() / RAND_MAX;
    if(u<0.1667) return 1;
    else if(u<0.5001) return 2;
    else if(u<0.8335) return 3;
    return 4;
}

void Counter::terminationHandler() {
    /// disable any more arrivals - simulation will end automatically
    allowArrival_ = false;
}
