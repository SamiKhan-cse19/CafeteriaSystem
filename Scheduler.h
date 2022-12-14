//
// Created by samikhan on 11/12/22.
//

#ifndef CAFETERIASIMULATION_SCHEDULER_H
#define CAFETERIASIMULATION_SCHEDULER_H

#include "Event.h"

class Scheduler {
    public:
		Scheduler ();
		~Scheduler ();
		void trigger ();
		void run ();
		void initialize ();

	//protected:
		static double now ();
		static Scheduler& instance ();
		void schedule (Event *e);
		void cancel (Event *e);

	private:
		void addEvent (Event *e);
		Event* removeEvent ();
		void updateClock (double t);

	public:
		static double clock_;
		static Event* eventList_;
		static Scheduler* instance_;
};


#endif //CAFETERIASIMULATION_SCHEDULER_H
