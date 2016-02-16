
//
// MPI_ElementConstIterator.h
//
// Description:
//   For iterating over a list of elements
//

#ifndef __MPI_ELEMENTCONSTITERATOR_H__
#define __MPI_ELEMENTCONSTITERATOR_H__

#include "MPI_Iterator.h"

class MPI_OneSpaceElement;

class MPI_ElementConstIterator : public MPI_Iterator
{

  public:

    virtual MPI_OneSpaceElement const* getElement( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
