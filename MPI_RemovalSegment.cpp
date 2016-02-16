
//
// MPI_RemovalSegment.cpp
//

#include "MPI_RemovalSegment.h"

#include "MPI_IsctWithRemovalSegmentVisitor.h"

MPI_RemovalSegment::MPI_RemovalSegment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint, MPI_Scheduler &scheduler ) :
    MPI_Segment( workspace, intersectionpolyline, firstpoint, secondpoint ),
    scheduler_( scheduler )
{
    // empty
}

void MPI_RemovalSegment::acceptVisitor( MPI_SegmentVisitor const& visitor )
{
    visitor.visitRemovalSegment( *this );
}

MPI_SegmentIntersectionVisitor* MPI_RemovalSegment::allocateIntersectionVisitor( void )
{
    return new MPI_IsctWithRemovalSegmentVisitor( *this, scheduler_ );
}

// vim:sw=4:et:cindent:
