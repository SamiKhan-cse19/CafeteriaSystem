//
// Created by Win10 on 11/13/2022.
//

#include "ArrivalEvent.h"
#include "Counter.h"

// handle an arrival event
void
ArrivalEvent :: handle () {
    counter -> arrivalHandler();
}
