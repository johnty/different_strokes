
//
// MPI_IteratorPtr.h
//
// Description:
//   Encapsulates a pointer to an iterator.  Automatically deletes the pointer
//   in the destructor, so the client code using the iterator doesn't have to
//   remember to.
//   This is an implementation of the proxy pattern, Gamma et al.,
//   as suggested in the section "Making sure iterators get deleted", p 266,
//   Gamma et al.
//

#ifndef __MPI_ITERATORPTR_H__
#define __MPI_ITERATORPTR_H__

template <class Iterator>
class MPI_IteratorPtr
{

  public:

    MPI_IteratorPtr( Iterator* iteratorptr ) : iteratorptr_(iteratorptr) {}
    ~MPI_IteratorPtr() { delete iteratorptr_; }

    Iterator* operator->() { return iteratorptr_; }
    Iterator& operator*() { return *iteratorptr_; }

  private:

    // don't allow copy and assignment -- don't want iteratorptr_ deleted
    // multiple times.  these don't need to be defined anywhere.
    MPI_IteratorPtr(const MPI_IteratorPtr&);
    MPI_IteratorPtr& operator=(const MPI_IteratorPtr&);

    // the pointer
    Iterator* iteratorptr_;

};

#endif

// vim:sw=4:et:cindent:
