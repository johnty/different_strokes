
//
// MPI_AudioWavetableSynth.cpp
//

#include "MPI_AudioWavetableSynth.h"

#include "MPI_AudioWavetable.h"
#include <cmath>

MPI_AudioWavetableSynth::MPI_AudioWavetableSynth( MPI_Audio &audioinstance, MPI_AudioWavetable &wavetable ) :
    MPI_AudioSynth( audioinstance ),
    wavetable_( wavetable ),
    gain_( 0.0 )
{
    // FIXME application sampling rate hardcoded here!  Should come from
    // MPI_Audio...
    reset();
    setRate( wavetable_.getFileRate() / 44100.0 );
    addSynthToAudioInstance();
}

MPI_AudioWavetableSynth::~MPI_AudioWavetableSynth()
{
    removeSynthFromAudioInstance();
}

MPI_AudioWavetable& MPI_AudioWavetableSynth::getWavetable( void ) const
{
    return wavetable_;
}

void MPI_AudioWavetableSynth::reset( void )
{
    time_ = 0.0;
    finished_ = false;
    lastOutput_ = 0.0;
}

bool MPI_AudioWavetableSynth::isFinished( void ) const
{
    return finished_;
}

void MPI_AudioWavetableSynth::setRate( float rate )
{

    rate_ = rate;

    // If negative rate and at beginning of sound, move pointer to end
    // of sound.
    // FIXME how does this work?  getSize() returns the number of sample frames
    // in the file.
    if ( (rate_ < 0.0) && (time_ == 0.0) )
        time_ = rate_ + wavetable_.getSize();

    if ( fmod(rate_, 1.0) != 0.0 )
        interpolate_ = true;
    else
        interpolate_ = false;

}

void MPI_AudioWavetableSynth::addTime( float time )
{

    // Add an absolute time in samples
    time_ += time;

    if ( time_ < 0.0 )
        time_ = 0.0;

    if ( time_ >= wavetable_.getSize() ) {
        time_ = wavetable_.getSize();
        finished_ = true;
    }

}

void MPI_AudioWavetableSynth::setInterpolate( bool doInterpolate )
{
    interpolate_ = doInterpolate;
}

float MPI_AudioWavetableSynth::tick( void )
{

    if ( finished_ ) return lastOutput_;

    float lastOutput_ = gain_ * wavetable_.getValueAtTime( time_, interpolate_ );

    // Increment time, which can be negative.
    // adapted from WvIn::tickFrame()
    time_ += rate_;
    if ( time_ < 0.0 || time_ >= wavetable_.getSize() )
        finished_ = true;

    return lastOutput_;

}

void MPI_AudioWavetableSynth::setGain( float value )
{
    gain_ = value;
}

// vim:sw=4:et:cindent:
