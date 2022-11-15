//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_FOODSERVER_H
#define CAFETERIASIMULATION_FOODSERVER_H


#include "Customer.h"
#include "DepartureEvent.h"
#include "EvaluationEvent.h"
#include "RefillEvent.h"
#include <queue>
#include <cmath>
using namespace std;

class FoodServer {
private:
    // state variables
    queue <Customer*> queue_;
    int id_;
    int status_;
    Customer* customerInService_;
    double foodLevel_;

    // constants
    double minLevel_;
    double maxLevel_;
    double departureMean_;
    double evaluationInterval_;
    double refillMinLag_;
    double refillMaxLag_;
    double customerMinAmount_;
    double customerMaxAmount_;


    // events
    DepartureEvent d_;
    EvaluationEvent e_;
    RefillEvent r_;

    // helper probability functions
    double exponential (double mean);

    // statistical variables
    double timeLastEvent_;
    double areaQueue_;
    double areaFoodLevel_;
    double totalQueueingDelay_;
    double delay_;
    int customersArrived_;
    int customersServed_;

public:
    FoodServer(int id, double minLevel, double maxLevel, double departureMean, double evaluationInterval, double refillMinLag, double refillMaxLag, double customerMinAmount, double customerMaxAmount);
    void initialize();

    // state variables accessors
    inline int& status() { return status_; }
    inline int queueLength() { return queue_.size(); }

    // constant accessors
    inline double& minLevel() { return minLevel_; }
    inline double& maxLevel() { return maxLevel_; }
    inline double& departureMean() { return departureMean_; }
    inline double& evaluationInterval() { return evaluationInterval_; }
    inline double& refillMinLag() { return refillMinLag_; }
    inline double& refillMaxLag() { return refillMaxLag_; }

    void arrivalHandler (Customer* cus);
    void departureHandler ();
    void evaluationHandler ();
    void refillHandler ();
};


#endif //CAFETERIASIMULATION_FOODSERVER_H
