
//
// MPI_Point2D.cpp
//

#include "MPI_Point2D.h"

MPI_Point2D::MPI_Point2D( float x, float y )
{
    x_ = x;
    y_ = y;
}

float MPI_Point2D::getX( void ) const
{
    return x_;
}

float MPI_Point2D::getY( void ) const
{
    return y_;
}

void MPI_Point2D::setX( float value )
{
    x_ = value;
}

void MPI_Point2D::setY( float value )
{
    y_ = value;
}

void MPI_Point2D::print( std::ostream &os ) const
{
    os << '(' << x_ << ',' << y_ << ')';
}

std::ostream &operator<<( std::ostream &os, MPI_Point2D const &point )
{
    point.print(os);
    return os;
}

// vim:sw=4:et:cindent:
