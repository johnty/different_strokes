
//
// MPI_FloatTrain.cpp
//

#include "MPI_FloatTrain.h"

#include "MPI_FloatTrainConstIterator.h"
#include "MPI_Scheduler.h"

#include <algorithm>
#include <cassert>

MPI_FloatTrain::MPI_FloatTrain( MPI_Scheduler const &scheduler ) :
    scheduler_( scheduler )
{
    // empty
}

void MPI_FloatTrain::addItem( float value )
{

    // FIXME
    // this is called in the draw callback; items are added at each animation frame
    // the scheduler is advanced during the idleCallback(), so by requiring that
    // the scheduler is advanced between calls to this, it means the idleCallback()
    // must be called between frames.
    // when you move the window and let go, glut does two draws in a row; ie, the
    // scheduler doesn't get advanced.  That's why the assertion is tripped.
    // trick is to decouple adding items here from the drawing functionality.
    // draw should just draw; it shouldn't do any processing.  it should be
    // callable a bunch of times in a row

    // assert the the items are being added in order, ie that the current time
    // is later than latest time in our list.  this ensures the list is sorted.
    assert( train_.size() == 0 || train_.back().getTime() <= scheduler_.getTime() );
    // FIXME temp fix -- this assertion should be strictly less than

    // append the time float
    train_.push_back( MPI_TimeFloat( value, scheduler_ ) );

}

MPI_FloatTrainConstIterator* MPI_FloatTrain::allocateFloatTrainConstIterator( void ) const
{
    return new MPI_FloatTrainConstIterator( train_ );
}

void MPI_FloatTrain::removeOldItems( float age )
{

    // remove list items that are older than cutofftime

    // encapsulate the cutofftime in an MPI_TimeFloat instance for feeding to
    // TimeFloatBefore.
    MPI_TimeFloat cutoffitem( 0.0, scheduler_.getTime()-age, scheduler_ );

    // find the removal boundary.  all items before the removal boundary have
    // time less than cutofftime.
    std::list<MPI_TimeFloat>::iterator removalboundary;
    removalboundary = lower_bound( train_.begin(), train_.end(), cutoffitem,
            TimeFloatBefore() );

    // erase the items
    train_.erase( train_.begin(), removalboundary );

}

bool MPI_FloatTrain::TimeFloatBefore::operator()( MPI_TimeFloat const& a, MPI_TimeFloat const& b ) const
{
    // return true if a comes strictly before b
    return a.getTime() < b.getTime();
}

// vim:sw=4:et:cindent:
