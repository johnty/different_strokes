
//
// MPI_IntersectionPolyLine.h
//
// Description:
//   Polyline which handles intersections.  Abstract class; needs to be
//   subclassed.
//

#ifndef __MPI_INTERSECTIONPOLYLINE_H__
#define __MPI_INTERSECTIONPOLYLINE_H__

#include "MPI_PolyLine.h"
#include <list>

class MPI_Workspace;
class MPI_Segment;
class MPI_SegmentVisitor;

class MPI_IntersectionPolyLine : public MPI_PolyLine
{
    // FIXME this class should be renamed; should be MPI_SegmentPolyline there
    // shouldn't be anything in here explicitly about intersection.

  public:

    MPI_IntersectionPolyLine( MPI_Workspace &workspace );
    virtual ~MPI_IntersectionPolyLine();

    virtual void appendPoint( MPI_Point2D const &point );

    void markForRemoval( void );
    bool isMarkedForRemoval( void ) const;

    void visitSegments( MPI_SegmentVisitor const& visitor ) const;

    // NB: there is no acceptVisitor() method for this class since it's pure
    // virtual and can't be instantiated.

  protected:

    virtual MPI_Segment* allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint );
    virtual MPI_Point2D const* getLastPoint( void ) const = 0;
    unsigned int getNumSegments( void ) const;
    MPI_Workspace& getWorkspace( void ) const;

  private:

    std::list<MPI_Segment*> segmentlist_;
    MPI_Workspace &workspace_;
    bool markedforremoval_;

};

#endif

// vim:sw=4:et:cindent:
