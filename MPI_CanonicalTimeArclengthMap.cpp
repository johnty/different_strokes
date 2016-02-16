
//
// MPI_CanonicalTimeArclengthMap.cpp
//

#include "MPI_CanonicalTimeArclengthMap.h"

#include "MPI_Scheduler.h"

#include <cassert>
#include <math.h>

MPI_CanonicalTimeArclengthMap::MPI_CanonicalTimeArclengthMap( MPI_Scheduler const& scheduler ) :
    scheduler_( scheduler ),
    previouspoint_( 0.0, 0.0 )
{
    // empty
}

void MPI_CanonicalTimeArclengthMap::appendPoint( MPI_Point2D const &point )
{

    if ( isEmpty() ) {

        framelist_.appendFrame( scheduler_.getTime() );
        canonicalvstime_.appendBreakpoint( MPI_Point2D( 0.0, 0.0 ) );
        arclengthvscanonical_.appendBreakpoint( MPI_Point2D( 0.0, 0.0 ) );
        canonicalvsarclength_.appendBreakpoint( MPI_Point2D( 0.0, 0.0 ) );

    }
    else {

        framelist_.appendFrame( scheduler_.getTime() );

        float canonicalcoord = getLastCanonicalCoord() + 1.0;
        float arclength = computeSegmentLength( previouspoint_, point ) + getTotalArclength();
        float time = framelist_.getTimeSinceStart( canonicalcoord );

        canonicalvstime_.appendBreakpoint( MPI_Point2D( time, canonicalcoord ) );
        arclengthvscanonical_.appendBreakpoint( MPI_Point2D( canonicalcoord, arclength ) );
        canonicalvsarclength_.appendBreakpoint( MPI_Point2D( arclength, canonicalcoord ) );

    }

    previouspoint_ = point;

}

MPI_Framelist const& MPI_CanonicalTimeArclengthMap::getFramelist( void ) const
{
    return framelist_;
}

bool MPI_CanonicalTimeArclengthMap::inCanonicalRange( float canonicalcoord ) const
{
    return arclengthvscanonical_.inRange( canonicalcoord );
}

bool MPI_CanonicalTimeArclengthMap::inTimeRange( float time ) const
{
    return canonicalvstime_.inRange( time );
}

bool MPI_CanonicalTimeArclengthMap::inTimeRangeOpenEnd( float time ) const
{
    return canonicalvstime_.inRangeOpenEnd( time );
}

bool MPI_CanonicalTimeArclengthMap::inArclengthRange( float arclength ) const
{
    return canonicalvsarclength_.inRange( arclength );
}

bool MPI_CanonicalTimeArclengthMap::isEmpty( void ) const
{

    // assert that they're consistent; can't check framelist_ directly
    assert( ( canonicalvstime_.isEmpty() && arclengthvscanonical_.isEmpty() && canonicalvsarclength_.isEmpty() ) ||
            ( !canonicalvstime_.isEmpty() && !arclengthvscanonical_.isEmpty() && !canonicalvsarclength_.isEmpty() ) );

    return arclengthvscanonical_.isEmpty();

}

float MPI_CanonicalTimeArclengthMap::getTimeFromCanonical( float canonicalcoord ) const
{
    // this assumes inCanonicalRange() is true
    return framelist_.getTimeSinceStart( canonicalcoord );
}

float MPI_CanonicalTimeArclengthMap::getArclengthFromCanonical( float canonicalcoord ) const
{
    // this assumes inCanonicalRange() is true
    return arclengthvscanonical_.evaluate( canonicalcoord );
}

float MPI_CanonicalTimeArclengthMap::getCanonicalFromTime( float time ) const
{
    // this assumes inTimeRange() is true
    return canonicalvstime_.evaluate( time );
}

float MPI_CanonicalTimeArclengthMap::getArclengthFromTime( float time ) const
{
    // this assumes inTimeRange() is true
    return arclengthvscanonical_.evaluate( canonicalvstime_.evaluate( time ) );
}

float MPI_CanonicalTimeArclengthMap::getCanonicalFromArclength( float arclength ) const
{
    // this assumes inArclengthRange() is true
    return canonicalvsarclength_.evaluate( arclength );
}

float MPI_CanonicalTimeArclengthMap::getTimeFromArclength( float arclength ) const
{
    // this assumes inArclengthRange() is true
    return framelist_.getTimeSinceStart( canonicalvsarclength_.evaluate( arclength ) );
}

float MPI_CanonicalTimeArclengthMap::getLastCanonicalCoord( void ) const
{
    // this assumes isEmpty() is false
    return arclengthvscanonical_.getLastBreakpoint().getX();
}

float MPI_CanonicalTimeArclengthMap::getTotalTime( void ) const
{
    // this assumes isEmpty() is false
    return canonicalvstime_.getLastBreakpoint().getX();
}

float MPI_CanonicalTimeArclengthMap::getTotalArclength( void ) const
{
    // this assumes isEmpty() is false
    return canonicalvsarclength_.getLastBreakpoint().getX();
}

float MPI_CanonicalTimeArclengthMap::getArclengthVsTimeSlope( float time ) const
{

    // this assumes inTimeRangeOpenEnd() is true
    // returns arclength units per time unit

    MPI_Point2D const& leftbreakpoint = canonicalvstime_.getBreakpointAtOrBefore( time );
    MPI_Point2D const& rightbreakpoint = canonicalvstime_.getBreakpointAfter( time );

    return computeSlope(
        MPI_Point2D(
            leftbreakpoint.getX(),
            getArclengthFromCanonical( leftbreakpoint.getY() )
        ),
        MPI_Point2D(
            rightbreakpoint.getX(),
            getArclengthFromCanonical( rightbreakpoint.getY() )
        )
    );

}

float MPI_CanonicalTimeArclengthMap::getResampledArclengthVsTimeSlope( float time, float samplingperiod ) const
{

    // find the left and right points to sample at, and return the slope
    // this assumes inTimeRangeOpenEnd() is true and that 0.0 < samplingperiod

    assert( 0.0 < samplingperiod );

    float timeinperiods = time / samplingperiod;
    float leftsampletimeinperiods = floor( timeinperiods );
    float rightsampletimeinperiods = leftsampletimeinperiods + 1.0;

    float leftsampletime = leftsampletimeinperiods * samplingperiod;
    float rightsampletime = rightsampletimeinperiods * samplingperiod;

    // leftsampletime < 0.0 should never happen
    assert( 0.0 <= leftsampletime );

    // clamp the left and right sample times to the boundaries of the map
    if ( getTotalTime() < rightsampletime )
        rightsampletime = getTotalTime();

    // assert that everything's kosher -- this should never be false if our
    // assumptions are true up to this point.
    assert( leftsampletime < rightsampletime );

    // return the computed slope
    return computeSlope(
        MPI_Point2D( leftsampletime, getArclengthFromTime( leftsampletime ) ),
        MPI_Point2D( rightsampletime, getArclengthFromTime( rightsampletime ) )
    );

}

void MPI_CanonicalTimeArclengthMap::print( std::ostream &os ) const
{
    os << "framelist_: " << framelist_ << ", ";
    os << "canonicalvstime_: " << canonicalvstime_ << ", ";
    os << "arclengthvscanonical_: " << arclengthvscanonical_ << ", ";
    os << "canonicalvsarclength_: " << canonicalvsarclength_ << ", ";
    os << "previouspoint_: " << previouspoint_;
}

float MPI_CanonicalTimeArclengthMap::computeSlope( MPI_Point2D const& leftpoint, MPI_Point2D const& rightpoint ) const
{
    return ( rightpoint.getY() - leftpoint.getY() ) /
        ( rightpoint.getX() - leftpoint.getX() );
}

float MPI_CanonicalTimeArclengthMap::computeSegmentLength( MPI_Point2D const& leftpoint, MPI_Point2D const& rightpoint ) const
{
    float deltax = rightpoint.getX() - leftpoint.getX();
    float deltay = rightpoint.getY() - leftpoint.getY();
    return sqrt( deltax*deltax + deltay*deltay );
}

std::ostream &operator<<( std::ostream &os, MPI_CanonicalTimeArclengthMap const &canonicaltimearclengthmap )
{
    canonicaltimearclengthmap.print(os);
    return os;
}

// vim:sw=4:et:cindent:
