
//
// MPI_RemovalStroke.cpp
//

#include "MPI_RemovalStroke.h"

#include "MPI_PolyLinePoint.h"
#include "MPI_PolyLinePointListIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_PolyLineVisitor.h"
#include "MPI_RemovalSegment.h"
#include "MPI_RemovePolyLineEvent.h"
#include "MPI_Scheduler.h"

MPI_RemovalStroke::MPI_RemovalStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    MPI_IntersectionPolyLine( workspace ),
    scheduler_( scheduler )
{
    // empty
}

MPI_RemovalStroke::~MPI_RemovalStroke()
{
    // free allocated points
    MPI_IteratorPtr<MPI_PointListIterator> curpoint( allocatePointListIterator() );
    for ( curpoint->first(); !curpoint->isDone(); curpoint->next() )
        delete curpoint->getPoint();
}

void MPI_RemovalStroke::end( void )
{
    // when the pen is lifted (ie, when this method is called), remove the
    // stroke
    scheduler_.scheduleEvent( new MPI_RemovePolyLineEvent( getWorkspace(), *this ), 0.0 );
}

MPI_PointListIterator* MPI_RemovalStroke::allocatePointListIterator( void ) const
{
    return new MPI_PolyLinePointListIterator( pointList_ );
}

void MPI_RemovalStroke::acceptVisitor( MPI_PolyLineVisitor const& visitor )
{
    visitor.visitRemovalStroke( *this );
}

void MPI_RemovalStroke::allocatePointAndAddToList( MPI_Point2D const &point )
{
    pointList_.push_back( new MPI_PolyLinePoint( *this, point ) );
}

MPI_Segment* MPI_RemovalStroke::allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint )
{
    return new MPI_RemovalSegment( getWorkspace(), *this, firstpoint, secondpoint, scheduler_ );
}

MPI_Point2D const* MPI_RemovalStroke::getLastPoint( void ) const
{
    if ( pointList_.empty() )
        return NULL;
    else
        return &pointList_.back()->getPoint();
}

// vim:sw=4:et:cindent:
