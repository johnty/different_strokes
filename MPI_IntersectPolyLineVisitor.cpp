
//
// MPI_IntersectPolyLineVisitor.cpp
//

#include "MPI_IntersectPolyLineVisitor.h"

#include "MPI_Segment.h"
#include "MPI_SegmentIntersectionVisitor.h"
#include "MPI_RemovalStroke.h"
#include "MPI_PlayheadStroke.h"

MPI_IntersectPolyLineVisitor::MPI_IntersectPolyLineVisitor( MPI_SegmentIntersectionVisitor &segmentintersectionvisitor ) :
    segmentintersectionvisitor_( segmentintersectionvisitor )
{
    // empty
}

void MPI_IntersectPolyLineVisitor::visitParticleStroke( MPI_ParticleStroke& polyline ) const
{
    visitIntersectionPolyLine( polyline );
}

void MPI_IntersectPolyLineVisitor::visitRemovalStroke( MPI_RemovalStroke& polyline ) const
{
    visitIntersectionPolyLine( polyline );
}

void MPI_IntersectPolyLineVisitor::visitPlayheadStroke( MPI_PlayheadStroke& polyline ) const
{
    visitIntersectionPolyLine( polyline );
}

void MPI_IntersectPolyLineVisitor::visitIntersectionPolyLine( MPI_IntersectionPolyLine& polyline ) const
{

    // this is a private helper method; MPI_IntersectionPolyLine doesn't have
    // an entry in the polyline visitors since it's an abstract base class and
    // can't be instantiated.

    if ( segmentintersectionvisitor_.getSegment().getBoundingBox().overlaps( polyline.getBoundingBox() ) )
        polyline.visitSegments( segmentintersectionvisitor_ );

}

// vim:sw=4:et:cindent:
