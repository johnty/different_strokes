
//
// MPI_Map.cpp
//

#include "MPI_Map.h"

#include "MPI_Point2D.h"

#include <cassert>

void MPI_Map::appendBreakpoint( MPI_Point2D const& point )
{

    // append the next breapoint to the breakpoint list.
    // the x value of the point *must* be strictly greater than the x value of
    // the previous breakpoint.

    // assert that they're being appended in order
    assert( breakpoints_.size() == 0 || getLastBreakpoint().getX() < point.getX() );

    // append the breakpoint
    breakpoints_.push_back( point );

}

bool MPI_Map::inRange( float x ) const
{
    // return true if x is in the range of the function, ie.
    // [firstbreakpoint.getX(), lastbreakpoint.getX()]
    // this method is used to check when it's valid to call
    // getBreakpointAtOrBefore() or evaluate()
    if ( breakpoints_.size() == 0 )
        return false;
    else
        return getFirstBreakpoint().getX() <= x && x <= getLastBreakpoint().getX();
}

bool MPI_Map::inRangeOpenEnd( float x ) const
{
    // return true if x is in the range of the function and before the last
    // breakpoint, ie.
    // [firstbreakpoint.getX(), lastbreakpoint.getX()) <- nb: open end
    // this method is used to check when it's valid to call
    // getBreakpointAfter()
    if ( breakpoints_.size() == 0 )
        return false;
    else
        return getFirstBreakpoint().getX() <= x && x < getLastBreakpoint().getX();
}

bool MPI_Map::isEmpty( void ) const
{
    return breakpoints_.size() == 0;
}

float MPI_Map::evaluate( float x ) const
{

    // evaluate the map as a piecewise linear function.
    // assumes inRange(x) is true, ie, that x is on
    // [firstbreakpoint.getX(), lastbreakpoint.getX()]

    // check if x is in line with the last breakpoint; if so, return the
    // appropriate y value without computing.  the getBreakpointAfter() method
    // won't accept an x value in line with the last breakpoint.
    if ( x == getLastBreakpoint().getX() )
        return getLastBreakpoint().getY();

    // get the breakpoints before and after
    MPI_Point2D const& before = getBreakpointAtOrBefore( x );
    MPI_Point2D const& after = getBreakpointAfter( x );

    // linearly interpolate.  this expression comes from a simple algebraic
    // manipuation of the interpolation function.
    return ((after.getX()-x)*before.getY() + (x-before.getX())*after.getY()) /
        (after.getX() - before.getX());

}

MPI_Point2D const& MPI_Map::getBreakpointAtOrBefore( float x ) const
{

    // return the closest breakpoint whose x value is equal to or less than the
    // argument (x).  Assumes that x is on
    // [firstbreakpoint.getX(), lastbreakpoint.getX()]
    // ie, that inRange(x) is true

    // we find the breakpoint that comes strictly after x, decrement it,
    // and then return its value.  the reason we do it this way is because of
    // how lower_bound and upper_bound work.  lower_bound() returns the first
    // item at or after the argument; upper_bound() returns the first item
    // after the argument.  Since we want to access the breakpoints on either
    // side of the argument, lower_bound() wouldn't work since we wouldn't know
    // without checking whether we should decrement it or not.  We know that
    // we'll always have to when working with upper_bound().

    std::list<MPI_Point2D>::const_iterator breakpoint;

    // find the closest breakpoint that comes strictly after x
    breakpoint = upper_bound( breakpoints_.begin(), breakpoints_.end(),
            MPI_Point2D( x, 0.0 ), BreakpointBefore() );

    // return the one just before the one we found
    --breakpoint;
    return *breakpoint;

}

MPI_Point2D const& MPI_Map::getBreakpointAfter( float x ) const
{
    // return the closest breakpoint whose x value is greater than the argument
    // (x).  Assumes that x is on
    // [firstbreakpoint.getX(), lastbreakpoint.getX()) <-- open at right
    // ie, that inRangeOpenEnd(x) is true
    // (NB: x cannot be in line with the last breakpoint.  Must check for this
    // case before calling this method.)

    // see notes in getBreakpointAtOrBefore() for the reasoning behind how
    // these methods work.

    std::list<MPI_Point2D>::const_iterator breakpoint;

    // find the closest breakpoint that comes strictly after x
    breakpoint = upper_bound( breakpoints_.begin(), breakpoints_.end(),
            MPI_Point2D( x, 0.0 ), BreakpointBefore() );

    // return its value
    return *breakpoint;

}

MPI_Point2D const& MPI_Map::getFirstBreakpoint( void ) const
{
    // this method assumes breakpoints_ is nonempty.
    return breakpoints_.front();
}

MPI_Point2D const& MPI_Map::getLastBreakpoint( void ) const
{
    // this method assumes breakpoints_ is nonempty.
    return breakpoints_.back();
}

void MPI_Map::print( std::ostream &os ) const
{
    std::list<MPI_Point2D>::const_iterator currentbp;
    for ( currentbp = breakpoints_.begin(); currentbp != breakpoints_.end();
            ++currentbp )
        os << *currentbp << ", ";
    os << "done";
}

bool MPI_Map::BreakpointBefore::operator()( MPI_Point2D const& a, MPI_Point2D const& b ) const
{
    // return true if a comes strictly before b in the domain
    return a.getX() < b.getX();
}

std::ostream &operator<<( std::ostream &os, MPI_Map const &map )
{
    map.print(os);
    return os;
}

// vim:sw=4:et:cindent:
