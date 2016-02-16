
//
// MPI_AudioParticleSpace.h
//
// Description:
//   A particle space which plays a wavetable based on the movement of its
//   elements.
//

#ifndef __MPI_AUDIOPARTICLESPACE_H__
#define __MPI_AUDIOPARTICLESPACE_H__

#include "MPI_ParticleSpace.h"
#include "MPI_AudioWavetableSynth.h"

class MPI_Audio;
class MPI_AudioWavetable;
class MPI_CanonicalTimeArclengthMap;

class MPI_AudioParticleSpace : public MPI_ParticleSpace
{

  public:

    MPI_AudioParticleSpace( MPI_Audio &audioinstance, MPI_AudioWavetable &wavetable, MPI_CanonicalTimeArclengthMap const& canonicaltimearclengthmap );

    virtual void addElement( MPI_OneSpaceElement *element, float position );
    virtual void removeElement( MPI_OneSpaceElement const *element );

    void refreshPlayRate( void );

    MPI_AudioWavetable const& getWavetable( void ) const;

  private:

    float arclengthToWavetableSeconds( float arclengthpos ) const;
    float getPlayRate( float canonicalpos ) const;
    float canonicalToWavetableSamples( float canonicalpos ) const;

    MPI_AudioWavetableSynth wavetablesynth_;
    MPI_OneSpaceElement *playhead_;
    MPI_CanonicalTimeArclengthMap const& canonicaltimearclengthmap_;
    const float resamplingperiod_;

};

#endif

// vim:sw=4:et:cindent:
