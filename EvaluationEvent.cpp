//
// Created by Win10 on 11/13/2022.
//

#include "EvaluationEvent.h"

EvaluationEvent::EvaluationEvent(FoodServer *s) : server(s) {

}

void EvaluationEvent::handle() {
    server -> evaluationHandler();
}
