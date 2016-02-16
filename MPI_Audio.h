
//
// MPI_Audio.h
//
// Description:
//   Handles audio functionality
//

#ifndef __MPI_AUDIO_H__
#define __MPI_AUDIO_H__

#include <list>
#include <algorithm>

#include "MPI_AudioSynth.h"
#include "MPI_AudioCallback.h"

#include "RtAudio.h"
#include <cassert>

class MPI_AudioSynth;
class RtAudio;

class MPI_Audio
{

  public:

    MPI_Audio();
    ~MPI_Audio();

    void start( void );

    void addSynth( MPI_AudioSynth *synth );
    void removeSynth( MPI_AudioSynth *synth );

    void tickBuffer( double *buffer, int bufferSize ) const;

  private:

    RtAudio* audio_;

    // all of the synths that this top level holds
    std::list<MPI_AudioSynth*> synthList_;

};

#endif

// vim:sw=4:et:cindent:
