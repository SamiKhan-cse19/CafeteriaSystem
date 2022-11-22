//
// Created by Win10 on 11/13/2022.
//

#include "DepartureEvent.h"
#include "FoodServer.h"

DepartureEvent::DepartureEvent(FoodServer *s) : server(s) {

}

void DepartureEvent::handle() {
    server -> departureHandler();
}
