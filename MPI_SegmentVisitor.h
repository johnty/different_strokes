
//
// MPI_SegmentVisitor.h
//
// Description:
//   Visitor for MPI_Segment objects
//

#ifndef __MPI_SEGMENTVISITOR_H__
#define __MPI_SEGMENTVISITOR_H__

class MPI_Segment;
class MPI_ParticleSegment;
class MPI_RemovalSegment;

class MPI_SegmentVisitor
{

  public:

    virtual ~MPI_SegmentVisitor() {}

    virtual void visitSegment( MPI_Segment &segment ) const {}
    virtual void visitParticleSegment( MPI_ParticleSegment &segment ) const {}
    virtual void visitRemovalSegment( MPI_RemovalSegment &segment ) const {}

};

#endif

// vim:sw=4:et:cindent:
