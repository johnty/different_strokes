
//
// MPI_Map.h
//
// Description:
//   Represents a piecewise linear curve in two dimensions.
//

#ifndef __MPI_MAP_H__
#define __MPI_MAP_H__

#include <list>
#include <ostream>

class MPI_Point2D;

class MPI_Map
{

  public:

    void appendBreakpoint( MPI_Point2D const& point );

    bool inRange( float x ) const;
    bool inRangeOpenEnd( float x ) const;
    bool isEmpty( void ) const;

    float evaluate( float x ) const;

    MPI_Point2D const& getBreakpointAtOrBefore( float x ) const;
    MPI_Point2D const& getBreakpointAfter( float x ) const;
    MPI_Point2D const& getFirstBreakpoint( void ) const;
    MPI_Point2D const& getLastBreakpoint( void ) const;

    void print( std::ostream &os ) const;

  private:

    // comparison operator for working with the sorted list of breakpoints.
    // operator() returns true if a.getX() < b.getX().
    class BreakpointBefore
    {
      public:
        bool operator()( MPI_Point2D const& a, MPI_Point2D const& b ) const;
    };

    std::list<MPI_Point2D> breakpoints_;

};

std::ostream &operator<<( std::ostream &os, MPI_Map const &map );

#endif

// vim:sw=4:et:cindent:
