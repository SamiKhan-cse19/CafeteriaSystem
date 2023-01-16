
#include <iostream>
#include "Counter.h"
#include "Scheduler.h"

int main() {
    srand(42);

    Scheduler *sch = new Scheduler();
    Counter *c = new Counter(0);
    for (int i=0; i<10; i++) {


        sch->initialize();
        FoodServer::createTraceFile();
//        FoodServer :: createStaticReportFiles();

        c->initialize();

        /// set input parameters
        c->setMinLevel(1); // 0 = maxAmount, 1 = 2*maxAmount
        c->setEvaluationInterval(13.0);

        sch->run();


        c->report();

    }

//    c->finalReport();
    /// Food Amount Unit testing
//    SubCounter sc (0, 0, 0.5, 0.5, 4, 7, 1, nullptr, nullptr);
//    cout<<sc.getCustomerAmount()<<endl;


    return 0;
}
