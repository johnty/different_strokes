
//
// MPI_CollisionElementVisitor.h
//
// Description:
//   Visitor that gets sent to elements that are collided with
//

#ifndef __MPI_COLLISIONELEMENTVISITOR_H__
#define __MPI_COLLISIONELEMENTVISITOR_H__

#include "MPI_ElementVisitor.h"

class MPI_CollisionElementVisitor : public MPI_ElementVisitor
{

  public:

    void visitIntersectionElement( MPI_IntersectionElement& element );

};

#endif

// vim:sw=4:et:cindent:
