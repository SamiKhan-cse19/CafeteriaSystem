
#include <iostream>
#include "Counter.h"
#include "Scheduler.h"

int main() {
    srand(time(nullptr));

    Scheduler *sch = new Scheduler();
    Counter *c = new Counter(0);
    for (int i=0; i<10; i++) {


        sch->initialize();
        FoodServer::createTraceFile();

        c->initialize();

        /// set input parameters
        c->setMinLevel(0); // 0 = maxAmount, 1 = 2*maxAmount
        c->setEvaluationInterval(8.0);

        sch->run();

        c->report();

    }

    /// Food Amount Unit testing
//    SubCounter sc (0, 0, 0.5, 0.5, 4, 7, 1, nullptr, nullptr);
//    cout<<sc.getCustomerAmount()<<endl;


    return 0;
}
