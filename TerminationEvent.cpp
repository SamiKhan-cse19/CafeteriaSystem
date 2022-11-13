//
// Created by Win10 on 11/13/2022.
//

#include "TerminationEvent.h"

void TerminationEvent::handle() {
    // call termination event handler in counter
    counter -> terminationHandler();

}
