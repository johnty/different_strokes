
//
// MPI_CountPoweredElementsVisitor.h
//
// Description:
//   Count the number of MPI_PoweredElement objects (and subclasses) visited.
//   Visit all of the elments you want to count, and then call
//   getPoweredElementCount() to get the total number seen.
//

#ifndef __MPI_COUNTPOWEREDELEMENTSVISITOR_H__
#define __MPI_COUNTPOWEREDELEMENTSVISITOR_H__

#include "MPI_ElementConstVisitor.h"

class MPI_CountPoweredElementsVisitor : public MPI_ElementConstVisitor
{

  public:

    MPI_CountPoweredElementsVisitor( void );

    unsigned int getPoweredElementCount( void ) const;

    void visitOneSpaceElement( MPI_OneSpaceElement const& element );
    void visitIntersectionElement( MPI_IntersectionElement const& element );
    void visitPoweredElement( MPI_PoweredElement const& element );
    void visitTrainElement( MPI_TrainElement const& element );

  private:

    unsigned int numpoweredelements_;

};

#endif

// vim:sw=4:et:cindent:
