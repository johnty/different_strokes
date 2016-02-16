
//
// MPI_AudioParticleFactory.h
//
// Description:
//   audio version of MPI_ParticleFactory
//

#ifndef __MPI_AUDIOPARTICLEFACTORY_H__
#define __MPI_AUDIOPARTICLEFACTORY_H__

#include "MPI_ParticleFactory.h"
#include "MPI_AudioWavetable.h"
#include <vector>

class MPI_Audio;

class MPI_AudioParticleFactory : public MPI_ParticleFactory
{

  private:

    class AudioPlayheadStrokeState : public MPI_ParticleFactory::ParticleFactoryState
    {
      public:
        AudioPlayheadStrokeState( MPI_AudioParticleFactory &factory ) : audioparticlefactory_(factory) {}
        MPI_PolyLine* createPolyLine( void ) const;
      private:
        // NB: this reference needs to be non-const since getWavetable() is
        // non-const and we need to call it.
        MPI_AudioParticleFactory &audioparticlefactory_;
    };

  public:

    MPI_AudioParticleFactory( MPI_Audio &audioinstance, MPI_Workspace &workspace, MPI_Scheduler &scheduler );

    MPI_Audio& getAudioInstance( void ) const;
    MPI_AudioWavetable& getWavetable( void );

    virtual void setStatePlayheadStroke( unsigned int strokenum );

  private:

    MPI_Audio &audioinstance_;

    // state instances
    AudioPlayheadStrokeState audioplayheadstrokestate_;

    // wavetables
    std::vector<MPI_AudioWavetable*> wavetables_;
    // currently selected wavetable
    int currentwavetable_;

    static char const *samplelistfilename_;

};

#endif

// vim:sw=4:et:cindent:
