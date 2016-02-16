
//
// MPI_OneSpaceElementPos.cpp
//

#include "MPI_OneSpaceElementPos.h"

#include "MPI_OneSpaceElement.h"

MPI_OneSpaceElementPos::MPI_OneSpaceElementPos( MPI_OneSpaceElement *element, float position ) :
    element_( element ),
    position_( position )
{
    // empty
}

MPI_OneSpaceElement* MPI_OneSpaceElementPos::getElement( void ) const
{
    return element_;
}

void MPI_OneSpaceElementPos::setElement( MPI_OneSpaceElement *element )
{
    element_ = element;
}

float MPI_OneSpaceElementPos::getPosition( void ) const
{
    return position_;
}

void MPI_OneSpaceElementPos::setPosition( float position )
{
    position_ = position;
}

bool MPI_OneSpaceElementPos::operator==( MPI_OneSpaceElementPos const& elementpos ) const
{
    return element_ == elementpos.element_ && position_ == elementpos.position_;
}

void MPI_OneSpaceElementPos::print( std::ostream &os ) const
{
    os << *element_ << ", position: " << position_;
}

std::ostream &operator<<( std::ostream &os, MPI_OneSpaceElementPos const &elementpos )
{
    elementpos.print(os);
    return os;
}

// vim:sw=4:et:cindent:
