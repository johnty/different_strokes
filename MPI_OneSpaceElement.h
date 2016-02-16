
//
// MPI_OneSpaceElement.h
//
// Description:
//   A point element which sits in an MPI_OneSpace.  Subclasses represent
//   different types of elements.
//

#ifndef __MPI_ONESPACEELEMENT_H__
#define __MPI_ONESPACEELEMENT_H__

#include <ostream>

class MPI_ElementVisitor;
class MPI_ElementConstVisitor;

class MPI_OneSpaceElement
{

  public:

    virtual ~MPI_OneSpaceElement( void ) {}

    // activate the elemenet.  subclasses override this for specific behaviour.
    // FIXME I'm not really crazy about having this method; it makes this
    // interface less than minimal.
    virtual void activate( void ) {}

    virtual void acceptVisitor( MPI_ElementVisitor& visitor );
    virtual void acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const;

    virtual void print( std::ostream &os ) const;

};

std::ostream &operator<<( std::ostream &os,MPI_OneSpaceElement const &element );

#endif

// vim:sw=4:et:cindent:
