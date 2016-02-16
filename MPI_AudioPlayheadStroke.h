
//
// MPI_AudioPlayheadStroke.h
//
// Description:
//   A particle stroke which plays back a wavetable as the particles move along
//   it.  The wavetable is mapped to the length of the stroke, and the most
//   recently added particle acts as the playhead.
//

// NB: note that the way the initial playhead movement interacts
// with the assumptions I've made for 0-length MPI_AudioParticleSpace
// instances, the initial head particle will stay at pos 0, speed 0, even
// though it's at the end of the onespace.  (Only rate is updated on each
// movement, not pos.  It starts with pos 0, and then since it's at the end, it
// sticks with speed 0.0, so the wavetable position stays at zero the whole
// time)

#ifndef __MPI_AUDIOPLAYHEADSTROKE_H__
#define __MPI_AUDIOPLAYHEADSTROKE_H__

#include "MPI_PlayheadStroke.h"
#include "MPI_AudioParticleSpace.h"

class MPI_AudioPlayheadStroke : public MPI_PlayheadStroke
{

  public:

    MPI_AudioPlayheadStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler, MPI_Audio &audio, MPI_AudioWavetable &wavetable );

    virtual void updateState( void );

    virtual MPI_OneSpace& getOneSpace( void );
    virtual MPI_OneSpace const& getOneSpace( void ) const;

    virtual float getLength( void ) const;

  private:

    MPI_AudioParticleSpace audioparticlespace_;

};

#endif

// vim:sw=4:et:cindent:
