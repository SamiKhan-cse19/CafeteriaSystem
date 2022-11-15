//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_COUNTER_H
#define CAFETERIASIMULATION_COUNTER_H

#include "ArrivalEvent.h"
#include "TerminationEvent.h"
#include "SubCounter.h"

class Counter{
public:
    static int customerArrived_;

    Counter (int id);
    void initialize();
    void arrivalHandler();
    void terminationHandler();

    inline int& customerArrived () { return (customerArrived_); }
    inline double& arrivalMean () { return (arrivalMean_); }

private:
    ArrivalEvent a_;
    TerminationEvent t_;
    int id_;
    vector <vector <SubCounter*> > subCounters; // 2D vector of sub-counters (represents levels and choice items)

    // state variables
    bool allowArrival_;

    // input variables
    double arrivalMean_;
    vector <vector <double> > probabilities; // P(i,j) = probability of choosing item j from level i

    // probability distribution functions
    double exponential (double mean);
    static int discreteRandom ();

};


#endif //CAFETERIASIMULATION_COUNTER_H
