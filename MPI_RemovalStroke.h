
//
// MPI_RemovalStroke.h
//
// Description:
//   Editing stroke which removes any MPI_IntersectionPolyLine instances it
//   intersects.
//

#ifndef __MPI_REMOVALSTROKE_H__
#define __MPI_REMOVALSTROKE_H__

#include "MPI_IntersectionPolyLine.h"

class MPI_Scheduler;

class MPI_RemovalStroke : public MPI_IntersectionPolyLine
{

  public:

    MPI_RemovalStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler );
    virtual ~MPI_RemovalStroke();

    virtual void end( void );

    virtual MPI_PointListIterator* allocatePointListIterator( void ) const;

    virtual void acceptVisitor( MPI_PolyLineVisitor const& visitor );

  protected:

    virtual void allocatePointAndAddToList( MPI_Point2D const &point );
    virtual MPI_Segment* allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint );
    virtual MPI_Point2D const* getLastPoint( void ) const;

  private:

    std::list<MPI_PolyLinePoint*> pointList_;
    MPI_Scheduler &scheduler_;

};

#endif

// vim:sw=4:et:cindent:
