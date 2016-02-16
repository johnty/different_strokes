
//
// MPI_IsctWithParticleSegmentVisitor.cpp
//

#include "MPI_IsctWithParticleSegmentVisitor.h"

#include "MPI_ParticleSegment.h"
#include "MPI_RemovalSegment.h"

MPI_IsctWithParticleSegmentVisitor::MPI_IsctWithParticleSegmentVisitor( MPI_ParticleSegment &particlesegment ) :
    MPI_SegmentIntersectionVisitor( particlesegment ),
    particlesegment_( particlesegment )
{
    // empty
}

void MPI_IsctWithParticleSegmentVisitor::visitSegment( MPI_Segment &segment ) const
{
    // empty
}

void MPI_IsctWithParticleSegmentVisitor::visitParticleSegment( MPI_ParticleSegment &segment ) const
{

    // determine if the two segments intersect, and if they do,
    // add the appropriate intersection between them.
    // findIntersection() returns the parameter values where the intersection
    // happens for each segment through the arguments thissegpos, othersegpos.
    float thissegpos  = 0.0;
    float othersegpos = 0.0;
    if ( particlesegment_.findIntersection(segment, thissegpos, othersegpos) )
        particlesegment_.addParticleSegIntersection( segment, thissegpos, othersegpos );

}

void MPI_IsctWithParticleSegmentVisitor::visitRemovalSegment( MPI_RemovalSegment &segment ) const
{
    visitSegment( segment );
}

// vim:sw=4:et:cindent:
