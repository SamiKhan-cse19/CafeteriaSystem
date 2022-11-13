//
// Created by samikhan on 11/12/22.
//

#include "Scheduler.h"
#include "Event.h"

#include <iostream>
#include <fstream>
using namespace std;

Event* Scheduler :: eventList_;
double Scheduler :: clock_;
Scheduler* Scheduler::instance_;

Scheduler :: Scheduler () {
	eventList_ = 0;
}

Scheduler :: ~Scheduler () {

}

double
Scheduler :: now () {
	return clock_;
}


Scheduler&
Scheduler :: instance () {
	return (*instance_);
}

void
Scheduler :: schedule (Event* e) {
	addEvent (e);
}


void
Scheduler :: updateClock (double t) {
    // ------------------------------------Task-1 (start)--------------------------------------------------
    // update clock time
    clock_ = t;

	// ------------------------------------Task-1 (end)--------------------------------------------------
}

void
Scheduler :: initialize () {
    // ------------------------------------Task-2 (start)--------------------------------------------------
    // initialize the simulator
    // Hint: What's the value of clock in the beginning?
    clock_ = 0;

	// ------------------------------------Task-2 (end)--------------------------------------------------
}

void
Scheduler :: addEvent (Event *e) {

	Event *current;
	Event *previous;

	// add in an empty list
	if (!eventList_) {
		eventList_ = e;
		e->next_ = 0;

		return;
	}



	previous = eventList_;
	// ------------------------------------Task-3 (start)--------------------------------------------------
	// Add the event as a first element in a non-empty list
	// Hint: check for event expiry time
	// Don't forget to return after adding the event
	if(e->expire() < eventList_->expire()) {
		e->next_ = eventList_;
		eventList_ = e;
		return;
	}
	// ------------------------------------Task-3 (end)--------------------------------------------------




	current = previous -> next_;
	// ------------------------------------Task-4 (start)--------------------------------------------------
	// Add the event as an intermediate element of the eventlist
	while (current != 0) {
		if (e->expire() < current->expire ()) {
			e->next_ = current;
			previous->next_=e;
			return;
		} else {
			current = current->next_;
			previous = previous->next_;
		}
	}
    // ------------------------------------Task-4 (end)--------------------------------------------------



	// add as the last element
	previous->next_ = e;
	e->next_ = 0;

	return;
}

Event*
Scheduler :: removeEvent () {
	Event* temp;

	temp = eventList_;
	eventList_ = eventList_->next_;

	return temp;
}


void
Scheduler :: trigger () {
	Event* temp;

	temp = removeEvent ();
	temp->handle ();
}

// ------------------------------------Task-5 (start)--------------------------------------------------
// Complete the run() function
// Follow the flow-chart provided in theory class
void
Scheduler :: run () {
	Event * temp;
	while(eventList_ != 0) {
		temp = removeEvent();

		updateClock(temp->expire());

		temp->handle();
	}
}
// ------------------------------------Task-5 (end)--------------------------------------------------





