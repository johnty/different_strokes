
//
// MPI_Framelist.cpp
//

#include "MPI_Framelist.h"

#include "MPI_Point2D.h"

#include <math.h>

void MPI_Framelist::appendFrame( double time )
{

    // if this is the first frame, record this time as the first frame time
    // if this isn't, compute the new frame index
    float framenumber = 0.0;
    if ( frames_.isEmpty() )
        firstframetime_ = time;
    else
        framenumber = getNextFrameNumber( frames_.getLastBreakpoint().getX() );

    // append the time since the first frame on the frames list
    float timesincestart = time - firstframetime_;
    frames_.appendBreakpoint( MPI_Point2D( framenumber, timesincestart ) );

}

bool MPI_Framelist::nextFrameExists( float currentframe ) const
{
    return frames_.inRange( getNextFrameNumber( currentframe ) );
}

float MPI_Framelist::getNextFrameNumber( float currentframe ) const
{
    return floor(currentframe) + 1.0;
}

float MPI_Framelist::getDelayToNextFrame( float currentframe ) const
{

    // assumes frames_.inRange(currentframe) is true
    // assumes nextFrameExists() is true

    double currentframetime = getTimeSinceStart( currentframe );
    double nextframetime = getTimeSinceStart( getNextFrameNumber( currentframe ) );
    return nextframetime - currentframetime;

}

float MPI_Framelist::getTimeSinceStart( float currentframe ) const
{
    // assumes frames_.inRange(currentframe) is true
    return frames_.evaluate( currentframe );
}

void MPI_Framelist::print( std::ostream &os ) const
{
    os << frames_;
}

std::ostream &operator<<( std::ostream &os, MPI_Framelist const &framelist )
{
    framelist.print(os);
    return os;
}

// vim:sw=4:et:cindent:
