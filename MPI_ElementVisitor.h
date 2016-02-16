
//
// MPI_ElementVisitor.h
//
// Description:
//   Visitor for MPI_OneSpaceElement objects
//

#ifndef __MPI_ELEMENTVISITOR_H__
#define __MPI_ELEMENTVISITOR_H__

class MPI_OneSpaceElement;
class MPI_IntersectionElement;
class MPI_PoweredElement;
class MPI_TrainElement;

class MPI_ElementVisitor
{

  public:

    virtual ~MPI_ElementVisitor() {};

    // one entry here for each thing you can visit
    virtual void visitOneSpaceElement( MPI_OneSpaceElement& element ) {};
    virtual void visitIntersectionElement( MPI_IntersectionElement& element ) {};
    virtual void visitPoweredElement( MPI_PoweredElement& element ) {};
    virtual void visitTrainElement( MPI_TrainElement& element ) {};

    // NB: we don't provide const versions of these methods since if we allowed
    // const visitor objects, each element would have to implement four accept
    // methods: const/non-const visitor, const/non-const element.
    // Easier to just make all element visitors non-const.

};

#endif

// vim:sw=4:et:cindent:
