
//
// MPI_SegmentIntersectionVisitor.cpp
//

#include "MPI_SegmentIntersectionVisitor.h"

MPI_SegmentIntersectionVisitor::MPI_SegmentIntersectionVisitor( MPI_Segment &segment ) :
    segment_( segment )
{
    // empty
}

MPI_Segment const& MPI_SegmentIntersectionVisitor::getSegment( void ) const
{
    return segment_;
}

// vim:sw=4:et:cindent:
