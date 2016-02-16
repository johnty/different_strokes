
//
// MPI_ElementIterator.h
//
// Description:
//   For iterating over a list of elements
//

#ifndef __MPI_ELEMENTITERATOR_H__
#define __MPI_ELEMENTITERATOR_H__

#include "MPI_Iterator.h"

class MPI_OneSpaceElement;

class MPI_ElementIterator : public MPI_Iterator
{

  public:

    virtual MPI_OneSpaceElement* getElement( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
