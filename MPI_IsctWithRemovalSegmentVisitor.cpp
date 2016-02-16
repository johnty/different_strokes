
//
// MPI_IsctWithRemovalSegmentVisitor.cpp
//

#include "MPI_IsctWithRemovalSegmentVisitor.h"

#include "MPI_ParticleSegment.h"
#include "MPI_RemovalSegment.h"
#include "MPI_Scheduler.h"
#include "MPI_IntersectionPolyLine.h"
#include "MPI_RemovePolyLineEvent.h"

MPI_IsctWithRemovalSegmentVisitor::MPI_IsctWithRemovalSegmentVisitor( MPI_RemovalSegment &removalsegment, MPI_Scheduler &scheduler ) :
    MPI_SegmentIntersectionVisitor( removalsegment ),
    scheduler_( scheduler )
{
    // empty
}

void MPI_IsctWithRemovalSegmentVisitor::visitSegment( MPI_Segment &segment ) const
{

    // remove the polyline that owns the segment if there's an intersection
    // schedule the removal at the current logical time -- this causes the
    // removal to be called from the top level, outside any visitor traversals
    // (in particular, the one we're in now).

    float thissegpos  = 0.0;
    float othersegpos = 0.0;
    if ( !segment.getIntersectionPolyLine().isMarkedForRemoval() &&
            getSegment().findIntersection(segment, thissegpos, othersegpos) ) {

        // schedule its removal.  this is scheduled to go off at the current
        // logical time, after any pending events are dispatched.
        scheduler_.scheduleEvent( new MPI_RemovePolyLineEvent( segment.getWorkspace(), segment.getIntersectionPolyLine() ), 0.0 );
        segment.getIntersectionPolyLine().markForRemoval();

    }

}

void MPI_IsctWithRemovalSegmentVisitor::visitParticleSegment( MPI_ParticleSegment &segment ) const
{
    visitSegment( segment );
}

void MPI_IsctWithRemovalSegmentVisitor::visitRemovalSegment( MPI_RemovalSegment &segment ) const
{
    // empty -- do nothing if you intersect another removal segment
}

// vim:sw=4:et:cindent:
