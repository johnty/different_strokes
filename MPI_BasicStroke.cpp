
//
// MPI_BasicStroke.cpp
//

#include "MPI_BasicStroke.h"

#include "MPI_PolyLinePoint.h"
#include "MPI_PolyLinePointListIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_PolyLineVisitor.h"

MPI_BasicStroke::~MPI_BasicStroke()
{
    // free allocated points
    MPI_IteratorPtr<MPI_PointListIterator> curpoint( allocatePointListIterator() );
    for ( curpoint->first(); !curpoint->isDone(); curpoint->next() )
        delete curpoint->getPoint();
}

MPI_PointListIterator* MPI_BasicStroke::allocatePointListIterator( void ) const
{
    return new MPI_PolyLinePointListIterator( pointList_ );
}

void MPI_BasicStroke::acceptVisitor( MPI_PolyLineVisitor const& visitor )
{
    visitor.visitBasicStroke( *this );
}

void MPI_BasicStroke::allocatePointAndAddToList( MPI_Point2D const &point )
{
    pointList_.push_back( new MPI_PolyLinePoint( *this, point ) );
}

// vim:sw=4:et:cindent:
