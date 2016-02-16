
//
// MPI_OneSpaceConstIterator.cpp
//

#include "MPI_OneSpaceConstIterator.h"

#include "MPI_OneSpaceElementPos.h"

MPI_OneSpaceConstIterator::MPI_OneSpaceConstIterator( std::list<MPI_OneSpaceElementPos> const& items ) :
    items_( items )
{
    // empty
}

void MPI_OneSpaceConstIterator::first( void )
{
    iterator_ = items_.begin();
}

void MPI_OneSpaceConstIterator::next( void )
{
    ++iterator_;
}

bool MPI_OneSpaceConstIterator::isDone( void ) const
{
    return iterator_ == items_.end();
}

MPI_OneSpaceElement const* MPI_OneSpaceConstIterator::getElement( void ) const
{
    return iterator_->getElement();
}

// vim:sw=4:et:cindent:
