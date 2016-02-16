
//
// MPI_AudioWavetableSynth.h
//
// Description:
//   A synth that plays the contents of a wavetable.  Doesn't actually hold
//   any of the sample data; just holds a reference to an MPI_AudioWavetable
//   object which holds the data.  Multiple voices can read from the same
//   wavetable at once.
//   NB: This class assumes that the contents of the wavetable that it refers
//   to doesn't change over its lifetime.
//

#ifndef __MPI_AUDIOWAVETABLESYNTH_H__
#define __MPI_AUDIOWAVETABLESYNTH_H__

#include "MPI_AudioSynth.h"

class MPI_AudioWavetable;

class MPI_AudioWavetableSynth : public MPI_AudioSynth
{

  public:

    MPI_AudioWavetableSynth( MPI_Audio &audioinstance, MPI_AudioWavetable &wavetable );
    ~MPI_AudioWavetableSynth();

    MPI_AudioWavetable& getWavetable( void ) const;

    void reset( void );
    bool isFinished( void ) const;
    void setRate( float rate );
    void addTime( float time );
    void setInterpolate( bool doInterpolate );

    float tick( void );

    void setGain( float value );

  private:

    MPI_AudioWavetable &wavetable_;
    bool finished_;
    bool interpolate_;
    float time_; // current time in sample frames
    float rate_; // speed wrt fileRate_
    float lastOutput_;
    float gain_;

};

#endif

// vim:sw=4:et:cindent:
