
//
// MPI_PolyLinePointDequeIterator.h
//
// Description:
//   A object for sequentially accessing the elements of an MPI_PolyLinePoint
//   deque.
//

#ifndef __MPI_POLYLINEPOINTDEQUEITERATOR_H__
#define __MPI_POLYLINEPOINTDEQUEITERATOR_H__

#include "MPI_PointListIterator.h"
#include <deque>

class MPI_PolyLinePointDequeIterator : public MPI_PointListIterator
{

  public:

    MPI_PolyLinePointDequeIterator( std::deque<MPI_PolyLinePoint*> const& pointlist );

    void first( void );
    void next( void );
    bool isDone( void ) const;
    MPI_PolyLinePoint* getPoint( void ) const;

  private:

    std::deque<MPI_PolyLinePoint*> const& pointlist_;
    std::deque<MPI_PolyLinePoint*>::const_iterator iterator_;

};

#endif

// vim:sw=4:et:cindent:
