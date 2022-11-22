
#include "Counter.h"
#include "Scheduler.h"


int main() {
    Scheduler sch;
    sch.initialize();
    FoodServer::createTraceFile();
    Counter c(0);
    c.initialize();
    sch.run();
    return 0;
}
