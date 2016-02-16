
//
// MPI_Point2D.h
//
// Description:
//   A two dimensional point
//

#ifndef __MPI_POINT2D_H__
#define __MPI_POINT2D_H__

#include <ostream>

class MPI_Point2D
{

  public:

    MPI_Point2D( float x, float y );

    float getX( void ) const;
    float getY( void ) const;
    void  setX( float value );
    void  setY( float value );

    void print( std::ostream &os ) const;

  private:

    float x_;
    float y_;

};

std::ostream &operator<<( std::ostream &os, MPI_Point2D const &point );

#endif

// vim:sw=4:et:cindent:
