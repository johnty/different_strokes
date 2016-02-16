
//
// MPI_CountPoweredElementsVisitor.cpp
//

#include "MPI_CountPoweredElementsVisitor.h"

#include "MPI_TrainElement.h"

MPI_CountPoweredElementsVisitor::MPI_CountPoweredElementsVisitor( void ) :
    numpoweredelements_( 0 )
{
    // empty
}

unsigned int MPI_CountPoweredElementsVisitor::getPoweredElementCount( void ) const
{
    return numpoweredelements_;
}

void MPI_CountPoweredElementsVisitor::visitOneSpaceElement( MPI_OneSpaceElement const& element )
{
    // empty
}

void MPI_CountPoweredElementsVisitor::visitIntersectionElement( MPI_IntersectionElement const& element )
{
    // empty
}

void MPI_CountPoweredElementsVisitor::visitPoweredElement( MPI_PoweredElement const& element )
{
    numpoweredelements_++;
}

void MPI_CountPoweredElementsVisitor::visitTrainElement( MPI_TrainElement const& element )
{
    visitPoweredElement( element );
}

// vim:sw=4:et:cindent:
