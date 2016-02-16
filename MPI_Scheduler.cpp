
//
// MPI_Scheduler.cpp
//

#include "MPI_Scheduler.h"

#include "MPI_Event.h"

#include <algorithm>
#include <cassert>

// FIXME use this "initialiser list" notation everywhere or nowhere
// if this were a derived class, you could pass arguments to the derived by
// giving the class name and args
MPI_Scheduler::ScheduledEvent::ScheduledEvent( MPI_Event *event, double eventTime ) :
    event_(event),
    eventTime_(eventTime)
{
    // empty
}

MPI_Event* MPI_Scheduler::ScheduledEvent::getEvent( void ) const
{
    return event_;
}

double MPI_Scheduler::ScheduledEvent::getEventTime( void ) const
{
    return eventTime_;
}

bool MPI_Scheduler::Earlier::operator()( ScheduledEvent const& a, ScheduledEvent const& b )
{
    return a.getEventTime() < b.getEventTime();
}

bool MPI_Scheduler::ContainsEvent::operator()( ScheduledEvent const& a )
{
    return event_ == a.getEvent();
}

double MPI_Scheduler::getTime( void ) const
{
    return time_;
}

void MPI_Scheduler::scheduleEvent( MPI_Event *event, double delaytime )
{
    // compute absolute time of event and schedule it at that time
    double absolutetime = time_ + delaytime;
    scheduleEventAbs( event, absolutetime );
}

void MPI_Scheduler::scheduleEventAbs( MPI_Event *event, double eventtime )
{
    // ignore request if it's in the past
    if ( eventtime < time_ ) return;

    // insert event at the appropriate point in the list
    // if there are other events at the same time, insert the event after them

    // find the insert point.  upper_bound gives an iterator pointing to
    // the first element at time greater than eventtime
    // see stroustrup, c++ programming lang, 3rd ed, section 18.7.2
    ScheduledEvent searchtime( NULL, eventtime );
    std::list<ScheduledEvent>::iterator insertpoint;
    insertpoint = upper_bound( pendingEvents_.begin(), pendingEvents_.end(),
            searchtime, Earlier());

    // insert the event at insertpoint
    // the MPI_Scheduler is responsible for deleting this ScheduledEvent object
    // in its destructor
    pendingEvents_.insert( insertpoint, ScheduledEvent(event, eventtime) );

    // see http://www.camtp.uni-mb.si/books/Thinking-in-C++/Chapter05.html
    // "stl algorithms".  has example of how to define a sorting compare
    // (see "Sorting and operations on sorted ranges")
    // -- this reference notes that the default sorting function templates
    // use the objects operator<, and this would be easy to define!
    // also has interesting stuff on patterns...
    //
    // also see stroustrup, 3rd ed, sect 18.4.2.1 "overview of predicates" for
    // an example of defining your own

}

void MPI_Scheduler::cancelEvent( MPI_Event *event )
{

    // remove the event from the pending events queue and delete the object

    std::list<ScheduledEvent>::iterator eventtocancel;
    eventtocancel = find_if( pendingEvents_.begin(), pendingEvents_.end(),
            ContainsEvent( event ) );
    assert( eventtocancel != pendingEvents_.end() );

    delete eventtocancel->getEvent();
    pendingEvents_.erase( eventtocancel );

}

void MPI_Scheduler::dispatchEventsUpToTime( double time )
{

    // loop through events until the time on top of the list is greater than time
    //   set logical time to the time on top of the list
    //   dispatch the event

    assert( time_ <= time );

    MPI_Event *eventtodispatch = NULL;
    std::list<ScheduledEvent>::iterator firstevent = pendingEvents_.begin();

    // handle this by always looking at the beginning of the list
    // the iterator might become invalid because of things that the event
    // triggers
    while ( !pendingEvents_.empty() && firstevent->getEventTime() <= time )
    {
        // update the current scheduler logical time
        time_ = firstevent->getEventTime();

        // grab the event and remove the associated ScheduledEvent object
        eventtodispatch = firstevent->getEvent();
        pendingEvents_.pop_front();

        // dispatch the event and delete it
        eventtodispatch->execute();
        delete eventtodispatch;

        // update firstevent to point to the beginning of list
        // we need to refresh the iterator like this since
        // eventtodispatch->execute() may have changed pendingEvents_, which
        // would invalidate any iterators we had pointing into the list
        firstevent = pendingEvents_.begin();
    }

    // there are no more events before or at dispatch time, so advance the
    // logical clock.  If we didn't do this, the logical clock would still have
    // the time of the last event dispatched.
    time_ = time;

}

void MPI_Scheduler::print( std::ostream &os ) const
{
    // loop through the events and print them
    std::list<ScheduledEvent>::const_iterator currentevent;
    for ( currentevent = pendingEvents_.begin();
            currentevent != pendingEvents_.end();
            ++currentevent )
    {
        // print a separator if necessary
        if ( currentevent != pendingEvents_.begin() )
                os << ", ";
        // print the scheduled event
        os << '[' << currentevent->getEventTime() << ", ";
        os << std::showbase << std::hex << currentevent->getEvent()
            << std::noshowbase << std::dec;
        os << ']';
    }
}

MPI_Scheduler::MPI_Scheduler() :
    time_(0)
{
    // empty
}

MPI_Scheduler::~MPI_Scheduler()
{
    // loop through the list and delete the ScheduledEvent objects
    std::list<ScheduledEvent>::const_iterator currentevent;
    MPI_Event *currenteventevent = NULL;
    for ( currentevent = pendingEvents_.begin();
            currentevent != pendingEvents_.end();
            ++currentevent )
    {
        currenteventevent = currentevent->getEvent();
        if ( currenteventevent != NULL ) delete currenteventevent;
    }
}

std::ostream &operator<<( std::ostream &os, MPI_Scheduler const &scheduler )
{
    scheduler.print(os);
    return os;
}

// vim:sw=4:et:cindent:
