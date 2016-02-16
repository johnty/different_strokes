
//
// MPI_AudioSynth.cpp
//

#include "MPI_AudioSynth.h"

#include "MPI_Audio.h"

MPI_AudioSynth::MPI_AudioSynth( MPI_Audio &audioinstance ) :
    audioinstance_( audioinstance ),
    active_( false )
{
    // empty
}

MPI_AudioSynth::~MPI_AudioSynth()
{
    // empty
}

void MPI_AudioSynth::addSynthToAudioInstance( void )
{
    // This needs to be called at the END of the constructor in a derived
    // class.  The derived classes data members should all be in a callable
    // state before addSynthToAudioInstance() is called.
    audioinstance_.addSynth( this );
}

void MPI_AudioSynth::removeSynthFromAudioInstance( void )
{
    // This needs to be called at the BEGINNING of the destructor in a derived
    // class.  The derived classes data members should all be in a callable
    // state until addSynthToAudioInstance() has returned.
    audioinstance_.removeSynth( this );
}

void MPI_AudioSynth::setActiveFlag( bool value )
{
    active_ = value;
}

bool MPI_AudioSynth::isActive( void ) const
{
    return active_;
}

// vim:sw=4:et:cindent:
