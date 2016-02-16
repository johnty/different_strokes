
//
// MPI_PolyLinePointListIterator.h
//
// Description:
//   A object for sequentially accessing the elements of an MPI_PolyLinePoint
//   list.
//

#ifndef __MPI_POLYLINEPOINTLISTITERATOR_H__
#define __MPI_POLYLINEPOINTLISTITERATOR_H__

#include "MPI_PointListIterator.h"
#include <list>

class MPI_PolyLinePointListIterator : public MPI_PointListIterator
{

  public:

    // ctor takes list reference
    MPI_PolyLinePointListIterator( std::list<MPI_PolyLinePoint*> const& pointlist );

    void first( void );
    void next( void );
    bool isDone( void ) const;
    MPI_PolyLinePoint* getPoint( void ) const;

  private:

    std::list<MPI_PolyLinePoint*> const& pointlist_;
    std::list<MPI_PolyLinePoint*>::const_iterator iterator_;

};

#endif

// vim:sw=4:et:cindent:
