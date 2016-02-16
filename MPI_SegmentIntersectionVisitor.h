
//
// MPI_SegmentIntersectionVisitor.h
//
// Description:
//   Base class for the segment/segment intersection visitors.
//   The object gets initialised with a segment, and this is intersected with
//   the visited segment.  The details are left up to the subclasses.
//

#ifndef __MPI_SEGMENTINTERSECTIONVISITOR_H__
#define __MPI_SEGMENTINTERSECTIONVISITOR_H__

#include "MPI_SegmentVisitor.h"

class MPI_SegmentIntersectionVisitor : public MPI_SegmentVisitor
{

  public:

    MPI_SegmentIntersectionVisitor( MPI_Segment &segment );

    MPI_Segment const& getSegment( void ) const;

  private:

    MPI_Segment const& segment_;

};

#endif

// vim:sw=4:et:cindent:
