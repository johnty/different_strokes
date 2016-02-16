
//
// MPI_IsctWithSegmentVisitor.h
//
// Description:
//   Visitor that intersects the visited segment with an MPI_Segment instance
//

// FIXME this naming is kind of confusing... what's the difference between
// MPI_IsctWithSegmentVisitor and MPI_SegmentIntersectionVisitor?

#ifndef __MPI_ISCTWITHSEGMENTVISITOR_H__
#define __MPI_ISCTWITHSEGMENTVISITOR_H__

#include "MPI_SegmentIntersectionVisitor.h"

class MPI_IsctWithSegmentVisitor : public MPI_SegmentIntersectionVisitor
{

  public:

    MPI_IsctWithSegmentVisitor( MPI_Segment &segment );

    // FIXME can these be const?  we'll be changing the segment...
    virtual void visitSegment( MPI_Segment &segment ) const;
    virtual void visitParticleSegment( MPI_ParticleSegment &segment ) const;
    virtual void visitRemovalSegment( MPI_RemovalSegment &segment ) const;

  private:

    MPI_Segment &segment_;

};

#endif

// vim:sw=4:et:cindent:
