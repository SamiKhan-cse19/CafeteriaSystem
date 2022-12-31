//
// Created by Win10 on 11/13/2022.
//

#include <iostream>
#include "FoodServer.h"
#include "Scheduler.h"
#include "SubCounter.h"

ofstream FoodServer :: trace_;

FoodServer::FoodServer(int id, double minLevel, double maxLevel, double departureMean, double evaluationInterval, double refillMinLag, double refillMaxLag, SubCounter* sc) : id_(id), subCounter_(sc), d_(this), e_(this), r_(this) {
    minLevel_ = minLevel;
    maxLevel_ = maxLevel;
    departureMean_ = departureMean;
    evaluationInterval_ = evaluationInterval;
    refillMinLag_ = refillMinLag;
    refillMaxLag_ = refillMaxLag;
//    customerMinAmount_ = customerMinAmount;
//    customerMaxAmount_ = customerMaxAmount;
}

void FoodServer::initialize() {
    status_ = 0;
    foodLevel_ = maxLevel_;

    customersArrived_ = 0;
    customersServed_ = 0;
    customersLeft_ = 0;
    customerInService_ = nullptr;

    timeLastEvent_ = 0.0;
    areaBusy_ = 0.0;
    areaQueue_ = 0.0;
    areaFoodLevel_ = 0.0;
    totalQueueingDelay_ = 0.0;

    allowEvaluation_ = true;

    /// trigger first evaluation event
    e_.activate(evaluationInterval_);
}

void FoodServer::departureHandler() {
//    // debug
//    cout << "departure handler " << Scheduler :: now() << endl;

    /// update statistical variables
    updateStat();

    /// a customer has finished service at a server
    status() = 0;
    trace_<<"D\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

    customersServed_ ++;
    serverDelay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
    totalServerDelay_ += serverDelay_;

    /// send to next sub-counter
    subCounter_ ->departureHandler(customerInService_);

    if (queueLength() > 0) {
        customerInService_ = queue_.front();

        /// check if food is available
        if(customerInService_ -> foodAmount() < foodLevel_) {
            // if yes, decrease food level and trigger departure event from server
            status() = 1;
            queue_.pop();

            /// trace file output : service start
            trace_<<"S\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;


            // calculate delay
            delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
            totalQueueingDelay_ += delay_;

            foodLevel_ -= customerInService_ -> foodAmount();
            double t = exponential(departureMean_);
            /// trace file output
            trace_<< "\tservice time = " << t << endl;
//            cout << "service time = " << t << endl;
            d_.activate(t);
        } else {
            /// trace file output
            trace_ << "\tinsufficient food level"<<endl;
            customerInService_ = nullptr;

            if (!allowEvaluation_) {
                /// no more refill event, serve first customer with remaining food (If any) and clear queue
                if (foodLevel_ > 0) {
                    status() = 1;
                    customerInService_ = queue_.front();
                    queue_.pop();

                    // calculate delay
                    delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
                    totalQueueingDelay_ += delay_;
                    foodLevel_ = 0.0;

                    double t = exponential(departureMean_);
                    /// trace file output
                    trace_<< "\tservice time = " << t << endl;
//                    cout << "service time = " << t << endl;
                    d_.activate(t);
                }
                clearQueue();
            }
        }

    } else {
        customerInService_ = nullptr;
    }
}

void FoodServer::evaluationHandler() {
//    // debug
//    cout << "evaluation handler " << Scheduler :: now() << endl;

    /// No more evaluation and refill after termination
    if (!allowEvaluation_)
        return;

    /// update statistical variables
    updateStat();

    string cid_ = "X";
    if (customerInService_) {
        cid_ = to_string(customerInService_ -> id());
    }
    /// trace file output
    trace_<<"E\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cid_<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;
    if (foodLevel_ < minLevel_) {
        double t = refillMinLag_ + (refillMaxLag_ - refillMinLag_) * (double)rand()/(RAND_MAX);
        /// trace file output
        trace_<<"\tdelivery lag = "<<t<<endl;
//        cout << "delivery lag = " << t << endl;
        r_.activate(t);
    }

    /// trigger next evaluation event
    e_.activate(evaluationInterval_);

}

void FoodServer::refillHandler() {
//    // debug
//    cout << "refill handler " << Scheduler :: now() << endl;

    /// update statistical variables
    updateStat();

    foodLevel_ = maxLevel_;
    string cid_ = "X";

    /// trace file output
    trace_<<"R\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cid_<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

    if (status() == 0 && queueLength() > 0) {
        customerInService_ = queue_.front();

        /// check if food is available [Probably Redundant]
        if(customerInService_ -> foodAmount() < foodLevel_) {
            // if yes, decrease food level and trigger departure event from server
            status() = 1;
            queue_.pop();

            /// trace file output : service start
            trace_<<"S\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<customerInService_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

            // calculate delay
            delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
            totalQueueingDelay_ += delay_;

            foodLevel_ -= customerInService_ -> foodAmount();
            double t = exponential(departureMean_);
            /// trace file output
            trace_<< "\tservice time = " << t << endl;
//            cout << "service time = " << t << endl;
            d_.activate(t);
        } else {
            /// trace file output
            trace_ << "\tinsufficient food level"<<endl;
            customerInService_ = nullptr;

            if (!allowEvaluation_) {
                /// no more refill event, serve first customer with remaining food (If any) and clear queue
                if (foodLevel_ > 0) {
                    status() = 1;
                    customerInService_ = queue_.front();
                    queue_.pop();

                    // calculate delay
                    delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
                    totalQueueingDelay_ += delay_;
                    foodLevel_ = 0.0;

                    double t = exponential(departureMean_);
                    /// trace file output
                    trace_<< "\tservice time = " << t << endl;
//                    cout << "service time = " << t << endl;
                    d_.activate(t);
                }
                clearQueue();
            }
        }

    }
}

void FoodServer::arrivalHandler(Customer* cus) {
//    // debug
//    cout << "arrival handler " << Scheduler :: now() << endl;

    /// update statistical variables
    updateStat();

    customersArrived_ ++;
    /// trace file output
    /// <Event> <Server> <Time> <Customer ID> <Server Status> <Queue Size> <Food Level>
    trace_<<"A\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cus->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

    if (status() == 0) {  /// server is idle
        /// check if food is available
        if(cus -> foodAmount() < foodLevel_) {
            // if yes, make server busy, decrease food level and trigger departure event from server
            status() = 1;
            trace_<<"S\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<cus->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

            customerInService_ = cus;

            /// calculate delay
            delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
            totalQueueingDelay_ += delay_;

            foodLevel_ -= customerInService_ -> foodAmount();
            double t = exponential(departureMean_);
            /// trace file output
            trace_<< "\tservice time = " << t << endl;
//            cout << "service time = " << t << endl;
            d_.activate(t);
        } else {
            ///  trace file output
            trace_<<"\tinsufficient food level"<<endl;
            queue_.push(cus);
            customerInService_ = nullptr;

            if (!allowEvaluation_) {
                /// no more refill event, serve first customer with remaining food (If any) and clear queue
                if (foodLevel_ > 0) {
                    status() = 1;
                    customerInService_ = queue_.front();
                    queue_.pop();

                    // calculate delay
                    delay_ = Scheduler :: now() - customerInService_ -> serverArrivalTime();
                    totalQueueingDelay_ += delay_;
                    foodLevel_ = 0.0;

                    double t = exponential(departureMean_);
                    /// trace file output
                    trace_<< "\tservice time = " << t << endl;
//                    cout << "service time = " << t << endl;
                    d_.activate(t);
                }
                clearQueue();
            }
        }

    } else {
        trace_<<"\tserver busy"<<endl;
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
       << " refillMinLag_: " << server.refillMinLag_ << " refillMaxLag_: " << server.refillMaxLag_;

    return os;
}

void FoodServer::createTraceFile() {
    trace_.open ("trace.out", ios::out);
    if (!trace_) {
        cout << "cannot open the trace file.\n";
    }
    trace_<< "trace file for the simulation" << endl;
    trace_ << "format of the file" << endl;
    trace_ << "<Event> <Server> <Time> <Customer ID> <Server Status> <Queue Size> <Food Level>" << endl << endl;
}

string FoodServer::getServerAddress() {
    return  "[" + subCounter_->getAddress() + "," + to_string(id_) + "]";
}

int FoodServer::discreteRandom() {
    // for determining batch size (number of customers arriving at a time)
    double u = (double)rand() / (RAND_MAX);
    if(u<0.1667) return 1;
    else if(u<0.5001) return 2;
    else if(u<0.8335) return 3;
    return 4;
}

void FoodServer::terminationHandler() {
//    // debug
//    cout << "termination handler " << Scheduler :: now() << endl;

    allowEvaluation_ = false;

    if (status() == 0 && queueLength() > 0) { /// if customers waiting for refill event
        clearQueue();
    }
}

void FoodServer::report() {
    /// update statistical variables
    updateStat();

    cout << "Server: " << getServerAddress() << endl;
    cout << "Total Customers Arrived: " << customersArrived_ << endl;
    cout << "Total Customers Served: " << customersServed_ <<endl;
    cout << "Total Customers Left Unserved: " << customersLeft_ <<endl;
    cout << "Average Server Utilization: " << 100 * areaBusy_ / Scheduler :: now() << "%" << endl;
    cout << "Average Queue Length: " << areaQueue_ / Scheduler :: now() << endl;
    cout << "Average Food Level: " << areaFoodLevel_ / Scheduler :: now() << endl;
    cout << "Average Queue Delay: " << totalQueueingDelay_ / customersArrived_ << endl;
    cout << "Average Service Delay: " << totalServerDelay_ / customersServed_ << endl;

    // debug
    if (customersArrived_ != customersServed_ + customersLeft_) cout << "XXXXXXXXXX" <<endl;
}

void FoodServer::updateStat() {
    double duration_ = Scheduler :: now() - timeLastEvent_;
    areaBusy_ += duration_ * status();
    areaQueue_ += duration_ * queueLength();
    areaFoodLevel_ += duration_ * foodLevel_;
    timeLastEvent_ = Scheduler :: now();
}

void FoodServer::clearQueue() {
    while (queueLength() > 0) {
        Customer* unservedCustomer_ = queue_.front();
        queue_.pop();

        customersLeft_ ++;

        trace_<<"N\t"<<getServerAddress()<<"\t"<<Scheduler::now()<<"\t"<<unservedCustomer_->id()<<"\t"<<status()<<"\t"<<queueLength()<<"\t"<<foodLevel_<<endl;

        delay_ = Scheduler :: now() - unservedCustomer_ -> serverArrivalTime();
        totalQueueingDelay_ += delay_;

        /// send to next sub-counter
        subCounter_ ->departureHandler(unservedCustomer_);
    }
}
