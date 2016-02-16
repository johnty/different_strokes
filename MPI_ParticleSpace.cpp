
//
// MPI_ParticleSpace.cpp
//

#include "MPI_ParticleSpace.h"

#include "MPI_OneSpaceElement.h"
#include "MPI_CollisionElementVisitor.h"
#include "MPI_CountPoweredElementsVisitor.h"

// maximum number of elements allowed in the onespace.  attempts to add
// elements beyond this limit will be ignored.
int unsigned const MPI_ParticleSpace::maxPoweredElements_ = 5;

void MPI_ParticleSpace::addElement( MPI_OneSpaceElement *element, float position )
{
    // test if there are too many powered elements
    // if there are, ignore the add request

    // count how many powered elements are already on the stroke
    MPI_CountPoweredElementsVisitor countvisitor;
    visitConstElements( countvisitor );

    // also count the element we're about to add
    element->acceptConstVisitor( countvisitor );

    // bail if adding this new powered element would take us over our
    // maxPoweredElements_
    if ( countvisitor.getPoweredElementCount() > maxPoweredElements_ )
        return;

    MPI_OneSpace::addElement( element, position );

}

MPI_ElementVisitor* MPI_ParticleSpace::allocateElementVisitor( void ) const
{
    return new MPI_CollisionElementVisitor;
}

// vim:sw=4:et:cindent:
