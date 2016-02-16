
//
// MPI_PolyLine.h
//
// Description:
//   A polyline (a piecewise linear curve)
//

#ifndef __MPI_POLYLINE_H__
#define __MPI_POLYLINE_H__

#include <ostream>

class MPI_Point2D;
class MPI_PolyLinePoint;
class MPI_PointListIterator;
class MPI_PolyLineVisitor;
class MPI_BoundingBox;

class MPI_PolyLine
{

  public:

    MPI_PolyLine();
    virtual ~MPI_PolyLine();

    virtual void appendPoint( MPI_Point2D const &point );
    virtual void end( void );

    virtual MPI_PointListIterator* allocatePointListIterator( void ) const = 0;
    MPI_BoundingBox const& getBoundingBox( void ) const;

    virtual void updateState( void );

    virtual void acceptVisitor( MPI_PolyLineVisitor const& visitor ) = 0;

    virtual void print( std::ostream &os ) const;

  protected:

    virtual void allocatePointAndAddToList( MPI_Point2D const &point ) = 0;

  private:

    MPI_BoundingBox *boundingbox_;

};

std::ostream &operator<<( std::ostream &os, MPI_PolyLine const &polyline );

#endif

// vim:sw=4:et:cindent:
