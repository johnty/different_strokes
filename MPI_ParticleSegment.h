
//
// MPI_ParticleSegment.h
//
// Description:
//   An MPI_Segment subclass for use with the "particle" stroke set.  knows
//   about onespaces, and marries the segment intersections with the onespace
//   intersection elements.
//

#ifndef __MPI_PARTICLESEGMENT_H__
#define __MPI_PARTICLESEGMENT_H__

#include "MPI_Segment.h"

class MPI_OneSpace;
class MPI_ElementFactory;

class MPI_ParticleSegment : public MPI_Segment
{

  public:

    MPI_ParticleSegment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint, MPI_OneSpace &onespace, float const firstposition, float const secondposition, MPI_ElementFactory const& elementfactory );

    virtual void acceptVisitor( MPI_SegmentVisitor const& visitor );

    virtual MPI_SegmentIntersectionVisitor* allocateIntersectionVisitor( void );

    void addParticleSegIntersection( MPI_ParticleSegment &otherseg, float thissegpos, float othersegpos );

  private:

    MPI_OneSpace &onespace_;
    float const firstposition_;
    float const secondposition_;
    MPI_ElementFactory const& elementfactory_;

};

#endif

// vim:sw=4:et:cindent:
