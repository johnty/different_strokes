
//
// MPI_Segment.h
//
// Description:
//   Represents a single straight-line segment.  Can find the intersection
//   between it and another segment.
//

#ifndef __MPI_SEGMENT_H__
#define __MPI_SEGMENT_H__

#include "MPI_BoundingBox.h"

class MPI_Workspace;
class MPI_IntersectionPolyLine;
class MPI_SegmentVisitor;
class MPI_SegmentIntersectionVisitor;

class MPI_Segment
{

  public:

    MPI_Segment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint );
    virtual ~MPI_Segment() {}

    MPI_Workspace& getWorkspace( void ) const;
    MPI_IntersectionPolyLine& getIntersectionPolyLine( void ) const;
    MPI_BoundingBox const& getBoundingBox( void ) const;

    virtual void acceptVisitor( MPI_SegmentVisitor const& visitor );

    virtual MPI_SegmentIntersectionVisitor* allocateIntersectionVisitor( void );

    bool findIntersection( MPI_Segment const &otherseg, float &thisisctpoint, float &otherisctpoint ) const;
    // methods to change the endpoints

    // FIXME might eventually want to separate the intersection functionality
    // from the segment class (put it in a subclass), but for now leave it in.
    // eg, having the class know about non-vanilla visitors
    // (MPI_SegmentIntersectionVisitor) seems to violate a nice, clean
    // dependency structure.

  private:

    MPI_Workspace &workspace_;
    MPI_IntersectionPolyLine &intersectionpolyline_;
    MPI_Point2D firstpoint_;
    MPI_Point2D secondpoint_;
    MPI_BoundingBox boundingbox_;
    // FIXME the bounding box can't be changed once it's been made; this will
    // be inefficient when we have to move polylines and the points are moving
    // around.

    // FIXME the workspace and polyline references are needed for the "removal"
    // editing operation.  I kind of feel they clutter up the class and that I
    // need to think more deeply about how to organize the editing
    // functionality.

};

#endif

// vim:sw=4:et:cindent:
