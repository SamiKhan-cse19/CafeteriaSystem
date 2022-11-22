//
// Created by Win10 on 11/13/2022.
//

#include "Customer.h"
#include "Scheduler.h"

Customer ::Customer(int id) : id_(id){
    systemArrivalTime_ = Scheduler :: now();
    next_ = nullptr;
}