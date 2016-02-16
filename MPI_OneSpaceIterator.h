
//
// MPI_OneSpaceIterator.h
//
// Description:
//   For iterating over the elements in an MPI_OneSpace
//

#ifndef __MPI_ONESPACEITERATOR_H__
#define __MPI_ONESPACEITERATOR_H__

#include "MPI_ElementIterator.h"
#include <list>

class MPI_OneSpaceElementPos;

class MPI_OneSpaceIterator : public MPI_ElementIterator
{

  public:

    MPI_OneSpaceIterator( std::list<MPI_OneSpaceElementPos> const& items );

    void first( void );
    void next( void );
    bool isDone( void ) const;
    MPI_OneSpaceElement* getElement( void ) const;

  private:

    std::list<MPI_OneSpaceElementPos> const& items_;
    std::list<MPI_OneSpaceElementPos>::const_iterator iterator_;

};

#endif

// vim:sw=4:et:cindent:
