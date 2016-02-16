
//
// MPI_OneSpaceElement.cpp
//

#include "MPI_OneSpaceElement.h"

#include "MPI_ElementVisitor.h"
#include "MPI_ElementConstVisitor.h"

void MPI_OneSpaceElement::acceptVisitor( MPI_ElementVisitor& visitor )
{
    visitor.visitOneSpaceElement( *this );
}

void MPI_OneSpaceElement::acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const
{
    visitor.visitOneSpaceElement( *this );
}

void MPI_OneSpaceElement::print( std::ostream &os ) const
{
    os << std::showbase << std::hex << this << std::noshowbase << std::dec;
}

std::ostream &operator<<( std::ostream &os, MPI_OneSpaceElement const &element )
{
    element.print(os);
    return os;
}

// vim:sw=4:et:cindent:
