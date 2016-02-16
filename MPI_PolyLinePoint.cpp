
//
// MPI_PolyLinePoint.cpp
//

#include "MPI_PolyLinePoint.h"

#include "MPI_PolyLinePointVisitor.h"

MPI_PolyLinePoint::MPI_PolyLinePoint( MPI_PolyLine const &owner, MPI_Point2D const &point ) :
    owner_(owner),
    point_(point)
{
    // empty
}

MPI_PolyLinePoint::MPI_PolyLinePoint( MPI_PolyLine const &owner, float x, float y ) :
    owner_(owner),
    point_(x, y)
{
    // empty
}

float MPI_PolyLinePoint::getX( void ) const
{
    return point_.getX();
}

float MPI_PolyLinePoint::getY( void ) const
{
    return point_.getY();
}

void MPI_PolyLinePoint::setX( float value )
{
    point_.setX( value );
}

void MPI_PolyLinePoint::setY( float value )
{
    point_.setY( value );
}

MPI_PolyLine const& MPI_PolyLinePoint::getOwner( void ) const
{
    return owner_;
}

MPI_Point2D const& MPI_PolyLinePoint::getPoint( void ) const
{
    return point_;
}

void MPI_PolyLinePoint::acceptVisitor( MPI_PolyLinePointVisitor const& visitor )
{
    visitor.visitPolyLinePoint( *this );
}

void MPI_PolyLinePoint::print( std::ostream &os ) const
{
    os << point_;
}

std::ostream &operator<<( std::ostream &os, MPI_PolyLinePoint const &point )
{
    point.print(os);
    return os;
}

// vim:sw=4:et:cindent:
