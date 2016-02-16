
//
// MPI_Framelist.h
//
// Description:
//   Manages a list of framenumber/time pairs; used for animation.
//   given a frame number, will return the next frame number and the time to
//   delay until the frame should happen.
//

#ifndef __MPI_FRAMELIST_H__
#define __MPI_FRAMELIST_H__

#include "MPI_Map.h"
#include <ostream>

class MPI_Framelist
{

  public:

    void appendFrame( double time );
    bool nextFrameExists( float currentframe ) const;
    float getNextFrameNumber( float currentframe ) const;
    float getDelayToNextFrame( float currentframe ) const;
    float getTimeSinceStart( float currentframe ) const;

    void print( std::ostream &os ) const;

  private:

    MPI_Map frames_;
    double firstframetime_;

};

std::ostream &operator<<( std::ostream &os, MPI_Framelist const &framelist );

#endif

// vim:sw=4:et:cindent:
