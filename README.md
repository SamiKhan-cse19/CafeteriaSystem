# Cafeteria System
<hr>
A simulation program for a cafeteria system that models, simulates, analyses and evaluates different configurations. The program output is used to find the best configuration of the cafeteria system resulting in optimum performance.

Here are the links to the detailed <a href="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/report/CSE_4550_Project_Report.pdf"> report </a> and summary <a href="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/report/data.xlsx">data sheet</a>.

# Introduction
<hr>

The cafeteria system is a common spectacle in everyday life of urban people. It is a form of
service that gives equal treatment to all the customers by means of time taken for service as well
as the choice of items based on availability. It is a common scenario in most developed countries
but in Bangladesh, it is mostly common in educational institutions. The experiment focused on
the common cafeteria found in Bangladesh and provide some optimizations.

The cafeteria model is simulated for some set of input variables following a recommended experimental design (2k Factorial Design). The output of the simulation is analysed for performance
based on some performance criteria and the best performing configuration is selected.
The remainder of this report is structured as follows. Section 2 explores the problem statement
of the experiment and identifies the goals and objectives of the simulation. Section 3 outlines the
conceptual model of the simulation along with the relations. Section 4 explores the specification
model followed by the computational model in section 5. Section 6 summarizes the experimental
outline and the performance criteria. Section 7 contains the result discussion and finally section 8
drives a conclusion

# Goals and Objectives
<hr>

- Maximizing Customer Satisfaction
  - Minimize average queuing delay of customers
    - Find optimum number of servers for each sub-counter
  - Minimize number of stalled customers (due to insufficient food)
    - Find optimum server threshold
  - Minimize number of unsatisfied customers (stayed in queue but did not receive food)
    - Find optimum evaluation interval
- Minimizing Resource Wastage
  - Maximize utilization rate of each server
    - Find optimum number of servers for each sub-counter
  - Minimize remaining food after simulation ends
    - Find optimum evaluation interval
    - Find optimum server threshold

# Images
<hr>
<img alt="System Diagram" width="600" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/System%20Diagram.png?raw=true">

## Event handlers (Flow Charts)
### Arrival handler
<img alt="Arrival Handler" width="550" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/Final%20Project%20UML%20Diagram%20-%20Arrival%20Handler.png?raw=true">

### Departure Handler 
<img alt="Departure Handler" width="800" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/Final%20Project%20UML%20Diagram%20-%20Departure%20handler.png?raw=true">

### Evaluation Handler
<img alt="Evaluation Handler" width="500" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/Final%20Project%20UML%20Diagram%20-%20Evaluation%20Handler.png?raw=true">

### Refill Handler
<img alt="Refill Handler" width="450" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/Final%20Project%20UML%20Diagram%20-%20Refill%20handler.png?raw=true">

### Termination Handler
<img alt="Termination Handler" width="200" src="https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/Final%20Project%20UML%20Diagram%20-%20Termination%20Handler.png?raw=true">

## System States
### State Variables
![State Variables](https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/img.png?raw=true)
### State Equations
![State Equations](https://github.com/SamiKhan-cse19/CafeteriaSystem/blob/master/images/img_1.png?raw=true)

# Run
```bash
cmake -Bbuild -H.
cmake --build build --target all
```