
//
// MPI_PolyLinePoint.h
//
// Description:
//   A point that is a member of a polyline
//

#ifndef __MPI_POLYLINEPOINT_H__
#define __MPI_POLYLINEPOINT_H__

#include "MPI_Point2D.h"

class MPI_PolyLine;
class MPI_PolyLinePointVisitor;

class MPI_PolyLinePoint
{

  public:

    MPI_PolyLinePoint( MPI_PolyLine const &owner, MPI_Point2D const &point );
    MPI_PolyLinePoint( MPI_PolyLine const &owner, float x, float y );
    virtual ~MPI_PolyLinePoint( void ) {}

    float getX( void ) const;
    float getY( void ) const;
    void  setX( float value );
    void  setY( float value );

    MPI_PolyLine const& getOwner( void ) const;
    MPI_Point2D const& getPoint( void ) const;

    virtual void acceptVisitor( MPI_PolyLinePointVisitor const& visitor );

    virtual void print( std::ostream &os ) const;

  private:

    MPI_PolyLine const &owner_;
    MPI_Point2D point_;

};

std::ostream &operator<<( std::ostream &os, MPI_PolyLinePoint const &point );

#endif

// vim:sw=4:et:cindent:
