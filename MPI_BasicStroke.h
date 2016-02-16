
//
// MPI_BasicStroke.h
//
// Description:
//   Basic stroke type.  Doesn't do anything -- just draws
//

#ifndef __MPI_BASICSTROKE_H__
#define __MPI_BASICSTROKE_H__

#include "MPI_PolyLine.h"
#include <list>

class MPI_BasicStroke : public MPI_PolyLine
{

  public:

    virtual ~MPI_BasicStroke();

    virtual MPI_PointListIterator* allocatePointListIterator( void ) const;

    virtual void acceptVisitor( MPI_PolyLineVisitor const& visitor );

  protected:

    virtual void allocatePointAndAddToList( MPI_Point2D const &point );

  private:

    std::list<MPI_PolyLinePoint*> pointList_;

};

#endif

// vim:sw=4:et:cindent:
