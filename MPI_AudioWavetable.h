
//
// MPI_AudioWavetable.h
//
// Description:
//   A wavetable which holds sample data.  It's read by an associated
//   MPI_AudioWavetableSynth object.  It can be accessed by multiple readers at
//   once.
//   This is relatively hacky -- you shouldn't be able to tick a wavetable, but
//   you can tick this class.  We do it this way to avoid code duplication of
//   the file reading code and other stuff.  It'd be better to have a nicer
//   separation, though.
//

#ifndef __MPI_AUDIOWAVETABLE_H__
#define __MPI_AUDIOWAVETABLE_H__

#include "WvIn.h"

class MPI_AudioWavetable : public WvIn
{

  public:

    MPI_AudioWavetable( std::string fileName, bool raw = false, bool doNormalize = true );
    virtual ~MPI_AudioWavetable();

    float getValueAtTime( float time, bool interpolate );
    float const* getFrameAtTime( float time, bool interpolate );

    float getLength( void ) const;

  private:

    static char unsigned const maxChannels_;
    float *lastFrameQueried_;

};

#endif

// vim:sw=4:et:cindent:
