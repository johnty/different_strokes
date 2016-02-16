
//
// MPI_PolyLinePointVisitor.h
//
// Description:
//   Encapsulates operations on points.  Subclass to create particular
//   operations.
//   Taken from the visitor pattern, Gamma et al., page 331.
//

#ifndef __MPI_POLYLINEPOINTVISITOR_H__
#define __MPI_POLYLINEPOINTVISITOR_H__

class MPI_PolyLinePoint;

class MPI_PolyLinePointVisitor
{

  public:

    virtual ~MPI_PolyLinePointVisitor() {};

    virtual void visitPolyLinePoint( MPI_PolyLinePoint & point ) const {};

};

#endif

// vim:sw=4:et:cindent:
