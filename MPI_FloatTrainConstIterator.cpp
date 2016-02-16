
//
// MPI_FloatTrainConstIterator.cpp
//

#include "MPI_FloatTrainConstIterator.h"

#include "MPI_TimeFloat.h"

MPI_FloatTrainConstIterator::MPI_FloatTrainConstIterator( std::list<MPI_TimeFloat> const& timefloatlist ) :
    timefloatlist_( timefloatlist )
{
    // empty
}

void MPI_FloatTrainConstIterator::first( void )
{
    iterator_ = timefloatlist_.begin();
}

void MPI_FloatTrainConstIterator::next( void )
{
    ++iterator_;
}

bool MPI_FloatTrainConstIterator::isDone( void ) const
{
    return iterator_ == timefloatlist_.end();
}

MPI_TimeFloat const& MPI_FloatTrainConstIterator::getTimeFloat( void ) const
{
    return *iterator_;
}

// vim:sw=4:et:cindent:
