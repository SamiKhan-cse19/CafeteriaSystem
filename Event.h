//
// Created by samikhan on 11/12/22.
//

#ifndef CAFETERIASIMULATION_EVENT_H
#define CAFETERIASIMULATION_EVENT_H

class Server;

class Event {
    public:
		Event (Server* s) : server (s) {
 			stime_ = 0.0;
			rtime_ = 0.0;
		}

   		inline int& eventType () { return (eventType_); }
		inline double& expire () { return (rtime_); }
		inline double& start () { return (stime_); }

		void activate (double t);
		void cancel ();
		virtual void handle () = 0;

		Event* next_;
	protected:
		Server* server;

	private:
		int eventType_;	// represented by event id
		double stime_;
		double rtime_;
		int status_;
};


#endif //CAFETERIASIMULATION_EVENT_H
