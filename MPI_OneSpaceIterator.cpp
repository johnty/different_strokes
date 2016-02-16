
//
// MPI_OneSpaceIterator.cpp
//

#include "MPI_OneSpaceIterator.h"

#include "MPI_OneSpaceElementPos.h"

MPI_OneSpaceIterator::MPI_OneSpaceIterator( std::list<MPI_OneSpaceElementPos> const& items ) :
    items_( items )
{
    // empty
}

void MPI_OneSpaceIterator::first( void )
{
    iterator_ = items_.begin();
}

void MPI_OneSpaceIterator::next( void )
{
    ++iterator_;
}

bool MPI_OneSpaceIterator::isDone( void ) const
{
    return iterator_ == items_.end();
}

MPI_OneSpaceElement* MPI_OneSpaceIterator::getElement( void ) const
{
    return iterator_->getElement();
}

// vim:sw=4:et:cindent:
