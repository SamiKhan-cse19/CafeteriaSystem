//
// Created by Win10 on 11/13/2022.
//

#include "RefillEvent.h"
#include "FoodServer.h"

RefillEvent::RefillEvent(FoodServer *s) : server(s) {

}

void RefillEvent::handle() {
    server->refillHandler();
}
