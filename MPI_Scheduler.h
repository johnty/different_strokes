
//
// MPI_Scheduler.h
//
// Description:
//   Scheduler class
//   Keeps track of the current logical time and pending events, and dispatches
//   events when it's time to.
//

// TODO
//  - what would an event handle look like?  just an iterator or something?
//  - what if the object is destroyed or something before the event is fired?
//  - figure out if it'd be better for MPI_Scheduler not to be a singleton
//  - invariant: when you start dispatching events, the current logical time is
//    less than the first time on the queue
//  - think about removing the Earlier class -- could just as easily do it with
//    an operator<, and it'd obviate a class.  Simpler is better.

#ifndef __MPI_SCHEDULER_H__
#define __MPI_SCHEDULER_H__

#include <ostream>
#include <list>

class MPI_Event;

class MPI_Scheduler
{

  private:

    // class to bundle an event with a time
    // gets initialised with an even and the time it's supposed to fire at;
    // ScheduledEvent takes responsibility for deleting the event object.
    class ScheduledEvent
    {

      public:

        ScheduledEvent( MPI_Event *event, double eventTime );

        MPI_Event* getEvent( void ) const;
        double getEventTime( void ) const;

      private:

        MPI_Event *event_;
        double eventTime_;

    };

    // comparison operator for use in sorting list of ScheduledEvent objects
    class Earlier
    {
      public:
        bool operator()( ScheduledEvent const& a, ScheduledEvent const& b );
    };

    // operator which returns true if the ScheduledEvent points to a particluar
    // event
    class ContainsEvent
    {
      public:
        ContainsEvent( MPI_Event *event ) : event_(event) {}
        bool operator()( ScheduledEvent const& a );
      private:
        MPI_Event *event_;
    };

  public:

    MPI_Scheduler();
    ~MPI_Scheduler();

    // return the scheduler's current logical time
    double getTime( void ) const;

    // these can be called by clients to schedule events
    void scheduleEvent( MPI_Event *event, double delaytime );
    void scheduleEventAbs( MPI_Event *event, double eventtime );
    void cancelEvent( MPI_Event *event );

    // this should be only be called from the top level, main loop
    void dispatchEventsUpToTime( double time );

    void print( std::ostream &os ) const;

  private:

    double time_;
    std::list<ScheduledEvent> pendingEvents_;

};

std::ostream &operator<<( std::ostream &os, MPI_Scheduler const &scheduler );

#endif

// vim:sw=4:et:cindent:
