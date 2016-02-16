
//
// MPI_IsctWithRemovalSegmentVisitor.h
//
// Description:
//   Visitor that intersects the visited segment with an MPI_RemovalSegment
//   instance
//

#ifndef __MPI_ISCTWITHREMOVALSEGMENTVISITOR_H__
#define __MPI_ISCTWITHREMOVALSEGMENTVISITOR_H__

#include "MPI_SegmentIntersectionVisitor.h"

class MPI_Scheduler;

class MPI_IsctWithRemovalSegmentVisitor : public MPI_SegmentIntersectionVisitor
{

  private:

  public:

    MPI_IsctWithRemovalSegmentVisitor( MPI_RemovalSegment &removalsegment, MPI_Scheduler &scheduler );

    virtual void visitSegment( MPI_Segment &segment ) const;
    virtual void visitParticleSegment( MPI_ParticleSegment &segment ) const;
    virtual void visitRemovalSegment( MPI_RemovalSegment &segment ) const;

  private:

    MPI_Scheduler &scheduler_;

};

#endif

// vim:sw=4:et:cindent:
