//
// Created by Win10 on 11/13/2022.
//

#include "RestockEvent.h"

RestockEvent::RestockEvent(FoodServer *s) : server(s) {

}

void RestockEvent::handle() {
    server -> restockHandler();
}
