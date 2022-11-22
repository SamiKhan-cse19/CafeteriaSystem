//
// Created by Win10 on 11/13/2022.
//

#include <iostream>
#include "FoodServer.h"
#include "Scheduler.h"
#include "SubCounter.h"

ofstream FoodServer :: trace_;

FoodServer::FoodServer(int id, double minLevel, double maxLevel, double departureMean, double evaluationInterval, double refillMinLag, double refillMaxLag, double customerMinAmount, double customerMaxAmount, SubCounter* sc) : id_(id), subCounter_(sc), d_(this), e_(this), r_(this) {
    minLevel_ = minLevel;
    maxLevel_ = maxLevel;
    departureMean_ = departureMean;
    evaluationInterval_ = evaluationInterval;
    refillMinLag_ = refillMinLag;
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
    if (queueLength() > 0) {
        trace_<<"d\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
    } else {
        trace_<<"d\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
    }

    customersArrived_ ++;
    serverDelay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
    totalServerDelay_ += serverDelay_;

    Customer* exitingCustomer = customerInService_;

    if (queueLength() > 0) {
        customerInService_ = queue_.front();
        queue_.pop();

        trace_<<"s\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
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
            trace_<< "\tservice time = " << t << endl;
            d_.activate(t);
        }

    } else {
        status() = 0;
        customerInService_ = nullptr;
    }

    /// send to next sub-counter
    subCounter_ ->departureHandler(exitingCustomer);
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
    trace_<<"a\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cus->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
    if (status() == 0) {
        status() = 1;
        trace_<<"s\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cus->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
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
            trace_<< "\tservice time = " << t << endl;
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

std::ostream &operator<<(std::ostream &os, const FoodServer &server) {
    os << "id_: " << server.id_ << " minLevel_: " << server.minLevel_ << " maxLevel_: " << server.maxLevel_
       << " departureMean_: " << server.departureMean_ << " evaluationInterval_: " << server.evaluationInterval_
       << " refillMinLag_: " << server.refillMinLag_ << " refillMaxLag_: " << server.refillMaxLag_
       << " customerMinAmount_: " << server.customerMinAmount_ << " customerMaxAmount_: " << server.customerMaxAmount_;
    return os;
}

void FoodServer::createTraceFile() {
    trace_.open ("trace.out", ios::out);
    if (!trace_) {
        cout << "cannot open the trace file.\n";
    }
    trace_<< "trace file for the simulation" << endl;
    trace_ << "format of the file" << endl;
    trace_ << "<event> <sid,scid,sclvl,cid> <time> <cus id> <server status> <queue size> <food level>" << endl << endl;
}

string FoodServer::getServerAddress() {
    return to_string(id_) + "," + subCounter_->getAddress();
}
