
//
// MPI_CollisionElementVisitor.cpp
//

#include "MPI_CollisionElementVisitor.h"

#include "MPI_IntersectionElement.h"

void MPI_CollisionElementVisitor::visitIntersectionElement( MPI_IntersectionElement& element )
{
    // spawn a particle at the corresponding half of the intersection pair.
    element.getOtherIntersection()->spawnElement();
}

// vim:sw=4:et:cindent:
