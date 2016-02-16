
//
// MPI_ElementConstVisitor.h
//
// Description:
//   Visitor for const MPI_OneSpaceElement objects
//

#ifndef __MPI_ELEMENTCONSTVISITOR_H__
#define __MPI_ELEMENTCONSTVISITOR_H__

class MPI_OneSpaceElement;
class MPI_IntersectionElement;
class MPI_PoweredElement;
class MPI_TrainElement;

class MPI_ElementConstVisitor
{

  public:

    virtual ~MPI_ElementConstVisitor() {};

    // one entry here for each thing you can visit
    virtual void visitOneSpaceElement( MPI_OneSpaceElement const& element ) {};
    virtual void visitIntersectionElement( MPI_IntersectionElement const& element ) {};
    virtual void visitPoweredElement( MPI_PoweredElement const& element ) {};
    virtual void visitTrainElement( MPI_TrainElement const& element ) {};

    // NB: we don't provide const versions of these methods since if we allowed
    // const visitor objects, each element would have to implement four accept
    // methods: const/non-const visitor, const/non-const element.
    // Easier to just make all element visitors non-const.

};

#endif

// vim:sw=4:et:cindent:
