cmake_minimum_required(VERSION 3.23)
project(CafeteriaSimulation)

set(CMAKE_CXX_STANDARD 23)

add_executable(CafeteriaSimulation main.cpp Scheduler.cpp Scheduler.h Event.cpp Event.h ArrivalEvent.cpp ArrivalEvent.h Counter.cpp Counter.h SubCounter.cpp SubCounter.h Customer.cpp Customer.h TerminationEvent.cpp TerminationEvent.h FoodServer.cpp FoodServer.h DepartureEvent.cpp DepartureEvent.h EvaluationEvent.cpp EvaluationEvent.h RestockEvent.cpp RestockEvent.h)
