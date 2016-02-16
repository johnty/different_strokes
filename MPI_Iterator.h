
//
// MPI_Iterator.h
//
// Description:
//   A object for sequentially accessing the elements of a list.
//   Implementation of the Iterator pattern (Gamma et al.)
//   Abstract base class -- to be overridden for each type iterated over.  Just
//   defines the interface for list iterators.
//

#ifndef __MPI_ITERATOR_H__
#define __MPI_ITERATOR_H__

class MPI_Iterator
{

  public:

    virtual ~MPI_Iterator() {};

    virtual void first( void ) = 0;
    virtual void next( void ) = 0;
    virtual bool isDone( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
