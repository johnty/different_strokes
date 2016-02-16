
//
// MPI_AudioParticleFactory.cpp
//

#include "MPI_AudioParticleFactory.h"

#include "MPI_AudioPlayheadStroke.h"
#include "MPI_TextLines.h"

char const *MPI_AudioParticleFactory::samplelistfilename_ = "dssamples.txt";

MPI_PolyLine* MPI_AudioParticleFactory::AudioPlayheadStrokeState::createPolyLine( void ) const
{
    return new MPI_AudioPlayheadStroke( audioparticlefactory_.getWorkspace(), audioparticlefactory_.getScheduler(), audioparticlefactory_.getAudioInstance(), audioparticlefactory_.getWavetable() );
}

MPI_AudioParticleFactory::MPI_AudioParticleFactory( MPI_Audio &audioinstance, MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    MPI_ParticleFactory( workspace, scheduler ),
    audioinstance_( audioinstance ),
    audioplayheadstrokestate_( *this ),
    currentwavetable_( 0 )
{

    MPI_TextLines samplelist( samplelistfilename_ );

    if ( samplelist.openOk() ) {

        std::list<std::string> const& samplenames = samplelist.getFileLines();

        std::list<std::string>::const_iterator samplename;
        for (samplename = samplenames.begin(); samplename != samplenames.end(); ++samplename)
            wavetables_.push_back( new MPI_AudioWavetable( *samplename, false, true ) );

    }
    else {
        std::cerr << "Error opening sample list file " << samplelistfilename_ << std::endl;
    }

    // We need to make wavetables_ a list of pointers since I can't do
    // something like
    //    std::vector<MPI_AudioWavetable> wavetables_;
    //    stdwavetables_.push_back( MPI_AudioWavetable( "/Users/mark/mysample.wav", false, true ) );
    // since wvin's copy constructor doesn't seem to work.

}

MPI_Audio& MPI_AudioParticleFactory::getAudioInstance( void ) const
{
    return audioinstance_;
}

MPI_AudioWavetable& MPI_AudioParticleFactory::getWavetable( void )
{
    // NB: this method can't be const since we're returning a reference to a
    // member variable which could subsequently be changed.
    // one solution would be to return a const reference and then make it
    // const, but wavetable_ wouldn't be usable then since getValueAtTime()
    // needs to be non-const (because of how MPI_AudioWavetable is implemented)
    return *wavetables_[currentwavetable_];
}

void MPI_AudioParticleFactory::setStatePlayheadStroke( unsigned int strokenum )
{
    if ( strokenum < wavetables_.size() ) {
        currentwavetable_ = strokenum;
        setParticleFactoryState( &audioplayheadstrokestate_ );
    }
    else {
        std::cerr << "Audio playhead stroke " << strokenum << " not available" << std::endl;
    }
}

// vim:sw=4:et:cindent:
