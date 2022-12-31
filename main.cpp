
#include <iostream>
#include "Counter.h"
#include "Scheduler.h"

int main() {
    srand(time(nullptr));
    Scheduler* sch = new Scheduler();
    sch -> initialize();
    FoodServer::createTraceFile();
    Counter* c = new Counter(0);
    c -> initialize();
    sch -> run();

    c -> report();


    /// Food Amount Unit testing
//    SubCounter sc (0, 0, 0.5, 0.5, 4, 7, 1, nullptr, nullptr);
//    cout<<sc.getCustomerAmount()<<endl;


    return 0;
}
