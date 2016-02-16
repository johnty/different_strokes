
//
// MPI_PolyLinePointDequeIterator.cpp
//

#include "MPI_PolyLinePointDequeIterator.h"

MPI_PolyLinePointDequeIterator::MPI_PolyLinePointDequeIterator( std::deque<MPI_PolyLinePoint*> const& pointlist ) :
    pointlist_( pointlist )
{
    // empty
}

void MPI_PolyLinePointDequeIterator::first( void )
{
    iterator_ = pointlist_.begin();
}

void MPI_PolyLinePointDequeIterator::next( void )
{
    ++iterator_;
}

bool MPI_PolyLinePointDequeIterator::isDone( void ) const
{
    return iterator_ == pointlist_.end();
}

MPI_PolyLinePoint* MPI_PolyLinePointDequeIterator::getPoint( void ) const
{
    return *iterator_;
}

// vim:sw=4:et:cindent:
