
//
// MPI_IsctWithSegmentVisitor.cpp
//

#include "MPI_IsctWithSegmentVisitor.h"

#include "MPI_ParticleSegment.h"
#include "MPI_RemovalSegment.h"

MPI_IsctWithSegmentVisitor::MPI_IsctWithSegmentVisitor( MPI_Segment &segment ) :
    MPI_SegmentIntersectionVisitor( segment ),
    segment_( segment )
{
    // empty
}

void MPI_IsctWithSegmentVisitor::visitSegment( MPI_Segment &segment ) const
{
    // empty
    // nothing happens when plain MPI_Segment objects are intersected
}

void MPI_IsctWithSegmentVisitor::visitParticleSegment( MPI_ParticleSegment &segment ) const
{
    visitSegment( segment );
}

void MPI_IsctWithSegmentVisitor::visitRemovalSegment( MPI_RemovalSegment &segment ) const
{
    visitSegment( segment );
}

// vim:sw=4:et:cindent:
