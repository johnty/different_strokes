
//
// MPI_IntersectionElement.h
//
// Description:
//   onespace element for embedding an intersection in a onespace.
//
//   intersections occur between two onespaces.  this class handles one of the
//   spaces; a pointer is stored to the corresponding intersection in the other
//   onespace.
//

// TODO
//  - think about how these classes are set up.  MPI_IntersectionElement needs
//    to know about MPI_ParticleSpace; MPI_ElementVisitor needs to know about
//    all of the elements, and so the basic onespace classes need to know about
//    collisions.  think about redoing this so that you can have a generic
//    intersection element class, and then subclass it to extend its behaviour
//    so it knows about collisions.  basically just think about how the classes
//    are partitioned into groups and try to minimise and control the
//    dependencies between the groups.
//    - you could also have a subclass of the general visitor which knows about
//      collisions and particlespaces, and that way you can extend the visitors
//      and still prevent the basic onespace classes from being exposed to
//      things they shouldn't be.
//    - this doesn't matter -- particle spaces eliminated, intersection doesn't
//      know about them anymore
//    - the visitor base class shouldn't count as a dependency, maybe -- it
//      doesn't include any header files (just defines the class names for all
//      of the elements), and it sort of acts as a global at the edge of a
//      subsystem.  you could sublcass the visitor and extend it for other
//      sub-subsystems, but maybe that would get too complicated.

#ifndef __MPI_INTERSECTIONELEMENT_H__
#define __MPI_INTERSECTIONELEMENT_H__

#include "MPI_OneSpaceElement.h"

class MPI_OneSpace;
class MPI_ElementFactory;

class MPI_IntersectionElement : public MPI_OneSpaceElement
{

  public:

    MPI_IntersectionElement( MPI_OneSpace &onespace, MPI_ElementFactory const& elementfactory );
    ~MPI_IntersectionElement();

    void setOtherIntersection( MPI_IntersectionElement *intersection );
    MPI_IntersectionElement* getOtherIntersection( void ) const;

    void spawnElement( void ) const;

    void acceptVisitor( MPI_ElementVisitor& visitor );
    void acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const;

    static void createIntersectionPair( MPI_OneSpace &onespaceone, MPI_ElementFactory const& elementfactoryone, float positionone, MPI_OneSpace &onespacetwo, MPI_ElementFactory const& elementfactorytwo, float positiontwo );

  private:

    MPI_OneSpace &onespace_;
    MPI_ElementFactory const& elementfactory_;
    MPI_IntersectionElement *otherintersection_;

};

#endif

// vim:sw=4:et:cindent:
