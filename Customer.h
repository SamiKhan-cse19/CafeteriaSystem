//
// Created by Win10 on 11/13/2022.
//

#ifndef CAFETERIASIMULATION_CUSTOMER_H
#define CAFETERIASIMULATION_CUSTOMER_H


class Customer {
private:
    int id_;
    Customer* next_;
    double arrivalTime_;
    double foodAmount_;

public:
    Customer (int id);

    inline double& foodAmount() { return foodAmount_; }
    inline int& id() { return id_; }
    inline double& arrivalTime() { return arrivalTime_; }
    inline Customer* next() { return next_; }

};


#endif //CAFETERIASIMULATION_CUSTOMER_H
