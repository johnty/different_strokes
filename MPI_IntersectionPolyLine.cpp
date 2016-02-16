
//
// MPI_IntersectionPolyLine.cpp
//

#include "MPI_IntersectionPolyLine.h"

#include "MPI_Segment.h"
#include "MPI_SegmentIntersectionVisitor.h"
#include "MPI_Workspace.h"
#include "MPI_IntersectPolyLineVisitor.h"

MPI_IntersectionPolyLine::MPI_IntersectionPolyLine( MPI_Workspace &workspace ) :
    workspace_( workspace ),
    markedforremoval_( false )
{
    // empty
}

MPI_IntersectionPolyLine::~MPI_IntersectionPolyLine()
{
    // delete the segments
    std::list<MPI_Segment*>::iterator seg;
    for (seg = segmentlist_.begin(); seg != segmentlist_.end(); ++seg)
        delete *seg;
}

void MPI_IntersectionPolyLine::appendPoint( MPI_Point2D const &point )
{

    // grab the previous point.  this will be null if there is none.
    MPI_Point2D const* lastpoint = getLastPoint();

    // continue processing the point
    MPI_PolyLine::appendPoint( point );

    if ( lastpoint != NULL ) {

        // add the new segment to the list
        segmentlist_.push_back( allocateSegment( *lastpoint, point ) );

        // intersect this new segment with the rest of the polylines
        MPI_SegmentIntersectionVisitor *segisctvisitor = segmentlist_.back()->allocateIntersectionVisitor();
        workspace_.visitPolyLines( MPI_IntersectPolyLineVisitor(*segisctvisitor) );
        delete segisctvisitor;

    }

}

void MPI_IntersectionPolyLine::markForRemoval( void )
{
    // markedforremoval_ should be true when this polyline has been scheduled
    // to be deleted.  we keep track of this so that we only attempt to delete
    // a polyline exactly once.  it's possible to decide to delete a polyline
    // multiple times while traversing its segments, and this mechanism allows
    // us to avoid deleting the polyline multiple times.
    markedforremoval_ = true;
    // FIXME this is mixing the removal functionality with the
    // segment/intersection subsystem.  the editing functionality should be a
    // separate, independent subsystem.
}

bool MPI_IntersectionPolyLine::isMarkedForRemoval( void ) const
{
    return markedforremoval_;
}

void MPI_IntersectionPolyLine::visitSegments( MPI_SegmentVisitor const& visitor ) const
{
    // visit each of the segments
    std::list<MPI_Segment*>::const_iterator seg;
    for (seg = segmentlist_.begin(); seg != segmentlist_.end(); ++seg)
        (*seg)->acceptVisitor( visitor );
}

MPI_Segment* MPI_IntersectionPolyLine::allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint )
{
    return new MPI_Segment( workspace_, *this, firstpoint, secondpoint );
}

unsigned int MPI_IntersectionPolyLine::getNumSegments( void ) const
{
    return segmentlist_.size();
}

MPI_Workspace& MPI_IntersectionPolyLine::getWorkspace( void ) const
{
    return workspace_;
}

// vim:sw=4:et:cindent:
