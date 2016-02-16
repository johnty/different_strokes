
//
// MPI_IsctWithParticleSegmentVisitor.h
//
// Description:
//   Visitor that intersects the visited segment with an MPI_ParticleSegment
//   instance
//

#ifndef __MPI_ISCTWITHPARTICLESEGMENTVISITOR_H__
#define __MPI_ISCTWITHPARTICLESEGMENTVISITOR_H__

#include "MPI_SegmentIntersectionVisitor.h"

class MPI_IsctWithParticleSegmentVisitor : public MPI_SegmentIntersectionVisitor
{

  public:

    MPI_IsctWithParticleSegmentVisitor( MPI_ParticleSegment &particlesegment );

    virtual void visitSegment( MPI_Segment &segment ) const;
    virtual void visitParticleSegment( MPI_ParticleSegment &segment ) const;
    virtual void visitRemovalSegment( MPI_RemovalSegment &segment ) const;

  private:

    MPI_ParticleSegment &particlesegment_;

};

#endif

// vim:sw=4:et:cindent:
