//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_FOODSERVER_H
#define CAFETERIASIMULATION_FOODSERVER_H


#include "Customer.h"
#include "DepartureEvent.h"
#include <queue>
using namespace std;

class FoodServer {
private:
    // state variables
    queue <Customer> queue_;
    int id_;
    int status_;
    double foodLevel_;

    // constants
    double minLevel_;
    double maxLevel_;
    double departureMean_;
    double evaluationInterval_;
    double restockMean_;

    // events
    DepartureEvent d_;
    EvaluationEvent e_;
    RestockEvent r_;

public:
    FoodServer();
    void initialize();

    void departureHandler ();
    void evaluationHandler ();
    void restockHandler ();
};


#endif //CAFETERIASIMULATION_FOODSERVER_H
