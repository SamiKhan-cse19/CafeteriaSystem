//
// Created by Win10 on 11/13/2022.
//

#include "FoodServer.h"
#include "Scheduler.h"

FoodServer::FoodServer(int id, double minLevel, double maxLevel, double departureMean, double evaluationInterval, double refillMinLag, double refillMaxLag, double customerMinAmount, double customerMaxAmount) : id_(id), d_(this), e_(this), r_(this) {
    minLevel_ = minLevel;
    maxLevel_ = maxLevel;
    departureMean_ = departureMean;
    evaluationInterval_ = evaluationInterval;
    refillMaxLag_ = refillMinLag;
    refillMaxLag_ = refillMaxLag;
    customerMinAmount_ = customerMinAmount;
    customerMaxAmount_ = customerMaxAmount;
}

void FoodServer::initialize() {
    status_ = 0;
    foodLevel_ = maxLevel_;

    customersArrived_ = 0;
    customersServed_ = 0;
    customerInService_ = nullptr;

    timeLastEvent_ = 0.0;
    areaQueue_ = 0.0;
    areaFoodLevel_ = 0.0;
    totalQueueingDelay_ = 0.0;

    /// trigger first evaluation event
    e_.activate(evaluationInterval_);
}

void FoodServer::departureHandler() {
    /// a customer has finished service at a server

    // send to next sub-counter
}

void FoodServer::evaluationHandler() {
    if (foodLevel_ < minLevel_) {
        double t = refillMinLag_ + (refillMaxLag_ - refillMinLag_) * (double)rand()/(RAND_MAX);
        r_.activate(t);
    }
}

void FoodServer::refillHandler() {
    foodLevel_ = maxLevel_;
    if (status() == 1) {
        foodLevel_ -= customerInService_ -> foodAmount();
        double t = exponential(departureMean_);
        /// trace file output
        d_.activate(t);
    }
}

void FoodServer::arrivalHandler(Customer* cus) {
    // server arrival handler from MSQS scenario 2
    customersArrived_ ++;
    /// trace file output
    if (status() == 0) {
        status() = 1;
        customerInService_ = cus;
        // calculate delay
        delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
        totalQueueingDelay_ += delay_;

        /// calculate customer food portion
        double u = customerMinAmount_ + (customerMaxAmount_ - customerMinAmount_) * (double)rand()/(RAND_MAX);
        customerInService_ -> foodAmount() = u;

        /// check if food is available
        if(customerInService_ -> foodAmount() < foodLevel_) {
            // if yes, decrease food level and trigger departure event from server
            foodLevel_ -= customerInService_ -> foodAmount();
            double t = exponential(departureMean_);
            /// trace file output
            d_.activate(t);
        }

    } else {
        queue_.push(cus);
    }
}

double FoodServer::exponential(double mean) {
    double r = (double)rand()/(RAND_MAX);
    double ex = -mean * log (r);
    return ex;
}
