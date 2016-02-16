
//
// MPI_BoundingBox.cpp
//

#include "MPI_BoundingBox.h"

MPI_BoundingBox::MPI_BoundingBox(MPI_Point2D const& firstpoint, MPI_Point2D const& secondpoint) :
    lowerleft_(firstpoint),
    upperright_(firstpoint)
{
    this->extendToContain( secondpoint );
}

bool MPI_BoundingBox::overlaps( MPI_BoundingBox const& otherbox ) const
{
    return
        lowerleft_.getX()          <= otherbox.upperright_.getX() &&
        otherbox.lowerleft_.getX() <= upperright_.getX()          &&
        lowerleft_.getY()          <= otherbox.upperright_.getY() &&
        otherbox.lowerleft_.getY() <= upperright_.getY();
}

bool MPI_BoundingBox::contains( MPI_Point2D const& point ) const
{
    return
        lowerleft_.getX() <= point.getX()       &&
        point.getX()      <= upperright_.getX() &&
        lowerleft_.getY() <= point.getY()       &&
        point.getY()      <= upperright_.getY();
}

void MPI_BoundingBox::extendToContain(  MPI_Point2D const& point )
{

    if ( point.getX() < lowerleft_.getX() )
        lowerleft_.setX( point.getX() );
    else if ( upperright_.getX() < point.getX() )
        upperright_.setX( point.getX() );

    if ( point.getY() < lowerleft_.getY() )
        lowerleft_.setY( point.getY() );
    else if ( upperright_.getY() < point.getY() )
        upperright_.setY( point.getY() );

}

MPI_Point2D const& MPI_BoundingBox::getLowerLeft( void ) const
{
    return lowerleft_;
}

MPI_Point2D const& MPI_BoundingBox::getUpperRight( void ) const
{
    return upperright_;
}

void MPI_BoundingBox::print( std::ostream &os ) const
{
    os << '[' << lowerleft_ << ','<< upperright_ << ']';
}

std::ostream &operator<<( std::ostream &os, MPI_BoundingBox const &bbox )
{
    bbox.print(os);
    return os;
}

// vim:sw=4:et:cindent:
