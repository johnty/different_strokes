
//
// MPI_OneSpaceConstIterator.h
//
// Description:
//   For iterating over the elements in an MPI_OneSpace
//

#ifndef __MPI_ONESPACECONSTITERATOR_H__
#define __MPI_ONESPACECONSTITERATOR_H__

#include "MPI_ElementConstIterator.h"
#include <list>

class MPI_OneSpaceElementPos;

class MPI_OneSpaceConstIterator : public MPI_ElementConstIterator
{

  public:

    MPI_OneSpaceConstIterator( std::list<MPI_OneSpaceElementPos> const& items );

    void first( void );
    void next( void );
    bool isDone( void ) const;
    MPI_OneSpaceElement const* getElement( void ) const;

  private:

    std::list<MPI_OneSpaceElementPos> const& items_;
    std::list<MPI_OneSpaceElementPos>::const_iterator iterator_;

};

#endif

// vim:sw=4:et:cindent:
