
//
// MPI_PointListIterator.h
//
// Description:
//   A object for sequentially accessing the elements of a point list.
//   Abstract base class -- to be overridden for each point type iterated over.
//

#ifndef __MPI_POINTLISTITERATOR_H__
#define __MPI_POINTLISTITERATOR_H__

#include "MPI_Iterator.h"

class MPI_PolyLinePoint;

class MPI_PointListIterator : public MPI_Iterator
{

  public:

    virtual MPI_PolyLinePoint* getPoint( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
