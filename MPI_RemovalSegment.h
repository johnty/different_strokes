
//
// MPI_RemovalSegment.h
//
// Description:
//   A segment which removes polylines that it intersects with
//

#ifndef __MPI_REMOVALSEGMENT_H__
#define __MPI_REMOVALSEGMENT_H__

#include "MPI_Segment.h"

class MPI_Scheduler;

class MPI_RemovalSegment : public MPI_Segment
{

  public:

    MPI_RemovalSegment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint, MPI_Scheduler &scheduler );

    virtual void acceptVisitor( MPI_SegmentVisitor const& visitor );

    virtual MPI_SegmentIntersectionVisitor* allocateIntersectionVisitor( void );

  private:

    MPI_Scheduler &scheduler_;

};

#endif

// vim:sw=4:et:cindent:
