
//
// MPI_IntersectPolyLineVisitor.h
//
// Description:
//   Intersect a polyline with a segment
//

#ifndef __MPI_INTERSECTPOLYLINEVISITOR_H__
#define __MPI_INTERSECTPOLYLINEVISITOR_H__

#include "MPI_PolyLineVisitor.h"

class MPI_SegmentIntersectionVisitor;
class MPI_IntersectionPolyLine;

class MPI_IntersectPolyLineVisitor : public MPI_PolyLineVisitor
{

  public:

    MPI_IntersectPolyLineVisitor( MPI_SegmentIntersectionVisitor &segmentintersectionvisitor );

    // one entry here for each subclass of MPI_IntersectionPolyLine
    void visitParticleStroke( MPI_ParticleStroke& polyline ) const;
    void visitRemovalStroke( MPI_RemovalStroke& polyline ) const;
    void visitPlayheadStroke( MPI_PlayheadStroke& polyline ) const;

  private:

    void visitIntersectionPolyLine( MPI_IntersectionPolyLine& polyline ) const;

    MPI_SegmentIntersectionVisitor &segmentintersectionvisitor_;

};

#endif

// vim:sw=4:et:cindent:
