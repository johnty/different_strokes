
//
// MPI_AudioPlayheadStroke.cpp
//

#include "MPI_AudioPlayheadStroke.h"

#include "MPI_AudioWavetable.h"

MPI_AudioPlayheadStroke::MPI_AudioPlayheadStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler, MPI_Audio &audio, MPI_AudioWavetable &wavetable ) :
    MPI_PlayheadStroke( workspace, scheduler ),
    audioparticlespace_( audio, wavetable, getCanonicalTimeArclengthMap() )
{
    // empty
}


void MPI_AudioPlayheadStroke::updateState( void )
{
    MPI_PlayheadStroke::updateState();
    audioparticlespace_.refreshPlayRate();
}

MPI_OneSpace& MPI_AudioPlayheadStroke::getOneSpace( void )
{
    return audioparticlespace_;
}

MPI_OneSpace const& MPI_AudioPlayheadStroke::getOneSpace( void ) const
{
    return audioparticlespace_;
}

float MPI_AudioPlayheadStroke::getLength( void ) const
{
    return audioparticlespace_.getWavetable().getLength();
}

// vim:sw=4:et:cindent:
