
//
// MPI_PolyLinePointListIterator.cpp
//

#include "MPI_PolyLinePointListIterator.h"

#include "MPI_PolyLinePoint.h"

MPI_PolyLinePointListIterator::MPI_PolyLinePointListIterator( std::list<MPI_PolyLinePoint*> const& pointlist ) :
    pointlist_(pointlist)
{
    // empty
}

void MPI_PolyLinePointListIterator::first( void )
{
    iterator_ = pointlist_.begin();
}

void MPI_PolyLinePointListIterator::next( void )
{
    iterator_++;
}

bool MPI_PolyLinePointListIterator::isDone( void ) const
{
    return iterator_ == pointlist_.end();
}

MPI_PolyLinePoint* MPI_PolyLinePointListIterator::getPoint( void ) const
{
    // why can I do this?  isn't iterator_ a const iterator?
    // Because I'm not changing the pointer value!  The const iterator just
    // protects where the pointer points to, not the contents of the object
    // pointed to.
    return *iterator_;
}

// vim:sw=4:et:cindent:
