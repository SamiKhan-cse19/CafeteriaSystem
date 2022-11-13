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

}

void Counter::arrivalHandler() {
    /// check if termination event has occurred - no more arrivals

    /// customers arrival in batches

    // determine batch size (Discrete Random)
    int batchSize = discreteRandom();

    for ( int i = 0; i < batchSize; i ++ ) {
        // create customer
        customerArrived_++;
        Customer *newCustomer = new Customer(customerArrived_);

        /// send customer to first sub-counter
    }
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

}
